/**
 * @file Configuration.hpp
 * @date 2025-02-20
 * @author Lankow
 * @version 1.0
 */

#ifndef CONFIGURATION_HPP
#define CONFIGURATION_HPP
#include <Arduino.h>
#include <ArduinoJson.h>
#include <vector>
#include "OBDInfo.hpp"

class Configuration
{
public:
    Configuration();

    bool loadConfig();
    bool saveConfig();
    bool resetConfig();

    uint32_t getCycleTime() const;
    std::string getSSID() const;
    std::string getPassword() const;
    bool getAdditionalDebug() const;
    std::vector<OBDInfo> &getObdInfoList();
    void setAdditionalDebug(bool isAdditionalDebug);

private:
    std::string m_ssid;
    std::string m_password;
    uint32_t m_cycleTime;
    bool m_additionalDebug;
    std::vector<OBDInfo> m_obdInfoList;

    void printConfig();
    void parseJson(DynamicJsonDocument &doc);
};
#endif // CONFIGURATION_HPP