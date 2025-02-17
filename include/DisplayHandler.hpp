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
#include "ObdManager.hpp"
#include "ButtonHandler.hpp"

class DisplayHandler
{
public:
    DisplayHandler(std::shared_ptr<ObdManager> manager, std::shared_ptr<ButtonHandler> buttonHandler);

    void initialize();
    void cyclic();

private:
    std::shared_ptr<ObdManager> m_manager;
    std::shared_ptr<ButtonHandler> m_buttonHandler;
    Adafruit_SSD1306 m_display;
    uint8_t m_displayCounter;
    bool m_isDisplayInfo;

    void update(const std::string &message);
    void displayMainScreen();
    void displayObdInfo();
    void displayWifiInfo();
};
#endif // DISPLAY_HANDLER_HPP