/**
 * @file PageGenerator.hpp
 * @date   2025-02-08
 * @author Lankow
 * @version 1.0
 */
#ifndef PAGE_GENERATOR_HPP
#define PAGE_GENERATOR_HPP
#include <Arduino.h>
#include "ObdInfo.hpp"

class PageGenerator
{
public:
    static std::string getMainPage(const std::vector<ObdInfo> &infos);
    static std::string getEditPage(const ObdInfo &info);
    static std::string getErrorPage(const std::string &errorMessage);
    static std::string getResetPage();
    static std::string getResetConfirmPage();

private:
    static std::string getHeader();
    static std::string getCss();
};
#endif // PAGE_GENERATOR_HPP