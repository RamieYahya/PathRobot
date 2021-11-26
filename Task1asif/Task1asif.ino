#include "IRremote.h"
#include <Servo.h>

int receiver = 12; // Signal Pin of IR receiver to Arduino Digital Pin
const int ldrR = A0;
const int ldrL = A1;
int Lbench, Rbench;
int thresh = 150;
int dir = 0;

Servo myservo;

void setup()
{
  Serial.begin(9600);
  pinMode(9, OUTPUT);
  myservo.attach(8);
  IrReceiver.begin(receiver, ENABLE_LED_FEEDBACK); // Start the receiver
  pinMode(ldrR, INPUT);
  pinMode(ldrL, INPUT);
}

void loop()
{
  int ldrRread = analogRead(ldrR);
  int ldrLread = analogRead(ldrL);
  if (IrReceiver.decode()) // have we received an IR signal?
  {
    if (IrReceiver.decodedIRData.decodedRawData == 3108437760) {  //vol+ button, uses raw value instead of hex
      //Serial.println("up");
      digitalWrite(9, HIGH);
      if (dir == 0) {
        delay(2000);
      }
      else if (dir == 1) {
        delay(1000);
      }
      else if (dir == 2) {
        delay(1400);
      }
      digitalWrite(9, LOW);
    }
    else if (IrReceiver.decodedIRData.decodedRawData == 3927310080) { //vol- button
      //Serial.println("down");
      myservo.write(90);
      dir = 0;
    }
    else if (IrReceiver.decodedIRData.decodedRawData == 3141861120) { //skip to start button
      //Serial.println("left");
      myservo.write(180 - 30);
      dir = 2;
      
    }
    else if (IrReceiver.decodedIRData.decodedRawData == 3158572800) { //skip to end button
      //Serial.println("right");
      myservo.write(0 + 30);
      dir = 1;
    }
    else if (IrReceiver.decodedIRData.decodedRawData == 3860463360) { //eq button
      Lbench = ldrLread;
      Rbench = ldrRread;
    }
    Serial.println(IrReceiver.decodedIRData.decodedRawData);
    IrReceiver.resume();
  }

//  if (ldrLread > Lbench + 150) {
//    myservo.write(90+15);
//  }
//  else if (ldrRread > Rbench + 150) {
//    myservo.write(90-15);
//  }
//  else if ((ldrRread < Rbench + 150) && (ldrLread > Lbench + 150)) {
//    myservo.write(90);
//  }

  Serial.print("right ");
  Serial.print(ldrRread);
  Serial.print("    left  ");
  Serial.println(ldrLread);
}
