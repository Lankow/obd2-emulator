/**
 * @file CycleHandler.cpp
 * @date   2025-03-06
 * @author Lankow
 * @version 1.0
 */
#include "CycleHandler.hpp"
#include "Constants.hpp"

CycleHandler::CycleHandler() : m_cycleCount(0), m_cycleStart(0) {};

void CycleHandler::startCycle()
{
    m_cycleStart = millis();
}

void CycleHandler::endCycle()
{
    long cycleDiff = millis() - m_cycleStart;
    long cycleDelay = Config::CYCLE_TIME_MS - cycleDiff;

    // TODO: Handle case where the cycle time is exceeded.
    if (cycleDiff > Config::CYCLE_TIME_MS)
    {
        Serial.println("Cycle time exceeded. Diff Time: ");
        Serial.println(cycleDiff);
    }
    else
    {
        delay(cycleDelay);
    }

    m_cycleCount++;
}

const uint32_t CycleHandler::getCycleCount() const { return m_cycleCount; };
