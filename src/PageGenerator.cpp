/**
 * @file PageGenerator.cpp
 * @date   2025-01-08
 * @author Lankow
 * @version 1.0
 */
#include <sstream>
#include <iomanip>
#include <vector>
#include "PageGenerator.hpp"

std::string PageGenerator::getMainPage(const std::vector<OBDInfo> &infos)
{
    std::ostringstream page;
    page << (infos.empty() ? "<p class='error-box'>NO PIDs available to edit."
                             "</p>"
                           : "");

    if (!infos.empty())
    {
        page << "<ul>";
        for (const auto &info : infos)
        {
            std::ostringstream hexPid;
            hexPid << "0x" << std::uppercase << std::hex << info.m_pid;
            page << "<li>" << generateButton("/edit?pid=" + std::to_string(info.m_pid), "Edit " + info.m_description + " - " + hexPid.str())
                 << "</li>";
        }
        page << "</ul>";
    }

    page << generateButton("/settings", "Settings");

    return wrapContent("OBD2 Emulator Configuration", page.str());
}

std::string PageGenerator::getEditPage(const OBDInfo &info)
{
    std::ostringstream hexPid;
    hexPid << "0x" << std::uppercase << std::hex << static_cast<int>(info.m_pid);

    std::ostringstream form;
    form << "<form action='/submit' method='post'>"
         << "<input type='hidden' id='pid' name='pid' value='" << info.m_pid << "'>"
         << generateInputField("minValue", "Min Value", info.m_min, info.m_defaultMin, info.m_defaultMax)
         << generateInputField("maxValue", "Max Value", info.m_max, info.m_defaultMin, info.m_defaultMax)
         << generateInputField("increment", "Increment Value", info.m_increment, info.m_defaultMin, info.m_defaultMax)
         << generateInputField("pace", "Increment Pace", info.m_pace, 0, 100)
         << "<div class='button-container'>"
         << "<input type='submit' value='Update'>"
         << generateButton("/", "Back")
         << "</div></form>";

    return wrapContent("Edit " + info.m_description + " - " + hexPid.str() + " PID Values", form.str());
}

std::string PageGenerator::getErrorPage(const std::string &errorMessage)
{
    return wrapContent("ERROR", "<div class='error-box'><p>" + errorMessage + "</p></div>" + generateButton("/", "Go to Main Page"));
}

std::string PageGenerator::getSettingsPage()
{
    std::ostringstream page;
    page << "<ul>";
    page << "<li>" << generateButton("/settings?update=reset", "Factory Reset") << "</li>";
    page << "<li>" << generateButton("/settings?update=logging", "Additional Logging") << "</li>";
    page << "</ul>";
    page << generateButton("/", "Back");

    return wrapContent("Settings", page.str());
}

std::string PageGenerator::getConfirmPage(const std::string &message)
{
    return wrapContent("Confirmation", "<p>" + message + "</p>" + generateButton("/", "Go to Main Page"));
}

std::string PageGenerator::wrapContent(const std::string &title, const std::string &bodyContent)
{
    std::ostringstream page;
    page << getHeader()
         << "<body><div class='container'><h1>" << title << "</h1>"
         << bodyContent
         << "</div></body></html>";
    return page.str();
}

std::string PageGenerator::generateButton(const std::string &href, const std::string &label, const std::string &extraClass)
{
    return "<a class='button " + extraClass + "' href='" + href + "'>" + label + "</a>";
}

std::string PageGenerator::generateInputField(const std::string &id, const std::string &label, double value, double min, double max)
{
    std::ostringstream input;
    input << std::fixed << std::setprecision(2)
          << "<label for='" << id << "'>" << label << ":</label>"
          << "<input type='number' step='0.01' id='" << id << "' name='" << id << "' value='" << value
          << "' min='" << min << "' max='" << max << "' required>";
    return input.str();
}

std::string PageGenerator::getHeader()
{
    return R"rawliteral(
        <!DOCTYPE html>
        <html>
        <head>
            <meta charset="UTF-8">
            <meta name="viewport" content="width=device-width, initial-scale=1.0">
            <title>OBD2 Emulator</title>
            <style>
    )rawliteral" +
           getCss() + R"rawliteral(
            </style>
        </head>
    )rawliteral";
}

std::string PageGenerator::getCss()
{
    return R"rawliteral(
        * {
            box-sizing: border-box;
            margin: 0;
            padding: 0;
            font-family: Arial, sans-serif;
        }

        body {
            background-color: #e3e6e8; /* Soft blue-gray */
            color: #333;
            text-align: center;
            padding: 20px;
        }

        .container {
            max-width: 500px;
            margin: 0 auto;
            background: #ffffff;
            padding: 20px;
            border-radius: 10px;
            box-shadow: 0px 4px 10px rgba(0, 0, 0, 0.1);
        }

        h1 {
            color: #0056b3;
            margin-bottom: 15px;
        }

        ul {
            list-style: none;
            padding: 0;
        }

        li {
            margin: 10px 0;
        }

        a.button {
            display: block;
            padding: 12px;
            background: #28a745; /* Green */
            color: white;
            font-weight: bold;
            border-radius: 5px;
            text-decoration: none;
            text-align: center;
            transition: background 0.3s ease-in-out;
        }

        a.button:hover {
            background: #218838;
        }

        form {
            display: flex;
            flex-direction: column;
            gap: 10px;
            padding: 20px;
            border-radius: 8px;
        }

        label {
            font-weight: bold;
            text-align: left;
            display: block;
            margin-bottom: 5px;
        }

        input[type="number"], input[type="hidden"] {
            width: 100%;
            padding: 10px;
            border: none;
            border-radius: 5px;
            background: #f8f9fa;
            font-size: 16px;
        }

        input:focus {
            outline: 2px solid #007BFF;
        }

        .button-container {
            display: flex;
            justify-content: space-between;
            gap: 10px;
        }

        input[type="submit"], .button {
            flex: 1;
            background: #28a745;
            color: white;
            border: none;
            padding: 12px;
            cursor: pointer;
            font-size: 16px;
            border-radius: 5px;
            text-align: center;
            transition: background 0.3s ease-in-out;
        }

        input[type="submit"]:hover, .button:hover {
            background: #218838;
        }

        .button.gray {
            background: #6c757d;
        }

        .button.gray:hover {
            background: #545b62;
        }

        .error-box {
            background: #ffdddd;
            padding: 20px;
            border-radius: 10px;
            color: #b30000;
            font-weight: bold;
            margin-bottom: 20px;
            border: 1px solid #ff4d4d;
        }
    )rawliteral";
}