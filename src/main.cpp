#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &SPI, 5, 6, -1);

void setup() {
    Serial.begin(115200);
    
    if (!display.begin())
    {
        Serial.println("SSD1306 allocation failed");
    }

    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.print("test");
        display.display();
        delay(1000);
}

void loop()
{
}