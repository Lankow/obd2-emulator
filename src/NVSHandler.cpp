/**
 * @file NVSHandler.cpp
 * @date   2025-02-23
 * @author Lankow
 * @version 1.0
 */
#include "NVSHandler.hpp"
#include <nvs_flash.h>

NVSHandler::NVSHandler(std::shared_ptr<OBDHandler> obdHandler) : m_obdHandler(obdHandler), m_preferences() {};

void NVSHandler::initialize()
{
    if (!customSettingsExist())
    {
    }
}

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
