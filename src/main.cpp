#include <Arduino.h>
#include <memory>
#include "BluetoothHandler.hpp"
#include "WifiHandler.hpp"
#include "DataProvider.hpp"
#include "EmulatedData.hpp"
#include "DataStorage.hpp"

std::shared_ptr<DataProvider> dataProvider  = std::make_shared<DataProvider>();
BluetoothHandler bluetoothHandler;
WifiHandler wifiHandler(dataProvider);
DataStorage dataStorage;

void setup() {
  Serial.begin(115200);
  Serial.println("Starting OBD2-Emulator.");
  bluetoothHandler.initialize();
  wifiHandler.initialize();
}

void loop() {
    wifiHandler.handle();
    dataStorage.updateAll();
    dataStorage.printAll();
    delay(100);
}