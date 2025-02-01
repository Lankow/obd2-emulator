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

DisplayHandler::DisplayHandler(std::shared_ptr<OBD2PIDManager> manager, std::shared_ptr<ButtonHandler> buttonHandler)
    : m_manager(manager),
      m_buttonHandler(buttonHandler),
      m_display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1),
      m_displayCounter(0) {};

void DisplayHandler::cyclic()
{
  BootButton::State state = m_buttonHandler->getState();

  switch (state)
  {
  case BootButton::State::ShortClick:
    m_displayCounter++;
    m_buttonHandler->reset();
    break;
  case BootButton::State::DoubleClick:
    m_displayCounter--;
    m_buttonHandler->reset();
    break;
  case BootButton::State::LongPressed:
    // Print Main Screen with setup info
    m_buttonHandler->reset();
  default:
    break;
  }

  displayObd2Info();
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

  update("OBD2-Emulator");
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

void DisplayHandler::displayObd2Info()
{
  const auto *entry = m_manager->getPIDInfoByIndex(m_displayCounter);
  if (!entry)
    return;

  uint8_t pid = entry->first;
  IOBD2PIDInfo *info = entry->second.get();

  std::ostringstream stream;
  stream << std::fixed << std::setprecision(2)
         << info->getDescription() << std::endl
         << "PID: 0x" << std::uppercase << std::hex << static_cast<int>(pid) << std::endl
         << "Current: " << info->getCurrentAsDouble() << std::endl
         << "Max: " << info->getMaxAsDouble() << std::endl
         << "Min: " << info->getMinAsDouble();

  update(stream.str());
}