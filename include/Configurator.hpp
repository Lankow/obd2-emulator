/**
 * @file Configurator.hpp
 * @date 2025-02-20
 * @author Lankow
 * @version 1.0
 */

#ifndef CONFIGURATOR_HPP
#define CONFIGURATOR_HPP
#include <Arduino.h>

// TODO: Add to NVS Handler
// TODO: Object not static
class Configurator
{
public:
    static const bool isAdditionalDebugEnabled();
    static const uint32_t getCycleCount();  // TODO: Move outside config
    static const void endCycle();
    static void toggleAdditionalLogging();

private:
    static bool m_additionalDebug;
    static uint32_t m_cycleCount;
};
#endif // CONFIGURATOR_HPP