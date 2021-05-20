//============

#include "MUX74HC4067.h"

// Creates a MUX74HC4067 instance
// 1st argument is the Arduino PIN to which the EN pin connects
// 2nd-5th arguments are the Arduino PINs to which the S0-S3 pins connect


MUX74HC4067 mux(8, A0, A1, A2, A3);
MUX74HC4067 mux2(26, A8, A9, A10, A11);

int dataMux;
int dataMux2;


//============

const byte numPieces = 32;
char boardPieceDetector[numPieces] = {
  '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'};
// 65 char boardPieceDetector[numPieces] = {'1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'};
void setup()
{
  Serial.begin(9600);

  // Configures how the SIG pin will be interfaced
  // e.g. The SIG pin connects to a ANALOG input
  mux.signalPin(A4, INPUT, ANALOG);
  mux2.signalPin(A12, INPUT, ANALOG);


}

void loop()
{
  readInputPieces();
  
  sendToPi();
}

void readInputPieces() {

  int data;
  int data2;

  for(byte i = 0; i < 8; i++){

    dataMux = mux.read(i);
    dataMux2 = mux2.read(i);

    if (dataMux > 25) {
      boardPieceDetector[i+16] = '0';
    }
    else {
      boardPieceDetector[i+16] = '1';
    }

    if (dataMux2 > 25) {
      boardPieceDetector[i + 0] = '0';
    }
    else {
      boardPieceDetector[i + 0] = '1';
    }
  }
  for(byte i = 8; i < 16; i++){

    dataMux = mux.read(i);
    dataMux2 = mux2.read(i);

    if (dataMux > 25) {
      boardPieceDetector[i+16] = '0';
    }
    else {
      boardPieceDetector[i+16] = '1';
    }

    if (dataMux2 > 25) {
      boardPieceDetector[i + 0] = '0';
    }
    else {
      boardPieceDetector[i + 0] = '1';
    }
  }
  delay(200); 
}

void sendToPi() {
  Serial.print("<");
  for (int i = 0; i < 32; i++) {
    Serial.print(boardPieceDetector[i]);
  }
  Serial.println(">");
}

