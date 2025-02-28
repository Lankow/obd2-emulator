/**
 * @file PageGenerator.hpp
 * @date   2025-02-08
 * @author Lankow
 * @version 1.0
 */
#ifndef PAGE_GENERATOR_HPP
#define PAGE_GENERATOR_HPP

#include <Arduino.h>
#include <vector>
#include "OBDInfo.hpp"

class PageGenerator
{
public:
    static std::string getMainPage(const std::vector<OBDInfo> &infos);
    static std::string getEditPage(const OBDInfo &info);
    static std::string getErrorPage(const std::string &errorMessage);
    static std::string getSettingsPage();
    static std::string getConfirmPage(const std::string &message);

private:
    static std::string getHeader();
    static std::string getCss();
    static std::string wrapContent(const std::string &title, const std::string &bodyContent);
    static std::string generateButton(const std::string &href, const std::string &label, const std::string &extraClass = "");
    static std::string generateInputField(const std::string &id, const std::string &label, double value, double min, double max);
};

#endif // PAGE_GENERATOR_HPP