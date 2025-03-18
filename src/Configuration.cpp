/**
 * @file Configuration.cpp
 * @date 2025-02-20
 * @author Lankow
 * @version 1.0
 */
#include "Configuration.hpp"
#include "FileSystemManager.hpp"

const std::string CONFIG_FILE_NAME = "/config.json";

Configuration::Configuration()
{
    Serial.println("Configuration: Initialization Started...");
    if (FileSystemManager::initFS())
    {
        if (loadConfig())
        {
            printConfig();
            Serial.println("Configuration: Initialization Finished!");
        }
    }
};

bool Configuration::loadConfig()
{
    std::string jsonStr = FileSystemManager::readFile(CONFIG_FILE_NAME.c_str());
    if (jsonStr.empty())
    {
        // TODO: Copy Default Config
        Serial.println("Configuration: Config File not found.");
        return false;
    }

    DynamicJsonDocument doc(1024);
    DeserializationError error = deserializeJson(doc, jsonStr);
    if (error)
    {
        Serial.println("Configuration: Config File deserialization Error!");
        return false;
    }

    parseJson(doc);
    return true;
}

bool Configuration::saveConfig()
{
    Serial.println("Configuration: Saving config file.");
    DynamicJsonDocument doc(1024);
    doc["ssid"] = m_ssid;
    doc["password"] = m_password;
    doc["cycleTime"] = m_cycleTime;
    doc["additionalDebug"] = m_additionalDebug;

    JsonArray obdArray = doc.createNestedArray("obdInfo");
    for (const auto &obd : m_obdInfoList)
    {
        JsonObject obj = obdArray.createNestedObject();
        obj["pid"] = obd.m_pid;
        obj["length"] = obd.m_length;
        obj["description"] = obd.m_description;
        obj["defaultMin"] = obd.m_defaultMin;
        obj["min"] = obd.m_min;
        obj["defaultMax"] = obd.m_defaultMax;
        obj["increment"] = obd.m_increment;
        obj["pace"] = obd.m_pace;
    }

    std::string jsonStr;
    serializeJson(doc, jsonStr);
    if (FileSystemManager::writeFile(CONFIG_FILE_NAME.c_str(), jsonStr))
    {
        printConfig();
        Serial.println("Configuration: Saving config file SUCCESS.");
        return true;
    }

    Serial.println("Configuration: Saving config file FAILED.");
    return false;
}

void Configuration::printConfig()
{
    Serial.print("SSID: ");
    Serial.println(m_ssid.c_str());
    Serial.print("Password: ");
    Serial.println(m_password.c_str());
    Serial.print("Cycle Time: ");
    Serial.println(m_cycleTime);
    Serial.print("Additional Debug: ");
    Serial.println(m_additionalDebug ? "ENABLED" : "DISABLED");
    Serial.print("Amount of OBD Infos: ");
    Serial.println(m_obdInfoList.size());
}

void Configuration::parseJson(DynamicJsonDocument &doc)
{
    Serial.println("Configuration: Parsing config JSON file started.");
    m_ssid = doc["ssid"].as<std::string>();
    m_password = doc["password"].as<std::string>();
    m_cycleTime = doc["cycleTime"];
    m_additionalDebug = doc["additionalDebug"];

    JsonArray obdArray = doc["obdInfo"].as<JsonArray>();
    m_obdInfoList.clear();

    for (JsonVariant v : obdArray)
    {
        OBDInfo obd;
        obd.m_pid = v["pid"];
        obd.m_length = v["length"];
        obd.m_description = v["description"].as<std::string>();
        obd.m_defaultMin = v["defaultMin"];
        obd.m_min = v["min"];
        obd.m_defaultMax = v["defaultMax"];
        obd.m_max = v["max"];
        obd.m_increment = v["increment"];
        obd.m_pace = v["pace"];
        m_obdInfoList.push_back(obd);
    }
    Serial.println("Configuration: Parsing config JSON file finished.");
}

uint32_t Configuration::getCycleTime() const { return m_cycleTime; };
std::string Configuration::getSSID() const { return m_ssid; };
std::string Configuration::getPassword() const { return m_password; };
bool Configuration::getAdditionalDebug() const { return m_additionalDebug; };
std::vector<OBDInfo> &Configuration::getObdInfoList() { return m_obdInfoList; }
void Configuration::setAdditionalDebug(bool isAdditionalDebug) { m_additionalDebug = isAdditionalDebug; }