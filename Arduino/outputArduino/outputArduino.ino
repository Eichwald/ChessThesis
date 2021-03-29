#define LED_1_PIN 6

#define BUTTON_PIN 7

byte lastButtonState = LOW;
byte currentButtonState = LOW;
unsigned long lastButtonDebounceTime = 0;
unsigned long buttonDebounceDelay = 20;

void powerOffAllLEDs()
{
    digitalWrite(LED_1_PIN, LOW);
}

void setup()
{
  Serial.begin(9600);
  pinMode(LED_1_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT);

  powerOffAllLEDs();
}

void loop()
{
  byte readValue = digitalRead(BUTTON_PIN);

  if (readValue != lastButtonState) {
    lastButtonDebounceTime = millis();
  }

  if (millis() - lastButtonDebounceTime > buttonDebounceDelay) {
    if (readValue != currentButtonState) {
      currentButtonState = readValue;
      if (currentButtonState == HIGH) {
        Serial.write(18);
      }
    }
  }

  lastButtonState = readValue;

  if (Serial.available() > 0) {
    int ledNumber = Serial.read() - '0';

    powerOffAllLEDs();
    
    switch (ledNumber) {
      case 2:
        digitalWrite(LED_1_PIN, HIGH);
        break;
      case 5:
        digitalWrite(LED_1_PIN, LOW);
        break;
      default: 
        // wrong pin number, do nothing
        // all LEDs will be powered off
        break;
    }
  }
}
