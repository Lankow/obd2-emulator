/**
 * @file ResponseParser.cpp
 * @date   2025-02-03
 * @author Lankow
 * @version 1.0
 */
#include <sstream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include "ResponseParser.hpp"
#include "Constants.hpp"

uint16_t ResponseParser::parseRequest(const std::string &response) {
    
    std::stringstream ss(response);
    uint16_t result = 0;
    int byteValue = 0;
    int byteCount = 0;
    
    while (ss >> std::ws >> std::hex >> byteValue) {
        if (byteValue > 0xFF) return OBDRequest::DEFAULT_VALUE;
        result = (result << 8) | (byteValue & 0xFF);
        byteCount++;
        if (byteCount > 2) return OBDRequest::DEFAULT_VALUE;
    }
    return (byteCount == 2) ? result : OBDRequest::DEFAULT_VALUE;
}
std::string ResponseParser::prepareResponse(uint32_t value, uint8_t size) {
    std::ostringstream stream;
    std::vector<uint8_t> bytes;
    
    for (int i = 0; i < size; ++i) {
        bytes.push_back((value >> ((size - 1 - i) * 8)) & 0xFF);
    }
    
    stream << std::hex << std::uppercase << std::setfill('0');
    for (size_t i = 0; i < bytes.size(); ++i) {
        if (i > 0) stream << " ";
        stream << std::setw(2) << static_cast<int>(bytes[i]);
    }
    
    return stream.str();
}