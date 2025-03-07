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
#include <memory>
#include "OBDHandler.hpp"
#include "ButtonHandler.hpp"

class DisplayHandler
{
public:
    DisplayHandler(std::shared_ptr<OBDHandler> obdHandler);

    void initialize();
    void cyclic();

private:
    std::shared_ptr<OBDHandler> m_obdHandler;
    ButtonHandler m_buttonHandler;
    Adafruit_SSD1306 m_display;
    uint8_t m_displayCounter;
    bool m_isDisplayInfo;

    void update(const std::string &message);
    void displayMainScreen();
    void displayOBDInfo();
    void displayWifiInfo();
};
#endif // DISPLAY_HANDLER_HPP