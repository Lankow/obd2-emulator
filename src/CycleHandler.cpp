/**
 * @file CycleHandler.cpp
 * @date   2025-03-06
 * @author Lankow
 * @version 1.0
 */
#include "CycleHandler.hpp"
#include "Configuration.hpp"

CycleHandler::CycleHandler() : m_cycleCount(0), m_cycleStart(0) {};

void CycleHandler::startCycle()
{
    m_cycleStart = millis();
}

void CycleHandler::endCycle()
{
    long cycleDiff = millis() - m_cycleStart;

    if (cycleDiff > Config::CYCLE_TIME_MS)
    {
        Serial.println("Cycle time exceeded. Diff Time: ");
        Serial.println(cycleDiff);
        uint32_t cycles = cycleDiff / Config::CYCLE_TIME_MS;

        m_cycleCount += cycleDiff % Config::CYCLE_TIME_MS == 0 ? cycles : cycles + 1;
        cycleDiff = cycleDiff % Config::CYCLE_TIME_MS;
    }
    else
    {
        m_cycleCount++;
    }

    long cycleDelay = Config::CYCLE_TIME_MS - cycleDiff;
    delay(cycleDelay);
}

const uint32_t CycleHandler::getCycleCount() const { return m_cycleCount; };
