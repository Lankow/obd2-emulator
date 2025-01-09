/**
 * @file EmulatedData.cpp
 * @date   2025-01-09
 * @author Lankow
 * @version 1.0
 */
#include "EmulatedData.hpp"

template<typename T>
EmulatedData<T>::EmulatedData(T current, T min, T max, T increment, int pace)
    : m_current(current),
      m_min(min),
      m_max(max),
      m_increment(increment),
      m_pace(pace),
      m_increasing(true) {
    if (m_min > m_max) {
        throw std::invalid_argument("Minimum value cannot be greater than maximum value.");
    }
    if (m_current < m_min || m_current > m_max) {
        throw std::out_of_range("Current value must be within the range defined by min and max.");
    }
    if (m_increment <= 0) {
        throw std::invalid_argument("Increment must be greater than 0.");
    }
    if (m_pace <= 0) {
        throw std::invalid_argument("Pace must be greater than 0.");
    }
}

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

// Explicit instantiation for specific types
template class EmulatedData<int>;
template class EmulatedData<float>;
template class EmulatedData<double>;
