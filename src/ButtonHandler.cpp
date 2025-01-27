/**
 * @file ButtonHandler.cpp
 * @date   2025-01-24
 * @author Lankow
 * @version 1.0
 */
#include "ButtonHandler.hpp"

ButtonHandler::ButtonHandler() : m_button(BootButton::PIN) {}

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
