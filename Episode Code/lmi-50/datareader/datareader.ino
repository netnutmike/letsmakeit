/*############################## READ FILE FROM SD CARD ##################################
       This sketch reads logged data from the log file on the SD card and outputs it to
       the serial port.

 
   From: Mike Myers (http://mikemyers.me)  @netnutmike
       Let's Make It Episode 50 (http://letmakeit.tv)
       
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

#include <SD.h>

void setup()
{
  Serial.begin(9600);

  pinMode(10, OUTPUT);
  
  // see if the card is present and can be initialized:
  if (!SD.begin(4)) {
    Serial.println("Card failed, or not present");
    return;
  }
  Serial.println("card initialized.");
}

void loop()
{
  File dataFile = SD.open("datalog.txt");

  // if the file is available, read from it:
  if (dataFile) {
    while (dataFile.available()) {
      Serial.write(dataFile.read());
    }
    dataFile.close();
    Serial.println("");
    Serial.println("");
  }  
  // if the file isn't open, pop up an error:
  else {
    Serial.println("error opening datalog.txt");
  } 
  
  delay(30000);
}
