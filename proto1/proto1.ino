#include "IRremote.h"

#define ENABLE 5  //dc motor driver pins
#define DIRA 3
#define DIRB 4

int receiver = 12; // Signal Pin of IR receiver to Arduino Digital Pin


void setup()
{
  Serial.begin(9600);
  pinMode(ENABLE, OUTPUT);
  pinMode(DIRA, OUTPUT);
  pinMode(DIRB, OUTPUT);
  pinMode(9, OUTPUT); //transistor pin
  IrReceiver.begin(receiver, ENABLE_LED_FEEDBACK); // Start the receiver
}

void loop()
{
  if (IrReceiver.decode()) // have we received an IR signal?
  {
    if (IrReceiver.decodedIRData.decodedRawData == 3108437760) {  //vol+ button, uses raw value instead of hex
      Serial.println("up");
      //digitalWrite(DIRA, LOW);  //motor driver
      //digitalWrite(DIRB, HIGH);
      //digitalWrite(ENABLE, 255);
      //delay(1500);
      //digitalWrite(ENABLE, LOW);
      digitalWrite(9, HIGH);  //transistor
      delay(1000);
      digitalWrite(9, LOW);
    }
    else if (IrReceiver.decodedIRData.decodedRawData == 3927310080) { //vol- button
      Serial.println("down");
    }
    else if (IrReceiver.decodedIRData.decodedRawData == 3141861120) { //skip to start button
      Serial.println("left");
    }
    else if (IrReceiver.decodedIRData.decodedRawData == 3158572800) { //skip to end button
      Serial.println("right");
    }
    //Serial.println(IrReceiver.decodedIRData.decodedRawData);
    IrReceiver.resume();
  }
  digitalWrite(DIRA, HIGH);
  digitalWrite(DIRB, LOW);
}
