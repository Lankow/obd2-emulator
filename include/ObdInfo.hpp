/**
 * @file OBDInfo.hpp
 * @date   2025-01-09
 * @author Lankow
 * @version 1.0
 */
#ifndef OBD_INFO_HPP
#define OBD_INFO_HPP
#include <Arduino.h>

struct OBDInfo
{
    uint16_t m_pid;
    uint8_t m_length;
    std::string m_description;

    double m_current;
    double m_defaultMin;
    double m_min;
    double m_defaultMax;
    double m_max;
    double m_increment;

    uint32_t m_pace;
    bool m_increasing;
    std::function<int32_t(const double &)> m_formulaGetter;
};

#endif // OBD_INFO_HPP
