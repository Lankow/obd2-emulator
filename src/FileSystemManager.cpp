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
    Serial.println("FileSystemManager: Initialization Started.");

    if (!SPIFFS.begin(true))
    {
        Serial.println("FileSystemManager: Initialization Failed.");
        return false;
    }

    Serial.println("FileSystemManager: Initialization Finished.");
    return true;
}

std::string FileSystemManager::readFile(const std::string &path)
{
    Serial.print("FileSystemManager: Started reading file: ");
    Serial.println(path.c_str());

    File file = SPIFFS.open(path.c_str(), "r");
    if (!file)
    {
        Serial.println("FileSystemManager: File not found.");
        return "";
    }

    String content;
    while (file.available())
    {
        content += file.readString();
    }
    file.close();
    Serial.println("FileSystemManager: Reading file finished.");
    return content.c_str();
}

bool FileSystemManager::writeFile(const std::string &path, const std::string &data)
{
    Serial.print("FileSystemManager: Started writing file: ");
    Serial.println(path.c_str());
    File file = SPIFFS.open(path.c_str(), "w");
    if (!file)
    {
        Serial.println("FileSystemManager: Writing file Failed.");
        return false;
    }

    file.print(data.c_str());
    file.close();
    Serial.println("FileSystemManager: Writing file Finished.");
    return true;
}