/**
 * @file ButtonHandler.cpp
 * @date   2025-01-24
 * @author Lankow
 * @version 1.0
 */
#include "ButtonHandler.hpp"

ButtonHandler::ButtonHandler()
    : m_button(BootButton::PIN),
      m_state(BootButton::State::Released),
      m_lastPressTimeMs(BootButton::DEFAULT_TIME),
      m_pressedCounterMs(BootButton::DEFAULT_TIME) {}

void ButtonHandler::initialize()
{
    m_button.begin();
}

void ButtonHandler::reset()
{
    Serial.println("Button Reset.");
    m_state = BootButton::State::Released;
    m_pressedCounterMs = BootButton::DEFAULT_TIME;
    m_lastPressTimeMs = BootButton::DEFAULT_TIME;
}

BootButton::State ButtonHandler::getState() { return m_state; };

void ButtonHandler::cyclic()
{
    uint16_t currentTime = millis();

    if (m_button.pressed())
    {
        Serial.println("Button Pressed...");
        m_state = BootButton::State::Pressed;

        if (currentTime - m_lastPressTimeMs <= BootButton::THRESHOLD_DOUBLE_MS)
        {
            Serial.println("Double Click detected!");
            m_state = BootButton::State::DoubleClick;
        }

        m_lastPressTimeMs = currentTime;
    }

    if (m_button.released())
    {
        Serial.println("Button released...");
        m_state = BootButton::State::Released;
        m_pressedCounterMs = BootButton::DEFAULT_TIME;
    }

    if (m_state == BootButton::State::Pressed)
    {
        m_pressedCounterMs += Config::CYCLE_TIME_MS;
        Serial.println(m_pressedCounterMs);

        if (m_pressedCounterMs >= BootButton::THRESHOLD_LONG_MS)
        {
            Serial.println("Long Click detected!");
            m_state = BootButton::State::LongPressed;
        }
    }

    if (m_state == BootButton::State::Released)
    {
        if (m_lastPressTimeMs != BootButton::DEFAULT_TIME &&
            currentTime - m_lastPressTimeMs > BootButton::THRESHOLD_DOUBLE_MS)
        {
            Serial.println("Short Click detected!");
            m_state = BootButton::State::ShortClick;
            m_lastPressTimeMs = BootButton::DEFAULT_TIME;
        }
    }
}
