/**
 * @file BtHandler.cpp
 * @date   2025-01-04
 * @author Lankow
 * @version 1.0
 */

#include "BtHandler.hpp"
#include "OBDInfo.hpp"
#include "StringUtils.hpp"

BtHandler::BtHandler(std::shared_ptr<OBDHandler> obdHandler) : m_staticRespHandler(), m_obdHandler(obdHandler) {}

void BtHandler::initialize()
{
  m_btSerial.begin("OBDII-ESP");
  Serial.println("Bluetooth started.");
}

void BtHandler::cyclic()
{
  while (m_btSerial.available())
  {
    String received = m_btSerial.readStringUntil('\r');
    received.replace(" ", "");

    Serial.print("Received: ");
    Serial.println(received);
    std::string response;

    if (StringUtils::isHeximalNumber(received.c_str()))
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
  uint16_t parsedPID = StringUtils::hexStringToUint16(request.c_str());
  Serial.println(parsedPID);

  OBDInfo *info = m_obdHandler->getByPid(parsedPID);

  if (info == nullptr)
  {
    Serial.println("Requested not found.");
    return "";
  }

  uint32_t pidValue = m_obdHandler->getFormula(*info);
  uint8_t pidLength = info->m_length;

  std::string response = StringUtils::intToHexString(pidValue, pidLength);
  return response;
}
