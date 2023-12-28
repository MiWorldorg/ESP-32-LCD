// Hardware-specific library for ST7789
#include <SPI.h>
// #include <Fonts/FreeMono9pt7b.h>
// #include <Fonts/TomThumb.h>
// #include <Fonts/FreeSerifBold9pt7b.h>
// #include <Fonts/FreeSans12pt7b.h>
// #include <Fonts/FreeSans9pt7b.h>

// #include <Fonts/FreeMonoOblique12pt7b.h>
// #include <Fonts/FM12.h>
// #include <Fonts/FreeSansBold9pt7b.h>
// #include <Fonts/FreeSerifBold12pt7b.h>
// #include <Fonts/FreeSans5pt7b.h>
// #include <Fonts/nexa_black15pt7b.h>
#include <string.h>
#include <stdio.h>
#include <TFT_eSPI.h>
#include "Free_Fonts.h"

#include "assets/wifi/wififull.h"
#include "assets/wifi/wifiunowkn.h"
#include "assets/wifi/wififair.h"
#include "assets/wifi/wifidc.h"

#include "assets/Battery/chargingBattery.h"
#include "assets/Battery/sevfiveBattery.h"
#include "assets/Battery/midBattery.h"
#include "assets/Battery/lowBattery.h"
#include "assets/Battery/fullBattery.h"
#include "assets/Battery/emptyBattery.h"
#include "TFT_Custom_Fonts.h"

TFT_eSPI myNewLCD = TFT_eSPI();

//
String jdate;   // Jalali Date String
int JY, JM, JD; // Jalali Year & Month & Day Intiger

// color definitions
const uint16_t Display_Color_Black = 0x0000;
const uint16_t Display_Color_Blue = 0x001F;
const uint16_t Display_Color_Red = 0xF800;
const uint16_t Display_Color_Green = 0x07E0;
const uint16_t Display_Color_Cyan = 0x07FF;
const uint16_t Display_Color_Magenta = 0xF81F;
const uint16_t Display_Color_Yellow = 0xFFE0;
const uint16_t Display_Color_White = 0xFFFF;
const uint16_t Display_Color_Whitew = 0xDFDF;
const uint16_t Display_Color_LightCyan = 0xBFBF;
const uint16_t Display_Color_DarkCyan = 0x1111;

// The colors we actually want to use
uint16_t Display_Text_Color = Display_Color_Green;
uint16_t Display_Backround_Color = Display_Color_White;

// assume the display is off until configured in setup()
bool isDisplayVisible = false;

// declare size of working string buffers. Basic strlen("d hh:mm:ss") = 10
const size_t MaxString = 20;

// the string being displayed on the SSD1331 (initially empty)
char oldTimeString[MaxString] = {0};
////////////////////////////////////
#include "jalalidate.h"
char newDateString[40], oldDateString[40], oldTimerLocal[80], newTimerLocal[50];
extern TIME_DATE_STR JalaliTimeDate;
void displayDate()
{
  /////////////// Main Clock /////////////////
  // time_t rawtime;
  // struct tm *info;
  ////////////////////////////////////////////
  struct tm *newtime;
  TIME_DATE_STR GtimeDate;

  time_t ltime;
  time(&ltime);
  newtime = localtime(&ltime);
  GtimeDate.Sec = newtime->tm_sec;
  GtimeDate.Min = newtime->tm_min;
  GtimeDate.Hour = newtime->tm_hour;
  GtimeDate.Day = newtime->tm_mday;
  GtimeDate.Mon = newtime->tm_mon;
  GtimeDate.Year = newtime->tm_year;
  GtimeDate.Year += 1900;
  JalaliTimeDate = Miladi2Shamsi(GtimeDate);

  char buffer[80];
  strftime(buffer, 80, "%s", newtime);
  //   strftime(buffer,80,"%x - %I:%M%p", info);
  // printf("Formatted date & time : |%s|\n", buffer );

  // strftime(buffer,80,"%T", info);
  // uint8_t a = info.tm_sec;

  // sprintf(newTimerLocal,"%s",);
  myNewLCD.fillRect(40, 0, 160, 35, TFT_WHITE);
  // myNewLCD.setTextFont(7);

  // myNewLCD.setTextSize(0.2);
  // myNewLCD.setCursor(10, 220);
  // myNewLCD.setTextColor(TFT_WHITE);
  // myNewLCD.print(oldTimerLocal);

  // myNewLCD.setTextFont(7);
  // myNewLCD.setTextSize(0.2);
  // myNewLCD.setCursor(10, 220);
  // myNewLCD.setTextColor(TFT_BLACK);
  // myNewLCD.print(newTimerLocal);

  myNewLCD.setTextSize(0.2);
  myNewLCD.setTextColor(TFT_WHITE);
  myNewLCD.setFreeFont(RB_9P);
  myNewLCD.setCursor(40, 23);
  myNewLCD.print(oldTimerLocal);
  myNewLCD.setTextSize(0.2);
  myNewLCD.setCursor(40, 23);
  myNewLCD.setTextColor(TFT_BLACK);
  myNewLCD.setFreeFont(RB_9P); // Select the font
  myNewLCD.printf(" %2u/%2u/%2u   %2u:%2u", JalaliTimeDate.Year, JalaliTimeDate.Mon + 1, JalaliTimeDate.Day, JalaliTimeDate.Hour, JalaliTimeDate.Min);

  // myNewLCD.printf("%4u/%2u/%2u", GtimeDate.Year, GtimeDate.Mon, GtimeDate.Day);

  // myNewLCD.drawString(newTimerLocal, 10, 220, GFXFF);

  // Serial.println(printLocalTime());

  // Serial.printf("%4u/%2u/%2u    %2u:%2u:%2u\r\n", JalaliTimeDate.Year, JalaliTimeDate.Mon, JalaliTimeDate.Day, JalaliTimeDate.Hour, JalaliTimeDate.Min, JalaliTimeDate.Sec);
  strcpy(oldTimerLocal, buffer);
  // strcpy(oldDateString,newDateString);

  //}
}
////////////////// Date Setup End ////////////////////

char newTempString[30], oldTempString[30];

// uint16_t temp2color(int degree, int lo, int hi)
// {
//   uint8_t r, g, b;
//   r = map(degree, lo, hi, 150, 0);
//   g = 0;
//   b = map(degree, lo, hi, 0, 120);
//   return myNewLCD.color565(r, g, b);
// }

// void colorgradient(int x, int y, int w, int h, int percent)
// {
//   myNewLCD.drawRect(x, y, w, h, TFT_BLACK);
//   for (int row = 1; row < h - 1; row++)
//   {
//     myNewLCD.drawFastHLine(x + 1, y + row, w - 2, temp2color(row, 0, h));
//   }
// }
void backCircle()
{
  int centerverticallalign = myNewLCD.width() / 2 + 20;
  myNewLCD.fillScreen(TFT_WHITE);
  myNewLCD.fillCircle(120, -20, 150, 0x1d1d);
  myNewLCD.fillCircle(120, -20, 120, 0x1e1e);
  myNewLCD.fillCircle(120, -20, 90, 0x1f1f);
  myNewLCD.fillCircle(120, centerverticallalign, 90, 0x1212);
  myNewLCD.fillCircle(120, centerverticallalign, 80, TFT_WHITE);
  myNewLCD.fillCircle(120, centerverticallalign, 90, 0x1212);
  myNewLCD.fillRectHGradient(0, 0, 240, 42, 0x1111, TFT_CYAN);
  myNewLCD.fillRect(0, 0, 240, 35, TFT_WHITE);
}
void backgrounddeep()
{
  myNewLCD.fillScreen(0x1C1C);
}

void displayTempData()
{
  float tempC = GetTemp();
  if (tempC == DEVICE_DISCONNECTED_C)
  {
    Serial.println("Error: Could not read temperature data");
    return;
  }
  sprintf(newTempString, "%.1f", tempC);

  int posdo = myNewLCD.width() / 2 - 70;
  int position1 = 0;
  int pos = 0;
  int nTemp = atoi(newTempString);
  // if (nTemp % 2 == 0)
  // {
  //   pos = myNewLCD.width() / 2 - 25;
  // }
  // else
  // {
  //   pos = myNewLCD.width() / 2 - 20;
  // }

  // myNewLCD.fillCircle(120, centerverticallalign, 85, backcolor);
  int centerverticallalign = myNewLCD.width() / 2 + 20;

  myNewLCD.fillCircle(120, centerverticallalign, 80, TFT_WHITE);

  // The custom font file attached to this sketch must be included

  // Stock font and GFXFF reference handle

  // Easily remembered name for the font
  // ?
  // myNewLCD.setTextDatum(MC_DATUM);

  // myNewLCD.setCursor(posdo, centerverticallalign - 15);
  // myNewLCD.setTextColor(TFT_WHITE);
  // myNewLCD.setTextSize(2);
  // myNewLCD.setTextFont(6);
  // myNewLCD.print(oldTempString);

  // myNewLCD.setCursor(posdo, centerverticallalign - 15);
  // myNewLCD.setTextColor(TFT_DARKCYAN);
  // myNewLCD.setTextSize(2);
  // myNewLCD.setTextFont(6);
  // myNewLCD.print(newTempString);
  // ?

  myNewLCD.setTextSize(2);
  myNewLCD.setTextColor(TFT_WHITE);
  myNewLCD.setFreeFont(NX_Y22); // Select the font
  myNewLCD.drawString(oldTempString, posdo, centerverticallalign - 22, GFXFF);
  myNewLCD.setTextSize(2);
  myNewLCD.setTextColor(0x1212);
  myNewLCD.setFreeFont(NX_Y22); // Select the font
  myNewLCD.drawString(newTempString, posdo, centerverticallalign - 22, GFXFF);
  strcpy(oldTempString, newTempString);

  /* colorgradient(20, 20, 50, 10); */
}

/*  */

void logopr()
{
  // iconCheck();

  myNewLCD.setFreeFont(FM12);
  myNewLCD.setTextSize(0.2);

  myNewLCD.setCursor(5, 20);
  myNewLCD.setTextColor(Display_Color_White);
  myNewLCD.print("DS");
}

void newwrap()
{
  myNewLCD.setFreeFont(FM12);
  myNewLCD.setTextSize(0.2);

  myNewLCD.setCursor(40, 190);
  myNewLCD.setTextColor(Display_Color_DarkCyan);
  myNewLCD.print("Temperature");
}

void setupLCD()
{

  ///

  ///

  // settling time
  delay(250);

  // ignore any power-on-reboot garbage

#ifdef ADAFRUIT_HALLOWING
  // HalloWing is a special case. It uses a ST7735R display just like the
  // breakout board, but the orientation and backlight control are different.
  myNewLCD.initR(INITR_HALLOWING); // Initialize HalloWing-oriented screen
  pinMode(myNewLCD_BACKLIGHT, OUTPUT);
  digitalWrite(myNewLCD_BACKLIGHT, HIGH); // Backlight on
#else

  // OR use this initializer (uncomment) if using a 1.54" 240x240 myNewLCD:
  myNewLCD.init(); // Init ST7789 240x240

  // SPI speed defaults to SPI_DEFAULT_FREQ defined in the library, you can override it here
  // Note that speed allowable depends on chip and quality of wiring, if you go too fast, you
  // may end up with a black screen some times, or all the time.
  // myNewLCD.setSPISpeed(40000000);
#endif

  // initialise the display
  myNewLCD.setFreeFont(FM12);
  myNewLCD.setRotation(3);
  myNewLCD.fillScreen(Display_Backround_Color);
  myNewLCD.setTextColor(Display_Text_Color);
  myNewLCD.setTextSize(0.5);

  // the display is now on
  isDisplayVisible = true;
}
char newVoltage[25], oldVoltage[25];

void voltageBattery()
{

  float voltage = analogRead(39) / 4096.0 * 3.7; // Ardunio UNO, no voltage divider required
  sprintf(newVoltage, "%d", analogRead(39));
  myNewLCD.setFreeFont(FM12);
  myNewLCD.setTextSize(0.2);

  myNewLCD.setCursor(80, 15);
  myNewLCD.setTextColor(Display_Color_Cyan);
  myNewLCD.print(oldVoltage);

  myNewLCD.setFreeFont(FM12);
  myNewLCD.setTextSize(0.2);

  myNewLCD.setCursor(80, 15);
  myNewLCD.setTextColor(Display_Color_Black);
  myNewLCD.print(newVoltage);

  strcpy(oldVoltage, newVoltage);

  Serial.println(voltage);
}

String readBattery()
{
  uint8_t percentage = 100;
  // float voltage = analogRead(35) / 4096.0 * 7.23; // LOLIN D32 (no voltage divider need already fitted to board.or NODEMCU ESP32 with 100K+100K voltage divider
  // float voltage = analogRead(39) / 4096.0 * 7.23; // NODEMCU ESP32 with 100K+100K voltage divider added
  // float voltage = analogRead(A0) / 4096.0 * 4.24;    // Wemos / Lolin D1 Mini 100K series resistor added
  float voltage = analogRead(39) / 4096.0 * 5.00; // Ardunio UNO, no voltage divider required
  Serial.println("Voltage = " + String(voltage)); // The voltage here needs to be reasonably accurate for a full LiFePO4 battery ~ 3.4v
  percentage = 4984.6172 * pow(voltage, 3) - 48287.7528 * pow(voltage, 2) + 155490.3329 * voltage - 166375.8607;
  if (voltage > 3.4)
    percentage = 100;
  else if (voltage <= 3.00)
    percentage = 0;
  // return String(percentage) + "%";
  return String(percentage);
}

void battericon()
{

  float voltage = analogRead(34) / 4096.0 * 3.58;

  int positionnew = myNewLCD.width() - 41;
  int positionnewx = 9;

  int batteryIcoX = myNewLCD.width() - 42;
  int batteryIcoY = 8;

  // myNewLCD.drawRect(batteryIcoX, batteryIcoY, 34, 18, 0x0000);

  // myNewLCD.fillRect(myNewLCD.width() - 8, 14, 3, 7, 0x0000); // mini rectangle
  if (voltage == 5)
  {
    myNewLCD.setSwapBytes(true); // swap the byte order for pushImage() - corrects endianness
    myNewLCD.pushImage(positionnew, 0, 35, 35, chargingBt);
    // myNewLCD.fillRect(positionnew, positionnewx, 32, 16, TFT_GREEN);
    // myNewLCD.fillTriangle(myNewLCD.width() - 38, 16, myNewLCD.width() - 24, 16, myNewLCD.width() - 24, 22, TFT_YELLOW);
    // myNewLCD.fillTriangle(myNewLCD.width() - 13, 16, myNewLCD.width() - 28, 16, myNewLCD.width() - 28, 11, TFT_YELLOW);
  }

  else if (voltage > 3.3)
  {
    myNewLCD.setSwapBytes(true); // swap the byte order for pushImage() - corrects endianness
    myNewLCD.pushImage(positionnew, 0, 35, 35, fullBt);
    // myNewLCD.fillRect(positionnew, positionnewx, 32, 16, 0xFFFF);
  }
  else if (voltage > 2.5 && voltage <= 3.3)
  {
    myNewLCD.setSwapBytes(true); // swap the byte order for pushImage() - corrects endianness
    myNewLCD.pushImage(positionnew, 0, 35, 35, sevfiveBt);
    // myNewLCD.fillRect(positionnew, positionnewx, 25, 16, 0xFFFF);
  }
  else if (voltage > 2 && voltage <= 2.5)
  {
    myNewLCD.setSwapBytes(true); // swap the byte order for pushImage() - corrects endianness
    myNewLCD.pushImage(positionnew, 0, 35, 35, midBt);
    // myNewLCD.fillRect(positionnew, positionnewx, 20, 16, 0xFFFF);
  }

  else if (voltage > 1.5 && voltage <= 2)
  {
    myNewLCD.setSwapBytes(true); // swap the byte order for pushImage() - corrects endianness
    myNewLCD.pushImage(positionnew, 0, 35, 35, midBt);
    //   myNewLCD.fillRect(positionnew, positionnewx, 15, 16, 0xFFFF);
  }
  else if (voltage > 1 && voltage <= 1.5)
  {
    myNewLCD.setSwapBytes(true); // swap the byte order for pushImage() - corrects endianness
    myNewLCD.pushImage(positionnew, 0, 35, 35, lowBt);
    // myNewLCD.fillRect(positionnew, positionnewx, 10, 16, 0xFFFF);
  }
  else if (voltage > 0.5 && voltage <= 1)
  {
    myNewLCD.setSwapBytes(true); // swap the byte order for pushImage() - corrects endianness
    myNewLCD.pushImage(positionnew, 0, 35, 35, lowBt);
    // myNewLCD.fillRect(positionnew, positionnewx, 5, 16, 0xFFFF);
  }
  else if (voltage > 0 && voltage <= 0.5)
  {
    myNewLCD.setSwapBytes(true); // swap the byte order for pushImage() - corrects endianness
    myNewLCD.pushImage(positionnew, 0, 35, 35, emptyBt);
    // myNewLCD.fillRect(positionnew, positionnewx, 2, 16, 0xFFFF);
  }
}

void monitorGrid()
{
  int grid = 20;
  int length = 240;
  int num = 0;
  while (num <= length)
  {
    num += length / grid;
    myNewLCD.fillRect(num, 0, 3, 240, TFT_BLUE);
    myNewLCD.fillRect(0, num, 240, 3, TFT_BLUE);
  }
}

void voltage2()
{
  float voltage = analogRead(39);
  Serial.println(voltage);
}

void WiFiIcon()
{ // initialize a ST7789 chip

  int RectStroke1 = 18;
  int RectStroke2 = 13;
  int RectStroke3 = 8;
  int RectRoundi = 8;

  if (WiFi.status() == WL_NO_SSID_AVAIL)
  {
    myNewLCD.setSwapBytes(true); // swap the byte order for pushImage() - corrects endianness
    myNewLCD.pushImage(10, 3, 24, 24, wifiunnow);
  }
  else if (WiFi.status() == WL_CONNECTED)
  {
    myNewLCD.setSwapBytes(true); // swap the byte order for pushImage() - corrects endianness
    myNewLCD.pushImage(10, 3, 24, 24, wififull);
  }
  else if (WiFi.status() == WL_DISCONNECTED)
  {
    myNewLCD.setSwapBytes(true); // swap the byte order for pushImage() - corrects endianness
    myNewLCD.pushImage(10, 3, 24, 24, wifidc);
  }
}
