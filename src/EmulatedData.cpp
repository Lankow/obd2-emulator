/**
 * @file EmulatedData.cpp
 * @date   2025-01-09
 * @author Lankow
 * @version 1.0
 */
#include <Arduino.h>
#include "EmulatedData.hpp"

template<typename T>
EmulatedData<T>::EmulatedData(uint8_t pid, T current, T min, T max, T increment, int pace, std::function<int32_t(const T& current)> customGetter)
    : m_pid(pid),
      m_current(current),
      m_min(min),
      m_max(max),
      m_increment(increment),
      m_pace(pace),
      m_increasing(true),
      m_customGetter(customGetter){}


template<typename T>
T EmulatedData<T>::getCurrent() const {
    return m_current;
}

template<typename T>
void EmulatedData<T>::update() {
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
void EmulatedData<T>::printCurrent() const{
    Serial.println("Current Value: ");
    Serial.println(m_pid);
    Serial.println(m_current);
    Serial.println("---------------");
}

template<typename T>
uint32_t EmulatedData<T>::getCustom() const {
    if (m_customGetter) {
        return m_customGetter(m_current);
    }
    return 0;
}

// Explicit instantiation for specific types
template class EmulatedData<int>;
template class EmulatedData<float>;
template class EmulatedData<double>;
