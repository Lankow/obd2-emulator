/**
 * @file WebServerHandler.cpp
 * @date   2025-01-05
 * @author Lankow
 * @version 1.0
 */
#include <vector>
#include "WebServerHandler.hpp"
#include "PageGenerator.hpp"
#include "OBDInfo.hpp"
#include "StringUtils.hpp"

constexpr uint16_t SERVER_PORT = 80;

namespace HttpCode
{
    constexpr int OK = 200;
    constexpr int ACCEPTED = 202;
    constexpr int BAD_REQUEST = 400;
    constexpr int NOT_FOUND = 404;
    constexpr int NOT_ACCEPTABLE = 406;
}

WebServerHandler::WebServerHandler(std::shared_ptr<OBDHandler> obdHandler,
                                   std::shared_ptr<Configuration> configuration)
    : m_obdHandler(obdHandler),
      m_server(SERVER_PORT),
      m_configuration(configuration) {}

void WebServerHandler::cyclic()
{
    m_server.handleClient();
}

void WebServerHandler::handleRoot()
{
    std::vector<OBDInfo> infos = m_obdHandler->getAll();
    std::string mainPageHtml = PageGenerator::getMainPage(infos);
    m_server.send(HttpCode::OK, "text/html", mainPageHtml.c_str());
}

void WebServerHandler::handleError(int errorCode, const std::string &errorMessage)
{
    std::string errorPageHtml = PageGenerator::getErrorPage(errorMessage);
    m_server.send(errorCode, "text/html", errorPageHtml.c_str());
}

void WebServerHandler::handleEdit()
{
    if (!m_server.hasArg("pid"))
    {
        handleError(HttpCode::BAD_REQUEST, "Edit Page is Missing PID parameter.");
        return;
    }

    std::string pidStr = m_server.arg("pid").c_str();

    if (!StringUtils::isDecimalNumber(pidStr))
    {
        handleError(HttpCode::NOT_ACCEPTABLE, "Invalid PID argument.");
        return;
    };

    uint16_t pid = std::stoi(pidStr);
    const auto *entry = m_obdHandler->getByPid(pid);

    if (entry != nullptr)
    {
        std::string editPageHtml = PageGenerator::getEditPage(*entry);
        m_server.send(HttpCode::OK, "text/html", editPageHtml.c_str());
    }
    else
    {
        handleError(HttpCode::BAD_REQUEST, "PID to edit not available.");
    }
}

void WebServerHandler::handleSubmit()
{
    uint16_t pid = std::stoi(m_server.arg("pid").c_str());
    double minValue = std::stod(m_server.arg("minValue").c_str());
    double maxValue = std::stod(m_server.arg("maxValue").c_str());
    double increment = std::stod(m_server.arg("increment").c_str());
    uint64_t pace = std::stoi(m_server.arg("pace").c_str());

    auto entry = m_obdHandler->getByPid(pid);
    if (entry != nullptr)
    {
        entry->m_min = minValue;
        entry->m_max = maxValue;
        entry->m_increment = increment;
        entry->m_pace = pace;
        m_configuration->saveConfig();
        
        std::string confirmPageHtml = PageGenerator::getConfirmPage("Object has been edited.");
        m_server.send(HttpCode::ACCEPTED, "text/html", confirmPageHtml.c_str());
    }
    else
    {
        handleError(HttpCode::BAD_REQUEST, "PID to edit not available.");
    }
}

void WebServerHandler::handleSettings()
{
    if (!m_server.hasArg("update"))
    {
        std::string settingsPageHtml = PageGenerator::getSettingsPage();
        m_server.send(HttpCode::OK, "text/html", settingsPageHtml.c_str());
    }
    else
    {
        std::string arg = m_server.arg("update").c_str();
        std::string confirmPageHtml;
        if (arg == "reset")
        {
            confirmPageHtml = PageGenerator::getConfirmPage("Factory reset Performed. Reconnect to a device.");
        }
        else if (arg == "logging")
        {
            confirmPageHtml = PageGenerator::getConfirmPage("Logging has been updated.");
            m_configuration->setAdditionalDebug(!m_configuration->getAdditionalDebug());
        }
        else
        {
            handleError(HttpCode::BAD_REQUEST, "No such setting available.");
            return;
        }
        m_server.send(HttpCode::ACCEPTED, "text/html", confirmPageHtml.c_str());
    }
}

void WebServerHandler::initialize()
{
    m_server.on("/", [this]()
                { handleRoot(); });
    m_server.on("/edit", [this]()
                { handleEdit(); });
    m_server.on("/submit", [this]()
                { handleSubmit(); });
    m_server.on("/settings", [this]()
                { handleSettings(); });
    m_server.onNotFound([this]()
                        { handleError(HttpCode::NOT_FOUND, "Page not Found."); });

    m_server.begin();
}
