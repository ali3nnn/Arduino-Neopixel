/*****************
  This is an example for the Adafruit VS1053 Codec Breakout

  Designed specifically to work with the Adafruit VS1053 Codec Breakout
  ----> https://www.adafruit.com/products/1381

  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.
  BSD license, all text above must be included in any redistribution
 ******************/

// include SPI, MP3 and SD libraries
#include <SPI.h>
#include <Adafruit_VS1053.h>
#include <SD.h>

// define the pins used
//#define CLK 13       // SPI Clock, shared with SD card
//#define MISO 12      // Input data, from VS1053/SD card
//#define MOSI 11      // Output data, to VS1053/SD card
// Connect CLK, MISO and MOSI to hardware SPI pins.
// See http://arduino.cc/en/Reference/SPI "Connections"

// These are the pins used for the breakout example
//#define BREAKOUT_RESET  8      // VS1053 reset pin (output)
//#define BREAKOUT_CS     10     // VS1053 chip select pin (output)
//#define BREAKOUT_DCS    8      // VS1053 Data/command select pin (output)
// These are the pins used for the music maker shield
#define SHIELD_RESET  8      // VS1053 reset pin (unused!)
#define SHIELD_CS     6      // VS1053 chip select pin (output)
#define SHIELD_DCS    7     // VS1053 Data/command select pin (output)

// These are common pins between breakout and shield
#define CARDCS 9     // Card chip select pin
// DREQ should be an Int pin, see http://arduino.cc/en/Reference/attachInterrupt
#define DREQ 2       // VS1053 Data request, ideally an Interrupt pin

Adafruit_VS1053_FilePlayer musicPlayer =
  // create breakout-example object!
  //  Adafruit_VS1053_FilePlayer(BREAKOUT_RESET, BREAKOUT_CS, BREAKOUT_DCS, DREQ, CARDCS);
  // create shield-example object!
  Adafruit_VS1053_FilePlayer(SHIELD_RESET, SHIELD_CS, SHIELD_DCS, DREQ, CARDCS);

void setup() {
  Serial.begin(9600);
  Serial.println("Adafruit VS1053 Simple Test");

  if (! musicPlayer.begin()) { // initialise the music player
    Serial.println(F("Couldn't find VS1053, do you have the right pins defined?"));
    while (1);
  }
  Serial.println(F("VS1053 found"));

  if (!SD.begin(CARDCS)) {
    Serial.println(F("SD failed, or not present"));
    while (1);  // don't do anything more
  }

  // list files
  //printDirectory(SD.open("/"), 0);

  // Set volume for left, right channels. lower numbers == louder volume!
  musicPlayer.setVolume(0, 0);

  musicPlayer.useInterrupt(VS1053_FILEPLAYER_PIN_INT);  // DREQ int

  //  // Play one file, don't return until complete
  //  Serial.println(F("Playing track 001"));
  //  musicPlayer.playFullFile("/track001.mp3");
  //  // Play another file in the background, REQUIRES interrupts!
  //musicPlayer.startPlayingFile("/track001.mp3");
  //  pinMode(3, INPUT_PULLUP);
  //  attachInterrupt(digitalPinToInterrupt(3), player, CHANGE);
  pinMode(A0, INPUT);
}

bool start = true;
unsigned long time;

void loop() {
  Serial.println(digitalRead(A0));
  if (digitalRead(A0) == 1 && start) {
    
    Serial.println("audio start");
    time = millis();
    musicPlayer.startPlayingFile("/track001.mp3");
    while (millis() - time < 23000) {
      Serial.println("audio playing");
      start = false;
      if (digitalRead(A0) == 0) {
        break;
      }
    }
    Serial.println("audio stop");
    musicPlayer.stopPlaying();
    
  }
  else if (digitalRead(A0) == 1) {
    
    musicPlayer.stopPlaying();
    Serial.println("audio stop - set button to OFF");
    
  } else if (start == false) {
    
    start = true;
    musicPlayer.stopPlaying();
    Serial.println("audio stop");
    
  }
  else {
    Serial.println("waiting to start again");
  }
}

void player() {
  if (digitalRead(A0) == 1 && start) {
    start = false;
    if (digitalRead(3) == 1) {
      musicPlayer.startPlayingFile("/track001.mp3");
    } else {
      musicPlayer.stopPlaying();
      start = true;
    }
  }
}

/// File listing helper
void printDirectory(File dir, int numTabs) {
  while (true) {

    File entry =  dir.openNextFile();
    if (! entry) {
      // no more files
      //Serial.println("*nomorefiles*");
      break;
    }
    for (uint8_t i = 0; i < numTabs; i++) {
      Serial.print('\t');
    }
    Serial.print(entry.name());
    if (entry.isDirectory()) {
      Serial.println("/");
      printDirectory(entry, numTabs + 1);
    } else {
      // files have sizes, directories do not
      Serial.print("\t\t");
      Serial.println(entry.size(), DEC);
    }
    entry.close();
  }
}
