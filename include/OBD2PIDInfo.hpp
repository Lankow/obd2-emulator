/**
 * @file OBD2PIDInfo.hpp
 * @date   2025-01-09
 * @author Lankow
 * @version 1.0
 */
#ifndef OBD2_PID_INFO_HPP
#define OBD2_PID_INFO_HPP

#include <stdexcept>
#include <type_traits>

// Base class for polymorphism
class IOBD2PIDInfo {
public:
    virtual ~IOBD2PIDInfo() = default;
    virtual void update() = 0;
    virtual void printCurrent() const = 0;
    virtual uint32_t getFormula() const = 0;
    virtual uint8_t getLength() const = 0;
};

template<typename T>
class OBD2PIDInfo : public IOBD2PIDInfo{
public:
    static_assert(std::is_arithmetic<T>::value, "OBD2PIDInfo only supports arithmetic types.");

    OBD2PIDInfo(uint8_t length, T current, T min, T max, T increment, int pace, std::function<int32_t(const T& current)> formulaGetter = nullptr);
    
    T getCurrent() const;
    void update() override;
    void printCurrent() const override;
    uint32_t getFormula() const override;
    uint8_t getLength() const override;

private:
    uint8_t m_length;
    T m_current;
    T m_min;
    T m_max;
    T m_increment;

    int m_pace;
    bool m_increasing;
    std::function<int32_t(const T&)> m_formulaGetter;
};

#endif // OBD2_PID_INFO_HPP
