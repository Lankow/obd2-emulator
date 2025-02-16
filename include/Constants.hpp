/**
 * @file Constants.hpp
 * @date 2025-01-25
 * @author Lankow
 * @version 1.0
 */

#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP
#include <Arduino.h>

#define NO_CUSTOM_GETTER nullptr

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

namespace BootButton
{
    constexpr uint16_t PIN = 0;                   /**< Pin number for the boot button. */
    constexpr uint16_t THRESHOLD_LONG_MS = 1500;  /**< Threshold time in milliseconds for the long click. */
    constexpr uint16_t THRESHOLD_DOUBLE_MS = 500; /**< Time window for double click detection */
    constexpr uint16_t DEFAULT_TIME = 0;          /**< Default Pressed Button Time ms */

    enum State
    {
        Released,
        Pressed,
        ShortClick,
        DoubleClick,
        LongPressed
    };
}

namespace OBDRequest
{
    constexpr uint16_t DEFAULT_VALUE = 0xFFFF; /**< Default value if requested PID is invalid */
}

#endif // CONSTANTS_HPP