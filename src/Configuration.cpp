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
    Serial.println("Configuration Init - START");
    if (FileSystemManager::initFS())
    {
        loadConfig();
        Serial.println("Configuration Init - FINISH");
    }
};

bool Configuration::loadConfig()
{
    std::string jsonStr = FileSystemManager::readFile(CONFIG_FILE_NAME.c_str());
    if (jsonStr.empty())
    {
        Serial.println("Configuration file not found!");
        return false;
    }

    DynamicJsonDocument doc(1024);
    DeserializationError error = deserializeJson(doc, jsonStr);
    if (error)
    {
        Serial.println("Configuration file deserialization error!");
        return false;
    }

    parseJson(doc);
    return true;
}

bool Configuration::saveConfig()
{
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
    return FileSystemManager::writeFile(CONFIG_FILE_NAME.c_str(), jsonStr);
}

void Configuration::parseJson(DynamicJsonDocument &doc)
{
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
}

uint32_t Configuration::getCycleTime() const { return m_cycleTime; };
std::string Configuration::getSSID() const { return m_ssid; };
std::string Configuration::getPassword() const { return m_password; };
bool Configuration::getAdditionalDebug() const { return m_additionalDebug; };
std::vector<OBDInfo> &Configuration::getObdInfoList() { return m_obdInfoList; }
void Configuration::setAdditionalDebug(bool isAdditionalDebug) { m_additionalDebug = isAdditionalDebug; }