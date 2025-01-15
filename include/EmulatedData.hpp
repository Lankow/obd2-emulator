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

// Base class for polymorphism
class IEmulatedData {
public:
    virtual ~IEmulatedData() = default;
    virtual void update() = 0;
    virtual void printCurrent() const = 0;
    virtual uint32_t getCustom() const = 0;
};

template<typename T>
class EmulatedData : public IEmulatedData{
public:
    static_assert(std::is_arithmetic<T>::value, "EmulatedData only supports arithmetic types.");

    EmulatedData(uint8_t pid, T current, T min, T max, T increment, int pace, std::function<int32_t(const T& current)> customGetter = nullptr);
    
    T getCurrent() const;
    void update() override;
    void printCurrent() const override;
    uint32_t getCustom() const override;

private:
    uint8_t m_pid;
    T m_current;
    T m_min;
    T m_max;
    T m_increment;

    int m_pace;
    bool m_increasing;
    std::function<int32_t(const T&)> m_customGetter;
};

#endif // EMULATED_DATA_HPP
