#include <TimerOne.h>

String LEDStatus = "OFF";

int yellowLED = 8;
int redLED = 9;

void setup()
{
    // Pin 13 has an LED connected on most Arduino boards
    pinMode(yellowLED, OUTPUT);
    pinMode(redLED, OUTPUT);

    Timer1.initialize(500000); // 0.5 s
    Timer1.attachInterrupt(blinkYellow);
    Serial.begin(9600);   
    
}

void loop()
{
    digitalWrite(redLED, HIGH);
    delay(1000);
    digitalWrite(redLED, LOW);
    delay(1000);
}

void blinkYellow()
{
    if(LEDStatus == "ON")
    {
        digitalWrite(yellowLED, LOW);
        LEDStatus = "OFF";
        return;
    }
    if(LEDStatus == "OFF")
    {
        digitalWrite(yellowLED, HIGH);
        LEDStatus = "ON";
        return;
    }
}