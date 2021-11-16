#include <IRremote.h>

//Pins in use -----------------------
// IR Reciever
int IR_RECEIVE_PIN = 12;

void setup() {
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK); // Start the receiver
  Serial.begin(9600);
}

void loop() {
  // no signal results = 0
 if (IrReceiver.decode()) {
      Serial.println(IrReceiver.decodedIRData.decodedRawData, HEX);
      //IrReceiver.printIRResultShort(&Serial); // optional use new print version
      
      IrReceiver.resume(); // Enable receiving of the next value
  }

  

}
