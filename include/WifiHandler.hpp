/**
 * @file WifiHandler.hpp
 * @date   2025-01-05
 * @author Lankow
 * @version 1.0
 */
#ifndef WIFI_HANDLER_HPP
#define WIFI_HANDLER_HPP

#include <Arduino.h>
#include <WebServer.h>
#include <memory>
#include "OBDHandler.hpp"

class WifiHandler
{
public:
    WifiHandler(std::shared_ptr<OBDHandler> obdHandler);

    void initialize();
    void cyclic();

private:
    std::shared_ptr<OBDHandler> m_obdHandler;
    WebServer m_server;
    IPAddress m_apIP;

    void handleRoot();
    void handleEdit();
    void handleSubmit();
    void handleReset();
    void handleError(int errorCode, const std::string &errorMessage);
};
#endif // WIFI_HANDLER_HPP