/**
 * @file BLEHandler.cpp
 * @date   2025-01-04
 * @author Lankow
 * @version 1.0
 */

#include "BLEHandler.hpp"
#include "OBD2PIDInfo.hpp"
#include "BluetoothSerial.h"

BLEHandler::BLEHandler(std::shared_ptr<OBD2PIDManager> manager) : m_manager(manager) {}

void BLEHandler::initialize() {
    BluetoothSerial serial;
    serial.begin("OBDII");
}

void BLEHandler::cyclic() {

}

