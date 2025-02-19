/**
 * @file OBDInfo.cpp
 * @date   2025-01-09
 * @author Lankow
 * @version 1.0
 */
#include <Arduino.h>
#include "OBDInfo.hpp"

OBDInfo::OBDInfo(uint16_t pid, uint8_t length, std::string description, double current,
                 double min, double max, double increment, uint64_t pace,
                 std::function<int32_t(const double &current)> formulaGetter)
    : m_pid(pid),
      m_length(length),
      m_description(description),
      m_current(current),
      m_defaultMin(min),
      m_min(min),
      m_defaultMax(max),
      m_max(max),
      m_increment(increment),
      m_pace(pace),
      m_increasing(true),
      m_formulaGetter(formulaGetter) {}

void OBDInfo::update()
{
    if (m_increasing)
    {
        m_current += m_increment;
        if (m_current >= m_max)
        {
            m_current = m_max;
            m_increasing = false;
        }
    }
    else
    {
        m_current -= m_increment;
        if (m_current <= m_min)
        {
            m_current = m_min;
            m_increasing = true;
        }
    }
}

void OBDInfo::printCurrent() const
{
    Serial.println("---------------");
    Serial.println(m_description.c_str());
    Serial.println("Pid: " + String(m_pid));
    Serial.println("Length: " + String(m_length));
    Serial.println("Current: " + String(m_current));
    Serial.println("Min: " + String(m_min));
    Serial.println("Max: " + String(m_max));
    Serial.println("Pace: " + String(m_pace));
    Serial.println("Increment: " + String(m_increment));
    Serial.println("---------------");
}

uint16_t OBDInfo::getPid() const { return m_pid; }
uint8_t OBDInfo::getLength() const { return m_length; }
const std::string &OBDInfo::getDescription() const { return m_description; }
double OBDInfo::getCurrent() const { return m_current; }
double OBDInfo::getMin() const { return m_min; }
double OBDInfo::getMax() const { return m_max; }
double OBDInfo::getDefaultMin() const { return m_defaultMin; }
double OBDInfo::getDefaultMax() const { return m_defaultMax; }
double OBDInfo::getIncrement() const { return m_increment; }
uint64_t OBDInfo::getPace() const { return m_pace; }
uint32_t OBDInfo::getFormula() const
{
    if (m_formulaGetter)
    {
        return m_formulaGetter(m_current);
    }

    return m_current;
}
void OBDInfo::setMin(double min)
{
    if (min <= m_max && min >= m_defaultMin)
    {
        m_min = min;
    }
}

void OBDInfo::setMax(double max)
{
    if (max >= m_min && max <= m_defaultMax)
    {
        m_max = max;
    }
}

void OBDInfo::setIncrement(double increment)
{
    if (increment >= m_min && increment <= m_defaultMax)
    {
        m_increment = increment;
    }
}

void OBDInfo::setPace(uint64_t pace)
{
    if (pace >= 0)
    {
        m_pace = pace;
    }
}
