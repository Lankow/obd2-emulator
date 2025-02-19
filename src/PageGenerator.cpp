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
    std::string pageContent = getHeader() + R"rawliteral(
        <body>
            <div class="container">
                <h1>OBD2 Emulator Configuration</h1>
    )rawliteral";

    if (infos.empty())
    {
        pageContent += "<p class='error-box'>NO PIDs available to edit.</p>";
    }
    else
    {
        pageContent += "<ul>";
        for (auto info : infos)
        {
            std::stringstream hexPid;
            hexPid << "0x" << std::uppercase << std::hex << info.getPid();
            pageContent += "<li><a class='button' href=\"/edit?pid=" + std::to_string(info.getPid()) + "\">Edit " + info.getDescription() + " - " + hexPid.str() + "</a></li>";
        }
        pageContent += "</ul>";
    }

    pageContent += R"rawliteral(
            </div>
        </body>
        </html>
    )rawliteral";

    return pageContent;
}

std::string PageGenerator::getEditPage(const OBDInfo &info)
{
    std::stringstream hexPid;
    hexPid << "0x" << std::uppercase << std::hex << static_cast<int>(info.getPid());

    return getHeader() + R"rawliteral(
        <body>
            <div class="container">
                <h1>Edit )rawliteral" +
           info.getDescription() + " - " + hexPid.str() + R"rawliteral( PID Values</h1>
                <form action="/submit" method="post">
                    <input type="hidden" id="pid" name="pid" value=")rawliteral" +
           std::to_string(info.getPid()) + R"rawliteral(">
                    <label for="minValue">Min Value:</label>
                    <input type="number" id="minValue" name="minValue" value=")rawliteral" +
           std::to_string(info.getMin()) + R"rawliteral(" min=")rawliteral" +
           std::to_string(info.getDefaultMin()) + R"rawliteral(" max=")rawliteral" +
           std::to_string(info.getDefaultMax()) + R"rawliteral(" required>
                    <label for="maxValue">Max Value:</label>
                    <input type="number" id="maxValue" name="maxValue" value=")rawliteral" +
           std::to_string(info.getMax()) + R"rawliteral(" min=")rawliteral" +
           std::to_string(info.getDefaultMin()) + R"rawliteral(" max=")rawliteral" +
           std::to_string(info.getDefaultMax()) + R"rawliteral(" required>
                    <label for="increment">Increment Value:</label>
                    <input type="number" id="increment" name="increment" value=")rawliteral" +
           std::to_string(info.getIncrement()) + R"rawliteral(" min=")rawliteral" +
           std::to_string(info.getDefaultMin()) + R"rawliteral(" max=")rawliteral" +
           std::to_string(info.getDefaultMax()) + R"rawliteral(" required>
                    <label for="pace">Increment Pace:</label>
                    <input type="number" id="pace" name="pace" value=")rawliteral" +
           std::to_string(info.getPace()) + R"rawliteral(" min="0" required>
                    <div class="button-container">
                        <input type="submit" value="Update">
                        <a class="button" href="/">Back</a>
                    </div>
                </form>
            </div>
        </body>
        </html>
    )rawliteral";
}

std::string PageGenerator::getErrorPage(const std::string &errorMessage)
{
    return getHeader() + R"rawliteral(
        <body>
            <div class="container">
                <div class="error-box">
                    <h1>ERROR</h1>
                    <p>)rawliteral" +
           errorMessage + R"rawliteral(</p>
                </div>
                <a class="button" href="/">Go to Main Page</a>
            </div>
        </body>
        </html>
    )rawliteral";
}

std::string PageGenerator::getResetPage()
{
    // TODO: Return confirmation or perform reset page
    return "";
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
