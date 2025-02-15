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
#include "ObdManager.hpp"

class WifiHandler
{
public:
    WifiHandler(std::shared_ptr<ObdManager> manager);

    void initialize();
    void handle();

private:
    std::shared_ptr<ObdManager> m_manager;
    WebServer m_server;
    IPAddress m_apIP;

    void handleRoot();
    void handleEdit();
    void handleSubmit();
    void handleError(int errorCode, const std::string &errorMessage);
};
#endif // WIFI_HANDLER_HPP