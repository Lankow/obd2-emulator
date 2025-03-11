/**
 * @file CycleHandler.cpp
 * @date   2025-03-06
 * @author Lankow
 * @version 1.0
 */
#include "CycleHandler.hpp"
#include "Configuration.hpp"

CycleHandler::CycleHandler(std::shared_ptr<Configuration> configuration) : m_configuration(configuration),
                                                                           m_cycleCount(0),
                                                                           m_cycleStart(0) {};

void CycleHandler::startCycle()
{
    m_cycleStart = millis();
}

void CycleHandler::endCycle()
{
    long cycleDiff = millis() - m_cycleStart;
    uint32_t cycleTime = m_configuration->getCycleTime();

    if (cycleDiff > cycleTime)
    {
        Serial.println("Cycle time exceeded. Diff Time: ");
        Serial.println(cycleDiff);
        uint32_t cycles = cycleDiff / cycleTime;

        m_cycleCount += cycleDiff % cycleTime == 0 ? cycles : cycles + 1;
        cycleDiff = cycleDiff % cycleTime;
    }
    else
    {
        m_cycleCount++;
    }

    long cycleDelay = cycleTime - cycleDiff;
    delay(cycleDelay);
}

const uint32_t CycleHandler::getCycleCount() const { return m_cycleCount; };
