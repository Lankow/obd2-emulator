/**
 * @file CycleHandler.hpp
 * @date   2025-03-06
 * @author Lankow
 * @version 1.0
 */
#ifndef CYCLE_HANDLER_HPP
#define CYCLE_HANDLER_HPP

#include <Arduino.h>
class CycleHandler
{
public:
    CycleHandler();
    void startCycle();
    void endCycle();
    const uint32_t getCycleCount() const;

private:
    uint32_t m_cycleCount;
    long m_cycleStart;
};
#endif // CYCLE_HANDLER_HPP