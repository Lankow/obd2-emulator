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

private:
    std::shared_ptr<OBDHandler> m_obdHandler;
    Preferences m_preferences;

    void initializeSettings();
    bool customSettingsExist();
    void clearSettings();
    void formatNVS();
};
#endif // NVS_HANDLER_HPP