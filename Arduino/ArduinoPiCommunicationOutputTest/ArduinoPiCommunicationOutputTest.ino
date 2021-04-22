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

const byte numChars = 65;
// char boardPieceController[numChars];
char boardPieceController[numChars] = {'4', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'};


boolean newData = false;

const byte numPWMBoards = 1;
//Adafruit_PWMServoDriver boardPWM[numPWMBoards] = {pwm1, pwm2, pwm3, pwm4, pwm5, pwm6, pwm7, pwm8, pwm9, pwm10, pwm11, pwm12};
Adafruit_PWMServoDriver boardPWM[numPWMBoards] = {pwm1};
//=============

void setup() {
  Serial.begin(9600);
  pixels.begin(); // INITIALIZE NeoPixel strip object

  // tell the PC we are ready
  Serial.println("<Arduino is ready>");

  /*for (byte n = 0; n < numPWMBoards; n++) {
    boardPWM[n].begin();
    boardPWM[n].setOscillatorFrequency(27000000);
    boardPWM[n].setPWMFreq(1600);
    // Wire.setClock(400000);
  }*/
  pwm1.begin();
  pwm1.setOscillatorFrequency(27000000);
  pwm1.setPWMFreq(1600);
  Serial.println("setup");
  delay(1000);
}

//=============

void loop() {
  //recvWithStartEndMarkers();
  showNewData();
  updateBoard();
  Serial.println("looping");
  pixels.show();  // Send the updated pixel colors to the hardware.
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
  Serial.println(boardPieceController[0]);
  if (boardPieceController[0] == '0') {//No Visual or Magnetic Feedback.
    turnOffVisual();
    turnOffMagnet();
  }

  if (boardPieceController[0] == '1') {//DemoMode :)

    demoMode();
  }

  if (boardPieceController[0] == '2') {//No Visual or Magnetic Feedback.

    turnOffVisual();
    turnOffMagnet();
  }

  if (boardPieceController[0] == '3') {//Visual Feedback --> No Magnetic Feedback.

    updateLED();
  }

  if (boardPieceController[0] == '4') {//Magnetic Feedback --> No Visual Feedback.
    Serial.println("test123");
    turnOffVisual();
    updateMagnet();
  }

  if (boardPieceController[0] == '5') {//Tænd magnetic og visual feedback
    updateLED();
    updateMagnet();

  }
}

//=============

void updateLED() {

  for (int i = 1; i < NUMPIXELS; i++) {
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
  Serial.println("test");
  for (int i = 0; i < 64; i++) {
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

    if (boardPieceController[i] == '1') { //Legal and Good Move. Attracts Magnet.
      Serial.println(boardNumber1);
      boardPWM[boardNumber1].setPWM(pinNumber1, 0, 0);
      boardPWM[boardNumber2].setPWM(pinNumber2, 0, 4095);
      boardPWM[boardNumber3].setPWM(pinNumber3, 0, 4095);
      
    }
    else if (boardPieceController[i] == '3') {//Illegal nove --> Pushes Magnet away.

    }
    else {
      boardPWM[boardNumber1].setPWM(pinNumber1, 0, 0);
      boardPWM[boardNumber2].setPWM(pinNumber2, 0, 0);
      boardPWM[boardNumber3].setPWM(pinNumber3, 0, 0);
    }
  }
}

void turnOffVisual() {

  for (int i = 0; i < NUMPIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(0, 0, 0)); //Multiply i with 2
  }
}

void turnOffMagnet() {
  for (int i = 0; i < 12; i++) {
    boardPWM[i].setPWM(0, 0, 0);
    boardPWM[i].setPWM(1, 0, 0);
    boardPWM[i].setPWM(2, 0, 0);
    boardPWM[i].setPWM(3, 0, 0);
    boardPWM[i].setPWM(4, 0, 0);
    boardPWM[i].setPWM(5, 0, 0);
    boardPWM[i].setPWM(6, 0, 0);
    boardPWM[i].setPWM(7, 0, 0);
    boardPWM[i].setPWM(8, 0, 0);
    boardPWM[i].setPWM(9, 0, 0);
    boardPWM[i].setPWM(10, 0, 0);
    boardPWM[i].setPWM(11, 0, 0);
    boardPWM[i].setPWM(12, 0, 0);
    boardPWM[i].setPWM(13, 0, 0);
    boardPWM[i].setPWM(14, 0, 0);
    boardPWM[i].setPWM(15, 0, 0);
  }

}
void demoMode() {

  //Demo Piece 1 --> Field 24 --> Positive Magnetic Feedback.
  
  pixels.setPixelColor(24, pixels.Color(ledBrightness, ledBrightness, ledBrightness));

  boardPWM[4].setPWM(8, 0, 0); //XXX Skal ændres til at passe til H-bridge.
  boardPWM[4].setPWM(9, 0, 0);
  boardPWM[4].setPWM(10, 0, 0);


  //Demo Piece 2 --> Field 33 --> Negative Magnetic Feedback.
  
  pixels.setPixelColor(33, pixels.Color(ledBrightness, ledBrightness, ledBrightness));

  boardPWM[6].setPWM(3, 0, 0); //XXX Skal ændres til at passe til H-bridge. Omvendt den første :)
  boardPWM[6].setPWM(4, 0, 0);
  boardPWM[6].setPWM(5, 0, 0);

  //Demo Piece 3 --> Field 26 --> Positive Vibration Feedback
  
  pixels.setPixelColor(26, pixels.Color(ledBrightness, ledBrightness, ledBrightness));

  boardPWM[4].setPWM(14, 0, 0); //XXX Skal ændres til at passe til H-bridge. 
  boardPWM[4].setPWM(15, 0, 0);
  boardPWM[5].setPWM(0, 0, 0);

  //Demo Piece 4 --> Field 35 --> Negative Vibration Feedback
  
  pixels.setPixelColor(35, pixels.Color(ledBrightness, ledBrightness, ledBrightness));

  boardPWM[6].setPWM(9, 0, 0); //XXX Skal ændres til at passe til H-bridge. 
  boardPWM[6].setPWM(10, 0, 0);
  boardPWM[6].setPWM(11, 0, 0);


  //Demo Piece 5 --> Field 28 --> Neutral Vibration Feedback
  
  pixels.setPixelColor(28, pixels.Color(ledBrightness, ledBrightness, ledBrightness));

  boardPWM[5].setPWM(4, 0, 0); //XXX Skal ændres til at passe til H-bridge. 
  boardPWM[5].setPWM(5, 0, 0);
  boardPWM[5].setPWM(6, 0, 0);

  //Demo Piece 6 --> Field 37 --> Slow Vibration Feedback
  
  pixels.setPixelColor(37, pixels.Color(ledBrightness, ledBrightness, ledBrightness));

  boardPWM[6].setPWM(15, 0, 0); //XXX Skal ændres til at passe til H-bridge. 
  boardPWM[7].setPWM(0, 0, 0);
  boardPWM[7].setPWM(1, 0, 0);

  //Demo Piece 7 --> Field 30 --> 
  
  pixels.setPixelColor(30, pixels.Color(ledBrightness, ledBrightness, ledBrightness));

  boardPWM[5].setPWM(10, 0, 0); //XXX Skal ændres til at passe til H-bridge.
  boardPWM[5].setPWM(11, 0, 0);
  boardPWM[5].setPWM(12, 0, 0);

  //Demo Piece 8 --> Field 39
  
  pixels.setPixelColor(39, pixels.Color(ledBrightness, ledBrightness, ledBrightness));

  boardPWM[7].setPWM(5, 0, 0); //XXX Skal ændres til at passe til H-bridge. 
  boardPWM[7].setPWM(6, 0, 0);
  boardPWM[7].setPWM(7, 0, 0);

}
