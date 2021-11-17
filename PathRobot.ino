#include <IRremote.h>

//Pins in use -----------------------
// IR Reciever
int IR_RECEIVE_PIN = 12;

// DC Motor
const int ENABLE = 5;
const int DIRA = 3;
const int DIRB = 4;

//LDRs
const int LEFT_LDR = 6;
const int RIGHT_LDR = 7;
int leftReading = 0;
int rightReading = 0;
int whiteThreshold = 0;

void setup() {
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK); // Start the receiver
  Serial.begin(9600);

  // Set up motor pins direction and voltage
  pinMode(ENABLE, OUTPUT);
  pinMode(DIRA, OUTPUT);
  pinMode(DIRB, OUTPUT);
  digitalWrite(DIRA, LOW);
  digitalWrite(DIRB, HIGH);
  digitalWrite(ENABLE, LOW);
}


void loop() {
  leftReading = analogRead (LEFT_LDR);
  rightReading = analogRead (RIGHT_LDR);

  if (leftReading < whiteThreshold && rightReading < whiteThreshold) {
    digitalWrite (ENABLE, HIGH);
  } else if (leftReading >= whiteThreshold && rightReading >= whiteThreshold) {
    digitalWrite (ENABLE, LOW);
  } else if (leftReading >= whiteThreshold) {
    // Turn right
  } else {
    // Turn Left
  }


  // no signal results = 0
  if (IrReceiver.decode()) {
    Serial.println(IrReceiver.decodedIRData.decodedRawData, HEX);
    //IrReceiver.printIRResultShort(&Serial); // optional use new print version

    IrReceiver.resume(); // Enable receiving of the next value
  }

}
