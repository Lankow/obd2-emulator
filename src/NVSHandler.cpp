/**
 * @file NVSHandler.cpp
 * @date   2025-02-23
 * @author Lankow
 * @version 1.0
 */
#include "NVSHandler.hpp"
#include <nvs_flash.h>
#include "OBDInfo.hpp"

NVSHandler::NVSHandler(std::shared_ptr<OBDHandler> obdHandler) : m_obdHandler(obdHandler), m_preferences() {};

void NVSHandler::initialize()
{
    if (settingsExist())
    {
        intializeInfos();
    }
}

template <typename SetterFunc>
void NVSHandler::getNvsToInfo(OBDInfo &info, const std::string &prefix, SetterFunc setter)
{
    std::string key = prefix + std::to_string(info.getPid());
    if (m_preferences.isKey(key.c_str()))
    {
        (info.*setter)(m_preferences.getDouble(key.c_str()));
    }
}

void NVSHandler::initializeNamespace(const std::string &key)
{
}

void NVSHandler::intializeInfos()
{
    for (auto &info : m_obdHandler->getAll())
    {
        getNvsToInfo(info, "max", &OBDInfo::setMax);
        getNvsToInfo(info, "min", &OBDInfo::setMin);
        getNvsToInfo(info, "inc", &OBDInfo::setIncrement);
        getNvsToInfo(info, "pac", &OBDInfo::setPace);
    }
};

void NVSHandler::clearSettings()
{
    if (!settingsExist())
    {
        Serial.println("Settings don't exist.");
    }
    else
    {
        m_preferences.clear();
        Serial.println("Settings cleared.");
    }
};

void NVSHandler::formatNVS()
{
    nvs_flash_erase();
    nvs_flash_init();
    delay(100);
    ESP.restart();
};

void NVSHandler::writeSetting(const std::string &key, double value)
{
    m_preferences.begin("settings", false);
    m_preferences.putDouble(key.c_str(), value);
    m_preferences.end();
}

bool NVSHandler::settingsExist()
{
    if (!m_preferences.begin("settings", false))
    {
        Serial.println("Failed to open NVS namespace.");
        return false;
    }

    return true;
}
