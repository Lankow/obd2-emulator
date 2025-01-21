/**
 * @file BLEHandler.hpp
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

class BLEHandler
{
    public:
        BLEHandler(std::shared_ptr<OBD2PIDManager> manager);

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
            public:
            CharacteristicCallbacks(std::shared_ptr<OBD2PIDManager> manager);

            private:
                void onWrite(NimBLECharacteristic* pCharacteristic, NimBLEConnInfo& connInfo) override;

                std::shared_ptr<OBD2PIDManager> m_manager;
        };
};  
#endif // BlUETOOTH_HANDLER_HPP