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
#include "CycleHandler.hpp"

std::shared_ptr<CycleHandler> cycleHandler = std::make_shared<CycleHandler>();
std::shared_ptr<OBDHandler> obdHandler = std::make_shared<OBDHandler>(cycleHandler);
std::shared_ptr<ButtonHandler> buttonHandler = std::make_shared<ButtonHandler>(); // TODO: Move to DisplayHandler
std::shared_ptr<NVSHandler> nvsHandler = std::make_shared<NVSHandler>(obdHandler);

WifiHandler wifiHandler(obdHandler, nvsHandler);
BtHandler btHandler(obdHandler);
DisplayHandler displayHandler(obdHandler, buttonHandler);

void handleCycleDiff(long cycleStart)
{
}

void setup()
{
  Serial.begin(115200);
  Serial.println("Starting OBD2-Emulator.");

  nvsHandler->initialize();
  buttonHandler->initialize();
  btHandler.initialize();
  wifiHandler.initialize();
  displayHandler.initialize();
}

void loop()
{
  cycleHandler->startCycle();
  obdHandler->cyclic();
  buttonHandler->cyclic();
  displayHandler.cyclic();
  wifiHandler.cyclic();
  btHandler.cyclic();
  cycleHandler->endCycle();
}
