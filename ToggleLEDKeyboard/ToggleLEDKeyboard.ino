//CS3514 - C Programming for Microcontrollers
// Lab 2:

// Write code to toggle the led by pressing a key on  
// the keyboard of the PC. 
// Report the LED status back to the the computer screen.

// Colin Kelleher - 117303353
// 07-Oct-2019

// Question 6
#define IN_PIN 8
#define OUT_PIN 13
char input = 0;
int prev = 0;

void setup(){
  pinMode(IN_PIN,  INPUT_PULLUP);
  pinMode(OUT_PIN, OUTPUT);
  Serial.begin(9600);
}

void toggle(){
  int current = !prev;
  digitalWrite(OUT_PIN, current);
  prev = current;
  if ( current == 1 ){
    Serial.write("LED turned on\n");// if current = 1 (LED ON)
  }else{
    Serial.write("LED turned off\n");
  }
}
void loop(){
  input = Serial.read();
  if ((input >= 't') ) { // the letter 't' is used on the keyboard
    // to toggle the LED on & off
        toggle();
    }
}
