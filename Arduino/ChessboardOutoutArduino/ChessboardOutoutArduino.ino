//============ Neopixel Code

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

// Arduino Output Pin for Neopixels
#define NEOPIXELPIN 47

// Number of Neopixels
#define NUMPIXELS 64

Adafruit_NeoPixel pixels(NUMPIXELS, NEOPIXELPIN, NEO_GRB + NEO_KHZ800);

int ledBrightness = 100;


//============= Communication Code



//============= PWM Shield Code

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm1 = Adafruit_PWMServoDriver(0x40);
Adafruit_PWMServoDriver pwm2 = Adafruit_PWMServoDriver(0x41);
Adafruit_PWMServoDriver pwm3 = Adafruit_PWMServoDriver(0x42);
Adafruit_PWMServoDriver pwm4 = Adafruit_PWMServoDriver(0x43);
Adafruit_PWMServoDriver pwm5 = Adafruit_PWMServoDriver(0x44);
Adafruit_PWMServoDriver pwm6 = Adafruit_PWMServoDriver(0x45);
Adafruit_PWMServoDriver pwm7 = Adafruit_PWMServoDriver(0x46);
Adafruit_PWMServoDriver pwm8 = Adafruit_PWMServoDriver(0x48);
Adafruit_PWMServoDriver pwm9 = Adafruit_PWMServoDriver(0x49);
Adafruit_PWMServoDriver pwm10 = Adafruit_PWMServoDriver(0x50);
Adafruit_PWMServoDriver pwm11 = Adafruit_PWMServoDriver(0x51);
Adafruit_PWMServoDriver pwm12 = Adafruit_PWMServoDriver(0x52);

//Board Output Controllers.

int boardController = 0;
const byte numChars = 64;
char boardPieceController[numChars];

boolean newData = false;

const byte numPWMBoards = 12;
Adafruit_PWMServoDriver boardPWM[numPWMBoards] = {pwm1, pwm2, pwm3, pwm4, pwm5, pwm6, pwm7, pwm8, pwm9, pwm10, pwm11, pwm12};

//=============

void setup() {
  Serial.begin(9600);
  pixels.begin(); // INITIALIZE NeoPixel strip object

  // tell the PC we are ready
  Serial.println("<Arduino is ready>");
  
  for (byte n = 0; n < numPWMBoards; n++) {
    boardPWM[n].begin();
    boardPWM[n].setOscillatorFrequency(27000000);
    boardPWM[n].setPWMFreq(1600);
    //Wire.setClock(400000);
  }

}

//=============

void loop() {
  recvWithStartEndMarkers();
  showNewData();
  updateBoard();
  pixels.show();   // Send the updated pixel colors to the hardware.
}


//=============


void recvWithStartEndMarkers() {
  static boolean recvInProgress = false;
  static byte ndx = 0;
  char startMarker = '<';
  char endMarker = '>';
  char rc;

  while (Serial.available() > 0 && newData == false) {
    rc = Serial.read();

    if (recvInProgress == true) {
      if (rc != endMarker) {
        boardPieceController[ndx] = rc;
        ndx++;
        if (ndx >= numChars) {
          ndx = numChars - 1;
        }
      }
      else {
        boardPieceController[ndx] = '\0'; // terminate the string
        recvInProgress = false;
        ndx = 0;
        newData = true;
      }
    }

    else if (rc == startMarker) {
      recvInProgress = true;
    }
  }
}

//=============

void showNewData() {
  if (newData == true) {
    Serial.print("This just in ... ");
    Serial.println(boardPieceController);

    newData = false;
  }
}

//============

void updateBoard() {

  if (boardPieceController[0] == '0') {
    updateLED();
  }

  else if (boardPieceController[0] == '1') {
    updateMagnet();
  }
}

//=============

void updateLED() {

  for (int i = 1; i <= NUMPIXELS; i++) {
    if (boardPieceController[i] == '1') {
      pixels.setPixelColor(i, pixels.Color(ledBrightness, ledBrightness, ledBrightness)); //Multiply i with 2
    }
    else {
      pixels.setPixelColor(i, pixels.Color(100, 0, 0)); //Multiply i with 2
    }
  }
}

//=============

void updateMagnet() {

  for (int i = 1; i <= 64; i++) {
    int boardNumber1 = i * 3 / 16;
    int boardNumber2 = boardNumber1;
    int boardNumber3 = boardNumber1;
    int pinNumber1 = i * 3 % 16;
    int pinNumber2 = pinNumber1 + 1;
    int pinNumber3 = pinNumber1 + 2;

    if (pinNumber2 > 15) {
      boardNumber2 = boardNumber1 + 1;
      pinNumber2 = ((i * 3) + 1) % 16;
    }

    if (pinNumber3 > 15) {
      boardNumber3 = boardNumber1 + 1;
      pinNumber3 = ((i * 3) + 2) % 16;
    }

    if (boardPieceController[i] == -1) {

    }
    else if (boardPieceController[i] == -1) {

    }
    else {
      boardPWM[boardNumber1].setPWM(pinNumber1, 0, 0);
      boardPWM[boardNumber2].setPWM(pinNumber2, 0, 0);
      boardPWM[boardNumber3].setPWM(pinNumber3, 0, 0);
    }

  }
}
