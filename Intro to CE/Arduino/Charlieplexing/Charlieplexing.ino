#define p1 3
#define p2 4
#define p3 5
void setup()
{

}

void loop() {
  // LED6 light on
  pinMode(p1, OUTPUT);
  pinMode(p2, INPUT);
  pinMode(p3, OUTPUT);
  digitalWrite(p1, HIGH );
  digitalWrite(p3, LOW);
  delay(500);

  // LED5 light on
  pinMode(p1, OUTPUT);
  pinMode(p2, INPUT);
  pinMode(p3, OUTPUT);
  digitalWrite(p1, LOW );
  digitalWrite(p3, HIGH);
  delay(500);

  // LED4 light on
  pinMode(p1, INPUT);
  pinMode(p2, OUTPUT);
  pinMode(p3, OUTPUT);
  digitalWrite(p2, HIGH );
  digitalWrite(p3, LOW);
  delay(500);

  // LED3 light on
  pinMode(p1, INPUT);
  pinMode(p2, OUTPUT);
  pinMode(p3, OUTPUT);
  digitalWrite(p2, LOW );
  digitalWrite(p3, HIGH);
  delay(500);

  // LED2 light on
  pinMode(p1, OUTPUT);
  pinMode(p2, OUTPUT);
  pinMode(p3, INPUT);
  digitalWrite(p1, HIGH);
  digitalWrite(p2, LOW);
  delay(500);

  // LED1 light on
  pinMode(p1, OUTPUT);
  pinMode(p2, OUTPUT);
  pinMode(p3, INPUT);
  digitalWrite(p1, LOW);
  digitalWrite(p2, HIGH);
  delay(500);

  // LED2 light on
  pinMode(p1, OUTPUT);
  pinMode(p2, OUTPUT);
  pinMode(p3, INPUT);
  digitalWrite(p1, HIGH);
  digitalWrite(p2, LOW);
  delay(500);

  // LED3 light on
  pinMode(p1, INPUT);
  pinMode(p2, OUTPUT);
  pinMode(p3, OUTPUT);
  digitalWrite(p2, LOW );
  digitalWrite(p3, HIGH);
  delay(500);

  // LED4 light on
  pinMode(p1, INPUT);
  pinMode(p2, OUTPUT);
  pinMode(p3, OUTPUT);
  digitalWrite(p2, HIGH );
  digitalWrite(p3, LOW);
  delay(500);

  // LED5 light on
  pinMode(p1, OUTPUT);
  pinMode(p2, INPUT);
  pinMode(p3, OUTPUT);
  digitalWrite(p2, LOW );
  digitalWrite(p3, HIGH);
  delay(500);
}
