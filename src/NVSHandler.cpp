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
    if (customSettingsExist())
    {
        initializeSettings();
    }
}

void NVSHandler::initializeSettings()
{
    for (auto &info : m_obdHandler->getAll())
    {
        std::string maxKey = "max" + std::to_string(info.getPid());
        std::string minKey = "min" + std::to_string(info.getPid());
        std::string paceKey = "pac" + std::to_string(info.getPid());
        std::string incrementKey = "inc" + std::to_string(info.getPid());

        if (m_preferences.isKey(maxKey.c_str()))
        {
            info.setMax(m_preferences.getDouble(maxKey.c_str()));
        };

        if (m_preferences.isKey(minKey.c_str()))
        {
            info.setMin(m_preferences.getDouble(minKey.c_str()));
        };

        if (m_preferences.isKey(incrementKey.c_str()))
        {
            info.setIncrement(m_preferences.getDouble(incrementKey.c_str()));
        };

        if (m_preferences.isKey(paceKey.c_str()))
        {
            info.setPace(m_preferences.getLong64(paceKey.c_str()));
        };
    }
};

bool NVSHandler::customSettingsExist()
{
    if (!m_preferences.begin("settings", true))
    {
        Serial.println("Failed to open NVS namespace.");
        return false;
    }

    return true;
}

void NVSHandler::clearSettings()
{
    if (!customSettingsExist())
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
};
