#include <AccelStepper.h>

#define dirPin 6
#define stepPin 5
#define motorInterfaceType 1

AccelStepper stepper = AccelStepper(motorInterfaceType, stepPin, dirPin);

//Pins 
int calibrationButton = 0;
int buttonPinNo = 2;
int buttonPinYes = 4;
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
boolean buttonLightsOn; 

int switchDelay = 3000;
int switchBDelay = 2000;
int switchNullDelay = 1500;

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
  digitalWrite(input1, LOW);
  digitalWrite(input2, LOW);
  
  stepper.setMaxSpeed(1000);
  
  while(stepper.currentPosition() != -280)
    {
      stepper.setSpeed(-80);
      stepper.runSpeed();
    }
  stepper.setCurrentPosition(0);
  
  while(stepper.currentPosition() != 232)
  {
      stepper.setSpeed(80); 
      stepper.runSpeed(); 
  }
  
  delay(1000);
} 
 
void loop() 
{
  
  while(Serial.available() > 0 ){
    
    String str = Serial.readString();
    //Serial.println(str);
        
    if(str.indexOf("a") > -1){
      analogWrite(enableB, 200);
      analogWrite(enableA, 127);
      digitalWrite(input1, LOW);
      digitalWrite(input2, HIGH);
      delay(switchDelay);
      analogWrite(enableB, 50);
      digitalWrite(input1, LOW);
      digitalWrite(input2, LOW);
      delay(switchNullDelay);
      analogWrite(enableB, 200);
      analogWrite(enableA, 179);
      digitalWrite(input1, LOW);
      digitalWrite(input2, HIGH);
      delay(switchBDelay);
      digitalWrite(input1, LOW);
      digitalWrite(input2, LOW);
      blinkButtonLED(5);
      

    } else if(str.indexOf("b") > -1) {
      analogWrite(enableB, 200);
      analogWrite(enableA, 153);
      digitalWrite(input1, LOW);
      digitalWrite(input2, HIGH);
      delay(switchDelay);
      analogWrite(enableB, 50);
      digitalWrite(input1, LOW);
      digitalWrite(input2, LOW);
      delay(switchNullDelay);
      analogWrite(enableB, 200);
      analogWrite(enableA, 179);
      digitalWrite(input1, LOW);
      digitalWrite(input2, HIGH);
      delay(switchBDelay);
      digitalWrite(input1, LOW);
      digitalWrite(input2, LOW);
      blinkButtonLED(5);
      

    } else if(str.indexOf("c") > -1) {
      analogWrite(enableB, 200);
      analogWrite(enableA, 179);
      digitalWrite(input1, LOW);
      digitalWrite(input2, HIGH);
      delay(switchDelay);
      analogWrite(enableB, 50);
      digitalWrite(input1, LOW);
      digitalWrite(input2, LOW);
      delay(switchNullDelay);
      analogWrite(enableB, 200);
      analogWrite(enableA, 179);
      digitalWrite(input1, LOW);
      digitalWrite(input2, HIGH);
      delay(switchBDelay);
      digitalWrite(input1, LOW);
      digitalWrite(input2, LOW);
      blinkButtonLED(5);
      

    } else if(str.indexOf("d") > -1) {
      analogWrite(enableB, 200);
      analogWrite(enableA, 204);
      digitalWrite(input1, LOW);
      digitalWrite(input2, HIGH);
      delay(switchDelay);
      analogWrite(enableB, 50);
      digitalWrite(input1, LOW);
      digitalWrite(input2, LOW);
      delay(switchNullDelay);
      analogWrite(enableB, 200);
      analogWrite(enableA, 179);
      digitalWrite(input1, LOW);
      digitalWrite(input2, HIGH);
      delay(switchBDelay);
      digitalWrite(input1, LOW);
      digitalWrite(input2, LOW);
      blinkButtonLED(5);
      

    } else if(str.indexOf("e") > -1) {
      analogWrite(enableB, 200);
      analogWrite(enableA, 230);
      digitalWrite(input1, LOW);
      digitalWrite(input2, HIGH);
      delay(switchDelay);
      analogWrite(enableB, 50);
      digitalWrite(input1, LOW);
      digitalWrite(input2, LOW);
      delay(switchNullDelay);
      analogWrite(enableB, 200);
      analogWrite(enableA, 179);
      digitalWrite(input1, LOW);
      digitalWrite(input2, HIGH);
      delay(switchBDelay);
      digitalWrite(input1, LOW);
      digitalWrite(input2, LOW);
      blinkButtonLED(5);
      

    } else if(str.indexOf("f") > -1) {
      analogWrite(enableB, 200);
      analogWrite(enableA, 255);
      digitalWrite(input1, LOW);
      digitalWrite(input2, HIGH);
      delay(switchDelay);
      analogWrite(enableB, 50);
      digitalWrite(input1, LOW);
      digitalWrite(input2, LOW);
      delay(switchNullDelay);
      analogWrite(enableB, 200);
      analogWrite(enableA, 179);
      digitalWrite(input1, LOW);
      digitalWrite(input2, HIGH);
      delay(switchBDelay);
      digitalWrite(input1, LOW);
      digitalWrite(input2, LOW);
      blinkButtonLED(5);
      

    } else if(str.indexOf("g") > -1) {
      analogWrite(enableB, 200);
      analogWrite(enableA, 127);
      digitalWrite(input1, HIGH);
      digitalWrite(input2, LOW);
      delay(switchDelay);
      analogWrite(enableB, 50);
      digitalWrite(input1, LOW);
      digitalWrite(input2, LOW);
      delay(switchNullDelay);
      analogWrite(enableB, 200);
      analogWrite(enableA, 179);
      digitalWrite(input1, HIGH);
      digitalWrite(input2, LOW);
      delay(switchBDelay);
      digitalWrite(input1, LOW);
      digitalWrite(input2, LOW);
      blinkButtonLED(5);
      

    } else if(str.indexOf("h") > -1) {
      analogWrite(enableB, 200);
      analogWrite(enableA, 153);
      digitalWrite(input1, HIGH);
      digitalWrite(input2, LOW);
      delay(switchDelay);
      analogWrite(enableB, 50);
      digitalWrite(input1, LOW);
      digitalWrite(input2, LOW);
      delay(switchNullDelay);
      analogWrite(enableB, 200);
      analogWrite(enableA, 179);
      digitalWrite(input1, HIGH);
      digitalWrite(input2, LOW);
      delay(switchBDelay);
      digitalWrite(input1, LOW);
      digitalWrite(input2, LOW);
      blinkButtonLED(5);
      

    } else if(str.indexOf("i") > -1) {
      analogWrite(enableB, 200);
      analogWrite(enableA, 179);
      digitalWrite(input1, HIGH);
      digitalWrite(input2, LOW);
      delay(switchDelay);
      analogWrite(enableB, 50);
      digitalWrite(input1, LOW);
      digitalWrite(input2, LOW);
      delay(switchNullDelay);
      analogWrite(enableB, 200);
      analogWrite(enableA, 179);
      digitalWrite(input1, HIGH);
      digitalWrite(input2, LOW);
      delay(switchBDelay);
      digitalWrite(input1, LOW);
      digitalWrite(input2, LOW);
      blinkButtonLED(5);
      

    } else if(str.indexOf("j") > -1) {
      analogWrite(enableB, 200);
      analogWrite(enableA, 204);
      digitalWrite(input1, HIGH);
      digitalWrite(input2, LOW);
      delay(switchDelay);
      analogWrite(enableB, 50);
      digitalWrite(input1, LOW);
      digitalWrite(input2, LOW);
      delay(switchNullDelay);
      analogWrite(enableB, 200);
      analogWrite(enableA, 179);
      digitalWrite(input1, HIGH);
      digitalWrite(input2, LOW);
      delay(switchBDelay);
      digitalWrite(input1, LOW);
      digitalWrite(input2, LOW);
      blinkButtonLED(5);
    } 
    
    else if(str.indexOf("k") > -1) {
      analogWrite(enableB, 200);
      analogWrite(enableA, 230);
      digitalWrite(input1, HIGH);
      digitalWrite(input2, LOW);
      delay(switchDelay);
      analogWrite(enableB, 50);
      digitalWrite(input1, LOW);
      digitalWrite(input2, LOW);
      delay(switchNullDelay);
      analogWrite(enableB, 200);
      analogWrite(enableA, 179);
      digitalWrite(input1, HIGH);
      digitalWrite(input2, LOW);
      delay(switchBDelay);
      digitalWrite(input1, LOW);
      digitalWrite(input2, LOW);
      blinkButtonLED(5);
    }
    
    else if(str.indexOf("l") > -1) {
      analogWrite(enableB, 200);
      analogWrite(enableA, 255);
      digitalWrite(input1, HIGH);
      digitalWrite(input2, LOW);
      delay(switchDelay);
      analogWrite(enableB, 50);
      digitalWrite(input1, LOW);
      digitalWrite(input2, LOW);
      delay(switchNullDelay);
      analogWrite(enableB, 200);
      analogWrite(enableA, 179);
      digitalWrite(input1, HIGH);
      digitalWrite(input2, LOW);
      delay(switchBDelay);
      digitalWrite(input1, LOW);
      digitalWrite(input2, LOW);
      blinkButtonLED(5);
    }
    else {
      return;
    }
  }
  yesButton = digitalRead(buttonPinYes);
  noButton = digitalRead(buttonPinNo);
  if (yesButton != oldSwitchState1){
    if (yesButton == HIGH){
      Serial.write("yes");
      blinkButtonLED(2);
    }
  }
  if (noButton != oldSwitchState2) {
    if (noButton == HIGH) {
      Serial.write("no");
      blinkButtonLED(2);
    } 
  }
  oldSwitchState1 = yesButton;
  oldSwitchState2 = noButton; 
}

void blinkButtonLED(int count){
  for(int i = 0; i <= count; i++){
    analogWrite(enableB, 0);
    delay(50);
    analogWrite(enableB, 200);
    delay(50); 
  }
}

