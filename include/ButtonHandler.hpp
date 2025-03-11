/**
 * @file ButtonHandler.hpp
 * @date   2025-01-24
 * @author Lankow
 * @version 1.0
 */
#ifndef BUTTON_HANDLER_HPP
#define BUTTON_HANDLER_HPP

#include <Arduino.h>
#include <Button.h>
#include <memory>
#include "Configuration.hpp"

namespace BootButton
{
    constexpr uint16_t PIN = 0;                   /**< Pin number for the boot button. */
    constexpr uint16_t THRESHOLD_LONG_MS = 1500;  /**< Threshold time in milliseconds for the long click. */
    constexpr uint16_t THRESHOLD_DOUBLE_MS = 500; /**< Time window for double click detection */
    constexpr uint16_t DEFAULT_TIME = 0;          /**< Default Pressed Button Time ms */
}

enum BootButtonState
{
    Released,
    Pressed,
    ShortClick,
    DoubleClick,
    LongPressed
};

class ButtonHandler
{
public:
    ButtonHandler(std::shared_ptr<Configuration> configuration);

    void initialize();
    void cyclic();
    void reset();
    BootButtonState getState();

private:
    std::shared_ptr<Configuration> m_configuration;
    Button m_button;
    BootButtonState m_state;
    uint16_t m_lastPressTimeMs;
    uint16_t m_pressedCounterMs;
};
#endif // BUTTON_HANDLER_HPP