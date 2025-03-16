/**
 * @file FileSystemManager.cpp
 * @date   2025-02-23
 * @author Lankow
 * @version 1.0
 */
#include <SPIFFS.h>
#include "FileSystemManager.hpp"

bool FileSystemManager::initFS()
{
    if (!SPIFFS.begin(true))
    {

        Serial.println("SPIFFS Initialization Failed!");
        return false;
    }

    Serial.println("SPIFFS Initialization Success!");
    return true;
}

std::string FileSystemManager::readFile(const std::string &path)
{
    File file = SPIFFS.open(path.c_str(), "r");
    if (!file)
        return "";

    String content;
    while (file.available())
    {
        content += file.readString();
    }
    file.close();
    return content.c_str();
    return "{}";
}

bool FileSystemManager::writeFile(const std::string &path, const std::string &data)
{
    File file = SPIFFS.open(path.c_str(), "w");
    if (!file)
        return false;

    file.print(data.c_str());
    file.close();
    return true;
}