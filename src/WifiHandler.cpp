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
    uint16_t minSpeed = 0;
    uint16_t maxSpeed = 255;

    uint16_t minRpm = 0;
    uint16_t maxRpm = 10000;

    std::string dynamicWebpage = R"rawliteral(
        <!DOCTYPE html>
        <html>
        <body>
            <h1>Configure OBD2 Emulator</h1>
            <form action="/submit" method="get">
                <label for="minSpeed">Min Speed:</label>
                <input type="text" id="minSpeed" name="minSpeed" value=")rawliteral" +
                                 std::to_string(minSpeed) + R"rawliteral("><br>
                <label for="maxSpeed">Max Speed:</label>
                <input type="text" id="maxSpeed" name="maxSpeed" value=")rawliteral" +
                                 std::to_string(maxSpeed) + R"rawliteral("><br>
                <input type="submit" value="Submit">
                <hr/>
                <label for="minRpm">Min RPM:</label>
                <input type="text" id="minRpm" name="minRpm" value=")rawliteral" +
                                 std::to_string(minRpm) + R"rawliteral("><br>
                <label for="maxRpm">Max RPM:</label>
                <input type="text" id="maxRpm" name="maxRpm" value=")rawliteral" +
                                 std::to_string(maxRpm) + R"rawliteral("><br>
                <input type="submit" value="Submit">
            </form>
        </body>
        </html>
    )rawliteral";

    m_server.send(200, "text/html", dynamicWebpage.c_str());
}

void WifiHandler::handleSubmit()
{
    uint16_t minSpeed = std::stoi(m_server.arg("minSpeed").c_str());;
    uint16_t maxSpeed = std::stoi(m_server.arg("maxSpeed").c_str());;
    
    uint16_t minRpm = std::stoi(m_server.arg("minRpm").c_str());;
    uint16_t maxRpm = std::stoi(m_server.arg("maxRpm").c_str());;
    
    Serial.println("Min Speed: " + minSpeed);
    Serial.println("Max Speed: " + maxSpeed);
    Serial.println("Min RPM: " + minRpm);
    Serial.println("Max RPM: " + maxRpm);

    m_server.send(200, "text/plain", "Data received. You can close this page.");
}

void WifiHandler::initialize()
{
    WiFi.softAP(Config::SSID.c_str(), Config::PASSWORD.c_str());
    IPAddress apIp = WiFi.softAPIP();

    m_server.on("/", [this]()
                { handleRoot(); });
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