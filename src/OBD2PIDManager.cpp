/**
 * @file OBD2PIDManager.cpp
 * @date   2025-01-11
 * @author Lankow
 * @version 1.0
 */
#include "OBD2PIDManager.hpp"

OBD2PIDManager::OBD2PIDManager() {
    m_OBD2PIDInfoList.push_back(std::unique_ptr<IOBD2PIDInfo>(
        new OBD2PIDInfo<float>(0x0C, 0, 0, 16383.75, 10, 100, 
        [this](const float& current) -> int32_t {
            Serial.println("Custom Engine Speed Getter:");
            Serial.println(current);
            return static_cast<int32_t>(current);
        }
    ))); // Engine Speed

    m_OBD2PIDInfoList.push_back(std::unique_ptr<IOBD2PIDInfo>(
        new OBD2PIDInfo<int>(0x0D, 0, 0, 255, 10, 100, 
        [this](const int& current) -> int32_t {
            Serial.println("Custom Vehicle Speed Getter:");
            Serial.println(current);
            return current;
        }
    ))); // Vehicle Speed
}

    void OBD2PIDManager::updateAll() {
        for (auto& OBD2PIDInfo : m_OBD2PIDInfoList) {
            OBD2PIDInfo->update();
        }
    }

    void OBD2PIDManager::printAll() const {
        for (const auto& OBD2PIDInfo : m_OBD2PIDInfoList) {
            OBD2PIDInfo->printCurrent();
            OBD2PIDInfo->getCustom();
        }
    }