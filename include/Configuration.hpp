/**
 * @file Configuration.hpp
 * @date 2025-02-20
 * @author Lankow
 * @version 1.0
 */

#ifndef CONFIGURATION_HPP
#define CONFIGURATION_HPP
#include <Arduino.h>

class Configuration
{
public:
    Configuration();

    uint32_t getCycleTime() const;
    std::string getSsid() const;
    std::string getPassword() const;
    bool getAdditionalDebug() const;
    IPAddress getIpAddress() const;
    IPAddress getGateway() const;
    IPAddress getSubnet() const;
    uint16_t getServerPort() const;

    void setCycleTime();
    void setSsid();
    void setPassword();
    void setAdditionalDebug(bool isAdditionalDebug);

private:
    uint32_t m_cycleTime;
    std::string m_ssid;
    std::string m_password;
    bool m_additionalDebug;

    IPAddress m_ipAddress;
    IPAddress m_gateway;
    IPAddress m_subnet;
    uint16_t m_serverPort;
};
#endif // CONFIGURATION_HPP