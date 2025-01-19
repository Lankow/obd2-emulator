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
#include "OBD2PIDManager.hpp"

class WifiHandler
{
    public:
        WifiHandler(std::shared_ptr<OBD2PIDManager> manager);

        void initialize();
        void handle();

    private:
        std::shared_ptr<OBD2PIDManager> m_manager;
        WebServer m_server;
        IPAddress m_apIP;

        void handleRoot();
        void handleSubmit();
};
#endif // WIFI_HANDLER_HPP