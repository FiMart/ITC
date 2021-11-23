#include <EEPROM.h>

const int buttonPin = 6;
const int ledPin = 13;

int ledState;
int buttonState;
int lastButtonState = LOW;

long debounceTime = 0;
long debounceDelay = 50;

void setup()
{
  Serial.begin(9600);
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
  ledState = EEPROM.read(0);
  digitalWrite(ledPin, ledState);
}
void loop()
{
  int reading = digitalRead(buttonPin);
  if (reading != lastButtonState)
  {
    debounceTime = millis();
  }
  if (millis() - debounceTime) > debounceDelay)
  {
    if (reading != buttonState)
    {
      buttonState = reading;
      if (buttonState == LOW)
      {
        ledState = !ledState;
      }
    }
  }
  digitalWrite(ledPin, ledState);
  EEPROM.update(0, ledState);
  lastButtonState = reading;
}
