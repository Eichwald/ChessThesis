int vibrationState = 0; //positive vibrationState
int vibrationState2 = 0; //Negative vibrationState

unsigned long vibrationStarted = 0; //Varible for millis

const long interval = 10; //interval for vibrations

int clickingState = 0; 
const long clickingInterval = 100; //Interval for clicking
unsigned long clickingStarted = 0;


int fadingState = 0;
const long fadingInterval = 10; //interval for fadingState
unsigned long fadingStarted = 0;

//============ Neopixel Code
#include <Adafruit_NeoPixel.h>


// Arduino Output Pin for Neopixels
#define NEOPIXELPIN 2

// Number of Neopixels
#define NUMPIXELS 128

Adafruit_NeoPixel pixels(NUMPIXELS, NEOPIXELPIN, NEO_GRB + NEO_KHZ800);

// Turn down NeoPixel brightness
int ledBrightness = 100;

//============= PWM Shield Code

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// Initiates the pwm boards. Based on indexing
Adafruit_PWMServoDriver pwm1 = Adafruit_PWMServoDriver(0x40);
Adafruit_PWMServoDriver pwm2 = Adafruit_PWMServoDriver(0x41);
Adafruit_PWMServoDriver pwm3 = Adafruit_PWMServoDriver(0x42);
Adafruit_PWMServoDriver pwm4 = Adafruit_PWMServoDriver(0x43);
Adafruit_PWMServoDriver pwm5 = Adafruit_PWMServoDriver(0x44);
Adafruit_PWMServoDriver pwm6 = Adafruit_PWMServoDriver(0x45);
Adafruit_PWMServoDriver pwm7 = Adafruit_PWMServoDriver(0x46);
Adafruit_PWMServoDriver pwm8 = Adafruit_PWMServoDriver(0x47);
Adafruit_PWMServoDriver pwm9 = Adafruit_PWMServoDriver(0x48);
Adafruit_PWMServoDriver pwm10 = Adafruit_PWMServoDriver(0x49);
Adafruit_PWMServoDriver pwm11 = Adafruit_PWMServoDriver(0x4A);
Adafruit_PWMServoDriver pwm12 = Adafruit_PWMServoDriver(0x4B);

//Board Output Controllers.
// Char array with length of 65
const char numChars = 65;
char receivedChars[numChars];
boolean newData = false;
//char boardPieceController[numChars];
char boardPieceController[numChars] = {
  '0',
  '0','0','0','0','0','0','0','0',
  '0','0','0','0','0','0','0','0',
  '0','0','0','0','0','0','0','0',
  '0','0','0','0','0','0','0','0',
  '0','0','0','0','0','0','0','0',
  '0','0','0','0','0','0','0','0',
  '0','0','0','0','0','0','0','0',
  '0','0','0','0','0','0','0','0'};

// Array of pwm boards
const byte numPWMBoards = 12;
Adafruit_PWMServoDriver boardPWM[numPWMBoards] = {
  pwm1, pwm2, pwm3, pwm4, pwm5, pwm6, pwm7, pwm8, pwm9, pwm10, pwm11, pwm12};

//=============

void setup() {
  Serial.begin(9600);
  pixels.begin(); // INITIALIZE NeoPixel strip object
  
  // Begin PWM boads
  for (byte n = 0; n < numPWMBoards; n++) {
    boardPWM[n].begin();
    boardPWM[n].setOscillatorFrequency(27000000);
    boardPWM[n].setPWMFreq(1600);
  }
}

//=============

void loop() {

  communicateWithPi(); //Recieve data from Raspberry
  updateBoard(); // Update board based on data from Raspberry
  pixels.show(); // Update NeoPixels
  if (boardPieceController[0] != '1') { //No daley in Demo Mode
    delay(100); 
  }

}


void communicateWithPi(){
  // Method for recieving data from Raspberry
  // Reads stsring between letter 8 and letter 9
  // Using numbers as identifiers for start and end
  // Updates Char array based on input from Raspberry
  while(Serial.available() > 0) {
    delay(10);
    String str = Serial.readStringUntil('9');
    int str_len = str.length() + 1; 
    char new_char_arr[str_len];
    str.toCharArray(new_char_arr, str_len);
    if(new_char_arr[0] == '8'){
      for (int i = 0; i  < 65; i++) {
        boardPieceController[i] = new_char_arr[i + 1];
      }
    }
  }
}


//============

void updateBoard() {
  // Based on the first index - Game mode - choose what to update
  if (boardPieceController[0] == '0') {//No Visual or Magnetic Feedback.
    turnOffVisual();
    turnOffMagnet();
  }

  else if (boardPieceController[0] == '1') {//DemoMode :)

    demoMode();
  }

  else if (boardPieceController[0] == '2') {//No Visual or Magnetic Feedback.

    turnOffVisual();
    turnOffMagnet();
  }

  else if (boardPieceController[0] == '3') {//Visual Feedback --> No Magnetic Feedback.
    updateLED();
  }

  else if (boardPieceController[0] == '4') {//Magnetic Feedback --> No Visual Feedback.
    turnOffVisual();
    updateMagnet();
  }

  else if (boardPieceController[0] == '5') {//T??nd magnetic og visual feedback
    updateLED();
    updateMagnet();

  }
}

//=============

void updateLED() {
  // Choose color (or turned off) based on char array
  for (int i = 0; i < NUMPIXELS / 2; i++) {
    if (boardPieceController[i + 1] == '1' || boardPieceController[i + 1] == '2') {
      pixels.setPixelColor(i * 2, pixels.Color(ledBrightness, ledBrightness, ledBrightness)); //Multiply i with 2
    }
    else {
      pixels.setPixelColor(i * 2, pixels.Color(0, 0, 0)); //Multiply i with 2
    }
  }
}

//=============

void updateMagnet() {

  // Method for chooseing which pin is for which electromagnet.
  // Each h bridge needs 3 pin one electromagnet
  // Choses pin and board
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
    // Sets PWM on the pins based on move
    if (boardPieceController[i + 1] == '2') { //Legal and Good Move. Attracts Magnet.
      boardPWM[boardNumber1].setPWM(pinNumber1, 0, 0);
      boardPWM[boardNumber2].setPWM(pinNumber2, 0, 4095);
      boardPWM[boardNumber3].setPWM(pinNumber3, 0, 4095);
    }
    else if (boardPieceController[i + 1] == '3') {//Illegal nove --> Pushes Magnet away.
      boardPWM[boardNumber1].setPWM(pinNumber1, 0, 4095);
      boardPWM[boardNumber2].setPWM(pinNumber2, 0, 0);
      boardPWM[boardNumber3].setPWM(pinNumber3, 0, 4095);
    }
    else if (boardPieceController[i + 1] == '4') { //Helding pieces to board
      boardPWM[boardNumber1].setPWM(pinNumber1, 0, 0);
      boardPWM[boardNumber2].setPWM(pinNumber2, 0, 4095);
      boardPWM[boardNumber3].setPWM(pinNumber3, 0, 2650);
    }
    else {
      boardPWM[boardNumber1].setPWM(pinNumber1, 0, 0);
      boardPWM[boardNumber2].setPWM(pinNumber2, 0, 0);
      boardPWM[boardNumber3].setPWM(pinNumber3, 0, 0);
    }
  }
}

void turnOffVisual() {
  // turns of NeoPixel
  for (int i = 0; i < NUMPIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(0, 0, 0)); //Multiply i with 2
  }
}

void turnOffMagnet() {
  // Turns off all electromagnets
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

  pixels.setPixelColor(24*2, pixels.Color(ledBrightness, ledBrightness, ledBrightness));

  boardPWM[4].setPWM(8, 0, 4095);
  boardPWM[4].setPWM(9, 0, 0);
  boardPWM[4].setPWM(10, 0, 4095);


  //Demo Piece 2 --> Field 33 --> Negative Magnetic Feedback.

  pixels.setPixelColor(33*2, pixels.Color(ledBrightness, ledBrightness, ledBrightness));

  boardPWM[6].setPWM(3, 0, 0); 
  boardPWM[6].setPWM(4, 0, 4095);
  boardPWM[6].setPWM(5, 0, 4095);

  //Demo Piece 3 --> Field 26 --> Positive Vibration Feedback


  pixels.setPixelColor(26*2, pixels.Color(ledBrightness, ledBrightness, ledBrightness));

  unsigned long currentMillis = millis();

  if (currentMillis - vibrationStarted >= interval) {
    vibrationStarted = currentMillis;

    if (vibrationState == 0) {
      vibrationState = 4095;
      vibrationState2 = 0;
    } 
    else {
      vibrationState = 0;
      vibrationState2 = 4095;
    }

  }

  boardPWM[4].setPWM(14, 0, vibrationState); 
  boardPWM[4].setPWM(15, 0, 0);
  boardPWM[5].setPWM(0, 0, 4095);

  //Demo Piece 4 --> Field 35 --> Negative Vibration Feedback

  pixels.setPixelColor(35*2, pixels.Color(ledBrightness, ledBrightness, ledBrightness));

  boardPWM[6].setPWM(9, 0, 0);
  boardPWM[6].setPWM(10, 0, vibrationState);
  boardPWM[6].setPWM(11, 0, 4095);


  //Demo Piece 5 --> Field 28 --> Neutral Vibration Feedback

  pixels.setPixelColor(28*2, pixels.Color(ledBrightness, ledBrightness, ledBrightness));

  boardPWM[5].setPWM(4, 0, vibrationState); 
  boardPWM[5].setPWM(5, 0, vibrationState2);
  boardPWM[5].setPWM(6, 0, 4095);

  //Demo Piece 6 --> Field 37 --> neutral Vibration Feedback piece shakingu

  pixels.setPixelColor(37*2, pixels.Color(ledBrightness, ledBrightness, ledBrightness));

  boardPWM[6].setPWM(15, 0, vibrationState); 
  boardPWM[7].setPWM(0, 0, vibrationState2);
  boardPWM[7].setPWM(1, 0, 2860);

  //Demo Piece 7 --> Field 30 --> clicking slowly

  if (currentMillis - clickingStarted >= clickingInterval) {
    clickingStarted = currentMillis;

    if (clickingState == 0) {
      clickingState = 4095;

    } 
    else {
      clickingState = 0;
    }
  }

  pixels.setPixelColor(30*2, pixels.Color(ledBrightness, ledBrightness, ledBrightness));

  boardPWM[5].setPWM(10, 0, clickingState); 
  boardPWM[5].setPWM(11, 0, 0);
  boardPWM[5].setPWM(12, 0, 4095);



  //Demo Piece 8 --> Field 39 --> Fading effect


  if (currentMillis - fadingStarted >= fadingInterval) {
    fadingStarted = currentMillis;

    if (fadingState < 4095) {
      fadingState += 80;    
    } 
    else {
      fadingState = 1000;
    }
  }

  pixels.setPixelColor(39*2, pixels.Color(ledBrightness, ledBrightness, ledBrightness));

  boardPWM[7].setPWM(5, 0, 4095); 
  boardPWM[7].setPWM(6, 0, 0);
  boardPWM[7].setPWM(7, 0, fadingState);

}






