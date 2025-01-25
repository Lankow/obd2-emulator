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
#include "Constants.hpp"

class ButtonHandler
{
    public:
        ButtonHandler();

        void initialize();
        void cyclic();
        
    private:
        Button m_button;
        BootButton::State m_state;
};  
#endif // BUTTON_HANDLER_HPP