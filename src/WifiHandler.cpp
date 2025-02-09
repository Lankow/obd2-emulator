/**
 * @file WifiHandler.cpp
 * @date   2025-01-05
 * @author Lankow
 * @version 1.0
 */
#include <vector>
#include "WifiHandler.hpp"
#include "Constants.hpp"
#include "PageGenerator.hpp"
#include "OBD2PIDInfo.hpp"

WifiHandler::WifiHandler(std::shared_ptr<OBD2PIDManager> manager) : m_manager(manager), m_server(Config::SERVER_PORT) {}

void WifiHandler::handleRoot()
{
    std::vector<uint16_t> pids = m_manager->getAllPIDs();
    std::string mainPageHtml = PageGenerator::getMainPage(pids);
    m_server.send(200, "text/html", mainPageHtml.c_str());
}

void WifiHandler::handleEdit()
{
    if (!m_server.hasArg("pid"))
    {
        m_server.send(400, "text/plain", "Missing PID parameter.");
        return;
    }

    uint16_t pid = std::stoi(m_server.arg("pid").c_str());
    const auto *entry = m_manager->getPIDInfoByIndex(pid);

    if (entry != nullptr)
    {
        IOBD2PIDInfo *info = entry->second.get();
        std::string editPageHtml = PageGenerator::getEditPage(entry->first, *info);
        m_server.send(200, "text/html", editPageHtml.c_str());
    }
}

void WifiHandler::handleSubmit()
{
    uint16_t pid = std::stoi(m_server.arg("pid").c_str());
    uint16_t minValue = std::stoi(m_server.arg("minValue").c_str());
    uint16_t maxValue = std::stoi(m_server.arg("maxValue").c_str());

    Serial.println("Updated PID: " + pid);
    Serial.println("Min value: " + minValue);
    Serial.println("Max value: " + maxValue);

    m_server.send(200, "text/plain", "Data received. You can close this page.");
}

void WifiHandler::initialize()
{
    WiFi.softAP(Config::SSID.c_str(), Config::PASSWORD.c_str());
    IPAddress apIp = WiFi.softAPIP();

    m_server.on("/", [this]()
                { handleRoot(); });
    m_server.on("/edit", [this]()
                { handleEdit(); });
    m_server.on("/submit", [this]()
                { handleSubmit(); });

    m_server.begin();
    Serial.println("Server started.");
    Serial.println(apIp.toString());
}

void WifiHandler::handle()
{
    m_server.handleClient();
}