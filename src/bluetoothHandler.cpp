/**
 * @file BluetoothHandler.cpp
 * @date   2025-01-04
 * @author Lankow
 * @version 1.0
 */

#include "BluetoothHandler.hpp"

void BluetoothHandler::initialize()
{
  if(m_serialBt.begin("OBDII"))
  {
    Serial.println("Bluetooth device started successfully");
  }
  else
  {
    Serial.println("Bluetooth device initialization failed");
  }
};
