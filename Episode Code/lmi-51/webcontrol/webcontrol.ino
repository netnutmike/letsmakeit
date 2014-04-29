/*############################## BASIC WEB SERVER ##################################
       This sketch Expands on Episode 49 and demonstrates how you can use a web
       server to control other things.
       
      

 
   From: Mike Myers (http://mikemyers.me)  @netnutmike
       Let's Make It Episode 51 (http://letmakeit.tv)
       
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

#include <SPI.h>         // needed for Arduino versions later than 0018
#include <Ethernet.h>
#include "WebServer.h"  // For web interface
#include <Servo.h>


static uint8_t mac[] = { 0x90, 0xA2, 0xDA, 0x0D, 0x3F, 0xBB };    // MAC address of your device

static uint8_t ip[] = { 10, 232, 1, 249 };

WebServer webserver("", 80);

Servo myservo;

int servoPin = 9;
int maxServo = 175;
int minServo = 13;
int currentServo = 13;

int cRed = 25;
int cGreen = 25;
int cBlue = 25;

const int redPin = 3;
const int greenPin = 5;
const int bluePin = 6;

void webDefaultView(WebServer &server, WebServer::ConnectionType type)
{
  P(htmlHead) =
    "<html>"
    "<head>"
    "<title>Arduino Web Control</title>"
    "<style type=\"text/css\">"
    "BODY { font-family: sans-serif }"
    "H1 { font-size: 14pt; }"
    "P  { font-size: 10pt; }"
    "</style>"
    "</head>"
    "<body>";

  server.httpSuccess();
  server.printP(htmlHead);
  
  server.print(F("<H1>Web Control</H1>"));
  server.print(F("<H2>Control Pins</H2>"));
  server.print(F("<H3>Pin 2</H3>"));
  server.print(F("<form action='/form' method='post'>"));
  if (digitalRead(2))
    server.print(F("<p><input type='submit' value='Off' name='Pin2'/>"));
  else
    server.print(F("<p><input type='submit' value='On' Name='Pin2'/>"));
    
  server.print(F("</form>"));
  
  server.print(F("<H3>Servo Position</H3>"));
  server.print(F("<form action='/form' method='post'>"));

  server.print(F("<p><input type='text' value='"));
  server.print(currentServo);
  server.print(F("' name='Servo'/>"));
  server.print(F("<p><input type='submit' value='Submit'/>"));
    
  server.print(F("</form>"));
  
  server.print(F("<H3>RGB LED</H3>"));
  server.print(F("<form action='/form' method='post'>"));

  server.print(F("<p>Red: <input type='text' value='"));
  server.print(cRed);
  server.print(F("' name='Red'/><br>"));
  
  server.print(F("<p>Green: <input type='text' value='"));
  server.print(cGreen);
  server.print(F("' name='Green'/><br>"));
  
  server.print(F("<p>Blue: <input type='text' value='"));
  server.print(cBlue);
  server.print(F("' name='Blue'/><br>"));
  server.print(F("<p><input type='submit' value='Submit'/>"));
    
  server.print(F("</form>"));
  
  server.print(F("</body></html>"));
}

void defaultCmd(WebServer &server, WebServer::ConnectionType type, char *url_tail, bool tail_complete)
{
  webDefaultView(server, type);  
}

void formCmd(WebServer &server, WebServer::ConnectionType type, char *url_tail, bool tail_complete)
{
  int servopos, colornum;
  
  if (type == WebServer::POST)
  {
    bool repeat;
    char name[16], value[16];
    
    do
    {
      repeat = server.readPOSTparam(name, 16, value, 16);

      String Name = String(name);
      String Value = String(value);
      
      if (Name.startsWith("Pin2"))  {
        if (Value.startsWith("Off"))
          digitalWrite(2, false);
        else
          digitalWrite(2, true);
      }
      
      if (Name.startsWith("Servo")) {
        servopos = atoi(value);
        if (servopos < minServo)
          servopos = minServo;
          
        if (servopos > maxServo)
          servopos = maxServo;
          
        myservo.write(servopos);
        currentServo = servopos;
      }
      
      if (Name.startsWith("Red")) {
        colornum = atoi(value);
        if (colornum < 0)
          colornum = 0;
          
        if (colornum > 255)
          colornum = 255;
         
        analogWrite(redPin, colornum); 
        cRed = colornum;
      }
      
      if (Name.startsWith("Green")) {
        colornum = atoi(value);
        if (colornum < 0)
          colornum = 0;
          
        if (colornum > 255)
          colornum = 255;
         
        analogWrite(greenPin, colornum); 
        cGreen = colornum;
      }
      
      if (Name.startsWith("Blue")) {
        colornum = atoi(value);
        if (colornum < 0)
          colornum = 0;
          
        if (colornum > 255)
          colornum = 255;
         
        analogWrite(bluePin, colornum); 
        cBlue = colornum;
      }
    }
    while (repeat);
    
    server.httpSeeOther("/");
    
  } else
    defaultCmd(server, type, url_tail, tail_complete);
}

void setup()
{                         
  Serial.begin(9600);
  
  pinMode(2, OUTPUT);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  
  myservo.attach(servoPin);
  
  Ethernet.begin(mac, ip);
  
  //start web server
  webserver.begin();
  webserver.setDefaultCommand(&defaultCmd);    //http://10.232.1.250
  webserver.addCommand("form", &formCmd);      //http://10.232.1.250/form
}

void loop()
{
  webserver.processConnection();
}
