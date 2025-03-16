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

std::shared_ptr<Configuration> configuration;
std::shared_ptr<CycleHandler> cycleHandler;
std::shared_ptr<OBDHandler> obdHandler;
std::shared_ptr<AccessPointInitializer> apInitializer;
std::shared_ptr<WebServerHandler> webServerHandler;
std::shared_ptr<BtHandler> btHandler;
std::shared_ptr<DisplayHandler> displayHandler;

void setup()
{
  Serial.begin(115200);
  Serial.println("Starting OBD2-Emulator.");

  configuration = std::make_shared<Configuration>();
  cycleHandler = std::make_shared<CycleHandler>(configuration);
  obdHandler = std::make_shared<OBDHandler>(cycleHandler, configuration);
  apInitializer = std::make_shared<AccessPointInitializer>(configuration);
  webServerHandler = std::make_shared<WebServerHandler>(obdHandler, configuration);
  btHandler = std::make_shared<BtHandler>(obdHandler);
  displayHandler = std::make_shared<DisplayHandler>(obdHandler, configuration);

  btHandler->initialize();
  apInitializer->initialize();
  webServerHandler->initialize();
  displayHandler->initialize();
}

void loop()
{
  cycleHandler->startCycle();
  obdHandler->cyclic();
  displayHandler->cyclic();
  webServerHandler->cyclic();
  btHandler->cyclic();
  cycleHandler->endCycle();
}
