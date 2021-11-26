const int LDR_PIN = 0;
const int LED1 = 3;
const int LED2 = 4;
int reading = 0;

void setup() {
  pinMode (LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  digitalWrite(LED1,HIGH);
  digitalWrite(LED2,HIGH);
  Serial.begin(9600);
}

void loop() {
  reading = analogRead(LDR_PIN);
  Serial.println(reading);

}
