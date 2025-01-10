#include <Arduino.h>
#include <memory>
#include "BluetoothHandler.hpp"
#include "WifiHandler.hpp"
#include "DataProvider.hpp"
#include "EmulatedData.hpp"

std::shared_ptr<DataProvider> dataProvider  = std::make_shared<DataProvider>();
BluetoothHandler bluetoothHandler;
WifiHandler wifiHandler(dataProvider);
EmulatedData<int> vehicleSpeed(0, 0, 255, 10, 100);
EmulatedData<float> engineSpeed(0, 0, 16383.75 , 10, 100);


void setup() {
  Serial.begin(115200);
  Serial.println("Starting OBD2-Emulator.");
  bluetoothHandler.initialize();
  wifiHandler.initialize();
}

void loop() {
    wifiHandler.handle();
    
    vehicleSpeed.update();
    engineSpeed.update();

    Serial.println("Vehicle Speed:");
    Serial.println(vehicleSpeed.getCurrent());

    Serial.println("Engine Speed:");
    Serial.println(engineSpeed.getCurrent());
    delay(100);
}