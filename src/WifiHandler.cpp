/**
 * @file WifiHandler.cpp
 * @date   2025-01-05
 * @author Lankow
 * @version 1.0
 */
#include "WifiHandler.hpp"

const std::string SSID = "config_plant_master";
const std::string PASSWORD = "plantmaster";
constexpr uint16_t SERVER_PORT = 80;

const char webpage[] PROGMEM = R"rawliteral(
    <!DOCTYPE html>
    <html>
    <body>
        <h1>Configure OBD2 Emulator</h1>
        <form action="/submit" method="get">
            <label for="minSpeed">Min Speed:</label>
            <input type="text" id="minSpeed" name="minSpeed"><br>
            <label for="maxSpeed">Max Speed:</label>
            <input type="text" id="maxSpeed" name="maxSpeed"><br>
            <input type="submit" value="Submit">
        </form>
    </body>
    </html>
)rawliteral";


WifiHandler::WifiHandler() : m_server(SERVER_PORT) {}

void WifiHandler::handleRoot() {
    m_server.send_P(200, "text/html", webpage);
}

void WifiHandler::handleSubmit() {
    String minSpeed = m_server.arg("minSpeed");
    String maxSpeed = m_server.arg("maxSpeed");

    Serial.println("Min Speed: " + minSpeed);
    Serial.println("Max Speed: " + maxSpeed);

    m_server.send(200, "text/plain", "Data received. You can close this page.");
}

void WifiHandler::initialize() {
    WiFi.softAP(SSID.c_str(), PASSWORD.c_str());

    m_server.on("/", handleRoot);
    m_server.on("/submit", handleSubmit);
    m_server.begin();
    Serial.println("Server started.");
}
