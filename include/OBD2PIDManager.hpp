/**
 * @file OBD2PIDManager.hpp
 * @date   2025-01-12
 * @author Lankow
 * @version 1.0
 */
#ifndef DATA_STORAGE_HPP
#define DATA_STORAGE_HPP

#include <Arduino.h>
#include <unordered_map>
#include <memory>
#include <vector>
#include "OBD2PIDInfo.hpp"

class OBD2PIDManager
{
public:
    explicit OBD2PIDManager();

    void updateAll();
    void printAll() const;
    OBD2PIDInfo *getPIDInfo(uint16_t pid) const;
    const std::pair<const uint16_t, std::unique_ptr<OBD2PIDInfo>> *getPIDInfoByIndex(uint8_t index) const;
    std::vector<uint16_t> getAllPIDs() const;

private:
    std::unordered_map<uint16_t, std::unique_ptr<OBD2PIDInfo>> m_OBD2PIDInfoMap;

    void addPID(std::string description, uint16_t pid, uint8_t length, double current, double min, double max, double increment, int pace,
                std::function<int32_t(const double &)> customGetter);
    void addPID(std::string description, uint16_t pid, uint8_t length, double current, double min, double max, double increment, int pace);
};
#endif // DATA_STORAGE_HPP