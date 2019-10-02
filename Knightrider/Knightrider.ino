// CS3514 - C Programming for Microcontrollers
// Lab 1: Getting Started
// Knigh Rider - write code to get the LEDs to "chase" each other back and forth.

// Colin Kelleher - 117303363
// 30 - Sept - 2019


#define MIN 3 // First position of LED
#define MAX 9 // Last position of LED
int d = 20; // d = delay

// the setup function runs once when you press reset or power the board
void setup() {
  for (int pin = MIN; pin <= MAX; pin++){
    pinMode(pin, OUTPUT);
  }  
}

// the loop function runs over and over again forever
void loop() {
  for (int pin = MIN; pin < MAX; pin++){
      digitalWrite(pin, HIGH);
      delay(d);
      digitalWrite(pin, LOW);
  }
  
  for (int pin = MAX -1; pin >= MIN; pin--){
      digitalWrite(pin, HIGH);
      delay(d);
      digitalWrite(pin, LOW);  
  }
}
