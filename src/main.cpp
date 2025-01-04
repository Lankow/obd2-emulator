#include <Arduino.h>
#include "BluetoothHandler.hpp"

BluetoothHandler bluetoothHandler;

void setup() {
  Serial.begin(115200);
  Serial.println("Starting OBD2-Emulator.");
  bluetoothHandler.initialize();
}

void loop() {
}