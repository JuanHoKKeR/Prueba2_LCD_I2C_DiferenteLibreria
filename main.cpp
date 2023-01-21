#include "mbed.h"
#include "TextLCD.h"

#define DISPLAY_RS_pin PA_6 //D12
#define DISPLAY_E_pin  PA_7 //D11
#define DISPLAY_D4_pin PB_4 //D5
#define DISPLAY_D5_pin PB_5 //D4
#define DISPLAY_D6_pin PB_3 //D3
#define DISPLAY_D7_pin PA_10 //D2

const uint8_t upArrow[8] = {
    0b00100,
    0b01010,
    0b10001,
    0b00100,
    0b00100,
    0b00100,
    0b00000,
};

const uint8_t downArrow[8] = {
    0b00000,
    0b00100,
    0b00100,
    0b00100,
    0b10001,
    0b01010,
    0b00100,
};

const uint8_t rightArrow[8] = {
    0b00000,
    0b00100,
    0b00010,
    0b11001,
    0b00010,
    0b00100,
    0b00000,
};

const uint8_t leftArrow[8] = {
    0b00000,
    0b00100,
    0b01000,
    0b10011,
    0b01000,
    0b00100,
    0b00000,
};

TextLCD lcd(DISPLAY_RS_pin, DISPLAY_E_pin, DISPLAY_D4_pin, DISPLAY_D5_pin,
             DISPLAY_D6_pin, DISPLAY_D7_pin);

int main() {
    ThisThread::sleep_for(50ms); // give a time to wakeup the controller

    lcd.init();
    lcd.display(TextLCD::DISPLAY_ON);

    lcd.printf("Hello world\n");

    // try display functions
    ThisThread::sleep_for(2s);
    lcd.display(TextLCD::CURSOR_ON);
    lcd.display(TextLCD::BLINK_ON);
    ThisThread::sleep_for(4s);
    lcd.display(TextLCD::BLINK_OFF);
    ThisThread::sleep_for(2s);
    lcd.display(TextLCD::CURSOR_OFF);
    ThisThread::sleep_for(2s);

    // clear
    lcd.cls();

    // create custom characters
    lcd.create(0, downArrow);
    lcd.create(1, upArrow);
    lcd.create(2, rightArrow);
    lcd.create(3, leftArrow);

    // show custom characters
    lcd.locate(0, 0);
    lcd.character(0, 0, 0);
    lcd.character(2, 0, 1);
    lcd.character(4, 0, 2);
    lcd.character(6, 0, 3);

    // try long text
    lcd.locate(0, 0);
    lcd.printf("Really long hello world\nwith scrolling");
    ThisThread::sleep_for(2s);

    // scroll
    while (1) {
        for (auto pos = 0; pos < (23 - lcd.columns()); pos++) {
            lcd.display(TextLCD::SCROLL_LEFT);
            ThisThread::sleep_for(150ms);
        }

        ThisThread::sleep_for(1s);

        for (auto pos = 0; pos < (23 - lcd.columns()); pos++) {
            lcd.display(TextLCD::SCROLL_RIGHT);
            ThisThread::sleep_for(150ms);
        }

        ThisThread::sleep_for(2s);
    }
}