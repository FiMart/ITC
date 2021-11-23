void setup()
{
  pinMode(11, OUTPUT);
}

void loop()
{
  digitalWrite(11, HIGH);
  delay(250); // Wait for 1000 millisecond(s)
  digitalWrite(11, LOW);
  delay(250); // Wait for 1000 millisecond(s)
}
