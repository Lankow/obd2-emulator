/**
 * @file ObdManager.hpp
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
#include "ObdInfo.hpp"

class ObdManager
{
public:
    explicit ObdManager();

    void updateAll(uint64_t cycleCount);
    void printAll() const;
    ObdInfo *getByPid(uint16_t pid);
    const ObdInfo *getByIndex(uint8_t index) const;

    std::vector<ObdInfo> getAll() const;

private:
    std::vector<ObdInfo> m_infos;

    void addNewInfo(uint16_t pid, uint8_t length, std::string description, double current,
                    double min, double max, double increment, uint64_t pace,
                    std::function<int32_t(const double &)> customGetter);
};
#endif // DATA_STORAGE_HPP