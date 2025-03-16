/**
 * @file WebServerHandler.hpp
 * @date   2025-01-05
 * @author Lankow
 * @version 1.0
 */
#ifndef WEB_SERVER_HANDLER_HPP
#define WEB_SERVER_HANDLER_HPP

#include <Arduino.h>
#include <WebServer.h>
#include <memory>
#include "OBDHandler.hpp"
#include "FileSystemManager.hpp"
#include "Configuration.hpp"

class WebServerHandler
{
public:
    WebServerHandler(std::shared_ptr<OBDHandler> obdHandler,
                     std::shared_ptr<Configuration> configuration);

    void initialize();
    void cyclic();

private:
    std::shared_ptr<OBDHandler> m_obdHandler;
    std::shared_ptr<Configuration> m_configuration;
    WebServer m_server;
    IPAddress m_apIP;

    void handleRoot();
    void handleEdit();
    void handleSubmit();
    void handleSettings();
    void handleError(int errorCode, const std::string &errorMessage);
};
#endif // WEB_SERVER_HANDLER_HPP