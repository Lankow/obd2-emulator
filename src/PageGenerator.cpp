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

std::string PageGenerator::getMainPage(const std::vector<uint16_t> &pids)
{
    std::string pageContent = getHeader() + R"rawliteral(
        <body>
            <h1>OBD2 Emulator Configuration</h1>
    )rawliteral";

    if (pids.empty())
    {
        pageContent += "<p>NO PIDs available to edit.</p>";
    }
    else
    {
        pageContent += "<ul>";
        for (uint16_t pid : pids)
        {
            std::stringstream hexPid;
            hexPid << "0x" << std::uppercase << std::hex << pid;
            pageContent += "<li><a href=\"/edit?pid=" + std::to_string(pid) + "\">Edit " + hexPid.str() + "</a></li>";
        }
        pageContent += "</ul>";
    }

    pageContent += R"rawliteral(
        </body>
        </html>
    )rawliteral";

    return pageContent;
}

std::string PageGenerator::getEditPage(uint16_t pid, const IOBD2PIDInfo &info)
{
    //TODO: Bug with wrong PID on Edit Page
    std::stringstream hexPid;
    hexPid << "0x" << std::uppercase << std::hex << pid;

    return getHeader() + R"rawliteral(
        <body>
            <h1>Edit )rawliteral" +
           hexPid.str() + R"rawliteral( PID Values</h1>
            <form action="/submit" method="post">
                <input type="hidden" id="pid" name="pid" value=")rawliteral" +
           std::to_string(pid) + R"rawliteral(">
                <label for="minValue">Min Value:</label>
                <input type="text" id="minValue" name="minValue" value=")rawliteral" +
           std::to_string(info.getMinAsDouble()) + R"rawliteral("><br>
                <label for="maxValue">Max Value:</label>
                <input type="text" id="maxValue" name="maxValue" value=")rawliteral" +
           std::to_string(info.getMaxAsDouble()) + R"rawliteral("><br>
                <input type="submit" value="Update">
            </form>
        </body>
        </html>
    )rawliteral";
}

std::string PageGenerator::getErrorPage(const std::string &errorMessage)
{
    return getHeader() + R"rawliteral(
        <body>
            <h1>ERROR: )rawliteral" +
           errorMessage.c_str() + R"rawliteral(</h1>
            <a href="/">
                <button>Go to Main Page</button>
            </a>
        </body>
        </html>
    )rawliteral";
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
        body { font-family: Arial, sans-serif; text-align: center; padding: 20px; }
        form { display: inline-block; text-align: left; background: #f4f4f4; padding: 15px; border-radius: 8px; }
        input { display: block; width: 100%; margin: 10px 0; padding: 5px; }
        input[type="submit"] { background: #4CAF50; color: white; border: none; padding: 10px; cursor: pointer; }
        input[type="submit"]:hover { background: #45a049; }
    )rawliteral";
}
