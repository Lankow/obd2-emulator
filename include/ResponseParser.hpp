/**
 * @file ResponseParser.hpp
 * @date   2025-02-03
 * @author Lankow
 * @version 1.0
 */
#ifndef RESPONSE_PARSER_HPP
#define RESPONSE_PARSER_HPP
#include <Arduino.h>

class ResponseParser
{
public:
    static uint16_t parseRequest(const std::string &response);
    static std::string prepareResponse(uint32_t value, uint8_t size);
};
#endif // RESPONSE_PARSER_HPP