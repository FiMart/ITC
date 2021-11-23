// (1 Send to Hello1  to 2), (2 Send to Hello2 and Send back to 1), (1 Send Hello2 to 3), (3 Send Hello3 Send back to 1)
// Mas1 to send information to slave2 and slave3
#include <Wire.h>

#define SLAVE2 2
#define SLAVE3 3

int i;

char hello[7] = "HELLO1";

void setup()
{
  Serial.begin(9600);
  Wire.begin();// Start
}

void loop()
{
  Serial.println(hello);// print("Hello")
  Wire.beginTransmission(SLAVE2);// Mas1 want to send information to Slave2
  Wire.write(hello);// Send Hello1 to Slave2
  Wire.endTransmission();// Mas1 stop send information
  Wire.requestFrom(SLAVE2, 6); // Mas1 tell slave2 to start continue send information
  for (int i = 0; Wire.available(); i++) // Mas1 and Slave2 check condition
  {
    hello[i] = Wire.read();// Read information from receive buffer
  }
  delay(500);

  Serial.println(hello);// print("Hello2")
  Wire.beginTransmission(SLAVE3);// Mas1 want to send information to Slave3
  Wire.write(hello);;// Send Hello2 to Slave3
  Wire.endTransmission();// Mas1 stop send information
  Wire.requestFrom(SLAVE3, 6); // Mas1 tell Slave3 start send information
  for (i = 0; Wire.available(); i++)// Mas1 and Slave3 check condition
  {
    hello[i] = Wire.read();// Read information from receive buffer
  }
}
