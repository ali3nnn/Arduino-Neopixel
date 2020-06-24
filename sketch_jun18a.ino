#include <Adafruit_NeoPixel.h>

// Which pin on the Arduino is connected to the NeoPixels?
#define NUMPIXELS 164 
#define PIN        26 

#define NUMPIXELS2 464 
#define PIN2        28

#define NUMPIXELS3 700 
#define PIN2        30

// How many NeoPixels are attached to the Arduino?
#define LINELENGTH 20

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels2(NUMPIXELS2, PIN2, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels3(NUMPIXELS3, PIN3, NEO_GRB + NEO_KHZ800);

#define DELAYVAL 500 // Time (in milliseconds) to pause between pixels

void setup() {
  pixels.begin();
  pixels2.begin();
  pixels3.begin();

  pinMode(32, INPUT);
}

void loop() {
   pixels.clear();
   pixels2.clear();
   pixels3.clear();

  pixels.show();
  pixels2.show();
  pixels3.show();

  delay(DELAYVAL);
  
}

void led(Adafruit_NeoPixel &pixels, int numpixel, int &counter, int line) {
  if (counter<numpixel + line) {
    int green = 255;
      pixels.setPixelColor(counter, pixels.Color(0, green, 0));
      pixels.setPixelColor(counter-1, pixels.Color(0, green, 0));

      pixels.setPixelColor(counter-2, pixels.Color(0, green-50, 0));
      pixels.setPixelColor(counter-3, pixels.Color(0, green-50, 0));
      pixels.setPixelColor(counter-4, pixels.Color(0, green-100, 0));
      pixels.setPixelColor(counter-5, pixels.Color(0, green-100, 0));
      pixels.setPixelColor(counter-6, pixels.Color(0, green-150, 0));
      pixels.setPixelColor(counter-7, pixels.Color(0, green-150, 0));
      pixels.setPixelColor(counter-8, pixels.Color(0, green-150, 0));
      pixels.setPixelColor(counter-9, pixels.Color(0, green-150, 0));

      pixels.setPixelColor(counter-10, pixels.Color(0, green-230, 0));
      pixels.setPixelColor(counter-11, pixels.Color(0, green-230, 0));
      pixels.setPixelColor(counter-12, pixels.Color(0, green-230, 0));
      pixels.setPixelColor(counter-13, pixels.Color(0, green-230, 0));

      pixels.setPixelColor(counter-14, pixels.Color(0, green-250, 0));
      pixels.setPixelColor(counter-15, pixels.Color(0, green-251, 0));
      pixels.setPixelColor(counter-16, pixels.Color(0, green-252, 70));
      pixels.setPixelColor(counter-17, pixels.Color(0, green-253, 70));
      pixels.setPixelColor(counter-18, pixels.Color(0, green-254, 70));
      pixels.setPixelColor(counter-19, pixels.Color(0, green-255, 70));
    counter ++;
  }
  else {
    counter = 0;
  }
}
