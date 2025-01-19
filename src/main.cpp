#include <Arduino.h>
#include <memory>
#include "OBD2PIDManager.hpp"
#include "WifiHandler.hpp"
#include "BluetoothHandler.hpp"
#include "DisplayHandler.hpp"

std::shared_ptr<OBD2PIDManager> manager  = std::make_shared<OBD2PIDManager>();
WifiHandler wifiHandler(manager);
BluetoothHandler bluetoothHandler(manager);
DisplayHandler displayHandler(manager);

void setup() {
  Serial.begin(115200);
  Serial.println("Starting OBD2-Emulator.");
  
  bluetoothHandler.initialize();
  wifiHandler.initialize();
  displayHandler.initialize();
}

void loop() {
    wifiHandler.handle();
    manager->updateAll();
    manager->printAll();
    bluetoothHandler.write();
    delay(100);
}
