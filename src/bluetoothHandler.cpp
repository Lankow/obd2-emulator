/**
 * @file BluetoothHandler.cpp
 * @date   2025-01-04
 * @author Lankow
 * @version 1.0
 */

#include "BluetoothHandler.hpp"
#include "OBD2PIDInfo.hpp"

BluetoothHandler::BluetoothHandler(std::shared_ptr<OBD2PIDManager> manager) : m_manager(manager){};

void BluetoothHandler::initialize()
{
    NimBLEDevice::init("OBDII");

    m_server = NimBLEDevice::createServer();
    
    if (m_server) {
        Serial.println("Bluetooth Low Energy server created successfully");
    } else {
        Serial.println("Failed to create Bluetooth Low Energy server");
        return;
    }
    
    m_server->setCallbacks(new ServerCallbacks());

    NimBLEAdvertising *advertising = NimBLEDevice::getAdvertising();
    advertising->addServiceUUID(NimBLEUUID((uint16_t)0x180D));
    advertising->start();

    Serial.println("Bluetooth Low Energy device started successfully");
    Serial.println("Device is now advertising as OBDII");
}

// ServerCallbacks Implementation
void BluetoothHandler::ServerCallbacks::onConnect(NimBLEServer* pServer, NimBLEConnInfo& connInfo) {
    Serial.printf("Client connected: %s\n", connInfo.getAddress().toString().c_str());
}

void BluetoothHandler::ServerCallbacks::onDisconnect(NimBLEServer* pServer, NimBLEConnInfo& connInfo, int reason) {
    Serial.println("Client disconnected, restarting advertising...");
    NimBLEDevice::startAdvertising();
}

// CharacteristicCallbacks Implementation
void BluetoothHandler::CharacteristicCallbacks::onRead(NimBLECharacteristic* pCharacteristic, NimBLEConnInfo& connInfo) {
    Serial.printf("Read characteristic %s: %s\n",
                  pCharacteristic->getUUID().toString().c_str(),
                  pCharacteristic->getValue().c_str());
}

void BluetoothHandler::CharacteristicCallbacks::onWrite(NimBLECharacteristic* pCharacteristic, NimBLEConnInfo& connInfo) {
    Serial.printf("Write characteristic %s: %s\n",
                  pCharacteristic->getUUID().toString().c_str(),
                  pCharacteristic->getValue().c_str());
}

// DescriptorCallbacks Implementation
void BluetoothHandler::DescriptorCallbacks::onWrite(NimBLEDescriptor* pDescriptor, NimBLEConnInfo& connInfo) {
    Serial.printf("Descriptor written: %s\n", pDescriptor->getValue().c_str());
}

void BluetoothHandler::DescriptorCallbacks::onRead(NimBLEDescriptor* pDescriptor, NimBLEConnInfo& connInfo) {
    Serial.printf("Descriptor read: %s\n", pDescriptor->getUUID().toString().c_str());
}