/**
 * @file EmulatedData.hpp
 * @date   2025-01-09
 * @author Lankow
 * @version 1.0
 */
#ifndef EMULATED_DATA_HPP
#define EMULATED_DATA_HPP

#include <stdexcept>
#include <type_traits>

template<typename T>
class EmulatedData {
public:
    static_assert(std::is_arithmetic<T>::value, "EmulatedData only supports arithmetic types.");

    EmulatedData(T current, T min, T max, T increment, int pace);

    T getCurrent() const;
    void update();

private:
    T m_current;
    T m_min;
    T m_max;
    T m_increment;

    uint8_t m_pid;
    int m_pace;
    bool m_increasing;
};

#endif // EMULATED_DATA_HPP
