#include <Arduino.h>
#include <memory>
#include "Constants.hpp"
#include "OBDHandler.hpp"
#include "WifiHandler.hpp"
#include "BtHandler.hpp"
#include "DisplayHandler.hpp"
#include "ButtonHandler.hpp"

std::shared_ptr<OBDHandler> obdHandler = std::make_shared<OBDHandler>();
std::shared_ptr<ButtonHandler> buttonHandler = std::make_shared<ButtonHandler>();

WifiHandler wifiHandler(obdHandler);
BtHandler btHandler(obdHandler);
DisplayHandler displayHandler(obdHandler, buttonHandler);

uint64_t cycleCount = 0;

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
  cycleCount++;
  long cycleStart = millis();

  buttonHandler->cyclic();
  btHandler.cyclic();
  wifiHandler.handle();
  obdHandler->updateAll(cycleCount);
#ifdef DEBUG_DATA
  obdHandler->printAll();
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
