int button_1 = 12;
int button_2 = 11;
int button_3 = 10;

int led_1 = 4;
int led_2 = 3;
int led_3 = 2;

int buttonState_1;
int buttonState_2;
int buttonState_3;

int lastButtonState_1 = LOW;
int lastButtonState_2 = LOW;
int lastButtonState_3 = LOW;

long lastDebounceTime_1 = 0;
long lastDebounceTime_2 = 0;
long lastDebounceTime_3 = 0;

long debounceDelay_1 = 50;
long debounceDelay_2 = 50;
long debounceDelay_3 = 50;

int ledState_1 = LOW;
int ledState_2 = LOW;
int ledState_3 = LOW;

void setup() {
  Serial.begin(9600);
  pinMode(led_1, OUTPUT);
  pinMode(led_2, OUTPUT);
  pinMode(led_3, OUTPUT);
  pinMode(button_1, INPUT);
  pinMode(button_2, INPUT);
  pinMode(button_3, INPUT_PULLUP);
}

void loop() {
  int reading_1 = digitalRead(button_1);
  int reading_2 = digitalRead(button_2);
  int reading_3 = digitalRead(button_3);

  if (reading_1 != lastButtonState_1) {
    lastDebounceTime_1 = millis();
  }

  // Red light is on 3 second
  if ( (millis() - lastDebounceTime_1) > debounceDelay_1 ) {
    if (reading_1 != buttonState_1 ) {
      buttonState_1 = reading_1;
    }
    if (buttonState_1 == HIGH) {
      ledState_1 = !ledState_1;
      Serial.println("PressedSwitch1.");
    }
    if (buttonState_1 == LOW && (millis() - lastDebounceTime_1) > 3000  ) {
      ledState_1 = LOW;
    }
  }

  // Green light is on but Red light is not effect Green light
  if (ledState_1 == HIGH) {
    if (buttonState_3 == HIGH && (millis() - lastDebounceTime_3) > 3000  ) {
      ledState_3 = LOW;
    }
  }
  else if (ledState_1 == LOW) {
    if (reading_3 != lastButtonState_3) {
      lastDebounceTime_3 = millis();
    }
    if ( (millis() - lastDebounceTime_3) > debounceDelay_3 ) {
      if (reading_3 != buttonState_3 ) {
        buttonState_3 = reading_3;
        if (buttonState_3 == LOW) {
          ledState_3 = !ledState_3;
          Serial.println("PressedSwitch3.");
        }
      }
      if (buttonState_3 == HIGH && (millis() - lastDebounceTime_3) > 3000  ) {
        ledState_3 = LOW;
      }
    }

  }

  // Yellow is on off on off
  if (ledState_1 == HIGH || ledState_3 == HIGH) {

    if (buttonState_2 == HIGH && (millis() - lastDebounceTime_2) > 500  ) {
      ledState_2 = HIGH;
    }
    if (buttonState_2 == HIGH && (millis() - lastDebounceTime_2) > 1000  ) {
      ledState_2 = LOW;
    }
    if (buttonState_2 == HIGH && (millis() - lastDebounceTime_2) > 1500  ) {
      ledState_2 = HIGH;
    }
    if (buttonState_2 == HIGH && (millis() - lastDebounceTime_2) > 2000  ) {
      ledState_2 = LOW;
    }
  }
  else {
    if (reading_2 != lastButtonState_2) {
      lastDebounceTime_2 = millis();
    }

    if ( (millis() - lastDebounceTime_2) > debounceDelay_2 ) {
      if (reading_2 == 0 ) {
        buttonState_2 = HIGH;
      }
      if (buttonState_2 == HIGH && (millis() - lastDebounceTime_2) > 500  ) {
        ledState_2 = HIGH;
      }
      if (buttonState_2 == HIGH && (millis() - lastDebounceTime_2) > 1000  ) {
        ledState_2 = LOW;
      }
      if (buttonState_2 == HIGH && (millis() - lastDebounceTime_2) > 1500  ) {
        ledState_2 = HIGH;
      }
      if (buttonState_2 == HIGH && (millis() - lastDebounceTime_2) > 2000  ) {
        ledState_2 = LOW;
      }
    }
  }
  digitalWrite(led_1, ledState_1);
  lastButtonState_1 = reading_1;

  digitalWrite(led_2, ledState_2);
  lastButtonState_2 = reading_2;

  digitalWrite(led_3, ledState_3);
  lastButtonState_3 = reading_3;
}
