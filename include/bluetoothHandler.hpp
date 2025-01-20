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
        void cyclic();
        
    private:
        std::shared_ptr<OBD2PIDManager> m_manager;
            NimBLEServer *m_server = nullptr;

        // Callbacks
        class ServerCallbacks : public NimBLEServerCallbacks {
            void onConnect(NimBLEServer* pServer, NimBLEConnInfo& connInfo) override;
            void onDisconnect(NimBLEServer* pServer, NimBLEConnInfo& connInfo, int reason) override;
        };

        class CharacteristicCallbacks : public NimBLECharacteristicCallbacks {
            void onRead(NimBLECharacteristic* pCharacteristic, NimBLEConnInfo& connInfo) override;
            void onWrite(NimBLECharacteristic* pCharacteristic, NimBLEConnInfo& connInfo) override;
        };

        class DescriptorCallbacks : public NimBLEDescriptorCallbacks {
            void onWrite(NimBLEDescriptor* pDescriptor, NimBLEConnInfo& connInfo) override;
            void onRead(NimBLEDescriptor* pDescriptor, NimBLEConnInfo& connInfo) override;
        };
};  
#endif // BlUETOOTH_HANDLER_HPP