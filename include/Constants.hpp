/**
 * @file Constants.hpp
 * @date 2025-01-25
 * @author Lankow
 * @version 1.0
 */

#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP
#include <Arduino.h>

namespace Config
{
    constexpr uint32_t CYCLE_TIME_MS = 100;    /**< Cycle time in milliseconds. */
    const std::string SSID = "OBDII-config";   /**< SSID for OBDII Emulator configuration page. */
    const std::string PASSWORD = "obd2config"; /**< Password for OBDII Emulator configuration page. */
}

namespace BootButton
{
    constexpr uint16_t PIN = 0;                    /**< Pin number for the boot button. */
    constexpr uint16_t THRESHOLD_LONG_MS = 1500;   /**< Threshold time in milliseconds for the long click. */
    constexpr uint16_t THRESHOLD_DOUBLE_MS = 500; /**< Time window for double click detection */
    constexpr uint16_t DEFAULT_TIME = 0;           /**< Default Pressed Button Time ms */

    enum State
    {
        Released,
        Pressed,
        ShortClick,
        DoubleClick,
        LongPressed
    };
}

#endif // CONSTANTS_HPP