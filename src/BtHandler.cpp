/**
 * @file BtHandler.cpp
 * @date   2025-01-04
 * @author Lankow
 * @version 1.0
 */

#include "BtHandler.hpp"
#include "OBD2PIDInfo.hpp"

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
    Serial.print("Received: ");
    Serial.println(received);
    m_btSerial.println("Message Received: " + received);
  }
}
