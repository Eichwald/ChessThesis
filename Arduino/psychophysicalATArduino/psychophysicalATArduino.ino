#include <AccelStepper.h>

#define dirPin 6
#define stepPin 5
#define motorInterfaceType 1

AccelStepper stepper = AccelStepper(motorInterfaceType, stepPin, dirPin);

//Pins 
int buttonPinNo = 2;
int buttonPinYes = 4;
int enableA = 10; //PWM for magnet - 65 pwm is almost neutral
int enableB = 9; //PWM for button LEDS
int input1 = 8; //in for magnet - negative
int input2 = 7; //in for magnet - positive
int input3 = 12; //in for button LED
int input4 = 13; //in for button LED


unsigned long currentMillis = 0;
unsigned long previousMillis = 0;
const long interval = 1000; 
const long electro_interval = 5000;
boolean oldSwitchState1 = LOW;
boolean oldSwitchState2 = LOW;

int magDirection = 0;
int steps_map = 0;
int pwmOutput = 0;
int stepsToMove = 0;
int prev_pos = 0;
boolean yesButton = LOW;
boolean noButton = LOW;
int powerValue = 0; 

void setup() 
{ 
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
  
  stepper.setMaxSpeed(1000);
  
  while(stepper.currentPosition() != -280)
    {
      stepper.setSpeed(-80);
      stepper.runSpeed(); 
    }
  stepper.setCurrentPosition(0);
  
  while(stepper.currentPosition() != 260)
    {
      stepper.setSpeed(80);
      stepper.runSpeed();
    }
  delay(1000);
} 
 //260 = 0 cm
 
void loop() 
{
  
  while(Serial.available() > 0 ){
    
    String str = Serial.readString();
        
    if(str.indexOf("a") > -1){        //Negative 1 cm
      powerValue = -1; 
      stepsToMove = 232;
    } else if(str.indexOf("b") > -1) {//Negative 2 cm
      powerValue = -1; 
      stepsToMove = 204;
    } else if(str.indexOf("c") > -1) {//Negative 3 cm
      powerValue = -1; 
      stepsToMove = 176;
    } else if(str.indexOf("d") > -1) {//Negative 4 cm
      powerValue = -1; 
      stepsToMove = 148;
    } else if(str.indexOf("e") > -1) {//Negative 5 cm
      powerValue = -1; 
      stepsToMove = 120;
    } else if(str.indexOf("f") > -1) {//Negative 6 cm
      powerValue = -1; 
      stepsToMove = 92;
    } else if(str.indexOf("g") > -1) {//Neutral 1 cm
      powerValue = 0; 
      stepsToMove = 232;
    } else if(str.indexOf("h") > -1) {//Neutral 2 cm
      powerValue = 0; 
      stepsToMove = 204;
    } else if(str.indexOf("i") > -1) {//Neutral 3 cm
      powerValue = 0; 
      stepsToMove = 176;
    } else if(str.indexOf("j") > -1) {//Positive 1 cm
      powerValue = 1; 
      stepsToMove = 232;
    } else if(str.indexOf("k") > -1) {//Positive 2 cm
      powerValue = 1; 
      stepsToMove = 204;
    } else if(str.indexOf("l") > -1) {//Positive 3 cm
      powerValue = 1; 
      stepsToMove = 176;
    } else if(str.indexOf("m") > -1) {//Positive 4 cm
      powerValue = 1; 
      stepsToMove = 148;
    } else if(str.indexOf("n") > -1) {//Positive 5 cm
      powerValue = 1; 
      stepsToMove = 120;
    } else if(str.indexOf("o") > -1) {//Positive 6 cm
      powerValue = 1; 
      stepsToMove = 92;
    }
    else {
      return;
    }
  }
  yesButton = digitalRead(buttonPinYes);
  noButton = digitalRead(buttonPinNo);
  if (yesButton != oldSwitchState1){
    if (yesButton == HIGH){
      analogWrite(enableB, 0);
      Serial.write("yes");
      blinkButtonLED();
    }
  }
  if (noButton != oldSwitchState2) {
    if (noButton == HIGH) {
      analogWrite(enableB, 0);
      Serial.write("no");
      blinkButtonLED();
    } 
  }
  oldSwitchState1 = yesButton;
  oldSwitchState2 = noButton;
 
 if(stepper.currentPosition() > stepsToMove) {
    while(stepper.currentPosition() != stepsToMove)
    {
      analogWrite(enableB, 0);
      digitalWrite(input1, LOW);
      digitalWrite(input2, LOW);
      stepper.setSpeed(-80);
      stepper.runSpeed();
    }
    analogWrite(enableB, 200);
 }
 else{
   while(stepper.currentPosition() != stepsToMove)
    {
      analogWrite(enableB, 0);
      digitalWrite(input1, LOW);
      digitalWrite(input2, LOW);
      stepper.setSpeed(80);
      stepper.runSpeed();
    } 
    analogWrite(enableB, 200);
 }
 

  if(powerValue == -1){
    digitalWrite(input1, HIGH);
    digitalWrite(input2, LOW);
    analogWrite(enableA, 255);
  }
  else if(powerValue == 0){
    digitalWrite(input1, LOW);
    digitalWrite(input2, LOW);
    analogWrite(enableA, 0);
  }
  else if(powerValue == 1){
    digitalWrite(input1, LOW);
    digitalWrite(input2, HIGH);
    analogWrite(enableA, 255);
  }
}

void blinkButtonLED(){
  for(int i = 0; i <= 5; i++){
    analogWrite(enableB, 0);
    delay(50);
    analogWrite(enableB, 200);
    delay(50); 
  }
}
