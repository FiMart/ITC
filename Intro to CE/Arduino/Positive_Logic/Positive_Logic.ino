#define led_G1 8 //led_G1 = pin8
#define led_R1 9 //led_R1 = pin9
#define led_R2 10 //led_R2 = pin10 
#define led_R3 11 //led_R3 = pin11
void setup()
{
  pinMode(led_G1,OUTPUT); //OUTPUT = led_G1
  pinMode(led_R1,OUTPUT); //OUTPUT = led_R1
  pinMode(led_R2,OUTPUT); //OUTPUT = led_R2
  pinMode(led_R3,OUTPUT); //OUTPUT = led_R3
}
void loop()
{
  digitalWrite(led_G1,0); //OFF
  digitalWrite(led_R1,0); //OFF
  digitalWrite(led_R2,0); //OFF
  digitalWrite(led_R3,0); //OFF
  delay(500);
  
  digitalWrite(led_G1,0); //OFF
  digitalWrite(led_R1,0); //OFF
  digitalWrite(led_R2,0); //OFF
  digitalWrite(led_R3,1); //ON
  delay(500);

  digitalWrite(led_G1,0); //OFF
  digitalWrite(led_R1,0); //OFF
  digitalWrite(led_R2,1); //ON
  digitalWrite(led_R3,1); //ON
  delay(500);

  digitalWrite(led_G1,0); //OFF
  digitalWrite(led_R1,1); //ON
  digitalWrite(led_R2,1); //ON
  digitalWrite(led_R3,1); //ON
  delay(500);

  digitalWrite(led_G1,1); //ON
  digitalWrite(led_R1,1); //ON
  digitalWrite(led_R2,1); //ON
  digitalWrite(led_R3,1); //ON
  delay(500);
}
