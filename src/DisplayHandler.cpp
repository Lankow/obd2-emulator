/**
 * @file DisplayHandler.cpp
 * @date   2025-01-07
 * @author Lankow
 * @version 1.0
 */
#include <Wire.h>
#include <iomanip>
#include <sstream>
#include "DisplayHandler.hpp"
#include "Constants.hpp"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

DisplayHandler::DisplayHandler(std::shared_ptr<OBDHandler> obdHandler, std::shared_ptr<ButtonHandler> buttonHandler)
    : m_obdHandler(obdHandler),
      m_buttonHandler(buttonHandler),
      m_display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1),
      m_displayCounter(Display::DISPLAY_COUNTER_DEFAULT),
      m_isDisplayInfo(false) {};

void DisplayHandler::cyclic()
{
  BootButton::State state = m_buttonHandler->getState();

  switch (state)
  {
  case BootButton::State::ShortClick:
    m_displayCounter++;
    m_isDisplayInfo = true;
    m_buttonHandler->reset();
    break;
  case BootButton::State::DoubleClick:
    m_displayCounter--;
    m_isDisplayInfo = true;
    m_buttonHandler->reset();
    break;
  case BootButton::State::LongPressed:
    m_buttonHandler->reset();
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
  Wire.begin(21, 22); // SDA = GPIO21, SCL = GPIO22
  Serial.println("Initializing OLED...");

  if (!m_display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
  {
    Serial.println("Failed to initialize SSD1306!");
    while (true)
      ;
  }

  displayMainScreen();
}

void DisplayHandler::update(const std::string &message)
{
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
         << info->getDescription() << std::endl
         << "PID: 0x" << std::uppercase << std::hex << static_cast<int>(info->getPid()) << std::endl
         << "Current: " << info->getCurrent() << std::endl
         << "Max: " << info->getMax() << std::endl
         << "Min: " << info->getMin() << std::endl
         << "Increment: " << info->getIncrement() << std::endl
         << "Pace: " << std::to_string(info->getPace()) << std::endl;

  update(stream.str());
}

void DisplayHandler::displayWifiInfo()
{
  std::ostringstream stream;
  stream << "OBD2-Emulator" << std::endl
         << "Use to configure: " << std::endl
         << "SSID: " << Config::SSID.c_str() << std::endl
         << "Password: " << Config::PASSWORD.c_str() << std::endl
         << "IP: " << Config::IP.toString().c_str() << std::endl;

  update(stream.str());
}