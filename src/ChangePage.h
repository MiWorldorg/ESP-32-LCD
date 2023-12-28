
#include "assets/Pages/secondPage/setting.h"
int pressButtonCounter = 0;
const int buttonPin = 4;
const int ledPin = 26;
int buttonState = 0;
int lastButtonState = 0;

bool readKey()
{
    static uint8_t debounce = 0;

    if (digitalRead(buttonPin) == LOW)
    {
        if (++debounce > 100)
        {
            debounce = 100;
            return true;
        }
    }
    else
    {
        debounce = 0;
    };

    return false;
}

uint8_t readKeys()
{
    static uint8_t debounce1 = 0, debounce2 = 0, Keys = 0;

    if (digitalRead(buttonPin) == LOW)
    {
        if (++debounce1 > 50)
        {
            debounce1 = 50;
            Keys |= 0x01;
        }
    }
    else
    {
        debounce1 = 0;
        Keys &= ~0x01;
    };

    if (digitalRead(27) == LOW)
    {
        if (++debounce2 > 50)
        {
            debounce2 = 50;
            Keys |= 0x02;
        }
    }
    else
    {
        debounce2 = 0;
        Keys &= ~0x02;
    };

    return Keys;
}

//? --------------------------------
void settingPage()
{
    int positionimageSettingx = myNewLCD.height() / 2;
    int positionimageSettingy = myNewLCD.width() / 2;
    myNewLCD.fillScreen(TFT_WHITE);
    myNewLCD.setTextSize(0.5);
    myNewLCD.setFreeFont(RB_12P);
    myNewLCD.setTextColor(TFT_GOLD);
    myNewLCD.setCursor(85, 20);
    myNewLCD.print("Setting");
    myNewLCD.setSwapBytes(true);
    myNewLCD.pushImage(positionimageSettingx - 85, positionimageSettingy - 85, 170, 170, settingicon);
}
//? --------------------------------

void menu1()
{
    settingPage();
}

void menu2()
{
    myNewLCD.fillScreen(TFT_BLUE);
}
uint8_t pageState()
{
    uint8_t menuNumber = 0;
    if (readKeys() == 0x00)
        return 0;

    while (1)
    {
        uint8_t key = readKeys();
        if (key & 0x01)
        {
            if (++menuNumber >= 3)
                return 1;
        }

        switch (menuNumber)
        {
        case 1:
            menu1();
            break;

        case 2:
            menu2();
            break;
        }
        while (key == readKeys())
        {
        };
    }
    return 0;
}
