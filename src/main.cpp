#include <Arduino.h>
#include "BluetoothHandler.hpp"
#include "WifiHandler.hpp"

BluetoothHandler bluetoothHandler;
WifiHandler wifiHandler;

void setup() {
  Serial.begin(115200);
  Serial.println("Starting OBD2-Emulator.");
  bluetoothHandler.initialize();
  wifiHandler.initialize();
}

void loop() {
    wifiHandler.handle();
    delay(100);
}