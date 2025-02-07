/**
 * @file WifiHandler.cpp
 * @date   2025-01-05
 * @author Lankow
 * @version 1.0
 */
#include "WifiHandler.hpp"
#include "Constants.hpp"

const std::string SSID = "";
const std::string PASSWORD = "";
constexpr uint16_t SERVER_PORT = 80;

WifiHandler::WifiHandler(std::shared_ptr<OBD2PIDManager> manager) : m_manager(manager), m_server(SERVER_PORT) {}

void WifiHandler::handleRoot()
{
    uint16_t minValue = 0;
    uint16_t maxValue = 255;

    std::string dynamicWebpage = R"rawliteral(
        <!DOCTYPE html>
        <html>
        <body>
            <h1>Configure OBD2 Emulator</h1>
            <form action="/submit" method="get">
                <label for="minValue">Min Value:</label>
                <input type="text" id="minValue" name="minValue" value=")rawliteral" +
                                 std::to_string(minValue) + R"rawliteral("><br>
                <label for="maxValue">Max Value:</label>
                <input type="text" id="maxValue" name="maxValue" value=")rawliteral" +
                                 std::to_string(maxValue) + R"rawliteral("><br>
                <input type="submit" value="Submit">
            </form>
        </body>
        </html>
    )rawliteral";

    m_server.send(200, "text/html", dynamicWebpage.c_str());
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
                { handleRoot(); }); // TODO: Handle Root Displays all PIDs
    
    // TODO: Handle changing exact PID
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