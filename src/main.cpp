#include <Arduino.h>
#include <memory>
#include "OBD2PIDManager.hpp"
#include "WifiHandler.hpp"
#include "BtHandler.hpp"
#include "DisplayHandler.hpp"
#include "ButtonHandler.hpp"

std::shared_ptr<OBD2PIDManager> manager  = std::make_shared<OBD2PIDManager>();
WifiHandler wifiHandler(manager);
BtHandler btHandler(manager);
DisplayHandler displayHandler(manager);
ButtonHandler buttonHandler;

void setup() {
  Serial.begin(115200);
  Serial.println("Starting OBD2-Emulator.");
  
  buttonHandler.initialize();
  btHandler.initialize();
  wifiHandler.initialize();
  displayHandler.initialize();
}

void loop() {
    buttonHandler.cyclic();
    btHandler.cyclic();
    wifiHandler.handle();
    manager->updateAll();
    // manager->printAll();
    delay(100);
}
