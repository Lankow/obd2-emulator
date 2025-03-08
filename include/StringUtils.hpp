/**
 * @file StringUtils.hpp
 * @date   2025-02-03
 * @author Lankow
 * @version 1.0
 */
#ifndef RESPONSE_PARSER_HPP
#define RESPONSE_PARSER_HPP
#include <Arduino.h>

class StringUtils
{
public:
    static bool isHeximalNumber(const std::string &str);
    static bool isDecimalNumber(const std::string &str);
    static uint16_t hexStringToUint16(const std::string &str);
    static std::string intToHexString(uint32_t input, uint8_t outputSize);
};
#endif // RESPONSE_PARSER_HPP