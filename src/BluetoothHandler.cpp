/**
 * @file BluetoothHandler.cpp
 * @date   2025-01-04
 * @author Lankow
 * @version 1.0
 */

#include "BluetoothHandler.hpp"
#include "OBDInfo.hpp"
#include "StringUtils.hpp"

const std::string BLUETOOTH_SERIAL_NAME = "OBDII-ESP";
constexpr uint8_t SERVICE_RESPONSE_OFFSET = 0x40;
constexpr uint8_t SERVICE_RESPONSE_LENGTH = 1;

BluetoothHandler::BluetoothHandler(std::shared_ptr<OBDHandler> obdHandler) : m_staticRespHandler(), m_obdHandler(obdHandler) {}

void BluetoothHandler::initialize()
{
  Serial.println("BluetoothHandler: Initialization Started...");

  if (m_bluetoothSerial.begin(BLUETOOTH_SERIAL_NAME.c_str()))
  {
    Serial.print("BluetoothHandler: Initialization Finished using name: ");
    Serial.println(BLUETOOTH_SERIAL_NAME.c_str());
  }
}

void BluetoothHandler::cyclic()
{
  while (m_bluetoothSerial.available())
  {
    String received = m_bluetoothSerial.readStringUntil('\r');
    received.replace(" ", "");

    Serial.println("BluetoothHandler: Received Request: ");
    Serial.println(received);
    std::string response;

    if (StringUtils::isHeximalNumber(received.c_str()))
    {
      Serial.println("BluetoothHandler: HEX Request confirmed. ");
      response = getOBD2PIDResponse(received.c_str());
    }
    else
    {
      response = m_staticRespHandler.getResponse(received.c_str());
    }

    Serial.println("BluetoothHandler: Sending Response: ");
    Serial.println(response.c_str());
    m_bluetoothSerial.println(response.c_str());
  }
}

std::string BluetoothHandler::getOBD2PIDResponse(const std::string &request)
{
  uint16_t parsedPID = StringUtils::hexStringToUint16(request.c_str());
  Serial.println(parsedPID);

  OBDInfo *info = m_obdHandler->getByPid(parsedPID);

  if (info == nullptr)
  {
    Serial.println("BluetoothHandler: Requested PID not found.");
    return "";
  }

  uint32_t pidValue = m_obdHandler->getFormula(*info);
  uint8_t pidLength = info->m_length;
  uint8_t pidServiceByte = static_cast<uint8_t>((info->m_pid >> 8) + SERVICE_RESPONSE_OFFSET);
  
  std::string pidServiceStr = StringUtils::intToHexString(pidServiceByte, SERVICE_RESPONSE_LENGTH);
  std::string pidValueStr = StringUtils::intToHexString(pidValue, pidLength);

  std::string response = pidServiceStr + " " + pidValueStr;

  return response;
}
