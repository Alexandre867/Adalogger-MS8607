// Wire Controller Reader
// by Nicholas Zambetti <http://www.zambetti.com>

// Demonstrates use of the Wire library
// Reads data from an I2C/TWI peripheral device
// Refer to the "Wire Peripheral Sender" example for use with this

// Created 29 March 2006

// This example code is in the public domain.


#include <Wire.h>

void setup() {
  Wire.begin();        // join i2c bus (address optional for master)
  Serial.begin(9600);  // start serial for output
  pinMode(13, OUTPUT); // initialize digital pin 13 as an output.
}

void loop() {
  digitalWrite(13, HIGH); // turn the LED on (HIGH is the voltage level)
  Wire.requestFrom(0x40, 30);    // request 30 bytes from peripheral device #0x40

  Serial.println("-- Start --");         // print start
  while (Wire.available()) { // peripheral may send less than requested
    char c = Wire.read(); // receive a byte as character
    Serial.print(c);         // print the character
  }
  Serial.println("-- Start --");         // print start
  digitalWrite(13, LOW); // turn the LED off by making the voltage LOW

  delay(1000);
}