#include <Arduino.h>
#include <memory>
#include "BluetoothHandler.hpp"
#include "WifiHandler.hpp"
#include "DataProvider.hpp"

std::shared_ptr<DataProvider> dataProvider;
BluetoothHandler bluetoothHandler;
WifiHandler wifiHandler(dataProvider);

void setup() {
  Serial.begin(115200);
  Serial.println("Starting OBD2-Emulator.");
  bluetoothHandler.initialize();
  wifiHandler.initialize();
}

void loop() {
    wifiHandler.handle();
    delay(100);
}