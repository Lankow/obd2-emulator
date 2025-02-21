/**
 * @file BtHandler.cpp
 * @date   2025-01-04
 * @author Lankow
 * @version 1.0
 */

#include "BtHandler.hpp"
#include "OBDInfo.hpp"
#include "ResponseParser.hpp"

BtHandler::BtHandler(std::shared_ptr<OBDHandler> obdHandler) : m_staticRespHandler(), m_obdHandler(obdHandler) {}

void BtHandler::initialize()
{
  m_btSerial.begin("OBDII-ESP");
  Serial.println("Bluetooth started.");
}

void BtHandler::cyclic()
{
  if (m_btSerial.available())
  {
    String received = m_btSerial.readStringUntil('\r');
    received.replace(" ", "");

    Serial.print("Received: ");
    Serial.println(received);
    std::string response;

    if (ResponseParser::isHexRequest(received.c_str()))
    {
      response = getOBD2PIDResponse(received.c_str());
    }
    else
    {
      response = m_staticRespHandler.getResponse(received.c_str());
    }

    m_btSerial.println(response.c_str());
  }
}

std::string BtHandler::getOBD2PIDResponse(const std::string &request)
{
  uint16_t parsedPID = ResponseParser::parseRequest(request.c_str());
  Serial.println(parsedPID);

  OBDInfo *info = m_obdHandler->getByPid(parsedPID);

  if (info == nullptr)
  {
    Serial.println("Requested not found.");
    return "";
  }

  uint32_t pidValue = info->getFormula();
  uint8_t pidLength = info->getLength();

  std::string response = ResponseParser::prepareResponse(pidValue, pidLength);
  return response;
}
