#include "IRremote.h"

int receiver = 12; // Signal Pin of IR receiver to Arduino Digital Pin


void setup()
{
  Serial.begin(9600);
  IrReceiver.begin(receiver, ENABLE_LED_FEEDBACK); // Start the receiver
}

void loop()
{
  if (IrReceiver.decode()) // have we received an IR signal?
  {
    if (IrReceiver.decodedIRData.decodedRawData == 3108437760) {  //vol+ button, uses raw value instead of hex
      Serial.println("up");
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
}
