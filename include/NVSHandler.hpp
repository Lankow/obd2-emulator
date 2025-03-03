/**
 * @file NVSHandler.hpp
 * @date   2025-02-23
 * @author Lankow
 * @version 1.0
 */
#ifndef NVS_HANDLER_HPP
#define NVS_HANDLER_HPP
#include <Arduino.h>
#include <Preferences.h>
#include <memory>
#include "OBDHandler.hpp"
class NVSHandler
{
public:
    NVSHandler(std::shared_ptr<OBDHandler> obdHandler);
    void initialize();
    void writeSetting(const std::string &key, double value);
    void formatNVS();

private:
    std::shared_ptr<OBDHandler> m_obdHandler;
    Preferences m_preferences;

    void intializeInfos();
    void initializeNamespace(const std::string &key);
    bool settingsExist();
    void clearSettings();
    template <typename SetterFunc>
    void getNvsToInfo(OBDInfo &info, const std::string &prefix, SetterFunc setter);
};
#endif // NVS_HANDLER_HPP