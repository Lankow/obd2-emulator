/**
 * @file DisplayHandler.hpp
 * @date   2025-01-07
 * @author Lankow
 * @version 1.0
 */
#ifndef DISPLAY_HANDLER_HPP
#define DISPLAY_HANDLER_HPP

#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
class DisplayHandler
{
    public:
        DisplayHandler();

        void initialize();
    private:
        Adafruit_SSD1306 m_display;
};
#endif // DISPLAY_HANDLER_HPP