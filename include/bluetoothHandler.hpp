/**
 * @file BluetoothHandler.hpp
 * @date   2025-01-04
 * @author Lankow
 * @version 1.0
 */
#ifndef BlUETOOTH_HANDLER_HPP
#define BlUETOOTH_HANDLER_HPP

#include <Arduino.h>
#include "BluetoothSerial.h"

class BluetoothHandler
{
    public:
        void initialize();

    private:
        BluetoothSerial m_serialBt;
};
#endif // BlUETOOTH_HANDLER_HPP