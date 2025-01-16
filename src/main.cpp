#include <Arduino.h>
#include <memory>
#include "OBD2PIDManager.hpp"
#include "WifiHandler.hpp"
#include "BluetoothHandler.hpp"
#include "DisplayHandler.hpp"

OBD2PIDManager manager;
WifiHandler wifiHandler;
BluetoothHandler bluetoothHandler;
DisplayHandler displayHandler;

void setup() {
  Serial.begin(115200);
  Serial.println("Starting OBD2-Emulator.");
  
  bluetoothHandler.initialize();
  wifiHandler.initialize();
  displayHandler.initialize();
}

void loop() {
    wifiHandler.handle();
    manager.updateAll();
    manager.printAll();
    delay(100);
}