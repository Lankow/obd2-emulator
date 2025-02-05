/**
 * @file ResponseParser.cpp
 * @date   2025-02-03
 * @author Lankow
 * @version 1.0
 */
#include <sstream>
#include <iostream>
#include <iomanip>
#include "ResponseParser.hpp"
#include "Constants.hpp"

bool ResponseParser::isHexRequest(const std::string &request)
{
    return request.size() > 2 && request.find_first_not_of("0123456789abcdefABCDEF") == std::string::npos;
};

uint16_t ResponseParser::parseRequest(const std::string &request)
{
    uint16_t result = OBDRequest::DEFAULT_VALUE;

    std::stringstream ss;
    ss << std::hex << request;
    ss >> result;

    return result;
}

std::string ResponseParser::prepareResponse(uint32_t value, uint8_t size)
{
    std::stringstream stream;
    stream << std::setfill('0') << std::setw(size * 2) << std::hex << value;

    std::string result = stream.str();
    result = result.substr(result.size() - size * 2);

    if (size > 1)
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