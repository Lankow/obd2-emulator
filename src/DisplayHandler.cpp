/**
 * @file DisplayHandler.cpp
 * @date   2025-01-07
 * @author Lankow
 * @version 1.0
 */
#include <Wire.h>
#include "DisplayHandler.hpp"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

DisplayHandler::DisplayHandler(std::shared_ptr<OBD2PIDManager> manager, std::shared_ptr<ButtonHandler> buttonHandler)
    : m_manager(manager),
      m_buttonHandler(buttonHandler),
      m_display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1) {}

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

  m_display.clearDisplay();
  m_display.setTextSize(1);
  m_display.setTextColor(SSD1306_WHITE);
  m_display.setCursor(0, 0);
  m_display.println("OBD2-Emulator");
  m_display.display();
}