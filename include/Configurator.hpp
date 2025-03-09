/**
 * @file Configurator.hpp
 * @date 2025-02-20
 * @author Lankow
 * @version 1.0
 */

#ifndef CONFIGURATOR_HPP
#define CONFIGURATOR_HPP
#include <Arduino.h>

namespace Config
{
    constexpr uint32_t CYCLE_TIME_MS = 100;    /**< Cycle time in milliseconds. */
    const std::string SSID = "OBDII-config";   /**< SSID for OBDII Emulator configuration page. */
    const std::string PASSWORD = "obd2config"; /**< Password for OBDII Emulator configuration page. */
    constexpr uint16_t SERVER_PORT = 80;       /**< Server port for access point. */

    const IPAddress IP(192, 168, 4, 2);
    const IPAddress GATEWAY(192, 168, 4, 2);
    const IPAddress SUBNET(255, 255, 255, 0);
}

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