#include <Arduino.h>
#include <memory>
#include "Constants.hpp"
#include "OBDHandler.hpp"
#include "WebServerHandler.hpp"
#include "BtHandler.hpp"
#include "DisplayHandler.hpp"
#include "ButtonHandler.hpp"
#include "Configurator.hpp"
#include "NVSHandler.hpp"
#include "CycleHandler.hpp"
#include "AccessPointInitializer.hpp"

std::shared_ptr<CycleHandler> cycleHandler = std::make_shared<CycleHandler>();
std::shared_ptr<OBDHandler> obdHandler = std::make_shared<OBDHandler>(cycleHandler);
std::shared_ptr<NVSHandler> nvsHandler = std::make_shared<NVSHandler>(obdHandler);

AccessPointInitializer apInitializer;
WebServerHandler webServerHandler(obdHandler, nvsHandler);
BtHandler btHandler(obdHandler);
DisplayHandler displayHandler(obdHandler);

void setup()
{
  Serial.begin(115200);
  Serial.println("Starting OBD2-Emulator.");

  nvsHandler->initialize();
  btHandler.initialize();
  apInitializer.initialize();
  webServerHandler.initialize();
  displayHandler.initialize();
}

void loop()
{
  cycleHandler->startCycle();
  obdHandler->cyclic();
  displayHandler.cyclic();
  webServerHandler.cyclic();
  btHandler.cyclic();
  cycleHandler->endCycle();
}
