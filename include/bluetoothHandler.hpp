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
#include <memory>
#include "OBD2PIDManager.hpp"

class BluetoothHandler
{
    public:
        BluetoothHandler(std::shared_ptr<OBD2PIDManager> manager);

        void initialize();
        void read();
        void write();
        
    private:
        std::shared_ptr<OBD2PIDManager> m_manager;
        NimBLEServer *m_server = nullptr;


};
#endif // BlUETOOTH_HANDLER_HPP