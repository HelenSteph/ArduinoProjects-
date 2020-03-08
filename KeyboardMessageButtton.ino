/*
  Keyboard Message test

  For the Arduino Leonardo and Micro.

  Sends a text string when a button is pressed.

  The circuit:
  - pushbutton attached from pin 4 to +5V
  - 10 kilohm resistor attached from pin 4 to ground

  created 24 Oct 2011
  modified 27 Mar 2012
  by Tom Igoe
  modified 11 Nov 2013
  by Scott Fitzgerald

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/KeyboardMessage
*/

#include "Keyboard.h"

const int buttonPin = 4;          // input pin for pushbutton
const int saveButton = 2;
int previousButtonState = HIGH;   // for checking the state of a pushButton
int previousButtonState2 = HIGH;   // for checking the state of a pushButton
int counter = 0;                  // button push counter

char myArray[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890@!#$%&/()=.,¡-¿?*+";
char wordSend[20];
int posLetters[15];
int temp = -1 ;

void setup() {
  // make the pushButton pin an input:
  pinMode(buttonPin, INPUT);
  pinMode(saveButton, INPUT);
  // initialize control over the keyboard:
  Keyboard.begin();
}

void loop() {
  // read the pushbutton:
  int buttonState = digitalRead(buttonPin);
  int buttonState2 = digitalRead(saveButton);
  // if the button state has changed,
  if (buttonState != previousButtonState) {
  // and it's currently pressed:
  delay(20);
    if (buttonState == HIGH) {
      // increment the button counter
      temp = temp + 1;
      // type out a message
      //Keyboard.print("You pressed the button ");
      Keyboard.write (8);
      Keyboard.write( myArray[temp]);
      
      //delay(500);
      if (temp == sizeof(myArray)) {
        temp = -1;

      if (buttonState2 == HIGH){
         Keyboard.write (32);
        }

        
      }

      //Keyboard.println(" times.");
    }
    // save the current button state for comparison next time:
    previousButtonState = buttonState;
  }
}
