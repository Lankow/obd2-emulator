/**
 * @file AccessPointInitializer.cpp
 * @date   2025-03-07
 * @author Lankow
 * @version 1.0
 */
#include "AccessPointInitializer.hpp"
#include "WiFi.h"

const IPAddress IP(192, 168, 4, 2);
const IPAddress GATEWAY(192, 168, 4, 2);
const IPAddress SUBNET(255, 255, 255, 0);

AccessPointInitializer::AccessPointInitializer(std::shared_ptr<Configuration> configuration) : m_configuration(configuration) {};

void AccessPointInitializer::initialize()
{
    WiFi.softAPConfig(IP, GATEWAY, SUBNET);
    WiFi.softAP(m_configuration->getSSID().c_str(), m_configuration->getPassword().c_str());
    IPAddress apIp = WiFi.softAPIP();

    Serial.println("Access Point started.");
    Serial.println(apIp.toString());
}
