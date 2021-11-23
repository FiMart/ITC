#include "LedControl.h"
#include "FontLEDClock.h"

LedControl lc = LedControl(11, 13, 10, 4);  // DIN,CLK,CS,Number of LED Module
uint8_t intensity = 8;
uint8_t hour  = 12, minute = 00, second = 0; //Variable Clock mode

void setup()
{
  //find no of LED modules 
  int devices = lc.getDeviceCount();            
  for (int addr = 0; addr < devices; addr++)  //set up each device
  { 
    //set up each device        
    lc.shutdown(addr, false);   //turn off power saving mode
    lc.setIntensity(addr, 2);   //set intensity = 2 of 8
    lc.clearDisplay(addr);      //clear screen
  }
                                                       
  //set up each device
  Serial.begin(9600);
  noInterrupts();           //disable all interrupts
  TCCR1A  = 0;
  TCCR1B  = 0;
  TCNT1   = 3036;           //preload timer 65536-16MHz/256/1Hz
  TCCR1B |= (1 << CS12);    //256 prescaler
  TIMSK1 |= (1 << TOIE1);   //enable timer overflow interrupt
  interrupts();             //enable all interrupts
}

void clear_display()
{
  for (uint8_t addr = 0; addr < 4; addr++)
    lc.clearDisplay(addr);
}

void fade_down()
{
  for (uint8_t i = intensity; i > 0; i--) //fade from global intensity to 1
  {
    for (uint8_t addr = 0; addr < 4; addr++)
      lc.setIntensity(addr, i);
    delay(30); //change this to change fade down speed
  }
}

void fade_up()
{
  for (uint8_t i = 1; i < intensity; i++) //fade from global intensity to 1
  {
    for (uint8_t addr = 0; addr < 4; addr++)
      lc.setIntensity(addr, i);
    delay(30); //change this to change fade down speed
  }
  for (uint8_t addr = 0; addr < 4; addr++)
    lc.setIntensity(addr, intensity);  //reset intentsity to global value
}

void plot (uint8_t x, uint8_t y, bool value)
{
  //select which matrix depending on the x coord
  uint8_t addr;                                      
  if (x >= 0  && x <= 7)  
  {
    addr = 3;
  }
  if (x >= 8  && x <= 15) 
  {
    addr = 2;
    x = x - 8;
  }
  if (x >= 16 && x <= 23) 
  {
    addr = 1;
    x = x - 16;
  }
  if (x >= 24 && x <= 31) 
  {
    addr = 0;
    x = x - 24;
  }

  if (value == 1)
    lc.setLed(addr, y, x, true);
  else
    lc.setLed(addr, y, x, false);
}

void print_tiny_char(uint8_t x, uint8_t y, char c)
{
  uint8_t dots;
  if (c >= 'A' && c <= 'Z' || (c >= 'a' && c <= 'z') )  c &= 0x1F;  //A-Z maps to 1-26  
  else if (c >= '0' && c <= '9')                        c  = (c - '0') + 32;
  else if (c == ' ' )                                   c  =  0;    //space      
  else if (c == '.' )                                   c  = 27;    //full stop      
  else if (c == ':' )                                   c  = 28;    //colon             
  else if (c == '\'')                                   c  = 29;    //single quote mark 
  else if (c == '!' )                                   c  = 30;    //single quote mark 
  else if (c == '?' )                                   c  = 31;    //question mark     

  for (uint8_t col = 0; col < 3; col++)
  {
    dots = pgm_read_byte_near(&mytinyfont[c][col]);
    for (uint8_t row = 0; row < 5; row++)
    {
      if (dots & (16 >> row))
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

void clocks()
{
  //print hour
  print_tiny_char( 2, 1,  hour / 10 + '0'); 
  print_tiny_char( 6, 1,  hour % 10 + '0');
  
  //print minute
  print_tiny_char(12, 1, minute / 10 + '0'); 
  print_tiny_char(16, 1, minute % 10 + '0');

  //print second
  print_tiny_char(22, 1, second / 10 + '0'); 
  print_tiny_char(26, 1, second % 10 + '0');

  if (second == 0)  // blink for each minute
  {
    plot(10, 2, 0);
    plot(10, 4, 0);
    plot(20, 2, 0);
    plot(20, 4, 0);
  }
  else
  {
    plot(10, 2, 1);
    plot(10, 4, 1);
    plot(20, 2, 1);
    plot(20, 4, 1);
  }
  
  if (second < 30)  // display second count line
  {
    plot(second + 1, 7, 1);
  }
  else
  {
    plot(60 - second, 7, 0);
  }
}

// interrupt service routine
ISR(TIMER1_OVF_vect)
{
  //preload timern
  TCNT1 = 3036;              
  Serial.println(second++);
  if (second > 59) 
  {
    second = 0;
    minute++;
  }
  if (minute > 59) 
  {
    minute = 0;
    hour++;
  }
  if (hour > 23) 
  {
    hour = 0;
  }
}

void loop() 
{
  clocks();
  delay(100);
}
