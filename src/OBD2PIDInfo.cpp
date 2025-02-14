/**
 * @file OBD2PIDInfo.cpp
 * @date   2025-01-09
 * @author Lankow
 * @version 1.0
 */
#include <Arduino.h>
#include "OBD2PIDInfo.hpp"

OBD2PIDInfo::OBD2PIDInfo(std::string description, uint8_t length, double current, double min, double max, double increment, int pace,
                         std::function<int32_t(const double &current)> formulaGetter)
    : m_description(description),
      m_length(length),
      m_current(current),
      m_defaultMin(min),
      m_min(min),
      m_defaultMax(max),
      m_max(max),
      m_increment(increment),
      m_pace(pace),
      m_increasing(true),
      m_formulaGetter(formulaGetter) {}

void OBD2PIDInfo::update()
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

void OBD2PIDInfo::printCurrent() const
{
    Serial.print("Length: ");
    Serial.println(m_length);
    Serial.print("Current: ");
    Serial.println(m_current);
    Serial.print("Min: ");
    Serial.println(m_min);
    Serial.print("Max: ");
    Serial.println(m_max);
    Serial.print("Pace: ");
    Serial.println(m_pace);
    Serial.print("Increment: ");
    Serial.println(m_increment);
}

const std::string &OBD2PIDInfo::getDescription() const { return m_description; }
double OBD2PIDInfo::getCurrent() const { return m_current; }
uint8_t OBD2PIDInfo::getLength() const { return m_length; }
double OBD2PIDInfo::getMin() const { return m_min; }
double OBD2PIDInfo::getMax() const { return m_max; }
double OBD2PIDInfo::getDefaultMin() const { return m_defaultMin; }
double OBD2PIDInfo::getDefaultMax() const { return m_defaultMax; }
uint32_t OBD2PIDInfo::getFormula() const
{
    if (m_formulaGetter)
    {
        return m_formulaGetter(m_current);
    }

    return m_current;
}
void OBD2PIDInfo::setMin(double min)
{
    if (min <= m_max && min >= m_defaultMin)
    {
        m_min = min;
    }
}

void OBD2PIDInfo::setMax(double max)
{
    if (max >= m_min && max <= m_defaultMax)
    {
        m_max = max;
    }
}
