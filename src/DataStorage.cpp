/**
 * @file DataStorage.cpp
 * @date   2025-01-11
 * @author Lankow
 * @version 1.0
 */
#include "DataStorage.hpp"

DataStorage::DataStorage() {
    m_emulatedDataList.push_back(std::unique_ptr<IEmulatedData>(
        new EmulatedData<float>(0x0C, 0, 0, 16383.75, 10, 100, 
        [this](const float& current) -> int32_t {
            Serial.println("Custom Engine Speed Getter:");
            Serial.println(current);
            return static_cast<int32_t>(current);
        }
    ))); // Engine Speed

    m_emulatedDataList.push_back(std::unique_ptr<IEmulatedData>(
        new EmulatedData<int>(0x0D, 0, 0, 255, 10, 100, 
        [this](const int& current) -> int32_t {
            Serial.println("Custom Vehicle Speed Getter:");
            Serial.println(current);
            return current;
        }
    ))); // Vehicle Speed
}

    void DataStorage::updateAll() {
        for (auto& emulatedData : m_emulatedDataList) {
            emulatedData->update();
        }
    }

    void DataStorage::printAll() const {
        for (const auto& emulatedData : m_emulatedDataList) {
            emulatedData->printCurrent();
            emulatedData->getCustom();
        }
    }