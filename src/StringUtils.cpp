/**
 * @file StringUtils.cpp
 * @date   2025-02-03
 * @author Lankow
 * @version 1.0
 */
#include <sstream>
#include <iostream>
#include <iomanip>
#include "StringUtils.hpp"

bool StringUtils::isHeximalNumber(const std::string &str)
{
    return str.size() > 2 && str.find_first_not_of("0123456789abcdefABCDEF") == std::string::npos;
};

bool StringUtils::isDecimalNumber(const std::string &str)
{
    return !str.empty() && std::all_of(str.begin(), str.end(), ::isdigit);
}

uint16_t StringUtils::hexStringToUint16(const std::string &str)
{
    uint16_t result;

    std::stringstream ss;
    ss << std::hex << str;
    ss >> result;

    return result;
}

std::string StringUtils::intToHexString(uint32_t input, uint8_t outputSize)
{
    std::stringstream stream;
    stream << std::setfill('0') << std::setw(outputSize * 2) << std::hex << input;

    std::string result = stream.str();
    result = result.substr(result.size() - outputSize * 2);

    if (outputSize > 1)
    {
        std::string formattedStr;
        for (size_t i = 0; i < result.size(); i += 2)
        {
            if (!formattedStr.empty())
                formattedStr += " ";
            formattedStr += result.substr(i, 2);
        }
        result = formattedStr;
    }

    return result;
}