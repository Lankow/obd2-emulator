#include <Arduino.h>
#include <memory>
#include "OBDHandler.hpp"
#include "WebServerHandler.hpp"
#include "BtHandler.hpp"
#include "DisplayHandler.hpp"
#include "ButtonHandler.hpp"
#include "FileSystemManager.hpp"
#include "CycleHandler.hpp"
#include "AccessPointInitializer.hpp"
#include "Configuration.hpp"

std::shared_ptr<Configuration> configuration = std::make_shared<Configuration>();
std::shared_ptr<CycleHandler> cycleHandler = std::make_shared<CycleHandler>(configuration);
std::shared_ptr<OBDHandler> obdHandler = std::make_shared<OBDHandler>(cycleHandler, configuration);
std::shared_ptr<FileSystemManager> nvsHandler = std::make_shared<FileSystemManager>(obdHandler);

AccessPointInitializer apInitializer(configuration);
WebServerHandler webServerHandler(obdHandler, nvsHandler, configuration);
BtHandler btHandler(obdHandler);
DisplayHandler displayHandler(obdHandler, configuration);

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

