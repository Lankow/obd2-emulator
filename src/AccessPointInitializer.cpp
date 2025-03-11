/**
 * @file AccessPointInitializer.cpp
 * @date   2025-03-07
 * @author Lankow
 * @version 1.0
 */
#include "AccessPointInitializer.hpp"
#include "WiFi.h"

AccessPointInitializer::AccessPointInitializer(std::shared_ptr<Configuration> configuration) : m_configuration(configuration) {};

void AccessPointInitializer::initialize()
{
    WiFi.softAPConfig(m_configuration->getIpAddress(), m_configuration->getGateway(), m_configuration->getSubnet());
    WiFi.softAP(m_configuration->getSsid().c_str(), m_configuration->getPassword().c_str());
    IPAddress apIp = WiFi.softAPIP();

    Serial.println("Access Point started.");
    Serial.println(apIp.toString());
}
