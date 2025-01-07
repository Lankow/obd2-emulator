/**
 * @file BluetoothHandler.hpp
 * @date   2025-01-04
 * @author Lankow
 * @version 1.0
 */
#ifndef BlUETOOTH_HANDLER_HPP
#define BlUETOOTH_HANDLER_HPP

#include <Arduino.h>
#include <NimBLEDevice.h>

class BluetoothHandler
{
    public:
        void initialize();

    private:
        NimBLEServer *m_server = nullptr;
};
#endif // BlUETOOTH_HANDLER_HPP