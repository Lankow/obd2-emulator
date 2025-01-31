/**
 * @file OBD2PIDManager.cpp
 * @date   2025-01-11
 * @author Lankow
 * @version 1.0
 */
#include "OBD2PIDManager.hpp"

OBD2PIDManager::OBD2PIDManager()
{

    // Engine Speed (0x0C)
    addPID<float>(
        0x0C, 2, 0.0f, 0.0f, 16383.75f, 100.0f, 100,
        [this](const float &current) -> int32_t
        {
            Serial.println("Formula Engine Speed:");

            int32_t scaledValue = static_cast<int32_t>(current * 4);
            uint8_t A = (scaledValue / 256) & 0xFF;
            uint8_t B = scaledValue % 256;

            int32_t result = (A << 8) | B;

            return result;
        });

    // Vehicle Speed (0x0D)
    addPID<int>(
        0x0D, 1, 0, 0, 255, 1, 100,
        [this](const int &current) -> int32_t
        {
            Serial.println("Formula Vehicle Speed:");
            return current;
        });
}

void OBD2PIDManager::updateAll()
{
    for (auto &pair : m_OBD2PIDInfoMap)
    {
        pair.second->update();
    }
}

void OBD2PIDManager::printAll() const
{
    for (const auto &pair : m_OBD2PIDInfoMap)
    {
        Serial.println("---------------");
        Serial.print("ID: ");
        Serial.println(pair.first, HEX);
        pair.second->printCurrent();
        Serial.println("---------------");
    }
}

IOBD2PIDInfo *OBD2PIDManager::getPIDInfo(uint8_t pid) const
{
    auto it = m_OBD2PIDInfoMap.find(pid);
    return (it != m_OBD2PIDInfoMap.end()) ? it->second.get() : nullptr;
}

const std::pair<const uint8_t, std::unique_ptr<IOBD2PIDInfo>> *OBD2PIDManager::getPIDInfoByIndex(uint8_t index) const
{
    if (0 == m_OBD2PIDInfoMap.size())
    {
        return nullptr;
    }

    uint8_t indexToDisplay = abs(index % (uint8_t)m_OBD2PIDInfoMap.size());

    auto it = m_OBD2PIDInfoMap.begin();
    std::advance(it, indexToDisplay);

    return &(*it);
}

template <typename T>
void OBD2PIDManager::addPID(uint8_t pid, uint8_t length, T current, T min, T max, T increment, int pace,
                            std::function<int32_t(const T &)> customGetter)
{
    m_OBD2PIDInfoMap[pid] = std::unique_ptr<IOBD2PIDInfo>(
        new OBD2PIDInfo<T>(length, current, min, max, increment, pace, customGetter));
}