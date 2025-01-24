/**
 * @file ButtonHandler.cpp
 * @date   2025-01-24
 * @author Lankow
 * @version 1.0
 */
#include "ButtonHandler.hpp"

#define BOOT_BUTTON_PIN 0

ButtonHandler::ButtonHandler() : m_button(BOOT_BUTTON_PIN), m_state(0){}

void ButtonHandler::initialize()
{
    m_button.begin();
}

void ButtonHandler::cyclic()
{
    if (m_button.pressed())
    {
        Serial.println("Button Pressed.");
    }
}
