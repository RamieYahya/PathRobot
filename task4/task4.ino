#include "IRremote.h"
#include "Servo.h"

#define SERVO 6
#define LDR1 0
#define LDR2 1
#define LED1 3
#define LED2 8


int receiver = 12; // Signal Pin of IR receiver to Arduino Digital Pin
int servoAngle = 90;
Servo turnServo = Servo();
int leftReading = 0;
int rightReading = 0;
int blackThreshold = 600;
int timeStep = 0;
boolean turnFlag = false;
int zeroAngle = 90;
int turnAngle = 30;
boolean alreadyTurning = false;
boolean go = false;
int numberOfGates = 0;

// Turning radius 11.5 in or 2.7 seconds

void setup()
{
  Serial.begin(9600);

  pinMode(9, OUTPUT); //transistor pin
  IrReceiver.begin(receiver, ENABLE_LED_FEEDBACK); // Start the receiver

  pinMode(LED1, OUTPUT);
  digitalWrite(LED1, HIGH);
  pinMode(LED2, OUTPUT);
  digitalWrite(LED2, HIGH);

  turnServo.attach(SERVO);
  turnServo.write(servoAngle);
  digitalWrite(9, LOW);
  delay(2000);
}

void loop()
{
    leftReading = analogRead(LDR1);
    rightReading = analogRead(LDR2);
    Serial.print(leftReading);
    Serial.print(",");
    Serial.println(rightReading);
  if (go) {
  

    int mil = millis();

    if (leftReading >= blackThreshold && (mil - timeStep) > 600) {
      if (numberOfGates == 6)
        go = false;
      timeStep = mil;
      if (!alreadyTurning) {
        alreadyTurning = true;
        turnWheel(-1);
      } else {
        alreadyTurning = false;
        turnWheel(1);
      }
      numberOfGates++;
    } else if (leftReading <= blackThreshold && rightReading  <= blackThreshold)
      turnFlag = false;

    digitalWrite(9, HIGH);
    delay(10);
    digitalWrite(9, LOW);
    delay(1);

  }
  if (IrReceiver.decode()) // have we received an IR signal?
  {
    if (IrReceiver.decodedIRData.decodedRawData == 3108437760) {  //vol+ button, uses raw value instead of hex
      Serial.println("up");
      //      digitalWrite(9, HIGH);  //transistor
      //      delay(2900); //
      //      digitalWrite(9, LOW);
      go = true;
    }
    else if (IrReceiver.decodedIRData.decodedRawData == 3927310080) { //vol- button
      Serial.println("down");
      digitalWrite(9, LOW);
      go = false;

    }
    else if (IrReceiver.decodedIRData.decodedRawData == 3141861120) { //skip to start button
      Serial.println("left");
      zeroAngle -= 2;
      resetWheel();
    }
    else if (IrReceiver.decodedIRData.decodedRawData == 3158572800) { //skip to end button
      Serial.println("right");
      zeroAngle += 2;
      resetWheel();
    } else if (IrReceiver.decodedIRData.decodedRawData == 4127850240) {//up key
      turnWheel(1);
    } else if (IrReceiver.decodedIRData.decodedRawData == 4161273600) { // Down key
      turnWheel(-1);
    }  else if (IrReceiver.decodedIRData.decodedRawData == 0xAD52FF00) {
      numberOfGates == 0;
      alreadyTurning = false;
      turnFlag = false;
      timeStep = -100;
    }
    IrReceiver.resume();
  }

}

void resetWheel() {
  if (zeroAngle > 135)
    zeroAngle = 135;
  else if (zeroAngle < 45)
    zeroAngle = 45;

  servoAngle = zeroAngle;
  turnServo.write(servoAngle);
}
void turnWheel (int dir) {
  servoAngle += dir * turnAngle;

  if (servoAngle > zeroAngle + turnAngle)
    servoAngle = zeroAngle + turnAngle;
  else if (servoAngle < zeroAngle - turnAngle)
    servoAngle = zeroAngle - turnAngle;;

  turnServo.write(servoAngle);
  delay(50);
}
