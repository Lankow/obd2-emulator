/**
 * @file Configuration.hpp
 * @date 2025-02-20
 * @author Lankow
 * @version 1.0
 */

#ifndef CONFIGURATOR_HPP
#define CONFIGURATOR_HPP
#include <Arduino.h>

namespace Config
{
    constexpr uint32_t CYCLE_TIME_MS = 100;    /**< Cycle time in milliseconds. */
    const std::string SSID = "OBDII-config";   /**< SSID for OBDII Emulator configuration page. */
    const std::string PASSWORD = "obd2config"; /**< Password for OBDII Emulator configuration page. */
    constexpr uint16_t SERVER_PORT = 80;       /**< Server port for access point. */

    const IPAddress IP(192, 168, 4, 2);
    const IPAddress GATEWAY(192, 168, 4, 2);
    const IPAddress SUBNET(255, 255, 255, 0);
}

class Configuration
{
public:
    Configuration();

    bool getCycleTime() const;
    bool getSsid() const;
    bool getPassword() const;
    bool getAdditionalDebug() const;

    void setCycleTime();
    void setSsid();
    void setPassword();
    void setAdditionalDebug();

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
#endif // CONFIGURATOR_HPP