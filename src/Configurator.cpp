/**
 * @file Configurator.cpp
 * @date 2025-02-20
 * @author Lankow
 * @version 1.0
 */
#include "Configurator.hpp"

bool Configurator::m_additionalDebug = false;

const bool Configurator::isAdditionalDebugEnabled() { return m_additionalDebug; };
void Configurator::toggleAdditionalLogging()
{
    m_additionalDebug = !m_additionalDebug;
}