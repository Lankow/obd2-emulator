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
#include "OBD2PIDManager.hpp"
#include "ButtonHandler.hpp"

class DisplayHandler
{
public:
    DisplayHandler(std::shared_ptr<OBD2PIDManager> manager, std::shared_ptr<ButtonHandler> buttonHandler);

    void initialize();
    void cyclic();

private:
    std::shared_ptr<OBD2PIDManager> m_manager;
    std::shared_ptr<ButtonHandler> m_buttonHandler;
    Adafruit_SSD1306 m_display;
    uint8_t m_displayCounter;

    void update(const std::string& message);
    void displayObd2Info();
};
#endif // DISPLAY_HANDLER_HPP