//Pedal Keyboard
#include "HID-Project.h"

//Inputs
// Variables will change:
const int buttonPin = 2;
const int selectPin = 3;
const int deletePin = 4;
//const int ledPin = 13;
int buttonPushCounter = 0;   // counter for the number of button presses
int buttonState = 0;         // current state of the button
int buttonSelect = 0;
int buttonDelete = 0;
int lastButtonState = HIGH;     // previous state of the button
int lastButtonStateD = HIGH; 
const int debounceDelay = 4;


char myArray[] = "ABCDEFGHIJKLMOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890@!#$%&/()=.,-?*+ ";
char wordSend[20];
int posLetters[15];
int temp = -1 ;


void setup() {
  // initialize the button pin as a input:

  pinMode(buttonPin, INPUT_PULLUP);
  // initialize the LED as an output:
  //  pinMode(ledPin, OUTPUT);
  // initialize serial communication
  pinMode(deletePin, INPUT);
  pinMode(selectPin, INPUT);

  Serial.begin(9600);
  while (!Serial);
  Serial.println("Start");
}


void loop() {
  // read the pushbutton input pin:
  buttonState = digitalRead(buttonPin);
  buttonSelect = digitalRead(selectPin);
  buttonDelete = digitalRead(deletePin);

  // compare the buttonState to its previous state
  if (buttonState == LOW) {
    // if the current state is HIGH then the button went from off to on:
    temp = temp + 1;
    Keyboard.write (8);
    Keyboard.write( myArray[temp]);
    Serial.println(myArray[temp]);
    delay(500);
    if (temp == sizeof(myArray)) {
      temp = -1;
    }

  }

  if (buttonSelect != lastButtonState) {

    // wait until button state stabilizes:

    delay(debounceDelay);

    if (buttonSelect == HIGH)
    {

      //Keyboard.write(32);
      temp = 0;
      Keyboard.write(myArray[temp]);
    }

   lastButtonState= buttonSelect;

  }

if (buttonDelete != lastButtonStateD) {

   delay(debounceDelay);
  if (buttonDelete == HIGH)
  {
    Keyboard.write(8);
  }

    lastButtonStateD= buttonDelete;
}
}
