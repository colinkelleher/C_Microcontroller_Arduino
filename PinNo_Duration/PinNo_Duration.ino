// CS3514 - C Programming for Microcontrollers
// Lab 1: Getting Started
// Write a C function that accepts a pin number 
// and a duration and output a HIGH on that pin for that duration.

// Colin Kelleher - 117303363
// 30 - Sept - 

void pinOn( int pinNum, int duration) {
  digitalWrite( pinNum, HIGH);
  delay (duration);
  digitalWrite( pinNum, LOW);
  
}

void setup() {
  pinMode (13, OUTPUT);
}

void loop () {
  pinOn (13, 500);
  delay (500);
}
