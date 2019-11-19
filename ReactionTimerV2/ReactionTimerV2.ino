/*
 *  CS3514 - C programming for Microcontrollers
 *  Lab5
 *  
 *  Colin Kelleher - 117303363
 *  
 *  Update the reaction timer from Session 5 to turn it into a 2 player game as follows:
 *  When a start button is pressed a 3 round game is initiated and the buzzer should sound after a random number of seconds (<10)
 *  
 *  When the buzzer sounds, each player reacts by pressing a button. The reaction time difference should be displayed on the LCD. 
 *  In addition, the round winner should be indicated by a green LED and the loser by a red LED.
 *  
 *  The game should continue with the buzzer sounding after a random  number of seconds. After 3 rounds have been completed, 
 *  the overall winner should be displayed on the LED together with the total time difference between the winner and loser.
 *  
 *  If a player presses their button before the buzzer sounds in any round, 
 *  they should be reported as the loser and the game should terminate. 
 */

 // Include the library code
#include <LiquidCrystal.h>


// Define Statements with Port Addresses
#define BUZZER B100000 // PORT 13 on Arduino
#define PLAYER1_BTTN B001000 // PORT 11 on Arduino
#define PLAYER2_BTTN B010000 // PORT 12 on Arduino
#define P2_WIN_LED B000001 // PORT 8 on Arduino
#define P1_WIN_LED B000010 // PORT 9 on Arduino
#define START_BUTTON B000100 // PORT 10 on Arduino

// Set the cursor to print on Line One of the LCD Display
#define printLineOne lcd.setCursor(0, 0); lcd.print
// Set the cursor to print on Line Two of the LCD Display
#define printLineTwo lcd.setCursor(0, 1); lcd.print

// Initialize the library by associating any needed LCD interface pins
// with the Arduino Pin it is connected to. 
const int rs = 12, en = 11, d4 = 2, d5 = 3, d6 = 4, d7 = 5;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// SETUP Function
void setup() {
  Serial.begin(9600); // Sets the data rate in bits per second (baud) for serial data transmission.

// PORT B maps to Arduino digital Pins 8 to 18.
  DDRB = B100011; // The Port B Data Direction Register = Read/Write
  PORTB = B011100; // The Port B Data Register - Read/Write

  // Begin position on LCD.
  lcd.begin(16, 2);
  printLineOne("Press Start Button!"); // Start message printed on LCD - start button must be pressed to begin game
}

// Loop Function
void loop() {
  if (!(PINB & START_BUTTON)){ // if the start button is pressed
    int timeDiff = 0; // keep track of the time difference 
    delay(500);
    for (int i=0; i<3; i++){ // keeps track of the rounds - 3 rounds required 
      PORTB = B011100;
      delay(1000);
      int resultTime = startRound();
      if (resultTime == -1 || resultTime == -2){ // If the result time is minus one or minus two (i.e.Pressed too early)
        earlyButtonPress(resultTime); // Run the earlyButtonPressed code from below
        continue; // Once the earlyButtonPressed code is run, continue with the code below. 
      }
      lcd.clear();
      timeDiff += resultTime; // Update the time difference variable 
      displayWinner(resultTime < 0); // Call the display winner on the LCD
      printLineTwo(resultTime);
      delay(5000);
    }
    char winner = timeDiff < 0 ? '1' : '2';
    displayWinner(timeDiff < 0); // Call the displayWinner function to display the winner
    lcd.clear(); // clear the LCD
    if (timeDiff < 0){
      printLineOne("Player 1 Wins!");
    } else {
      printLineOne("Player 2 Wins!");
    }
    printLineTwo(timeDiff); // On line two - Print the time difference between the players
  }
}

// Starting a Round Function 
int startRound(){
  // randomSeed - random number generalor
  randomSeed(analogRead(0));
  delay(random(10)); // Random delay between 0 - 10
  int player1Time = 0; // keep track of player 1's time
  int player2Time = 0; // keep track of player 2's time
  PORTB = PORTB ^ BUZZER; // toggle the buzzer
  delay(50); 
  PORTB = PORTB ^ BUZZER; // toggle the buzzer
  // Check to see if player 1 has pressed the buzzer already
  if (!(PINB & PLAYER1_BTTN)){
    return -1; // return -1 if the above is true
  }   // Check to see if player 2 has pressed the buzzer already
  if (!(PINB & PLAYER2_BTTN)){
    return -2; // return -2 if the above is true
  }
  while (!player1Time || !player2Time){
    int pins = PINB;
    int currentTime = millis(); // time taken using the millis function
    if (!player1Time && !(pins & PLAYER1_BTTN)){
      // if player one presses the button
      player1Time = currentTime; 
    }
    if (!player2Time && !(pins & PLAYER2_BTTN)){
      player2Time = currentTime;
    }
  }
  return player1Time - player2Time; // Return the result of Player2 time taken away from the time of Player1
}

// Function to handle a button being pressed before the Buzzer Sounds 
void earlyButtonPress(int result){
    lcd.clear();
  int player1_won = result == -2 ? 1 : 0; // Returns -2 if player 2 pressed the button
  // too early - therefore player 1 wins!
  PORTB |= (1<<player1_won); // shifts to the left and writes to the port 
  printLineOne("Button pressed early"); // display message on the LCD Display
  if (player1_won){
    printLineTwo("Player 1 wins!");// Display message on line two of LCD
  } else {
    printLineTwo("Player 2 wins!");
  }
}

// Function to Display the winner on the LCD 
void displayWinner(int player1_won){
  PORTB = PORTB | (1<<player1_won); // shifts to the left and writes to the port 
  if (player1_won){
    // Print which player won on line one of the LCD
    printLineOne("Player 1 Wins!"); // Display message on line one of LCD
  } else {
    printLineOne("Player 2 Wins!");
  }
}
