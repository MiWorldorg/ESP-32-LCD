
#include "JDateLib.h"
#include "OurClock.h"
#include "Log1.h"
#include "DSP_Ds18b20.h"
#include "lcd.h"
#include "JalaliDate.h"
#include <SPI.h>
#include <string.h>
#include <stdio.h>
#include "FSBrowser.h"
#include "OTA.h"
#include "ChangePage.h"

#define SerialDebugging true
const uint8_t Button_pin = 2;
const char *ssid2 = "ESP32-Iz-Project";
const char *password2 = "123456789";

//? the interrupt service routine affects this
volatile bool isButtonPressed = false;

#define BUTTON_PIN_BITMASK 0x8004 //? 2^33 in hex

#define uS_TO_S_FACTOR 1000000ULL // ! Conversion factor for micro seconds to seconds */
#define TIME_TO_SLEEP 5           // ! Time ESP32 will go to sleep (in seconds) */

RTC_DATA_ATTR int bootCount = 0;

// ? interrupt service routine
void senseButtonPressed()
{
  if (!isButtonPressed)
  {
    isButtonPressed = true;
  }
}

void setup()
{

  Serial.begin(115200);

  WiFi.mode(WIFI_AP_STA);
  WiFi.softAP(ssid2, password2);
  WiFi.begin(ssid, password);

  FILESYSTEM.begin();
  {
    File root = FILESYSTEM.open("/");
    File file = root.openNextFile();
    while (file)
    {
      String fileName = file.name();
      size_t fileSize = file.size();
      DBG_OUTPUT_PORT.printf("FS File: %s, size: %s\n", fileName.c_str(), formatBytes(fileSize).c_str());
      file = root.openNextFile();
    }
    DBG_OUTPUT_PORT.printf("\n");
  }
  if (!SPIFFS.begin(FORMAT_SPIFFS_IF_FAILED))
  {
    Serial.println("SPIFFS Mount Failed");
    return;
  }

  timerLocal = printLocalTime();
  // init and get the time
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  printLocalTime();
  //

  esp_sleep_get_ext1_wakeup_status();
  esp_sleep_get_wakeup_cause();
  setupLCD();
  int centerverticallalign = myNewLCD.width() / 2 + 20;

  logopr();
  sensors.begin();

  // myNewLCD.fillRectHGradient(0, 0, 240, 42, 0x1111, TFT_CYAN);
  // myNewLCD.fillRect(0, 0, 240, 35, TFT_WHITE);
  // displayTempData();
  // displayDate();
  isDisplayVisible = true;

  Serial.println("Connecting to WiFi");
  Serial.println();

  // Print ESP Local IP Address
  Serial.println(WiFi.localIP());
  Serial.println(WiFi.softAPIP());

  setupfbBrowseN();

#if (SerialDebugging)
  while (!Serial)
    ;
  Serial.println();
#endif
  backCircle();
  pinMode(GPIO_NUM_2, INPUT_PULLUP);
  pinMode(GPIO_NUM_15, INPUT_PULLUP);

  OTA();
}

unsigned long previousMillis = 0; // will store last time LED was updated

const long interval = 1000;        // interval at which to blink (milliseconds)
unsigned long previousMillis2 = 0; // will store last time LED was updated
unsigned long intervall2 = 1000;
void loop()
{

  ArduinoOTA.handle();
  unsigned long currentMillis = millis();

  //! unconditional display, regardless of whether display is visible
  //! has the button been pressed?
  server.handleClient();
  delay(2); //* allow the cpu to switch to other tasks

  unsigned long currentMillis2 = millis();
  // if WiFi is down, try reconnecting every CHECK_WIFI_TIME seconds
  if ((currentMillis2 - previousMillis2 >= intervall2))
  {
    previousMillis2 = currentMillis2;
    if ((WiFi.status() != WL_CONNECTED))
    {
      Serial.println("Reconnecting to WiFi...");
      WiFi.disconnect();
      WiFi.reconnect();
    }
  }

  //* and remember the new value
  if (currentMillis - previousMillis >= interval)
  {
    // * save the last time you blinked the LED
    previousMillis = currentMillis;

    displayDate();
    displayTempData();
    battericon();
    WiFiIcon();
  }

  if (pageState() == 1)
  {
    backCircle();
    displayDate();
    displayTempData();
    battericon();
    WiFiIcon();
  }
}
