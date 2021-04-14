//============

#include "MUX74HC4067.h"

// Creates a MUX74HC4067 instance
// 1st argument is the Arduino PIN to which the EN pin connects
// 2nd-5th arguments are the Arduino PINs to which the S0-S3 pins connect


MUX74HC4067 mux(8, A0, A1, A2, A3);
MUX74HC4067 mux2(26, A5, A6, A7, A8);

byte dataMux;
byte dataMux2;

//============

const byte numPieces = 32;
char boardPieceDetector[numPieces] = {'1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'};
// 65 char boardPieceDetector[numPieces] = {'1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'};
void setup()
{
  Serial.begin(9600);
  Serial.println("<Arduino3 is ready>");

  // Configures how the SIG pin will be interfaced
  // e.g. The SIG pin connects to a ANALOG input
  mux.signalPin(A4, INPUT, ANALOG);
  mux2.signalPin(A9, INPUT, ANALOG);

}

void loop()
{
  readInputPieces();
}

void readInputPieces() {

  int data;
  int data2;

  for (byte i = 0; i < 16; ++i)
  {
    // Reads from channel i and returns HIGH or LOW
    dataMux = mux.read(i);
    dataMux2 = mux2.read(i);

    if (dataMux > 205) {
      boardPieceDetector[i] = '0';
    }

    if (dataMux2 > 205) {
      boardPieceDetector[i + 16] = '0';
    }
    else {
      boardPieceDetector[i] = '1';
      boardPieceDetector[i + 16] = '1';
    }
  }
}

void sendToPi() {
  Serial.print("<");
  for (int i = 0; i < 32; i++) {
    Serial.print(boardPieceDetector[i]);
  }
  Serial.println(">");
}
