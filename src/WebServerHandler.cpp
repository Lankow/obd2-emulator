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
    if (m_configuration->getAdditionalDebug())
        Serial.println("WebServerHandler: Cycle Started.");

    m_server.handleClient();

    if (m_configuration->getAdditionalDebug())
        Serial.println("WebServerHandler: Cycle Finished.");
}

void WebServerHandler::handleRoot()
{
    Serial.println("WebServerHandler: Root Requested.");

    std::vector<OBDInfo> infos = m_obdHandler->getAll();
    std::string mainPageHtml = PageGenerator::getMainPage(infos);
    m_server.send(HttpCode::OK, "text/html", mainPageHtml.c_str());
}

void WebServerHandler::handleError(int errorCode, const std::string &errorMessage)
{
    Serial.print("WebServerHandler: Send Error Page: ");
    Serial.println(errorMessage.c_str());

    std::string errorPageHtml = PageGenerator::getErrorPage(errorMessage);
    m_server.send(errorCode, "text/html", errorPageHtml.c_str());
}

void WebServerHandler::handleEdit()
{
    Serial.println("WebServerHandler: Edit Requested.");

    if (!m_server.hasArg("pid"))
    {
        std::string errorMessage = "Edit Page is Missing PID parameter.";
        Serial.print("WebServerHandler: ");
        Serial.println(errorMessage.c_str());

        handleError(HttpCode::BAD_REQUEST, errorMessage);
        return;
    }

    std::string pidStr = m_server.arg("pid").c_str();

    if (!StringUtils::isDecimalNumber(pidStr))
    {
        std::string errorMessage = "Invalid PID argument.";
        Serial.print("WebServerHandler: ");
        Serial.println(errorMessage.c_str());

        handleError(HttpCode::NOT_ACCEPTABLE, errorMessage);
        return;
    };

    uint16_t pid = std::stoi(pidStr);
    const auto *entry = m_obdHandler->getByPid(pid);

    if (entry != nullptr)
    {
        Serial.print("WebServerHandler: Edit Successful!");
        std::string editPageHtml = PageGenerator::getEditPage(*entry);
        m_server.send(HttpCode::OK, "text/html", editPageHtml.c_str());
    }
    else
    {
        std::string errorMessage = "PID to edit not available.";
        Serial.print("WebServerHandler: ");
        Serial.println(errorMessage.c_str());

        handleError(HttpCode::BAD_REQUEST, errorMessage);
    }
}

void WebServerHandler::handleSubmit()
{
    Serial.print("WebServerHandler: Handle Submit.");

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
        std::string errorMessage = "PID to edit not available.";
        Serial.print("WebServerHandler: ");
        Serial.println(errorMessage.c_str());

        handleError(HttpCode::BAD_REQUEST, errorMessage);
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
            if (m_configuration->resetConfig())
            {
                confirmPageHtml = PageGenerator::getConfirmPage("Factory reset Performed. Reconnect to a device.");
                ESP.restart();
            }
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
    Serial.print("WebServerHandler: Initialization Started. ");
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
    Serial.print("WebServerHandler: Initialization Finished. ");
}
