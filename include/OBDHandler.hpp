/**
 * @file OBDHandler.hpp
 * @date   2025-01-12
 * @author Lankow
 * @version 1.0
 */
#ifndef OBD_HANDLER_HPP
#define OBD_HANDLER_HPP

#include <Arduino.h>
#include <unordered_map>
#include <memory>
#include <vector>
#include "OBDInfo.hpp"
#include "CycleHandler.hpp"

class OBDHandler
{
public:
    explicit OBDHandler(std::shared_ptr<CycleHandler> cycleHandler);
    void cyclic();
    OBDInfo *getByPid(uint16_t pid);
    const OBDInfo *getByIndex(uint8_t index) const;

    std::vector<OBDInfo> &getAll();
    void update(OBDInfo &info);
    uint32_t getFormula(const OBDInfo &info) const;
    bool setMin(OBDInfo &info, double min);
    bool setMax(OBDInfo &info, double max);
    bool setPace(OBDInfo &info, uint32_t pace);
    bool setIncrement(OBDInfo &info, double increment);

private:
    std::shared_ptr<CycleHandler> m_cycleHandler;
    std::vector<OBDInfo> m_infos;

    void updateAll();
    void printAll() const;
    void addNewInfo(uint16_t pid, uint8_t length, std::string description, double current,
                    double min, double max, double increment, uint32_t pace,
                    std::function<int32_t(const double &)> customGetter);
};
#endif // OBD_HANDLER_HPP