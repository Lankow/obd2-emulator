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
    std::string serializeConfig();
    void deserializeConfig();

private:
    StaticJsonDocument<512> m_json;
};

#endif // JSON_HANDLER_HPP