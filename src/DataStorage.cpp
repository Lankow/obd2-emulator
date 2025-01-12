/**
 * @file DataStorage.cpp
 * @date   2025-01-11
 * @author Lankow
 * @version 1.0
 */
#include "DataStorage.hpp"

DataStorage::DataStorage() {
    m_emulatedDataList.push_back(std::unique_ptr<IEmulatedData>(new EmulatedData<float>(0x0C, 0, 0, 16383.75 , 10, 100))); // Engine Speed
    m_emulatedDataList.push_back(std::unique_ptr<IEmulatedData>(new EmulatedData<int>(0x0D, 0, 0, 255, 10, 100))); // Vehicle Speed
}

    void DataStorage::updateAll() {
        for (auto& emulatedData : m_emulatedDataList) {
            emulatedData->update();
        }
    }

    void DataStorage::printAll() const {
        for (const auto& emulatedData : m_emulatedDataList) {
            emulatedData->printCurrent();
        }
    }