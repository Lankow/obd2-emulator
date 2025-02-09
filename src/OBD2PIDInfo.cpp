/**
 * @file OBD2PIDInfo.cpp
 * @date   2025-01-09
 * @author Lankow
 * @version 1.0
 */
#include <Arduino.h>
#include "OBD2PIDInfo.hpp"

template <typename T>
OBD2PIDInfo<T>::OBD2PIDInfo(std::string description, uint8_t length, T current, T min, T max, T increment, int pace,
                            std::function<int32_t(const T &current)> formulaGetter)
    : m_description(description),
      m_length(length),
      m_current(current),
      m_min(min),
      m_max(max),
      m_increment(increment),
      m_pace(pace),
      m_increasing(true),
      m_formulaGetter(formulaGetter) {}

template <typename T>
T OBD2PIDInfo<T>::getCurrent() const
{
    return m_current;
}

template <typename T>
void OBD2PIDInfo<T>::update()
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

template <typename T>
void OBD2PIDInfo<T>::printCurrent() const
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

template <typename T>
uint32_t OBD2PIDInfo<T>::getFormula() const
{
    if (m_formulaGetter)
    {
        return m_formulaGetter(m_current);
    }
    
    return static_cast<double>(m_current);
}

template <typename T>
const std::string &OBD2PIDInfo<T>::getDescription() const { return m_description; }
template <typename T>
uint8_t OBD2PIDInfo<T>::getLength() const { return m_length; }
template <typename T>
double OBD2PIDInfo<T>::getCurrentAsDouble() const { return static_cast<double>(m_current); }
template <typename T>
double OBD2PIDInfo<T>::getMinAsDouble() const { return static_cast<double>(m_min); }
template <typename T>
double OBD2PIDInfo<T>::getMaxAsDouble() const { return static_cast<double>(m_max); }

template <typename T>
void OBD2PIDInfo<T>::setMin(double min)
{
    // Add Default min
    m_min = static_cast<T>(min);
}

template <typename T>
void OBD2PIDInfo<T>::setMax(double max)
{
    // Add Default max
    m_max = static_cast<T>(max);
}

// Explicit instantiation for specific types
template class OBD2PIDInfo<int>;
template class OBD2PIDInfo<float>;
template class OBD2PIDInfo<double>;
