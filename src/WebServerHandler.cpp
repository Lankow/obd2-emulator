/**
 * @file WebServerHandler.cpp
 * @date   2025-01-05
 * @author Lankow
 * @version 1.0
 */
#include <vector>
#include "WebServerHandler.hpp"
#include "Constants.hpp"
#include "PageGenerator.hpp"
#include "OBDInfo.hpp"
#include "Configurator.hpp"
#include "StringUtils.hpp"

WebServerHandler::WebServerHandler(std::shared_ptr<OBDHandler> obdHandler, std::shared_ptr<NVSHandler> nvsHandler)
    : m_obdHandler(obdHandler), m_nvsHandler(nvsHandler), m_server(Config::SERVER_PORT) {}

void WebServerHandler::cyclic()
{
    m_server.handleClient();
}

void WebServerHandler::handleRoot()
{
    std::vector<OBDInfo> infos = m_obdHandler->getAll();
    std::string mainPageHtml = PageGenerator::getMainPage(infos);
    m_server.send(200, "text/html", mainPageHtml.c_str());
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
        handleError(400, "Edit Page is Missing PID parameter.");
        return;
    }

    std::string pidStr = m_server.arg("pid").c_str();

    if (!StringUtils::isDecimalNumber(pidStr))
    {
        handleError(400, "Invalid PID argument.");
        return;
    };

    uint16_t pid = std::stoi(pidStr);
    const auto *entry = m_obdHandler->getByPid(pid);

    if (entry != nullptr)
    {
        std::string editPageHtml = PageGenerator::getEditPage(*entry);
        m_server.send(200, "text/html", editPageHtml.c_str());
    }
    else
    {
        handleError(400, "PID to edit not available.");
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
        m_nvsHandler->writeSetting("min" + std::to_string(entry->m_pid), minValue);

        entry->m_max = maxValue;
        m_nvsHandler->writeSetting("max" + std::to_string(entry->m_pid), maxValue);

        entry->m_increment = increment;
        m_nvsHandler->writeSetting("inc" + std::to_string(entry->m_pid), increment);

        entry->m_pace = pace;
        m_nvsHandler->writeSetting("pac" + std::to_string(entry->m_pid), pace);

        std::string confirmPageHtml = PageGenerator::getConfirmPage("Object has been edited.");
        m_server.send(200, "text/html", confirmPageHtml.c_str());
    }
    else
    {
        handleError(400, "PID to edit not available.");
    }
}

void WebServerHandler::handleSettings()
{
    if (!m_server.hasArg("update"))
    {
        std::string settingsPageHtml = PageGenerator::getSettingsPage();
        m_server.send(200, "text/html", settingsPageHtml.c_str());
    }
    else
    {
        std::string arg = m_server.arg("update").c_str();
        std::string confirmPageHtml;
        if (arg == "reset")
        {
            confirmPageHtml = PageGenerator::getConfirmPage("Factory reset Performed. Reconnect to a device.");
            m_nvsHandler->formatNVS();
        }
        else if (arg == "logging")
        {
            confirmPageHtml = PageGenerator::getConfirmPage("Logging has been updated.");
            Configurator::toggleAdditionalLogging();
        }
        else
        {
            handleError(400, "No such setting available.");
            return;
        }
        m_server.send(200, "text/html", confirmPageHtml.c_str());
    }
}
// TODO: Handle Error codes
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
                        { handleError(404, "Page not Found."); });

    m_server.begin();
}
