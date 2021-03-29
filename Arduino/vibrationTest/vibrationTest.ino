#include <AccelStepper.h>

#define dirPin 6
#define stepPin 5
#define motorInterfaceType 1

AccelStepper stepper = AccelStepper(motorInterfaceType, stepPin, dirPin);


int enableA = 10; //PWM for magnet - 65 pwm is almost neutral
int enableB = 9; //PWM for button LEDS
int input1 = 8; //in for magnet - negative
int input2 = 7; //in for magnet - positive
int input3 = 12; //in for buttqon LED
int input4 = 13; //in for button LED
int buttonPinNo = 2;
int buttonPinYes = 4;

int buttonvalue = 0;
int steps_map = 0;
int pwmOutput = 0;


boolean oldSwitchState1 = LOW;
boolean oldSwitchState2 = LOW;
boolean yesButton = LOW;
boolean noButton = LOW;

void setup() {
  Serial.begin(9600);
  pinMode(buttonPinNo, INPUT);
  pinMode(buttonPinYes, INPUT);
  pinMode(enableA, OUTPUT);
  pinMode(enableB, OUTPUT);
  pinMode(input1, OUTPUT);
  pinMode(input2, OUTPUT);
  pinMode(input3, OUTPUT);
  pinMode(input4, OUTPUT);
  
  digitalWrite(input3, LOW);
  digitalWrite(input4, HIGH);
  digitalWrite(input1, LOW);
  digitalWrite(input2, LOW);
  digitalWrite(enableB, 200);
  
  stepper.setMaxSpeed(1000);
  while(stepper.currentPosition() != -280)
    {
      stepper.setSpeed(-40);
      stepper.runSpeed();
    }
  stepper.setCurrentPosition(0);
  while(stepper.currentPosition() != 232)
  {
    stepper.setSpeed(40);
    stepper.runSpeed();
  }
    
  delay(1000);
}

void loop() {
  
  yesButton = digitalRead(buttonPinYes);
  noButton = digitalRead(buttonPinNo);
  
  if (yesButton != oldSwitchState1){
    if (yesButton == HIGH){
      if (buttonvalue < 10) { 
        buttonvalue ++;
      }
      else {
        buttonvalue = 0;
      }
      Serial.println(buttonvalue);
      delay(100);
    }
  }
  if (noButton != oldSwitchState2) {
    if (noButton == HIGH) {
      if (buttonvalue != 0) {
      buttonvalue --;
      } else {
        buttonvalue = 10;
      }
      Serial.println(buttonvalue);
      delay(100);
    } 
  }
  oldSwitchState1 = yesButton;
  oldSwitchState2 = noButton;
  
  switch (buttonvalue) {
    case 0:
      // Strong in one direction
      digitalWrite(input1, LOW);
      digitalWrite(input2, HIGH);
      analogWrite(enableA, 255); 
      break;
    case 1:
      // No power to magnet
      digitalWrite(input1, LOW);
      digitalWrite(input2, LOW);
      break;
    case 2:
      // Our approximation of neutral
      digitalWrite(input1, LOW);
      digitalWrite(input2, HIGH);
      analogWrite(enableA, 65);
      break;
    case 3:
      // Strong in other direction
      digitalWrite(input1, HIGH);
      digitalWrite(input2, LOW);
      analogWrite(enableA, 255);
      break;
    case 4:
      // Rapid shifts
      Serial.println("Rapid shift - 0 --> 255");
      digitalWrite(input1, HIGH);
      digitalWrite(input2, LOW);
      analogWrite(enableA, 0);
      delay(10);
      analogWrite(enableA, 255);
      delay(10);
      break;
    case 5:
      // Rapid shift 255 pos --> 255 neg
      Serial.println("255 pos --> 255 neg");
      digitalWrite(input1, HIGH);
      digitalWrite(input2, LOW);
      analogWrite(enableA, 255);
      delay(10);
      digitalWrite(input1, LOW);
      digitalWrite(input2, HIGH);
      analogWrite(enableA, 255);
      delay(10);
      break;
    case 6:
      digitalWrite(input1, LOW);
      digitalWrite(input2, HIGH);
      analogWrite(enableA, 255);
      delay(10);
      analogWrite(enableA, 0);
      delay(10);
      break;
    case 7:
      digitalWrite(input1, HIGH);
      digitalWrite(input2, LOW);
      analogWrite(enableA, 255);
      delay(2);
      analogWrite(enableA, 0);
      delay(2);
      break;
    case 8:
      digitalWrite(input1, LOW);
      digitalWrite(input2, HIGH);
      for (int i = 0; i < 254; i++) {
        analogWrite(enableA, i);
      }
      break;
    case 9:
      digitalWrite(input1, HIGH);
      digitalWrite(input2, LOW);
      for (int i = 255; i > 1; i--) {
        analogWrite(enableA, i);
      }
      break;
    case 10:
      digitalWrite(input1, HIGH);
      digitalWrite(input2, LOW);
      for (int i = 0; i < 255; i++) {
        analogWrite(enableA, i);
        delay(5);
      }
      break;
    default:
      return;
    break;
  }
}
