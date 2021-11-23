#include "LedControl.h"
#define BL 6
#define BR 5
#define speaker 3
LedControl lc = LedControl(11, 13, 10, 4);

unsigned long delaytime = 300;

struct Vector2i
{
    int x, y;
};

Vector2i plusVector(Vector2i a, Vector2i b)
{
    Vector2i temp;
    temp.x = a.x + b.x;
    temp.y = a.y + b.y;
    return temp;
}

Vector2i pongPos;
Vector2i pongDir;

Vector2i barTopPos;
Vector2i barBotPos;

void setup()
{
    randomSeed(analogRead(A0));
    int devices = lc.getDeviceCount();
    for (int address = 0; address < devices; address++)
    {
        lc.shutdown(address, false);
        lc.setIntensity(address, 8);
        lc.clearDisplay(address);
    }
    pinMode(BL, INPUT_PULLUP);
    pinMode(BR, INPUT_PULLUP);

    pongPos = { 3,7 };
    pongDir = { 0,1 };

    barTopPos = { 3,0 };
    barBotPos = { 3,15 };
}

void loop()
{
    int left = !digitalRead(BL);
    int right = !digitalRead(BR);
    barTopPos.x -= left;
    barTopPos.x += right;
    barBotPos.x -= left;
    barBotPos.x += right;
    if (barTopPos.x < 1)
    {
        barTopPos.x = 1;
        barBotPos.x = 1;
    }
    if (barTopPos.x > 6)
    {
        barTopPos.x = 6;
        barBotPos.x = 6;
    }
    
    if ((barTopPos.x - 1 <= pongPos.x && pongPos.x <= barTopPos.x + 1) && (pongPos.y == 1 || pongPos.y == 14))
    {
        pongDir.y = -pongDir.y;
        pongDir.x = random(-1, 1);
    }
    if (pongPos.x == 0 || pongPos.x == 7)
    {
        pongDir.x = -pongDir.x;
    }
    pongPos = plusVector(pongPos, pongDir);
    lc.clearDisplay(0);
    lc.clearDisplay(1);
    lc.setLed(pongPos.y / 8, pongPos.x, pongPos.y % 8, true);
    lc.setLed(barTopPos.y / 8, barTopPos.x, barTopPos.y % 8, true);
    lc.setLed(barTopPos.y / 8, barTopPos.x+1, barTopPos.y % 8, true);
    lc.setLed(barTopPos.y / 8, barTopPos.x-1, barTopPos.y % 8, true);
    lc.setLed(barBotPos.y / 8, barBotPos.x, barBotPos.y % 8, true);
    lc.setLed(barBotPos.y / 8, barBotPos.x+1, barBotPos.y % 8, true);
    lc.setLed(barBotPos.y / 8, barBotPos.x-1, barBotPos.y % 8, true);
    delay(delaytime);
    if(pongPos.y<=0 || pongPos.y>=7)
    {
      lc.clearDisplay(0);
      lc.clearDisplay(1);
    }
}   
