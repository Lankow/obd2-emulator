/**
 * @file AccessPointInitializer.cpp
 * @date   2025-03-07
 * @author Lankow
 * @version 1.0
 */
#include "AccessPointInitializer.hpp"
#include "WiFi.h"
#include "Constants.hpp"

void AccessPointInitializer::initialize()
{
    WiFi.softAPConfig(Config::IP, Config::GATEWAY, Config::SUBNET);
    WiFi.softAP(Config::SSID.c_str(), Config::PASSWORD.c_str());
    IPAddress apIp = WiFi.softAPIP();

    Serial.println("Access Point started.");
    Serial.println(apIp.toString());
}
