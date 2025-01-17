int ledPin=2;
int dit = 50;
int dah = 160;
int Wait = 2000;

void setup() {
  pinMode(ledPin, OUTPUT);
}

void loop() {
  digitalWrite(ledPin, HIGH);
  delay(dit);
  digitalWrite(ledPin, LOW);
  delay(dit);
    digitalWrite(ledPin, HIGH);
  delay(dit);
  digitalWrite(ledPin, LOW);
  delay(dit);
    digitalWrite(ledPin, HIGH);
  delay(dit);
  digitalWrite(ledPin, LOW);
  delay(dah);
    digitalWrite(ledPin, HIGH);
  delay(dah);
  digitalWrite(ledPin, LOW);
  delay(dah);
      digitalWrite(ledPin, HIGH);
  delay(dah);
  digitalWrite(ledPin, LOW);
  delay(dah);

    digitalWrite(ledPin, HIGH);
  delay(dah);
  digitalWrite(ledPin, LOW);
  delay(dah);

    digitalWrite(ledPin, HIGH);
  delay(dit);
  digitalWrite(ledPin, LOW);
  delay(dit);
      digitalWrite(ledPin, HIGH);
  delay(dit);
  digitalWrite(ledPin, LOW);
  delay(dit);
      digitalWrite(ledPin, HIGH);
  delay(dit);
  digitalWrite(ledPin, LOW);
  delay(Wait);
}