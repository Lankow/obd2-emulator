#include <Arduino.h>
#include <memory>
#include "BluetoothHandler.hpp"
#include "WifiHandler.hpp"
#include "DataProvider.hpp"
#include "EmulatedData.hpp"

std::shared_ptr<DataProvider> dataProvider  = std::make_shared<DataProvider>();
BluetoothHandler bluetoothHandler;
WifiHandler wifiHandler(dataProvider);
EmulatedData<int> data(0, 0, 100, 10, 100);

void setup() {
  Serial.begin(115200);
  Serial.println("Starting OBD2-Emulator.");
  bluetoothHandler.initialize();
  wifiHandler.initialize();
}

void loop() {
    wifiHandler.handle();
    data.update();
    Serial.println(data.getCurrent());
    delay(100);
}