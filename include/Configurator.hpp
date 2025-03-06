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
    static void toggleAdditionalLogging();

private:
    static bool m_additionalDebug;
};
#endif // CONFIGURATOR_HPP