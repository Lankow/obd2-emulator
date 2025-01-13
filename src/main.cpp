#include <Arduino.h>
#include <memory>
#include "DataStorage.hpp"
#include "WifiHandler.hpp"
#include "BluetoothHandler.hpp"

DataStorage dataStorage;
WifiHandler wifiHandler;
BluetoothHandler bluetoothHandler;

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