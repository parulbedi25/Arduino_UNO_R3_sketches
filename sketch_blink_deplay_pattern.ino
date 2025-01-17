
// SOS Message code //
// int ledPin=2;
// int dit = 50;
// int dah = 160;
// int Wait = 2000;

// void setup() {
//   pinMode(ledPin, OUTPUT);
// }

// void loop() {
//   digitalWrite(ledPin, HIGH);
//   delay(dit);
//   digitalWrite(ledPin, LOW);
//   delay(dit);
//     digitalWrite(ledPin, HIGH);
//   delay(dit);
//   digitalWrite(ledPin, LOW);
//   delay(dit);
//     digitalWrite(ledPin, HIGH);
//   delay(dit);
//   digitalWrite(ledPin, LOW);
//   delay(dah);
//     digitalWrite(ledPin, HIGH);
//   delay(dah);
//   digitalWrite(ledPin, LOW);
//   delay(dah);
//       digitalWrite(ledPin, HIGH);
//   delay(dah);
//   digitalWrite(ledPin, LOW);
//   delay(dah);

//     digitalWrite(ledPin, HIGH);
//   delay(dah);
//   digitalWrite(ledPin, LOW);
//   delay(dah);

//     digitalWrite(ledPin, HIGH);
//   delay(dit);
//   digitalWrite(ledPin, LOW);
//   delay(dit);
//       digitalWrite(ledPin, HIGH);
//   delay(dit);
//   digitalWrite(ledPin, LOW);
//   delay(dit);
//       digitalWrite(ledPin, HIGH);
//   delay(dit);
//   digitalWrite(ledPin, LOW);
//   delay(Wait);
// }



int redLed = 2;
int yellowLed = 3;
int greenLed = 4;

int redDelay = 200;
int yellowDelay = 600;
int greenDelay = 1000;

int redCount = 5;
int yellowCount = 10;
int greenCount = 15;

void setup() {
  pinMode(redLed, OUTPUT);
  pinMode(yellowLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
}

void loop() {
   for (int i = 0; i < redCount; i++) {
    digitalWrite(redLed, HIGH);
    delay(redDelay);
    digitalWrite(redLed, LOW);
    delay(redDelay);
  }


   for (int i = 0; i < yellowCount; i++) {
    digitalWrite(yellowLed, HIGH);
    delay(yellowDelay);
    digitalWrite(yellowLed, LOW);
    delay(yellowDelay);
  }

  for (int i = 0; i < greenCount; i++)
{
  digitalWrite(greenLed, HIGH);
  delay(greenDelay);
  digitalWrite(greenLed, LOW);
  delay(greenDelay);
}
  while(true);

}