#include <Adafruit_NeoPixel.h>
//#include <SPI.h>
//#include <Adafruit_VS1053.h>
//#include <SD.h>
//#define SHIELD_RESET  8      // VS1053 reset pin (unused!)
//#define SHIELD_CS     6      // VS1053 chip select pin (output)
//#define SHIELD_DCS    7     // VS1053 Data/command select pin (output)
//#define CARDCS 9     // Card chip select pin
//#define DREQ 2       // VS1053 Data request, ideally an Interrupt pin
//
//Adafruit_VS1053_FilePlayer musicPlayer =
//Adafruit_VS1053_FilePlayer(SHIELD_RESET, SHIELD_CS, SHIELD_DCS, DREQ, CARDCS);

// Which pin on the Arduino is connected to the NeoPixels?
#define NUMPIXELS 164 //scari
#define PIN 28

#define NUMPIXELS2 464 //geamuri
#define PIN2 26

#define NUMPIXELS3 700 //hol
#define PIN3 30

#define LINELENGTH 20

#define DELAYVAL 500

int counter = 0;
int counter2 = 0;
int counter3 = 0;
unsigned long time;
bool stoploop = false;
int timerAlarma = 23000; // 23 secunde

#define switchGeneral 32

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels2(NUMPIXELS2, PIN2, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels3(NUMPIXELS3, PIN3, NEO_GRB + NEO_KHZ800);

void setup()
{
  Serial.begin(9600);
  pixels.begin();
  pixels2.begin();
  pixels3.begin();

  pinMode(switchGeneral, INPUT); // pin buton alarma
  pinMode(22, OUTPUT); //pin blinders
  digitalWrite(22,HIGH);
}

bool timer = false;

void loop()
{

  //debug
  //    Serial.print("loop ");
  //    Serial.println(digitalRead(12));

  // merge in modul normal atata timp cat:
  // switchul este 0
  // si stoploop este true

  // normal mode
  led(pixels, NUMPIXELS, counter, LINELENGTH);
  led(pixels2, NUMPIXELS2, counter2, LINELENGTH);
  led(pixels3, NUMPIXELS3, counter3, LINELENGTH);

  // merge in modul alarma atata timp cat:
  // switchul este 1
  // si stoploop este false

  digitalWrite(22,HIGH);

  while (digitalRead(switchGeneral) == 1 && !stoploop) {

    if(digitalRead(switchGeneral) == 1 && timer==false) {
      time = millis();
      timer = true;

      //blinders goes down
      blindersDown(22);
    
    }
    //  debug
//    Serial.print(time);
//    Serial.print(" inner loop ");
//    Serial.println(digitalRead(12));

    

    //    start alarma
//    alarma(pixels, NUMPIXELS);
//    alarma(pixels2, NUMPIXELS2);
//    alarma(pixels3, NUMPIXELS3);
    for (int i = 0; i < NUMPIXELS3; i++) {
      pixels.setPixelColor(i, pixels.Color(30, 0, 0));
      pixels2.setPixelColor(i, pixels2.Color(30, 0, 0));
      pixels3.setPixelColor(i, pixels3.Color(30, 0, 0));
    }
    pixels.show();
    pixels2.show();
    pixels3.show();
    delay(500);
    pixels.clear();
    pixels2.clear();
    pixels3.clear();
    pixels.show();
    pixels2.show();
    pixels3.show();
    delay(500);

    // check if timerAlarma has been passed
    // modul alarma nu dureaza mai mult decat timerAlarma
    Serial.print(millis() - time);
    Serial.println(" test");
    if (millis() - time > timerAlarma) {
      stoploop = true;
      Serial.println(" test2");
      // make the leds blue
//      setBackground(pixels, NUMPIXELS);
//      setBackground(pixels2, NUMPIXELS2);
//      setBackground(pixels3, NUMPIXELS3);
    }

    // Se iese din while dupa ce treme timpul timerAlarma
    // Chiar daca switchul este 0
  }

  // dupa ce timerAlarma trece si stoploop = true
  // se asteapta wtichul sa devina 0
  // pentru a mai putea intra in modul alarma la urmatoarea apasare
  if (digitalRead(switchGeneral) == 0 && stoploop == true) {
    stoploop = false;
  }

  // show the pixels
  pixels.show();
  pixels2.show();
  pixels3.show();

  if (digitalRead(switchGeneral)==0) {
    timer = false;
  }

  //this timer should be 0 due to low speed
//  delay(0);
}

// end loop

void blindersDown(int pin)
{
//  Serial.print(" blinders goes down ");
  digitalWrite(pin, LOW);
  delay(500);
  digitalWrite(pin, HIGH);
  
}

void setBackground(Adafruit_NeoPixel &pixels, int numpixel) {
  for (int i = 0; i < numpixel; i++) {
    pixels.setPixelColor(i, pixels.Color(0, 0, 20));
  }
  pixels.show();
}

void led(Adafruit_NeoPixel &pixels, int numpixel, int &counter, int line)
{

  if (counter < numpixel + line) {

    int green = 255;
    pixels.setPixelColor(counter, pixels.Color(30, 14, 0));
    pixels.setPixelColor(counter - 1, pixels.Color(30, 14, 0));

    pixels.setPixelColor(counter - 2, pixels.Color(30, 14, 0));
    pixels.setPixelColor(counter - 3, pixels.Color(30, 14, 0));
    pixels.setPixelColor(counter - 4, pixels.Color(30, 14, 0));
    pixels.setPixelColor(counter - 5, pixels.Color(30, 14, 0));
    pixels.setPixelColor(counter - 6, pixels.Color(30, 14, 0));
    pixels.setPixelColor(counter - 7, pixels.Color(30, 14, 0));
    pixels.setPixelColor(counter - 8, pixels.Color(30, 14, 0));
    pixels.setPixelColor(counter - 9, pixels.Color(30, 14, 0));

    pixels.setPixelColor(counter - 10, pixels.Color(30, 14, 0));
    pixels.setPixelColor(counter - 11, pixels.Color(30, 14, 0));
    pixels.setPixelColor(counter - 12, pixels.Color(30, 14, 0));
    pixels.setPixelColor(counter - 13, pixels.Color(30, 14, 0));

    pixels.setPixelColor(counter - 14, pixels.Color(30, 14, 0));
    pixels.setPixelColor(counter - 15, pixels.Color(30, 14, 0));
    pixels.setPixelColor(counter - 16, pixels.Color(30, 14, 0));
    pixels.setPixelColor(counter - 17, pixels.Color(30, 14, 0));
    pixels.setPixelColor(counter - 18, pixels.Color(30, 14, 0));
    pixels.setPixelColor(counter - 19, pixels.Color(10, 25, 25));
    counter++;
  }
  else {
    counter = 0;
  }
}

void alarma(Adafruit_NeoPixel &pixels, int numpixel)
{
  for (int i = 0; i < numpixel; i++) {
    pixels.setPixelColor(i, pixels.Color(10, 0, 0));
  }
  pixels.show();
  delay(500);
  pixels.clear();
  pixels.show();
  delay(500);
}
