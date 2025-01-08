/**
 * @file DataProvider.cpp
 * @date   2025-01-07
 * @author Lankow
 * @version 1.0
 */
#include "DataProvider.hpp"

DataProvider::DataProvider():
    m_minSpeed(0),
    m_maxSpeed(255),
    m_minRpm(0),
    m_maxRpm(65535)
    {};

void DataProvider::setMinSpeed(uint16_t minSpeed)
{
    m_minSpeed = minSpeed;
};

void DataProvider::setMaxSpeed(uint16_t maxSpeed)
{
    m_maxSpeed = maxSpeed;
};

void DataProvider::setMinRpm(uint16_t minRpm)
{
    m_minRpm = minRpm;
};

void DataProvider::setMaxRpm(uint16_t maxRpm)
{
    m_maxRpm = maxRpm;
};

uint16_t DataProvider::getMinSpeed() const
{
    return m_minSpeed;
};

uint16_t DataProvider::getMaxSpeed() const
{
    return m_maxSpeed;
};

uint16_t DataProvider::getMinRpm() const
{
    return m_minRpm;
};

uint16_t DataProvider::getMaxRpm() const
{
    return m_maxRpm;
};
