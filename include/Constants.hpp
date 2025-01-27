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
    constexpr uint16_t THRESHOLD_LONG_MS = 3000;   /**< Threshold time in milliseconds for the long click. */
    constexpr uint16_t THRESHOLD_DOUBLE_MS = 1000; /**< Time window for double click detection */
}

#endif // CONSTANTS_HPP