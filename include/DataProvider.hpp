/**
 * @file DataProvider.hpp
 * @date   2025-01-07
 * @author Lankow
 * @version 1.0
 */
#ifndef DATA_PROVIDER_HPP
#define DATA_PROVIDER_HPP

#include <Arduino.h>

class DataProvider
{
    public:
        explicit DataProvider();

        void setMinSpeed(uint16_t minSpeed);
        void setMaxSpeed(uint16_t maxSpeed);
        void setMinRpm(uint16_t minRpm);
        void setMaxRpm(uint16_t maxRpm);

        uint16_t getMinSpeed() const;
        uint16_t getMaxSpeed() const;
        uint16_t getMinRpm() const;
        uint16_t getMaxRpm() const;

    private:
        uint16_t m_minSpeed;
        uint16_t m_maxSpeed;
        uint16_t m_minRpm;
        uint16_t m_maxRpm;
};
#endif // DATA_PROVIDER_HPP