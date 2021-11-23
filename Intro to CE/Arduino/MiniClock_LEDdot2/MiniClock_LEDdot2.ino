#include "LedControl.h"
#include <EEPROM.h>
#include "FontLEDClock.h"
#include <Button.h>
#include <wire.h>
#include "RTClib.h"

LedControl lc = LedControl{11, 13, 10, 4};  //DIN, CLK, CS, PIN of Modules

byte clock_mode = 0;
byte intensity = 7;
byte old_mode = clock_mode;
byte change_mode_time = 0;

bool random_mode = 0;
bool am_pm = 0;

unsigned long delaytime = 500;

int rtc[7];

char days_full[7][9] = 
{
    "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"
};

char day[7][4] =
{
    "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"
};

char suffix[4][3] = 
{
    "st", "nd", "rd", "th"
};

#define NUM_DISPLAYMODES 3
#define NUM_SETTINGSMODES 4
#define DELAY_SLIDE 20
#define cls clear_display

RTC_DS1307 ds1307;

Button button_A = Button(2, BUTTON_PULLUP);
Button button_B = Button(3, BUTTON_PULLUP);

void setup()
{
    digitalWrite(2, HIGH);
    digitalWrite(3, HIGH);
    digitalWrite(4, HIGH);

    Serial.begin(9600);
    int devices = lc.getDeviceCount();
    for(int addr = 0; addr < devices; addr++)
    {
        lc.shutdown(addr, 0);
        lc.setIntensity(addr, intensity);
        lc.clearDisplay(addr);
    }

    #ifdef AVR
        Wire.begin();
    #else
        Wire1.begin();
    #endif
        ds1307.begin();
    
    if(!ds1307.isRunning())
    {
        Serial.println("RTC is NOT running!");
        ds1307.adjust(DateTime(_DATE_, _TIME_));
    }
    printver();

    digitalWrite(13, HIGH);
}   

void loop()
{
    switch (clock_mode)
    {
        case 0;
            basic_mode();
            break;
        case 1;
            small_mode();
            break;
        case 2;
            slide();
            break;
        case 3;
            word_clock();
            break;
        case 4;
            setup_menu();
            break;
    }
}

void plot (byte x, byte y, byte val)
{
    byte addr;
    if(x >= 0 && x <= 7)
    {
        addr = 3;
    }
    if(x >= 8 && x <= 15)
    {
        addr = 2;
        x = x - 8;
    }
    if(x >= 16 && x <= 23)
    {
        addr = 1;
        x = x - 16;
    }
    if(x >= 24 && x <= 31)
    {
        addr = 0;
        x = x - 24;
    }

    if(val == 1)
    {
        lc.setLed(addr, y, x, 1);
    }
    else
    {
        lc.setLed(addr, y, x, 0);
    }
}

void clear_display()
{
    for(byte addr = 0; addr < 4; addr++)
    {
        lc.clearDisplay(addr);
    }
}

void fade_down()
{
    for(byte i = intensity; i > 0; i--)
    {
        for(byte addr = 0; addr < 4; addr++)
        {
            lc.setIntensity(address, i);
        }
        delay(30);
    }

    clear_display();

    for(byte addr = 0; addr < 4; addr++)
    {
        lc.setIntensity(addr, intensity);
    }
}

void printver()
{
    byte i = 0;
    char ver_a[9] = "Vers 1.0";
    char ver_b[9] = "Hello! ";

    for(byte x = 0; x <= 31; x++)
    {
        for(byte y = 0; y <= 7; y++)
        {
            plot(x, y, 1);
        }
    }
    delay(500);
    fade_down();

    while(ver_a[i])
    {
        puttinychar((i * 4), 1, ver_a[i]);
        delay(35);
        i++;
    }
    delay(700);
    fade_down();
    i = 0;
    while(ver_b[i])
    {
        puttinychar((i * 4), 1, ver_b[i]);
        delay(35);
        i++;
    }
    delay(700);
    fade_down();
}

void puttinychar(byte x, byte y, char c)
{
    byte dots;
    if(c >= 'A' && c <= 'Z' || (c >= 'a' && c <= 'z'))
    {
        c &= 0x1Fl
    }
    else if(c >= '0' && c <= '9')
    {
        c = (c - '0') + 32;
    }
    else if(c == ' ')
    {
        c = 0;
    }
    else if(c == '.')
    {
        c = 27;
    }
    else if(c == ':')
    {
        c = 28;
    }
    else if(c == '\'')
    {
        c = 29;
    }
    else if(c == '!')
    {
        c = 30;
    }
    else if(c == '?')
    {
        c = 31;
    }

    for(byte col = 0; col < 3; col++)
    {
        dots = pgm_read_byte_near(&mytinyfont[c][col]);
        for(char row = 0; row < 5; row++)
        {
            if(dots & (16 >> row))
            {
                plot(x + col, y + row, 1);
            }
            else
            {
                plot(x + col, y + row, 0);
            }
        }
    }
}

void small_mode()
{
    char textchar[8];
    byte mins = 100;
    byte secs = rtc[0];
    byte old_secs = secs;

    cls();

    while(run_mode())
    {
        get_time();
        if(button_A.uniquePress())
        {
            switch_mode();
            return;
        }
        if(button_B.uniquePress())
        {
            display_date();
            return;
        }

        secs = rtc[0];
        if(secs != old_secs)
        {
            char buffer[3];
            itoa(secs, buffer, 10);

             if(secs < 10)
            {
                buffer[1] = buffer[0];
                buffer[0] = '0';
            }
            puttinychar(20, 1, ':');
            puttinychar(24, 1, buffer[0]);
            puttinychar(28, 1, buffer[1]);
            old_secs = secs;
        }

        if(mins != rtc[1])
        {
            mins = rtc[1];
            byte hours = rtc[2];
            if(hours > 12)
            {
                hours = hours - am_pm * 12;
            }
            if(hours < 1)
            {
                hours = hours + am_pm * 12;
            }

            char buffer[3];
            itoa(hours, buffer, 10);

            if(hours < 10)
            {
                buffer[1] = buffer[0];
                if(am_pm)
                {
                    buffer[0] = ' ';
                }
                else 
                {
                    buffer[0] = '0';
                }
            }

            textchar[0] = buffer[0];
            textchar[1] = buffer[1];
            textchar[2] = ':';

            itoa(mins, buffer, 10);
            if(mins < 10)
            {
                buffer[1] = buffer[0];
                buffer[0] = '0';
            }

            textchar[3] = buffer[0];
            textchar[4] = buffer[1];

            textchar[5] = ':';
            buffer[3];
            secs = rtc[0];
            itoa(secs, buffer, 10);

            if(secs < 10)
            {
                buffer[1] = buffer[0];
                buffer[0] = '0';
            }

            textchar[6] = buffer[0];
            textchar[7] = buffer[1];

            byte x = 0;
            byte y = 0;

            for(byte x = 0; x < 6; x++)
            {
                puttinychar(x * 4, 1, textchar[x]);
            }
        }
        delay(50);
    }
    fade_down();
}

void basic_mode()
{
    
}