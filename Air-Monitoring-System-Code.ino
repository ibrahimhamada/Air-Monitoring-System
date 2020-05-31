/*
 Air Monitoring System
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
The project's objective is to design a simple system that is used for simulating an Air Monitoring System using Arduino Uno Board, Gas Sensor, Buzzer, LCD display, LEDs.
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

This sketch is used for Air-Monitoring. 
The LCD prints "Harmful Gas is Detected", the Buzzer will generate an alarm sound, and the RED LED will be turned on when the Gas Sensor detects a harmful gas in its reading range.  
The Buzzer will be turned off and the GREEN LED will be turned on when the Gas Sensor does not detect any harmful gases in its reading range.  

  The Circuit Connections:
 -LCD:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * wiper to LCD VO pin (pin 3)

 -Gas Sensor:
 * Gas Sensor Analog read pin to analog pin A0

 -Buzzer:
 * Buzzer pin to digital pin 8

 -LEDs:
 * Green LED pin to digital pin 6
 * Red LED pin to digital pin 7

 */

// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int sensor = A0;
int val = 0;
int limit = 40;

void setup() {
  Serial.begin(9600);
  // declaring LEDs pins as OUTPUTS Pins and turned them off at the beginning.
  pinMode(7, OUTPUT);
  pinMode(6, OUTPUT);
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);

  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Air Monitoring");
  lcd.setCursor(0, 1);
  lcd.print("System");
  delay(500); 
  lcd.clear();
}



void loop() {
  
  val = analogRead(sensor);         // Initialize the value of (val) Variable with the Gas Sensor Reading.
  val = map(val, 306, 750, 0, 100); //Mapping the output voltage values from the Gas Sensor to values in the range from 0 to 100.
  Serial.println(val);              //Printing the Gas Sensor Reading in the Serial Monitor.

//If a harmful gas is detected.
    if (val > limit) {
      lcd.setCursor(0, 0);
      lcd.print("Harmful Gas is");  //Print a message to the LCD.
      lcd.setCursor(0, 1);
      lcd.print("Detected");
      digitalWrite(7, HIGH);        //The Red LED wil be turned ON.
      digitalWrite(6, LOW);         //The Green LED wil be turned OFF.
      tone(8, 1000);                //The Buzzer will generate an alarm tone.
      delay(100);                   //Sound ON for 100 msec.
      noTone(8);                    
      delay(100);                   //Sound OFF for 100 msec.
    }
    
    else { 
      lcd.clear();                 //Clear the warning message from the LCD.
      noTone(8);                   //Sound OFF.
      digitalWrite(7, LOW);        //The Red LED wil be turned OFF.
      digitalWrite(6, HIGH);       //The Green LED wil be turned ON.
    } 
}
 


