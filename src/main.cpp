#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
  Serial.begin(115200);

  Wire.begin(14, 12); // SDA = GPIO14, SCL = GPIO12
  Serial.println("Initializing OLED...");

if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)){
    Serial.println("Failed to initialize SSD1306!");
    while (true); 
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("OBD2-Emulator");
  display.display();
}

void loop() {
}