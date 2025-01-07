/**
 * @file WifiHandler.cpp
 * @date   2025-01-05
 * @author Lankow
 * @version 1.0
 */
#include "WifiHandler.hpp"

const std::string SSID = "OBDII-config";
const std::string PASSWORD = "obd2config";
constexpr uint16_t SERVER_PORT = 80;

WifiHandler::WifiHandler() : m_server(SERVER_PORT) {}

void WifiHandler::handleRoot() {
    int minSpeed = 0;
    int maxSpeed = 200;

    int minRpm = 0;
    int maxRpm = 5000;

    std::string dynamicWebpage = R"rawliteral(
        <!DOCTYPE html>
        <html>
        <body>
            <h1>Configure OBD2 Emulator</h1>
            <form action="/submit" method="get">
                <label for="minSpeed">Min Speed:</label>
                <input type="text" id="minSpeed" name="minSpeed" value=")rawliteral" + std::to_string(minSpeed) + R"rawliteral("><br>
                <label for="maxSpeed">Max Speed:</label>
                <input type="text" id="maxSpeed" name="maxSpeed" value=")rawliteral" + std::to_string(maxSpeed) + R"rawliteral("><br>
                <input type="submit" value="Submit">
                <hr/>
                <label for="minRpm">Min RPM:</label>
                <input type="text" id="minRpm" name="minRpm" value=")rawliteral" + std::to_string(minRpm) + R"rawliteral("><br>
                <label for="maxRpm">Max RPM:</label>
                <input type="text" id="maxRpm" name="maxRpm" value=")rawliteral" + std::to_string(maxRpm) + R"rawliteral("><br>
                <input type="submit" value="Submit">
            </form>
        </body>
        </html>
    )rawliteral";

    m_server.send(200, "text/html", dynamicWebpage.c_str());
}

void WifiHandler::handleSubmit() {
    String minSpeedStr = m_server.arg("minSpeed");
    String maxSpeedStr = m_server.arg("maxSpeed");

    Serial.println("Min Speed: " + minSpeedStr);
    Serial.println("Max Speed: " + maxSpeedStr);

    m_server.send(200, "text/plain", "Data received. You can close this page.");
}

void WifiHandler::initialize() {
    WiFi.softAP(SSID.c_str(), PASSWORD.c_str());
    IPAddress apIp = WiFi.softAPIP();
    
    m_server.on("/", [this]() { handleRoot(); });
    m_server.on("/submit", [this]() { handleSubmit(); });

    m_server.begin();
    Serial.println("Server started.");
    Serial.println(apIp.toString());
}

void WifiHandler::handle() {
    m_server.handleClient();
}