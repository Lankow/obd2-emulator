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

    uint16_t parsedPID = ResponseParser::parseRequest(received.c_str());
    Serial.println(parsedPID);

    IOBD2PIDInfo *info = m_manager->getPIDInfo(parsedPID);
    if(info == nullptr)
    {
      Serial.println("Requested not found.");
      return;
    }

    uint32_t pidValue = info->getFormula();
    uint8_t pidLength = info->getLength();

    std::string response = ResponseParser::prepareResponse(pidValue, pidLength);
    m_btSerial.println(response.c_str());
  }
}
