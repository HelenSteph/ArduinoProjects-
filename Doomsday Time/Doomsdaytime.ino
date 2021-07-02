#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN 6

// Pin 3  Pump 

char rx_byte = 0;
String rx_str = "";
boolean not_number = false;
int result;
int timespace=0;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(60, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin();
  strip.setBrightness(80);
  strip.show(); // Initialize all pixels to 'off'
  Serial.begin(9600);
  pinMode(3,OUTPUT);
  Serial.println("Enter your result:");
}



void loop() {
  if (Serial.available() > 0) {    // is a character available?
    rx_byte = Serial.read();       // get the character
    
    if ((rx_byte >= '0') && (rx_byte <= '9')) {
      rx_str += rx_byte;
    }
    else if (rx_byte == '\n') {
      // end of string
      if (not_number) {
        Serial.println("Not a number");
      }
      else {
        // multiply the number by 2
        result = rx_str.toInt() * 2;
        // print the result
        Serial.print(rx_str);
        Serial.print(" x 2 = ");
        Serial.print(result);
        Serial.println("");
       // Serial.println("Enter a number to multiply by 2.");

        if (result/2 < 20)
           digitalWrite(3,LOW);
           colorWipe(strip.Color(255, 0, 0 ), 50); // Red
          
       if (result/2 > 20 & result/2<40){
           //timespace = ((100-(result/2))*0.5)*25*100;
           timespace = 60000;
           digitalWrite(3,HIGH);
           colorWipe(strip.Color(218,224,25), 50); // Yellow
           delay(timespace);
           digitalWrite(3,LOW);
          }


        if (result/2 > 40 & result/2 < 80){

           //timespace = ((100-(result/2))/0.5)*25*100;

           timespace = 30000;
           digitalWrite(3,HIGH);
           colorWipe(strip.Color(0,255, 0 ), 50); // Green
           delay(timespace);
           digitalWrite(3,LOW);

          
          }

           if (result/2 > 80 & result/2 < 100){
          // timespace = ((100-(result/2))*0.5)*25*100;

          timespace = 10000;
           digitalWrite(3,HIGH);
           colorWipe(strip.Color(0,0, 255 ), 50); // Green
           delay(timespace);
           digitalWrite(3,LOW);
          }

          
          else {
             digitalWrite(3,LOW);
             colorWipe(strip.Color(0,0,0 ), 50); // Green
            }
      }
      not_number = false;         // reset flag
      rx_str = "";                // clear the string for reuse
    }
    else {
      // non-number character received
      not_number = true;    // flag a non-number
    }
  } // end: if (Serial.available() > 0)
}


void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}
