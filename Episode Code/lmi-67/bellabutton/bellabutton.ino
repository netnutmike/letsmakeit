

// include SPI, MP3 and SD libraries
#include <SPI.h>
#include <Adafruit_VS1053.h>
#include <SD.h>

#define SHIELD_CS     7      // VS1053 chip select pin (output)
#define SHIELD_DCS    6      // VS1053 Data/command select pin (output)

// These are common pins between breakout and shield
#define CARDCS 4     // Card chip select pin
// DREQ should be an Int pin, see http://arduino.cc/en/Reference/attachInterrupt
#define DREQ 3       // VS1053 Data request, ideally an Interrupt pin

#define MAXMSG 6;

// Modes
#define WAITING 1;
#define GOTTAGO 2;

Adafruit_VS1053_FilePlayer musicPlayer = 
  Adafruit_VS1053_FilePlayer(SHIELD_CS, SHIELD_DCS, DREQ, CARDCS);
  

int currentMessage = 1;
int currentMode = 1;

int blinkCount = 0;
int buttonCount = 0;
int messageLoopCount = 0;
  
void setup() {
  Serial.begin(9600);
  Serial.println("Bellas potty button");

  if (! musicPlayer.begin()) { // initialise the music player
     Serial.println(F("Couldn't find VS1053, do you have the right pins defined?"));
     while (1);
  }
  Serial.println(F("audio chip found"));
  
  SD.begin(CARDCS);    // initialise the SD card
  
  // Set volume for left, right channels. lower numbers == louder volume!
  musicPlayer.setVolume(1,1);

  musicPlayer.useInterrupt(VS1053_FILEPLAYER_PIN_INT);  // DREQ int
  
  pinMode(2, OUTPUT);
  
  // Play one file, don't return until complete
  Serial.println(F("Playing track 001"));
  musicPlayer.playFullFile("track001.mp3");
  
}

void loop() {
  if (currentMode == 1) {
     if (!digitalRead(3)) {
       playMessage();
       buttonCount = 0;
       messageLoopCount = 0;
       currentMode = 2;
     }
     
     ++blinkCount;
     if (blinkCount >= 100) {
       digitalWrite(2, true);
       blinkCount = 0;
       delay(250);
       digitalWrite(2, false);
     }
  }
  
  if (currentMode == 2) {
     if (!digitalRead(3)) 
       ++buttonCount;
     else
       buttonCount = 0;
     
     if (buttonCount > 6) {
       currentMode = 1;
       while (!digitalRead(3));
     }
       
     ++messageLoopCount;
     if (messageLoopCount >= 60) {
       playMessage();
       messageLoopCount = 0;
     }
     
     blinkCount = blinkCount + 15;
     if (blinkCount >= 100) {
       digitalWrite(2, true);
       blinkCount = 0;
       delay(250);
       digitalWrite(2, false);
     }
  }

  delay(100);
}

void playMessage() {
  char filename[] = "track001.mp3";
  
  filename[7] = currentMessage + 48;
  
  musicPlayer.playFullFile(filename);
  
  ++currentMessage;
  
  if (currentMessage > 6)
    currentMessage = 1;
}
