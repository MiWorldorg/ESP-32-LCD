
// Required libraries
#include <SPIFFS.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>

// Display interface configuration
#define TFT_CS_PIN 15
#define TFT_DC_PIN 16
#define TFT_RST_PIN 17

Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS_PIN, TFT_DC_PIN, TFT_RST_PIN);

// Display backlight enable pin
#define TFT_BACKLIGHT_PIN GPIO_NUM_32

// Image reader
SPIFFS_ImageReader reader;

void fullwifisetup()
{
    Serial.begin(115200);
    tft.init(240, 240, SPI_MODE2); // Init ST7789 240x240
    delay(500);
    tft.fillScreen(ST77XX_WHITE);

    // initialize SPIFFS
    if (!SPIFFS.begin(false))
    {
        Serial.println("SPIFFS initialisation failed!");
        while (1)
            ;
    }
}

void fullwifiloop()
{

    tft.fillScreen(ST77XX_WHITE);
    delay(1000);
    uint32_t time = millis();
    reader.drawBMP("/DZM.bmp", tft, 0, 0);
    Serial.println(millis() - time);
    delay(1000);
}