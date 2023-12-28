
#define TEXT "TEST30" // Text that will be printed on screen in any font

#include "SPI.h"
#include "TFT_eSPI.h"

// Stock font and GFXFF reference handle
#define GFXFF 1

#define CF_OL24 &Orbitron_Light_24
#define CF_OL32 &Orbitron_Light_32
#define CF_RT24 &Roboto_Thin_24
#define CF_S24 &Satisfy_24
#define CF_Y32 &Yellowtail_32
#define NX_Y22 &nexa_black15pt7b
#define RB_12P &Roboto_Medium12pt7b
#define RB_10P &Roboto_Medium10pt7b
#define RB_9P &Roboto_Medium9pt7b

// Use hardware SPI
TFT_eSPI tft = TFT_eSPI();

void FontTest()
{

  // TL_DATUM = Top left (default)
  // TC_DATUM = Top centre
  // TR_DATUM = Top right
  // ML_DATUM = Middle left
  // MC_DATUM = Middle centre <<< This is used below
  // MR_DATUM = Middle right
  // BL_DATUM = Bottom left
  // BC_DATUM = Bottom centre
  // BR_DATUM = Bottom right
  // L_BASELINE = Left character baseline (Line the 'A' character would sit on)
  // C_BASELINE = Centre character baseline
  // R_BASELINE = Right character baseline

  // Serial.println();

  // Set text datum to middle centre (MC_DATUM)
  tft.setTextDatum(MC_DATUM);
  tft.setTextColor(TFT_BLUE);
  tft.setFreeFont(NX_Y22);               // Select the font
  tft.drawString(TEXT, 160, 100, GFXFF); // Print the test text in the custom font

  // Reset text padding to zero (default)
  tft.setTextPadding(0);
}
