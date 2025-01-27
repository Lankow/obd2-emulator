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
#include "OBD2PIDInfo.hpp"

class OBD2PIDManager
{
public:
    explicit OBD2PIDManager();

    void updateAll();
    void printAll() const;
    IOBD2PIDInfo *getPIDInfo(uint8_t pid) const;

private:
    std::unordered_map<uint8_t, std::unique_ptr<IOBD2PIDInfo>> m_OBD2PIDInfoMap;

    template <typename T>
    void addPID(uint8_t pid, uint8_t length, T current, T min, T max, T increment, int pace,
                std::function<int32_t(const T &)> customGetter);
};
#endif // DATA_STORAGE_HPP