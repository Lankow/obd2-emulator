/**
 * @file StaticRespHandler.cpp
 * @date 2025-02-14
 * @author Lankow
 * @version 1.0
 */
#include "Arduino.h"
#include "StaticRespHandler.hpp"

StaticRespHandler::StaticRespHandler()
{
    m_requestResponses["VER"] = "OBD2EMULATOR 1.0.0";
};

std::string StaticRespHandler::getResponse(const std::string &request) const
{
    Serial.print("StaticRespHandler: Trying to handle request:  ");
    Serial.println(request.c_str());

    if (m_requestResponses.find(request) != m_requestResponses.end())
    {
        Serial.print("StaticRespHandler: Static Response Found!");
        return m_requestResponses.at(request);
    }

    return "";
};
