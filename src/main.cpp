#include <Arduino.h>
#include <memory>
#include "Constants.hpp"
#include "OBDHandler.hpp"
#include "WifiHandler.hpp"
#include "BtHandler.hpp"
#include "DisplayHandler.hpp"
#include "ButtonHandler.hpp"
#include "Configurator.hpp"
#include "NVSHandler.hpp"

std::shared_ptr<OBDHandler> obdHandler = std::make_shared<OBDHandler>();
std::shared_ptr<ButtonHandler> buttonHandler = std::make_shared<ButtonHandler>();

WifiHandler wifiHandler(obdHandler);
BtHandler btHandler(obdHandler);
DisplayHandler displayHandler(obdHandler, buttonHandler);
NVSHandler nvsHandler(obdHandler);

void handleCycleDiff(long cycleStart)
{
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

void setup()
{
  Serial.begin(115200);
  Serial.println("Starting OBD2-Emulator.");

  buttonHandler->initialize();
  btHandler.initialize();
  wifiHandler.initialize();
  displayHandler.initialize();
  nvsHandler.initialize();
}

void loop()
{
  long cycleStart = millis();

  obdHandler->cyclic();
  buttonHandler->cyclic();
  displayHandler.cyclic();
  wifiHandler.cyclic();
  btHandler.cyclic();

  handleCycleDiff(cycleStart);
  Configurator::endCycle();
}
