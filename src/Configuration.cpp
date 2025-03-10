/**
 * @file Configuration.cpp
 * @date 2025-02-20
 * @author Lankow
 * @version 1.0
 */
#include "Configuration.hpp"


const bool Configuration::isAdditionalDebugEnabled() { return m_additionalDebug; };
void Configuration::toggleAdditionalLogging()
{
    m_additionalDebug = !m_additionalDebug;
}