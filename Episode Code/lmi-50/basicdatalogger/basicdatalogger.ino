/*############################## BASIC DATA LOGGER ##################################
       This sketch shows an example of how to log data to a file on an SD card.
       
       It reads the temperature every 60 seconds and writes the temperature to
       the SD card in Centigrade, Farenheit and also writes the humidity percentage.
       
       The SD card used in this example is a 2 GB card with 1975287808 bytes available.
       This sketch writes 9 bytes per reading to the card.  With taking a reading every
       60 seconds, the card can hold just over 417 years of logged data before it runs
       out of space.

 
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

#include <Wire.h>
#include <dht11.h>
#include <SD.h>

dht11 DHT11;

long nextLogTime = 0;
long logDelay = 60000;    //one minute

void setup()
{
  //DHT11.attach(4);                          
  
  Serial.begin(9600);
  
  //Serial.print("Initializing SD card...");
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
  String dataString = "";
  
  if (nextLogTime <= millis()) {
    File dataFile = SD.open("datalog.txt", FILE_WRITE);

    // if the file is available, write to it:
    if (dataFile) {
      int chk = DHT11.read(2);          // Read the sensor
      if (chk == 0) {
        dataString = String((int)DHT11.temperature,DEC);
        dataString += ",";
        dataString += String((int)DHT11.fahrenheit());
        dataString += ",";
        dataString += String(DHT11.humidity);
        dataString += "\r";
        dataFile.println(dataString);
      }
      dataFile.close();
      
      Serial.println(dataString);
    } else {
      Serial.println("error opening datalog.txt");
    }
    
    nextLogTime = millis() + logDelay;
  }
}
