/*################################# READ RFID #####################################
       This sketch reads from a parallax RFID reader and outputs to the display 
       the codes that are read. 

 
   From: Mike Myers (http://mikemyers.me)  @netnutmike
       Let's Make It Episode 15 (http://tech-zen.tv/index.php/shows/let-s-make-it/episodes/59-sensor-fun-with-arduino-1-massive-failure-but-4-successes-let-s-make-it-episode-6)
       
       http://tech-zen.tv
       
       For the sample code, show notes, contact information and many more 
       videos, visit the show page at http://tech-zen.tv/letsmakeit

       Please subscribe to our YouTube channel or our netcasts at any of 
       your favorite netcast / podcast outlets.

       We normally record Let's Make It live on Tuesday evenings around 
       7pm eastern. You can watch it live by going to tech-zen.tv and clicking 
       the live link at the top of the page.

       We also have a community setup for our viewers and listeners. You can 
       join the community by going to community.tech-zen.tv.

       We love input on what you would like to know or if you have an idea for 
       a new Let's Make it episode, you can contact us via email or phone at 
       the show information page.
################################################################################*/

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x3F,20,4);

void setup() {
  Serial.begin(2400);
  
  lcd.init();                // initialize the lcd 

  lcd.backlight();
  clearScreen();

  pinMode(2,OUTPUT);         // Set digital pin 2 as OUTPUT to connect it to the RFID /ENABLE pin 
  digitalWrite(2, LOW);      // Low enables reader
}

void loop() {
  char ch;
  if (Serial.available())      // is there anything to be read from serial port?
  {
    ch = Serial.read();        // read a single letter
    
    // print out to serial port the character we just read
    lcd.print(ch);
  } 
}

void clearScreen()
{
  lcd.setCursor(0,0);
  lcd.print("                    ");
  lcd.setCursor(0,1);
  lcd.print("                    ");
  lcd.setCursor(0,2);
  lcd.print("                    ");
  lcd.setCursor(0,3);
  lcd.print("                    ");
}
