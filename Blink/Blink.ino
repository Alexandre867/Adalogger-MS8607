

const int dit_length = 200;

const int pinout = 13; 

void dot() {
  digitalWrite(pinout, HIGH); // turn the LED on (HIGH is the voltage level)
  delay(dit_length); // wait for some time
  digitalWrite(pinout, LOW); // turn the LED off by making the voltage LOW
}

void dash() {
  digitalWrite(pinout, HIGH); // turn the LED on (HIGH is the voltage level)
  delay(dit_length*3); // wait for some time
  digitalWrite(pinout, LOW); // turn the LED off by making the voltage LOW
}

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin pinout as an output.
  pinMode(pinout, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
 // digitalWrite(pinout, HIGH); // turn the LED on (HIGH is the voltage level)
 // delay(1000); // wait for a second
 // digitalWrite(pinout, LOW); // turn the LED off by making the voltage LOW
 // delay(1000); // wait for a second

// Sending SOS

  dot();
  delay(dit_length);
  dot();
  delay(dit_length);
  dot();

  delay(dit_length*3);

  dash();
  delay(dit_length);
  dash();
  delay(dit_length);
  dash();

  delay(dit_length*3);

  dot();
  delay(dit_length);
  dot();
  delay(dit_length);
  dot();

  delay(dit_length*7);
}

