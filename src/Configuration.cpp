/**
 * @file Configuration.cpp
 * @date 2025-02-20
 * @author Lankow
 * @version 1.0
 */
#include "Configuration.hpp"

constexpr uint32_t CYCLE_TIME_MS = 100;
const std::string SSID = "OBDII-config";
const std::string PASSWORD = "obd2config";

const IPAddress IP(192, 168, 4, 2);
const IPAddress GATEWAY(192, 168, 4, 2);
const IPAddress SUBNET(255, 255, 255, 0);
constexpr uint16_t SERVER_PORT = 80;

Configuration::Configuration() : m_cycleTime(CYCLE_TIME_MS),
                                 m_ssid(SSID),
                                 m_password(PASSWORD),
                                 m_additionalDebug(false),
                                 m_ipAddress(IP),
                                 m_gateway(GATEWAY),
                                 m_subnet(SUBNET),
                                 m_serverPort(SERVER_PORT) {};

uint32_t Configuration::getCycleTime() const { return m_cycleTime; };
IPAddress Configuration::getIpAddress() const { return m_ipAddress; };
IPAddress Configuration::getGateway() const { return m_gateway; };
IPAddress Configuration::getSubnet() const { return m_subnet; };
std::string Configuration::getSsid() const { return m_ssid; };
std::string Configuration::getPassword() const { return m_password; };
uint16_t Configuration::getServerPort() const { return m_serverPort; };
bool Configuration::getAdditionalDebug() const { return m_additionalDebug; };
void Configuration::setAdditionalDebug(bool isAdditionalDebug)
{
    m_additionalDebug = isAdditionalDebug;
}