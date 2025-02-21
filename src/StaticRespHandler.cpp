/**
 * @file StaticRespHandler.cpp
 * @date 2025-02-14
 * @author Lankow
 * @version 1.0
 */
#include "StaticRespHandler.hpp"

StaticRespHandler::StaticRespHandler()
{
    m_requestResponses["VER"] = "OBD2EMULATOR 1.0.0";
};

std::string StaticRespHandler::getResponse(const std::string &request) const
{
    if (m_requestResponses.find(request) != m_requestResponses.end())
    {
        return m_requestResponses.at(request);
    }
    
    return "";
};
