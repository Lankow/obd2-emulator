/**
 * @file Constants.hpp
 * @date 2025-01-25
 * @author Lankow
 * @version 1.0
 */

#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP
#include <Arduino.h>

namespace BootButton
{
    constexpr uint16_t PIN = 0;                     /**< Pin number for the boot button. */
    constexpr uint16_t THRESHOLD_LONG_MS = 3000;    /**< Threshold time in milliseconds for the long click. */
    constexpr uint16_t THRESHOLD_DOUBLE_MS = 1000;  /**< Time window for double click detection */

    enum State
    {
        NotPressed,
        Click,
        DoubleClick,
        LongClick,
        LongClickHold
    };
}

#endif // CONSTANTS_HPP