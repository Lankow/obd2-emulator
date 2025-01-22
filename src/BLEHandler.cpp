/**
 * @file BLEHandler.cpp
 * @date   2025-01-04
 * @author Lankow
 * @version 1.0
 */

#include "BLEHandler.hpp"
#include "OBD2PIDInfo.hpp"

BLEHandler::BLEHandler(std::shared_ptr<OBD2PIDManager> manager) : m_manager(manager) {}
BLEHandler::CharacteristicCallbacks::CharacteristicCallbacks(std::shared_ptr<OBD2PIDManager> manager) : m_manager(manager) {}

void BLEHandler::initialize() {
    NimBLEDevice::init("OBDII");

    m_server = NimBLEDevice::createServer();
    
    if (m_server) {
        Serial.println("Bluetooth Low Energy server created successfully");
    } else {
        Serial.println("Failed to create Bluetooth Low Energy server");
        return;
    }
    
    m_server->setCallbacks(new ServerCallbacks());

    auto pOBDCharacteristic = m_server->createService("OBD2")->createCharacteristic(
        "OBD2PID",
        NIMBLE_PROPERTY::READ | NIMBLE_PROPERTY::WRITE | NIMBLE_PROPERTY::NOTIFY
    );
    pOBDCharacteristic->setCallbacks(new CharacteristicCallbacks(m_manager));

    NimBLEAdvertising *advertising = NimBLEDevice::getAdvertising();
    advertising->addServiceUUID(NimBLEUUID((uint16_t)0x180D));
    advertising->enableScanResponse(true);
    advertising->start();

    Serial.println("Bluetooth Low Energy device started successfully");
    Serial.println("Device is now advertising as OBDII");
}

void BLEHandler::cyclic() {
    if (m_server && m_server->getConnectedCount() > 0) {
        auto pService = m_server->getServiceByUUID("OBD2");
        if (pService) {
            auto pCharacteristic = pService->getCharacteristic("OBD2PID");
            if (pCharacteristic) {
                std::string liveData = "00";
                pCharacteristic->setValue(liveData);
                pCharacteristic->notify();
                Serial.printf("Cyclic notification sent: %s\n", liveData.c_str());
            }
        }
    }
}

// ServerCallbacks Implementation
void BLEHandler::ServerCallbacks::onConnect(NimBLEServer* pServer, NimBLEConnInfo& connInfo) {
    Serial.printf("Client connected: %s\n", connInfo.getAddress().toString().c_str());
}

void BLEHandler::ServerCallbacks::onDisconnect(NimBLEServer* pServer, NimBLEConnInfo& connInfo, int reason) {
    Serial.printf("Client disconnected from address: %s\n", connInfo.getAddress().toString().c_str());
    Serial.printf("Disconnect reason: %d (%s)\n", reason, disconnectReasonToString(reason).c_str());

    Serial.println("Restarting advertising...");
    NimBLEDevice::startAdvertising();
}

void BLEHandler::CharacteristicCallbacks::onWrite(NimBLECharacteristic* pCharacteristic, NimBLEConnInfo& connInfo) {
    std::string value = pCharacteristic->getValue();
    Serial.printf("Received request: %s\n", value.c_str());

    std::string pidResponse = "XX";

    pCharacteristic->setValue(pidResponse);
    pCharacteristic->notify();

    Serial.printf("Response sent: %s\n", pidResponse.c_str());
}

std::string BLEHandler::ServerCallbacks::disconnectReasonToString(int reason) {
    switch (reason) {
        case 0x08:
            return "Timeout";
        case 0x13:
            return "Remote User Terminated Connection";
        case 0x16:
            return "Connection Terminated by Local Host";
        case 0x3E:
            return "Connection Failed to be Established";
        case 0x22:
            return "Connection Interval Unacceptable";
        default:
            return "Unknown Reason";
    }
}
