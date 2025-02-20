/**
 * @file Configurator.cpp
 * @date 2025-02-20
 * @author Lankow
 * @version 1.0
 */
#include "Configurator.hpp"

bool Configurator::m_additionalDebug = false;
uint64_t Configurator::m_cycleCount = 0;

const bool Configurator::isAdditionalDebugEnabled() { return m_additionalDebug; };
const uint64_t Configurator::getCycleCount() { return m_cycleCount; };
const void Configurator::endCycle()
{
    m_cycleCount++;
};
