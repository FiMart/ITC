#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <TimerOne.h>
#include <EEPROM.h>

#define OLED_RESET -1
Adafruit_SSD1306 OLED(OLED_RESET);

#define button_1 6  //Save data of time in EEPROM
#define button_2 7  //Set Minute
#define button_3 8  //Set Hour
#define button_4 9  //Change Mode

#define clockTime 0 // Normal Mode

#define setClockTime 1 //Set Time Mode

#define setClockAlarm 2 //Set Alarm Mode

#define speaker 12

int8_t secondTime;
int8_t minuteTime;
int8_t hourTime;

int8_t minuteAlarm;
int8_t hourAlarm;

int mode = 0;

void updateTime() 
{
  secondTime++;
  if (secondTime == 60)
  {
    minuteTime++;
    secondTime = 0;
  }
  if (minuteTime == 60)
  {
    hourTime++;
    minuteTime = 0;
  }
  if (hourTime == 24)
  {
    hourTime = 0;
  }
}

void up_or_down() //Functions for ADXL335
{
  int directX = analogRead(A0);
  if (directX > 400)
  {
    // Serial.println("RO");
    OLED.setRotation(0);
  }
  if (directX < 300)
  {
    OLED.setRotation(2);
    // Serial.println("RO2");
  }
  // Serial.println(directX);
}

int bounce; // Functions of bounce 
bool Button(int pin)
{
  if (!digitalRead(pin))
  {
    if (millis() - bounce > 500)
    {
      bounce = millis();
      return true;
    }
    bounce = millis();
  }
  return false;
}

void setup()
{
  Serial.begin(9600);
  OLED.begin(SSD1306_SWITCHCAPVCC, 0x3c);
  // Use Timer of every 1 sec
  Timer1.initialize();  
  // Request updateTime every 1 sec follow Timer1.initialize();
  Timer1.attachInterrupt(updateTime); 

  EEPROM.get(0, secondTime);  //Call time from Rom
  EEPROM.get(1, minuteTime);
  EEPROM.get(2, hourTime);
  EEPROM.get(3, minuteAlarm);
  EEPROM.get(4, hourAlarm);

  pinMode(button_1, INPUT_PULLUP);
  pinMode(button_2, INPUT_PULLUP);
  pinMode(button_3, INPUT_PULLUP);
  pinMode(button_4, INPUT_PULLUP);
}

void loop()
{
  up_or_down();

  if (Button(button_1))
  {
    EEPROM.update(0, secondTime); //Write in EEPROM
    EEPROM.update(1, minuteTime);
    EEPROM.update(2, hourTime);
    EEPROM.update(3, minuteAlarm);
    EEPROM.update(4, hourAlarm);
  }

  if (Button(button_2))
  {
    if (mode == setClockTime)
    {
      minuteTime++; //Add time minute in set time mode
      minuteTime %= 60;
    }
    else if (mode == setClockAlarm)
    {
      minuteAlarm++;  // Add time minute in set alarm mode
      minuteAlarm %= 60;
    }
  }

  if (Button(button_3))
  {
    if (mode == setClockTime)
    {
      hourTime++; //  Set Hour in Normal and Alarm
      hourTime %= 24;
    }
    else if (mode == setClockAlarm)
    {
      hourAlarm++;  
      hourAlarm %= 24;
    }
  }

  if (Button(button_4))
  {
    mode++; //Change mode 0 1 2 are normal, set time and set alarm
    mode %= 3;
  }

  OLED.clearDisplay();
  OLED.setCursor(10, 0);
  OLED.setTextColor(WHITE);
  OLED.setTextSize(1.7);

  if (mode == clockTime)
  {
    OLED.println("Normal"); // In normal mode to print on this
    OLED.println("");
    OLED.print(hourTime);
    OLED.print(":");
    OLED.print(minuteTime);
    OLED.print(":");
    OLED.print(secondTime);
    // Serial.print("1");
  }
  else if (mode == setClockTime)
  {
    OLED.println("Set Time"); // In Set time mode to print on this
    OLED.println("");
    OLED.print(hourTime);
    OLED.print(":");
    OLED.print(minuteTime);
    OLED.print(":");
    OLED.print(secondTime);
    // Serial.print("2");
  }
  else if (mode == setClockAlarm)
  {
    OLED.println("Set Alarm");  // In Set alarm mode to print on this
    OLED.println("");
    OLED.print(hourAlarm);
    OLED.print(":");
    OLED.print(minuteAlarm);
    OLED.print(":");
    OLED.print(secondTime);
    // Serial.print("3");
  }

  if (minuteTime == minuteAlarm && hourTime == hourAlarm) // Set Alarm
  {
    Serial.println("ALARM");  // Notification "ALARM!"
    OLED.clearDisplay();
    OLED.println("ALARM!");
  }
  OLED.display();
}
