// CS3514 - C Programming for Microcontrollers
// Lab 3

// Update your program to read in characters from the serial monitor 
// running on the PC and sound the corresponding note and use the 
// space character to represents a period of silence.

// Colin Kelleher - 117303363
// 14-10-2019

#define MIDDLE_C 1911
#define D 1702
#define E 1517
#define F 1432
#define G 1276
#define A 1136
#define B 1012
#define HIGH_C 956

#define OUTPUTPIN 8

char input = ' ';
void setup() {
  // put your setup code here, to run once:
    pinMode(OUTPUTPIN, OUTPUT);
    Serial.begin(9600); 
}

int play(float d){
  for (int i = 0; i < 200; i++){
    digitalWrite(OUTPUTPIN, HIGH);
    delayMicroseconds(d);
    digitalWrite(OUTPUTPIN, LOW);
    delayMicroseconds(d);
  }
  return 1;
}

void loop() {
  // put your main code here, to run repeatedly:
  input = Serial.read();
  if ((input == ' ') ) {
    digitalWrite(OUTPUTPIN, LOW);
  } else if((input == 'c')){
    play(MIDDLE_C);
  } else if((input == 'd')){
    play(D);
  } else if((input == 'e')){
    play(E);
  } else if((input == 'f')){
    play(F);
  } else if((input == 'g')){
    play(G);
  } else if((input == 'a')){
    play(A);
  } else if((input == 'b')){
    play(B);
  } else if((input == 'C')){
    play(HIGH_C);
  }
}
