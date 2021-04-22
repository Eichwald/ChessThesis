//============ Neopixel Code

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

// Arduino Output Pin for Neopixels
#define NEOPIXELPIN 2

// Number of Neopixels
#define NUMPIXELS 14

Adafruit_NeoPixel pixels(NUMPIXELS, NEOPIXELPIN, NEO_GRB + NEO_KHZ800);

int ledBrightness = 100;

//============

#include "MUX74HC4067.h"

// Creates a MUX74HC4067 instance
// 1st argument is the Arduino PIN to which the EN pin connects
// 2nd-5th arguments are the Arduino PINs to which the S0-S3 pins connect


MUX74HC4067 mux(8, A0, A1, A2, A3);
MUX74HC4067 mux2(26, A8, A9, A10, A11);

byte dataMux;
byte dataMux2;

//============ Side Buttons Code

//int enablePwrLed = 41;
//int enableModeLed = 43;
//int enableDemoLed = ;

//H-bridge Pins
//int inputModeLed1 = 4;
//int inputModeLed2 = 5;
//int inputFeedbackLed1 = ;
//int inputFeedbackLed2 = ;

//Button Pins
int buttonModePin = 43;
int buttonFeedbackPin = 41;

boolean buttonModeState = LOW;
boolean buttonFeedbackState = LOW;

int currentButtonModeState = 0;
int currentButtonFeedbackState = 0;
boolean oldButtonModeState = LOW;
boolean oldButtonFeedbackState = LOW;

//============

const byte numPieces = 33;
char boardPieceDetector[numPieces] = {'1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'};
// 65 char boardPieceDetector[numPieces] = {'1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'};
void setup()
{
  Serial.begin(9600);
  pixels.begin(); // INITIALIZE NeoPixel strip object
  Serial.println("<Arduino2 is ready>");

  // Configures how the SIG pin will be interfaced
  // e.g. The SIG pin connects to a ANALOG input
  mux.signalPin(A4, INPUT, ANALOG);
  mux2.signalPin(A12, INPUT, ANALOG);

  // Button Setup

  pinMode(buttonModePin, INPUT);
  pinMode(buttonFeedbackPin, INPUT);

  powerOffAllLEDs();

}

void loop()
{
  //pixels.clear(); // Set all pixel colors to 'off'
  pixels.show();  // Send the updated pixel colors to the hardware.

  readInputPieces();
  buttonState();
  modeSelector();
  //sendToPi();
}


void readInputPieces() {

  int data;
  int data2;

  for (byte i = 8; i < 16; ++i)
  {
    // Reads from channel i and returns HIGH or LOW
    dataMux = mux.read(i);
    dataMux2 = mux2.read(i);

    if (dataMux > 25) {
      boardPieceDetector[i + 1 - 8] = '0';
    }
    else{
      boardPieceDetector[i + 1 - 8] = '1';
    }

    if (dataMux2 > 25) {
      boardPieceDetector[i + 1 + 16 - 8] = '0';
    }
    else {
      boardPieceDetector[i + 1 + 16 - 8] = '1';
    }
    Serial.print(i - 8 + 1);
    Serial.print(": ");
    Serial.println(dataMux); 
    Serial.print(i + 16 - 8 + 1);
    Serial.print(": ");
    Serial.println(dataMux2); 
  }
  for (byte i = 0; i < 8; ++i)
  {
    // Reads from channel i and returns HIGH or LOW
    dataMux = mux.read(i);
    dataMux2 = mux2.read(i);

    if (dataMux > 25) {
      boardPieceDetector[i + 1 + 8] = '0';
    }
    else{
      boardPieceDetector[i + 1 + 8] = '1';
    }

    if (dataMux2 > 25) {
      boardPieceDetector[i + 1 + 16 + 8] = '0';
    }
    else {
      boardPieceDetector[i + 1 + 16 + 8] = '1';
    }
    Serial.print(i + 8 + 1);
    Serial.print(": ");
    Serial.println(dataMux); 
    Serial.print(i + 16 + 8 + 1);
    Serial.print(": ");
    Serial.println(dataMux2); 
  }
  delay(200);
}

void buttonState() {

  buttonFeedbackState = digitalRead(buttonFeedbackPin);
  buttonModeState = digitalRead(buttonModePin);

  if (buttonModeState != oldButtonModeState) {
    if (buttonModeState == HIGH) {
      if (currentButtonModeState < 2) {
        currentButtonModeState ++;
      } else {
        currentButtonModeState = 0;
      }
      delay(100);
    }
  }

  if (buttonFeedbackState != oldButtonFeedbackState) {
    if (buttonFeedbackState == HIGH) {
      if (currentButtonFeedbackState < 3) {
        currentButtonFeedbackState ++;
      } else {
        currentButtonFeedbackState = 0;
      }
      delay(100);
    }
  }
  oldButtonModeState = buttonModeState;
  oldButtonFeedbackState = buttonFeedbackState;

  buttonLightControl(currentButtonModeState, currentButtonFeedbackState);

}

void powerOffAllLEDs()
{
  for (int i = 0; i < NUMPIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(0, 0, 0));
  }
}

void buttonLightControl(int buttonLightModeValue, int buttonLightFeedbackValue) {

  powerOffAllLEDs();
  pixels.setPixelColor(buttonLightModeValue, pixels.Color(ledBrightness, ledBrightness, ledBrightness));
  pixels.setPixelColor((buttonLightFeedbackValue + 7), pixels.Color(ledBrightness, ledBrightness, ledBrightness));
}

void modeSelector() {
  if (currentButtonModeState == 0) {
    boardPieceDetector[0] = '0';

  } else if (currentButtonModeState == 1) {
    boardPieceDetector[0] = '1';


  } else if (currentButtonModeState == 2) {

    switch (currentButtonFeedbackState) {
      case 0:
        boardPieceDetector[0] = '2';
        break;
      case 1:
        boardPieceDetector[0] = '3';
        break;
      case 2:
        boardPieceDetector[0] = '4';
        break;
      case 3:
        boardPieceDetector[0] = '5';
        break;
      default:
        break;
    }
  }
}

void sendToPi() {
  Serial.print("<");
  for (int i = 0; i < 33; i++) {
    Serial.print(boardPieceDetector[i]);
  }
  Serial.println(">");
}
