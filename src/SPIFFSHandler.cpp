/**
 * @file SPIFFSHandler.cpp
 * @date   2025-02-23
 * @author Lankow
 * @version 1.0
 */
#include <SPIFFS.h>
#include "SPIFFSHandler.hpp"

const std::string CONFIG_FILENAME = "/config.json";

SPIFFSHandler::SPIFFSHandler() : m_initialized(false)
{
    initialize();
};

void SPIFFSHandler::initialize()
{
    if (initializeSPIFFS() && configExists())
    {
        m_initialized = true;
    }
}

std::string SPIFFSHandler::loadConfigFile()
{
    if (!m_initialized)
    {
        Serial.println("Config Load FAILED - SPIFFS handler not initialized.");
        return;
    }

    File file = SPIFFS.open(CONFIG_FILENAME.c_str());
    String fileText = "";

    while (file.available())
    {
        fileText = file.readString();
    }

    file.close();
    return fileText.c_str();
};

void SPIFFSHandler::saveConfigFile(std::string &configStr)
{
    if (!m_initialized)
    {
        Serial.println("Config Save FAILED - SPIFFS handler not initialized.");
        return;
    }

    File file = SPIFFS.open(CONFIG_FILENAME.c_str(), FILE_WRITE);
    if (!file)
    {
        Serial.println("Failed to open config file.");
        return;
    }
    if (file.print(configStr.c_str()))
    {
        Serial.println("Config saved to SPIFFS.");
    }
    else
    {
        Serial.println("Config save to SPIFFS FAILED.");
    }
    file.close();
};

bool SPIFFSHandler::initializeSPIFFS()
{
    if (!SPIFFS.begin(false))
    {
        Serial.println("SPIFFS Mount Failed.");
        return false;
    }

    return true;
};

bool SPIFFSHandler::configExists()
{
    File file = SPIFFS.open(CONFIG_FILENAME.c_str());
    bool result = true;

    if (!file || file.isDirectory())
    {
        Serial.println("Failed to open config file for reading.");
        return false;
    }

    file.close();
    return result;
};
