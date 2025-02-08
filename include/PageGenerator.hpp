/**
 * @file PageGenerator.hpp
 * @date   2025-02-08
 * @author Lankow
 * @version 1.0
 */
#ifndef PAGE_GENERATOR_HPP
#define PAGE_GENERATOR_HPP
#include <Arduino.h>
#include "OBD2PIDInfo.hpp"

class PageGenerator
{
public:
    static std::string getMainPage();
    static std::string getEditPage(uint16_t pid, const IOBD2PIDInfo& info);

private:
    static std::string getHeader();
    static std::string getCss();
};
#endif // PAGE_GENERATOR_HPP