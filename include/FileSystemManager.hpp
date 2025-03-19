/**
 * @file FileSystemManager.hpp
 * @date   2025-02-23
 * @author Lankow
 * @version 1.0
 */
#ifndef FILE_SYSTEM_MANAGER_HPP
#define FILE_SYSTEM_MANAGER_HPP
#include <Arduino.h>

class FileSystemManager
{
public:
    static bool initFS();
    static std::string readFile(const std::string &path);
    static bool copyFile(const std::string &path, const std::string &copyPath);
    static bool writeFile(const std::string &path, const std::string &data);
};
#endif // FILE_SYSTEM_MANAGER_HPP