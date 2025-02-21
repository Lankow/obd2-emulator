/**
 * @file StaticRespHandler.hpp
 * @date 2025-02-14
 * @author Lankow
 * @version 1.0
 */
#ifndef STATIC_RESP_HANDLER_HPP
#define STATIC_RESP_HANDLER_HPP
#include <map>

class StaticRespHandler
{
public:
    StaticRespHandler();
    std::string getResponse(const std::string &request) const;

private:
    std::map<std::string, std::string> m_requestResponses;
};
#endif // STATIC_RESP_HANDLER_HPP