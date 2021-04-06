//============ Neopixel Code

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

// Arduino Output Pin for Neopixels
#define NEOPIXELPIN 47

// Number of Neopixels
#define NUMPIXELS 14

Adafruit_NeoPixel pixels(NUMPIXELS, NEOPIXELPIN, NEO_GRB + NEO_KHZ800);

int ledBrightness = 100;

//============

#include "MUX74HC4067.h"

// Creates a MUX74HC4067 instance
// 1st argument is the Arduino PIN to which the EN pin connects
// 2nd-5th arguments are the Arduino PINs to which the S0-S3 pins connect
//SIG pin = pin 3 = digitalPin = digitalRead;

MUX74HC4067 mux(8, 9, 10, 11, 12);
MUX74HC4067 mux2(26, 28, 30, 32, 34);
MUX74HC4067 mux3(40, 42, 44, 46, 48);
MUX74HC4067 mux4(49, 50, 51, 52, 53);

byte dataMux;
byte dataMux2;
byte dataMux3;
byte dataMux4;

//============ Side Buttons Code

int enablePwrLed = 10;
int enableModeLed = 11;
//int enableDemoLed = ;

//H-bridge Pins
int inputModeLed1 = 4;
int inputModeLed2 = 5;
//int inputFeedbackLed1 = ;
//int inputFeedbackLed2 = ;

//Button Pins
int buttonModePin = 8;
int buttonFeedbackPin = 0;

boolean buttonModeState = LOW;
boolean buttonFeedbackState = LOW;

int currentButtonModeState = 0;
int currentButtonFeedbackState = 0;
boolean oldButtonModeState = LOW;
boolean oldButtonFeedbackState = LOW;

//============

const byte numPieces = 65;
char boardPieceDetector[numPieces] = {'1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'};
//char boardPieceDetector[numPieces] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
void setup()
{
  Serial.begin(9600);
  pixels.begin(); // INITIALIZE NeoPixel strip object
  Serial.println("<Arduino2 is ready>");

  // Configures how the SIG pin will be interfaced
  // e.g. The SIG pin connects to PIN 13 on the Arduino and PIN 13 is a digital input
  mux.signalPin(13, INPUT, DIGITAL);
  mux2.signalPin(36, INPUT, DIGITAL);
  mux3.signalPin(23, INPUT, DIGITAL);
  mux4.signalPin(25, INPUT, DIGITAL);

  // Button Setup

  pinMode(buttonModePin, INPUT);
  pinMode(buttonFeedbackPin, INPUT);

  powerOffAllLEDs();

}

void loop()
{
  //pixels.clear(); // Set all pixel colors to 'off'
  pixels.show();  // Send the updated pixel colors to the hardware.

  //readInputPieces();
  buttonState();
  modeSelector();
  sendToPi();
}


void readInputPieces() {
  for (byte i = 0; i < 16; ++i)
  {
    // Reads from channel i and returns HIGH or LOW
    dataMux = mux.read(i);
    dataMux2 = mux2.read(i);
    dataMux3 = mux3.read(i);
    dataMux4 = mux4.read(i);
    boardPieceDetector[i + 1] = dataMux;
    boardPieceDetector[i + 1 + 16] = dataMux2;
    boardPieceDetector[i + 1 + 32] = dataMux3;
    boardPieceDetector[i + 1 + 48] = dataMux4;
    /*
      Serial.print("Push button at channel ");
      Serial.print(i);
      Serial.print(" is ");
      Serial.print(currentButtonModeState);
      if ( dataMux == HIGH ) Serial.println("not pressed");
      else if ( dataMux == LOW ) Serial.println("pressed");
    */
  }
}

void buttonState() {

  buttonFeedbackState = digitalRead(buttonFeedbackPin);
  buttonModeState = digitalRead(buttonModePin);

  if (buttonModeState != oldButtonModeState) {
    if (buttonModeState == HIGH) {
      if (currentButtonModeState < 3) {
        currentButtonModeState ++;
      } else {
        currentButtonModeState = 0;
      }
      delay(100);
    }
  }

  if (buttonFeedbackState != oldButtonFeedbackState) {
    if (buttonFeedbackState == HIGH) {
      if (currentButtonFeedbackState < 4) {
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
  pixels.setPixelColor((buttonLightFeedbackValue + 3), pixels.Color(ledBrightness, ledBrightness, ledBrightness));
}

void modeSelector() {
  if (currentButtonModeState == 0) {
    boardPieceDetector[0] = '0';

  } else if (currentButtonModeState == 1) {
    boardPieceDetector[0] = '1';


  } else if (currentButtonModeState == 2) {

    switch (currentButtonFeedbackState) {
      case 0:
        boardPieceDetector[0] = 2;
        break;
      case 1:
        boardPieceDetector[0] = 3;
        break;
      case 2:
        boardPieceDetector[0] = 4;
        break;
      case 3:
        boardPieceDetector[0] = 5;
        break;
      default:
        break;
    }
  }
}

void sendToPi() {
  Serial.print("<");
  for (int i = 0; i < 65; i++) {
    Serial.print(boardPieceDetector[i]);
  }
  Serial.println(">");
}
