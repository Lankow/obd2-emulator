#include <Arduino.h>
#include <memory>
#include "Constants.hpp"
#include "OBD2PIDManager.hpp"
#include "WifiHandler.hpp"
#include "BtHandler.hpp"
#include "DisplayHandler.hpp"
#include "ButtonHandler.hpp"

std::shared_ptr<OBD2PIDManager> manager = std::make_shared<OBD2PIDManager>();
std::shared_ptr<ButtonHandler> buttonHandler = std::make_shared<ButtonHandler>();

WifiHandler wifiHandler(manager);
BtHandler btHandler(manager);
DisplayHandler displayHandler(manager, buttonHandler);

void setup()
{
  Serial.begin(115200);
  Serial.println("Starting OBD2-Emulator.");

  buttonHandler->initialize();
  btHandler.initialize();
  wifiHandler.initialize();
  displayHandler.initialize();
}

void loop()
{
  long cycleStart = millis();

  buttonHandler->cyclic();
  btHandler.cyclic();
  wifiHandler.handle();
  manager->updateAll();
#ifdef DEBUG_DATA
  manager->printAll();
#endif
  displayHandler.cyclic();

  long cycleDiff = millis() - cycleStart;
  long cycleDelay = Config::CYCLE_TIME_MS - cycleDiff;

  if (cycleDiff > Config::CYCLE_TIME_MS)
  {
    Serial.println("Cycle time exceeded. Diff Time: ");
    Serial.println(cycleDiff);
  }
  else
  {
    delay(cycleDelay);
  }
}
