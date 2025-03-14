/**
 * @file SPIFFSHandler.hpp
 * @date   2025-02-23
 * @author Lankow
 * @version 1.0
 */
#ifndef SPIFFS_HANDLER_HPP
#define SPIFFS_HANDLER_HPP
#include <Arduino.h>

class SPIFFSHandler
{
public:
    std::string loadConfigFile();
    void saveConfigFile(std::string &configStr);

private:
    bool m_initialized;
    void initialize();
    bool initializeSPIFFS();
    bool configExists();
};
#endif // SPIFFS_HANDLER_HPP