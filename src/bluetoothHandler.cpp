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

    NimBLEAdvertising *advertising = NimBLEDevice::getAdvertising();
    advertising->addServiceUUID(NimBLEUUID((uint16_t)0x180D));
    advertising->start();

    Serial.println("Bluetooth Low Energy device started successfully");
    Serial.println("Device is now advertising as OBDII");
}

void BluetoothHandler::read()
{

}

void BluetoothHandler::write()
{
    uint8_t readPid = 0x0C; // Placeholder for initial testing purposes
    IOBD2PIDInfo* result =  m_manager->getPIDInfo(readPid);
    uint32_t formulaData = result->getFormula();

    Serial.print("Formula Data: ");
    Serial.println(formulaData);
}