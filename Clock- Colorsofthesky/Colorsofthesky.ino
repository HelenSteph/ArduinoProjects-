// All together

//Clock and light installation  playing with the colors of the sky and different effects

//Clock libraries
#include <Wire.h>
#include <DS3231.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>


// Neopixel libraries
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif


// Clock def
#define OLED_ADDR   0x3C
DS3231 Clock;
bool Century = false, h12, pm;
char week[7][20] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
char mon[12][4] = {"JAN", "FEB", "MAR", "APR", "MAY", "JUN", "JUL", "AUG", "SEP", "OCT", "NOV", "DEC"};
Adafruit_SSD1306 display(-1);

//byte  hourtime;


// Neopixel Def

#define PINA 6
#define PINB 7

Adafruit_NeoPixel stripA = Adafruit_NeoPixel(24, PINA, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel stripB = Adafruit_NeoPixel(24, PINB, NEO_GRB + NEO_KHZ800);



void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  Wire.begin();
  delay(3000);
  display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
  display.clearDisplay();
  display.display();


  stripA.begin();
  stripA.setBrightness(80);
  stripA.show(); // Initialize all pixels to 'off'

  stripB.begin();
  stripB.setBrightness(80);
  stripB.show(); // Initialize all pixels to 'off'

}




void loop() {
  // put your main code here, to run repeatedly:

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(30, 0);

  display.print(mon[Clock.getMonth(Century) - 1]);
  display.print(" ");
  display.print(Clock.getDate());
  display.print("  20");
  display.println(Clock.getYear());
  display.print("    ");
  display.print(Clock.getHour(h12, pm));
  display.print(" : ");
  display.print(Clock.getMinute());
  display.print(" : ");
  display.print(Clock.getSecond());
  display.println(" HRS");
  display.print("    Temp: ");
  display.print(Clock.getTemperature(), 1);
  display.println("  C");
  display.display();
  delay(1000);
  getCurrentdaylight();

}



void getCurrentdaylight() {


  int hourtime = Clock.getHour(h12,pm);
  int tempvalue =  Clock.getTemperature();

  Serial.println(hourtime);
  Serial.println(tempvalue);


  if (hourtime >= 5  && hourtime <= 7) {
    sunrise();
    Serial.println("sunrise");
  }


  if (hourtime >= 8 && hourtime <= 11) {

    if (tempvalue > 12) {
      sunnymorning();
      Serial.println("sunnymorning");
    }

    if (tempvalue < 12) {
      sadmorning();
       Serial.println("sadmorning");
    }
  }

  if (hourtime == 12) {
    noon();
    Serial.println("noon");
  }


  if (hourtime >= 13 && hourtime <= 18) {
    afternoon();
    Serial.println("afternoon");
  }


  if (hourtime == 18) {
    sunset();
    Serial.println("sunset");
  }

  if (hourtime >= 19 && hourtime <= 21) {
    night();
    Serial.println("night");
  }

  if (hourtime >= 22 && hourtime <= 4) {
    latenight();
    Serial.println("latenight");
  }

}










void sunrise() {

  colorWipeA(stripA.Color(0, 0, 255), 50); // Blue
  colorWipeB(stripB.Color(0, 0, 255), 50); // Blue
  colorWipeA(stripA.Color(235, 238, 72), 50); // Yellow
  colorWipeB(stripB.Color(248, 169, 20), 50); // Orange
  colorWipeB(stripB.Color(235, 238, 72), 50); // Yellow
  colorWipeB(stripB.Color(248, 169, 20), 50); // Yellow
  colorWipeA(stripA.Color(246, 242, 148), 50); // Orange
  delay(30000);

}


void sunnymorning() {

  colorWipeA(stripA.Color(246, 242, 148), 50); // Orange
  colorWipeB(stripB.Color(246, 242, 148), 50); // Orange
  colorWipeB(stripB.Color(235, 238, 72), 50); // Yellow
  colorWipeA(stripA.Color(235, 238, 72), 50); // Yellow
  colorWipeB(stripB.Color(253, 250, 163), 50); // Yellow light
  colorWipeA(stripA.Color(253, 250, 163), 50); // Yellow light
  colorWipeA(stripA.Color(251, 250, 228), 50); // Yellow light +
  colorWipeB(stripB.Color(112, 192, 251), 50); // Blue light
  colorWipeA(stripA.Color(112, 192, 251), 50); // Blue light
  delay(30000);
}



void sadmorning() {

  colorWipeB(stripB.Color(253, 250, 163), 50); // Yellow light
  colorWipeA(stripA.Color(253, 250, 163), 50); // Yellow light
  colorWipeA(stripA.Color(251, 250, 228), 50); // Yellow light +
  colorWipeB(stripB.Color(112, 192, 251), 50); // Blue light
  colorWipeA(stripA.Color(112, 192, 251), 50); // Blue light
  colorWipeB(stripB.Color(78, 137, 180), 50); // Blue light
  colorWipeA(stripA.Color(78, 137, 180), 50); // Blue light
  colorWipeB(stripB.Color(226, 211, 247), 50); // Blue light --
  colorWipeA(stripA.Color(78, 137, 180), 50); // Blue light--
  colorWipeB(stripB.Color(222, 224, 226), 50); // Blue light
  colorWipeA(stripA.Color(222, 224, 226), 50); // Blue light
  colorWipeB(stripB.Color(255, 255, 255), 80); //   Almost white
  colorWipeA(stripA.Color(255, 255, 255), 80); // Almost white
  delay(30000);

}



void  noon() {

  colorWipeB(stripB.Color(253, 250, 163), 50); // Yellow light
  colorWipeA(stripA.Color(253, 250, 163), 50); // Yellow light
  colorWipeA(stripA.Color(251, 250, 228), 50); // Yellow light +
  colorWipeA(stripA.Color(242, 251, 42), 50); // Yellow light
  colorWipeB(stripB.Color(246, 133, 32), 50); // Orange +
  colorWipeA(stripA.Color(246, 77, 32), 50); // Yellow light
  colorWipeB(stripB.Color(251, 248, 61), 50); // Orange +
  colorWipeA(stripA.Color(251, 250, 228), 50); // Yellow light
  colorWipeA(stripA.Color(241, 203, 48), 50); // Yellow light
  delay(30000);
}


void afternoon() {

  colorWipeB(stripB.Color(112, 192, 251), 50); // Blue light
  colorWipeA(stripA.Color(112, 192, 251), 50); // Blue light
  colorWipeB(stripB.Color(178, 102, 255), 50); // Blue light
  colorWipeA(stripA.Color(112, 192, 251), 50); // Blue light
  colorWipeA(stripA.Color(51, 51, 255), 50); // Blue light
  colorWipeB(stripB.Color(255, 153, 51), 50); // Blue light
  colorWipeA(stripA.Color(0, 0, 204), 50); // Blue light
  delay(30000);

}



void sunset() {

  colorWipeB(stripB.Color(255, 153, 51), 50); // Blue light
  colorWipeA(stripA.Color(0, 0, 204), 50); // Blue light
  colorWipeB(stripB.Color(255, 0, 127), 50); // Blue light
  colorWipeA(stripA.Color(178, 102, 255), 50); // Blue light
  colorWipeB(stripB.Color(255, 128, 0), 50); // Blue light
  colorWipeA(stripA.Color(255, 255, 0), 50); // Blue light
  colorWipeB(stripB.Color(255, 0, 0), 50); // Blue light
  colorWipeB(stripB.Color(255, 0, 255), 50); // Blue light
  colorWipeA(stripA.Color(0, 0, 255), 50); // Blue light
  colorWipeB(stripB.Color(0, 0, 255), 50); // Blue light
  delay(30000);
}





void night() {

  colorWipeA(stripA.Color(0, 0, 255), 50); // Blue light
  colorWipeB(stripB.Color(0, 0, 255), 50); // Blue light
  theaterChaseA(stripA.Color(0, 0, 255), 50); // Blue
  colorWipeB(stripB.Color(0, 0, 255), 50); // Blue light
  theaterChaseB(stripB.Color(127, 127, 127), 50); // White
  colorWipeA(stripA.Color(255, 153, 51), 50); // Blue light
  theaterChaseB(stripB.Color(0, 0, 255), 50); // White
  theaterChaseA(stripA.Color(0, 0, 255), 50); // White
  delay(30000);
}


void latenight() {

  theaterChaseB(stripB.Color(0, 0, 255), 50); // White
  theaterChaseA(stripA.Color(0, 0, 255), 50); // White
  theaterChaseB(stripB.Color(51, 51, 255), 50); // White
  theaterChaseA(stripA.Color(51, 51, 255), 50); // White
  theaterChaseB(stripB.Color(127, 0, 255), 50); // White
  theaterChaseA(stripA.Color(51, 51, 255), 50); // White
  theaterChaseB(stripB.Color(102, 178, 255), 50); // White
  theaterChaseA(stripA.Color(153, 255, 255), 50); // White
  colorWipeA(stripA.Color(0, 0, 255), 50); // Blue light
  colorWipeB(stripB.Color(0, 0, 255), 50); // Blue light

}




///Efectos


void colorWipeA(uint32_t c, uint8_t wait) {
  for (uint16_t i = 0; i < stripA.numPixels(); i++) {
    stripA.setPixelColor(i, c);
    stripA.show();
    delay(wait);
  }
}


void colorWipeB(uint32_t c, uint8_t wait) {
  for (uint16_t i = 0; i < stripB.numPixels(); i++) {
    stripB.setPixelColor(i, c);
    stripB.show();
    delay(wait);
  }
}


void theaterChaseA(uint32_t c, uint8_t wait) {
  for (int j = 0; j < 10; j++) { //do 10 cycles of chasing
    for (int q = 0; q < 3; q++) {
      for (uint16_t i = 0; i < stripA.numPixels(); i = i + 3) {
        stripA.setPixelColor(i + q, c);  //turn every third pixel on
      }
      stripA.show();

      delay(wait);

      for (uint16_t i = 0; i < stripA.numPixels(); i = i + 3) {
        stripA.setPixelColor(i + q, 0);      //turn every third pixel off
      }
    }
  }
}

void theaterChaseB(uint32_t c, uint8_t wait) {
  for (int j = 0; j < 10; j++) { //do 10 cycles of chasing
    for (int q = 0; q < 3; q++) {
      for (uint16_t i = 0; i < stripB.numPixels(); i = i + 3) {
        stripB.setPixelColor(i + q, c);  //turn every third pixel on
      }
      stripB.show();

      delay(wait);

      for (uint16_t i = 0; i < stripB.numPixels(); i = i + 3) {
        stripB.setPixelColor(i + q, 0);      //turn every third pixel off
      }
    }
  }
}
