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
    Serial.println("FileSystemManager: Initialization Started...");

    if (!SPIFFS.begin(true))
    {
        Serial.println("FileSystemManager: Initialization Failed!!!");
        return false;
    }

    Serial.println("FileSystemManager: Initialization Finished!");
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

bool FileSystemManager::copyFile(const std::string &path, const std::string &copyPath)
{
    Serial.print("FileSystemManager: Started copying file from ");
    Serial.print(path.c_str());
    Serial.print(" to ");
    Serial.println(copyPath.c_str());

    File sourceFile = SPIFFS.open(path.c_str(), "r");
    if (!sourceFile)
    {
        Serial.println("FileSystemManager: Source file not found.");
        return false;
    }

    if (SPIFFS.exists(copyPath.c_str()))
    {
        Serial.println("FileSystemManager: Destination file exists. Removing it...");
        if (!SPIFFS.remove(copyPath.c_str()))
        {
            Serial.println("FileSystemManager: Failed to remove existing destination file.");
            sourceFile.close();
            return false;
        }
    }

    File destFile = SPIFFS.open(copyPath.c_str(), "w");
    if (!destFile)
    {
        Serial.println("FileSystemManager: Failed to create destination file.");
        sourceFile.close();
        return false;
    }

    while (sourceFile.available())
    {
        destFile.write(sourceFile.read());
    }

    sourceFile.close();
    destFile.close();

    Serial.println("FileSystemManager: File copy completed successfully.");
    return true;
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