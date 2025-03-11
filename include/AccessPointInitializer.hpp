/**
 * @file AccessPointInitializer.hpp
 * @date   2025-03-07
 * @author Lankow
 * @version 1.0
 */
#ifndef ACCESS_POINT_INITIALIZER_HPP
#define ACCESS_POINT_INITIALIZER_HPP

#include <Arduino.h>
#include <memory>
#include "Configuration.hpp"
class AccessPointInitializer
{
public:
    AccessPointInitializer(std::shared_ptr<Configuration> configuration);
    void initialize();

private:
    std::shared_ptr<Configuration> m_configuration;
};

#endif // ACCESS_POINT_INITIALIZER_HPP