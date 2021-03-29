#include <AccelStepper.h>

#define dirPin 6
#define stepPin 5
#define motorInterfaceType 1

AccelStepper stepper = AccelStepper(motorInterfaceType, stepPin, dirPin);

//Pins 
int calibrationButton = 0;
int buttonPinNo = 2;
int buttonPinYes = 4;
int buttonvalue = 0;
int enableA = 10; //PWM for magnet - 65 pwm is almost neutral
int enableB = 9; //PWM for button LEDS
int input1 = 8; //in for magnet - negative
int input2 = 7; //in for magnet - positive
int input3 = 12; //in for buttqon LED
int input4 = 13; //in for button LED


unsigned long currentMillis = 0;
unsigned long previousMillis = 0;
const long interval = 1000; 
const long electro_interval = 5000;
boolean oldSwitchState1 = LOW;
boolean oldSwitchState2 = LOW;

int magDirection = 0;
int dist = 0;
int steps_map = 0;
int pwmOutput = 0;
int stepsToMove = 0;
boolean yesButton = LOW;
boolean noButton = LOW;

void setup() 
{ 
  Serial.begin(9600);
  pinMode(buttonPinNo, INPUT);
  pinMode(buttonPinYes, INPUT);
  pinMode(calibrationButton, INPUT);
  pinMode(enableA, OUTPUT);
  pinMode(enableB, OUTPUT);
  pinMode(input1, OUTPUT);
  pinMode(input2, OUTPUT);
  pinMode(input3, OUTPUT);
  pinMode(input4, OUTPUT);
  
  digitalWrite(input3, LOW);
  digitalWrite(input4, HIGH);
  digitalWrite(enableB, 200);
  digitalWrite(input1, LOW);
  digitalWrite(input2, LOW);
  
  stepper.setMaxSpeed(1000);
  
  while(stepper.currentPosition() != -280)
    {
      stepper.setSpeed(-80);
      stepper.runSpeed();
    }
  stepper.setCurrentPosition(0);
  
  while(stepper.currentPosition() != 240)
    {
      stepper.setSpeed(80);
      stepper.runSpeed();
    }
  
  delay(1000);
  buttonvalue = 0; 
 
} 

void loop() {
  
  yesButton = digitalRead(buttonPinYes);
  noButton = digitalRead(buttonPinNo);
  
  if (yesButton != oldSwitchState1){
    if (yesButton == HIGH){
      buttonvalue++;
    }
  }
  oldSwitchState1 = yesButton;
  oldSwitchState2 = noButton;
  
  switch (buttonvalue) {
    case 0:
      digitalWrite(input1, LOW);
      digitalWrite(input2, LOW);
      Serial.println(buttonvalue);
      break;
    case 1:
      // 100 % Positive
      digitalWrite(input1, LOW);
      digitalWrite(input2, HIGH);
      analogWrite(enableA, 255); 
      Serial.println(buttonvalue);

      break;
    case 2:
      // 20% Positive
      digitalWrite(input1, LOW);
      digitalWrite(input2, HIGH);
      analogWrite(enableA, 43);
      Serial.println(buttonvalue);
      break;
    case 3:
      digitalWrite(input1, LOW);
      digitalWrite(input2, LOW);
      
      while(stepper.currentPosition() != 70)
      {
        stepper.setSpeed(-80);
        stepper.runSpeed();
      }
      Serial.println(buttonvalue);
      break;
    case 4:
      while(stepper.currentPosition() != 240)
      {
        stepper.setSpeed(80);
        stepper.runSpeed();
      }
      //100% Negative
      digitalWrite(input1, HIGH);
      digitalWrite(input2, LOW);
      analogWrite(enableA, 255);
      Serial.println(buttonvalue);
      break;
    case 5:
      //20% Negative
      digitalWrite(input1, HIGH);
      digitalWrite(input2, LOW);
      analogWrite(enableA, 86);
      Serial.println(buttonvalue);
        break;
    case 6:
      digitalWrite(input1, LOW);
      digitalWrite(input2, LOW); 
      Serial.println(buttonvalue);
    break;
    case 7:
      buttonvalue = 0;
      Serial.println(buttonvalue);
      break; 
    default:
      return;
    break;
  }
}
