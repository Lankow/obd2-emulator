/**
 * @file DisplayHandler.cpp
 * @date   2025-01-07
 * @author Lankow
 * @version 1.0
 */
#include <Wire.h>
#include <iomanip>
#include <sstream>
#include "WiFi.h"
#include "DisplayHandler.hpp"

constexpr int SCREEN_WIDTH = 128;
constexpr int SCREEN_HEIGHT = 64;
constexpr int DISPLAY_COUNTER_DEFAULT = 0;

DisplayHandler::DisplayHandler(std::shared_ptr<OBDHandler> obdHandler, std::shared_ptr<Configuration> configuration)
    : m_obdHandler(obdHandler),
      m_configuration(configuration),
      m_buttonHandler(m_configuration),
      m_display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1),
      m_displayCounter(DISPLAY_COUNTER_DEFAULT),
      m_isDisplayInfo(false),
      m_isDisplayInitialized(false) {};

void DisplayHandler::cyclic()
{
  m_buttonHandler.cyclic();
  BootButtonState state = m_buttonHandler.getState();

  switch (state)
  {
  case BootButtonState::ShortClick:
    m_displayCounter++;
    m_isDisplayInfo = true;
    m_buttonHandler.reset();
    break;
  case BootButtonState::DoubleClick:
    m_displayCounter--;
    m_isDisplayInfo = true;
    m_buttonHandler.reset();
    break;
  case BootButtonState::LongPressed:
    m_buttonHandler.reset();
    m_isDisplayInfo = false;
    displayWifiInfo();
  default:
    break;
  }

  if (m_isDisplayInfo)
  {
    displayOBDInfo();
  }
}

void DisplayHandler::initialize()
{
  m_buttonHandler.initialize();

  Wire.begin(21, 22); // SDA = GPIO21, SCL = GPIO22
  Serial.println("Initializing OLED...");

  if (!m_display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
  {
    Serial.println("Failed to initialize SSD1306!");
    m_isDisplayInitialized = false;
  }

  m_isDisplayInitialized = true;
  displayMainScreen();
}

void DisplayHandler::update(const std::string &message)
{
  if (!m_isDisplayInitialized)
    return;

  m_display.clearDisplay();
  m_display.setTextSize(1);
  m_display.setTextColor(SSD1306_WHITE);
  m_display.setCursor(0, 0);
  m_display.println(message.c_str());
  m_display.display();
}

void DisplayHandler::displayMainScreen()
{
  std::ostringstream stream;
  stream << "OBD2-Emulator" << std::endl
         << "Button clicks: " << std::endl
         << "- single - next OBD" << std::endl
         << "- double - back OBD" << std::endl
         << "- long - Config info" << std::endl;

  update(stream.str());
}

void DisplayHandler::displayOBDInfo()
{
  const auto *info = m_obdHandler->getByIndex(m_displayCounter);
  if (!info)
    return;

  std::ostringstream stream;
  stream << std::fixed << std::setprecision(2)
         << info->m_description << std::endl
         << "PID: 0x" << std::uppercase << std::hex << static_cast<int>(info->m_pid) << std::endl
         << "Current: " << info->m_current << std::endl
         << "Max: " << info->m_max << std::endl
         << "Min: " << info->m_min << std::endl
         << "Increment: " << info->m_increment << std::endl
         << "Pace: " << std::to_string(info->m_pace) << std::endl;

  update(stream.str());
}

void DisplayHandler::displayWifiInfo()
{
  std::ostringstream stream;
  IPAddress apIp = WiFi.softAPIP();

  stream << "OBD2-Emulator" << std::endl
         << "Use to configure: " << std::endl
         << "SSID: " << m_configuration->getSSID().c_str() << std::endl
         << "Password: " << m_configuration->getPassword().c_str() << std::endl
         << "IP: " << apIp.toString().c_str() << std::endl;

  update(stream.str());
}