/**
 * @file BtHandler.cpp
 * @date   2025-01-04
 * @author Lankow
 * @version 1.0
 */

#include "BtHandler.hpp"
#include "OBD2PIDInfo.hpp"
#include "ResponseParser.hpp"

BtHandler::BtHandler(std::shared_ptr<OBD2PIDManager> manager) : m_manager(manager) {}

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

    if (ResponseParser::isHexRequest(received.c_str()))
    {
      std::string response = getOBD2PIDResponse(received.c_str());
      m_btSerial.println(response.c_str());
    }
    else
    {
      Serial.println("Request is not PID request.");
    }
  }
}

std::string BtHandler::getOBD2PIDResponse(const std::string &request)
{
  uint16_t parsedPID = ResponseParser::parseRequest(request.c_str());
  Serial.println(parsedPID);

  OBD2PIDInfo *info = m_manager->getPIDInfo(parsedPID);

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
