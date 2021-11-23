//              1,     2,    3,    4,    5,    6,    7,    8,    9,   0,    G,    L,
int num[48] = {0xF3, 0x49, 0x61, 0x33, 0x25, 0x05, 0xB1, 0x01, 0x21, 0x81, 0x85, 0x8F};
int a = 1;
int b = 2;
int c = 3;
int d = 4;
int e = 5;
int f = 6;
int g = 7;
int i = 0;

int randomNum;

int button_no1 = 10;
int button_no2 = 11;

int buttonState_1;
int buttonState_2;

int lastButtonState_1 = LOW;
int lastButtonState_2 = LOW;

long lastDebounceTime_1 = 0;
long lastDebounceTime_2 = 0;

void setup()
{
  pinMode(button_no1, INPUT_PULLUP);
  pinMode(button_no2, INPUT_PULLUP);
  DDRD = 0xFF; // DDRD is port D read input and wirte input are input or output 0xFF is port 0-7
  PORTD = num[i]; // PORTD is similar of DDRD but it write what pin is 0 or 1
  randomNum = random(1, 9); // random number(1,9)
}

void loop()
{
  int reading_1 = digitalRead(button_no1);
  int reading_2 = digitalRead(button_no2);

  // button_no1 (INPUT_PULLUP)
  if (reading_1 != lastButtonState_1)
  {
    lastDebounceTime_1 = millis();
  }
  if (millis() - lastDebounceTime_1 > 50)
  {
    if (reading_1 != buttonState_1)
    {
      buttonState_1 = reading_1;

      if (buttonState_1 == LOW)
      {
        if (i == 9)
        {
          i = 0;
        }
        PORTD = num[i];
        i++;
      }
    }
  }

  // button_no2 (INPUT_PULLUP)
  if (reading_2 != lastButtonState_2)
  {
    lastDebounceTime_2 = millis();
  }
  if (millis() - lastDebounceTime_2 > 50)
  {
    if (reading_2 != buttonState_2)
    {
      buttonState_2 = reading_2;

      if (buttonState_2 == LOW)
      {

        if (i == randomNum)
        {
          PORTD = num[9];
          randomNum = random(1, 9);
          i = 0;
        }
        else if (i < randomNum)
        {
          PORTD = num[11];
        }
        else if (i > randomNum)
        {
          PORTD = num[10];
        }
      }
    }
  }

  lastButtonState_1 = reading_1;
  lastButtonState_2 = reading_2;
}
