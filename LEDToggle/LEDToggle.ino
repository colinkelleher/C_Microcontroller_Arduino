//CS3514 - C Programming for Microcontrollers
// Lab 2:

// Remove the pull-down resistor, engage the internal pull-up resistor 
// in the microcontroller and make any other 
// appropriate software changes to ensure that the 
// LED continues to toggle when the  button is released.

// Colin Kelleher - 117303353
// 07-Oct-2019
// Question 6
#define IN_PIN 8
#define OUT_PIN 13
#define MAX_BOUNCE_TIME 5

void setup(){
  pinMode(IN_PIN,  INPUT_PULLUP); //Internal pullup resistor
  pinMode(OUT_PIN, OUTPUT);
}
boolean debouncedRead(int pin, boolean state){
  if (digitalRead(pin) != state){
    delay(MAX_BOUNCE_TIME);
    return digitalRead(pin);
  } 
  return state;
}
void toggleOutPinWithInPin(int outPin, int inPin, int from, int to){
  static int currentInputState = LOW;
  static int prevInputState    = LOW;
  static int state             = LOW;
  
  currentInputState = debouncedRead(inPin, currentInputState);
  if (prevInputState == from && currentInputState == to)
    digitalWrite(outPin, (state = !state));
  prevInputState = currentInputState;
}
void loop(){
  toggleOutPinWithInPin(OUT_PIN, IN_PIN, LOW, HIGH);
}
