/**
 * @file OBD2PIDInfo.cpp
 * @date   2025-01-09
 * @author Lankow
 * @version 1.0
 */
#include <Arduino.h>
#include "OBD2PIDInfo.hpp"

template<typename T>
OBD2PIDInfo<T>::OBD2PIDInfo(uint8_t length, T current, T min, T max, T increment, int pace, std::function<int32_t(const T& current)> formulaGetter)
    : m_length(length),
      m_current(current),
      m_min(min),
      m_max(max),
      m_increment(increment),
      m_pace(pace),
      m_increasing(true),
      m_formulaGetter(formulaGetter){}


template<typename T>
T OBD2PIDInfo<T>::getCurrent() const {
    return m_current;
}

template<typename T>
void OBD2PIDInfo<T>::update() {
    if (m_increasing) {
        m_current += m_increment;
        if (m_current >= m_max) 
        {
            m_current = m_max;
            m_increasing = false;
        }
    } else {
        m_current -= m_increment;
        if (m_current <= m_min) 
        {
            m_current = m_min;
            m_increasing = true;
        }
    }
}

template<typename T>
void OBD2PIDInfo<T>::printCurrent() const{
    Serial.println("Current Value: ");
    Serial.println(m_length);
    Serial.println(m_current);
    Serial.println("---------------");
}

template<typename T>
uint32_t OBD2PIDInfo<T>::getFormula() const {
    if (m_formulaGetter) {
        return m_formulaGetter(m_current);
    }
    return 0;
}

// Explicit instantiation for specific types
template class OBD2PIDInfo<int>;
template class OBD2PIDInfo<float>;
template class OBD2PIDInfo<double>;
