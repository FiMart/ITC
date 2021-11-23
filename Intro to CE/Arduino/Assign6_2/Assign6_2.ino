// Slave2 send back to Master1
#include <Wire.h>

#define SLAVE2 2
#define SLAVE3 3

int i;

char hello[7];

void setup()
{
  Serial.begin(9600);
  Wire.begin(SLAVE2);// Start at Slave2
  Wire.onReceive(getHELLO);// When Slave2 receive information from Mas1
  Wire.onRequest(sentHELLO);// When Slave2 request information from Mas1
}

void loop()
{
  delay(100);
}

void getHELLO(int bytes)
{
  for (i = 0; i < bytes; i++)
  {
    hello[i] = Wire.read();
  }
  if (hello[5] < '9') // Loop Hello1 - Hello9
  {
    hello[5]++;
  }
  else
  {
    hello[5] = '1';
  }
}

void sentHELLO()
{
  Wire.write(hello);
  Serial.println(hello);
}
