long randNumber;

void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(0));
}

void loop() {
  randNumber = random(300);
  Serial.print("A random number: ");
  Serial.println(randNumber);
  delay(1000);
}
