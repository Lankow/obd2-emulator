/**
 * @file JSONHandler.hpp
 * @date   2025-03-11
 * @author Lankow
 * @version 1.0
 */
#ifndef JSON_HANDLER_HPP
#define JSON_HANDLER_HPP
#include <ArduinoJson.h>

class JSONHandler
{
public:
    void loadJson(const std::string &fileName);

private:
    std::string readString(const std::string &key);
    double readDouble(const std::string &key);
    uint16_t readUint16(const std::string &key);

    StaticJsonDocument<1024> m_json;
};

#endif // JSON_HANDLER_HPP