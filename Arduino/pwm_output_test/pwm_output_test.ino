/*************************************************** 
  This is an example for our Adafruit 16-channel PWM & Servo driver
  PWM test - this will drive 16 PWMs in a 'wave'

  Pick one up today in the adafruit shop!
  ------> http://www.adafruit.com/products/815

  These drivers use I2C to communicate, 2 pins are required to  
  interface.

  Adafruit invests time and resources providing this open source code, 
  please support Adafruit and open-source hardware by purchasing 
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.  
  BSD license, all text above must be included in any redistribution
 ****************************************************/

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

int brightness = 0;
int fadeAmount = 1;

// called this way, it uses the default address 0x40
//Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
// you can also call it with a different address you want
Adafruit_PWMServoDriver pwm1 = Adafruit_PWMServoDriver(0x40);
//Adafruit_PWMServoDriver pwm2 = Adafruit_PWMServoDriver(0x41);
// you can also call it with a different address and I2C interface 0  
//Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40, Wire);


void setup() {
  Serial.begin(9600);
  Serial.println("16 channel PWM test!");

  pwm1.begin();
  pwm1.setOscillatorFrequency(27000000);
  pwm1.setPWMFreq(1600);  // This is the maximum PWM frequency
  //pwm2.begin();
  //pwm2.setOscillatorFrequency(27000000);
  //pwm2.setPWMFreq(1600);  // This is the maximum PWM frequency
  

 
  
  
}

void loop() {
  
  pwm1.setPWM(0, 0, 4095);
  pwm1.setPWM(1, 0, 0);
  pwm1.setPWM(2, 0, 4095);
  
 
  
  Serial.println("Fuck");
 
}
