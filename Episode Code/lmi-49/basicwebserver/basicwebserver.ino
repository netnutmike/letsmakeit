/*############################## BASIC WEB SERVER ##################################
       This sketch shows an example of how to create a basic web server.
       
       This sketch has 3 pages, the default which has a link to page #2,
       Page #2 which has 4 input fields on it.  The last one is the
       receiver for the 4 input fields which prints to the serial interface
       the input values.

 
   From: Mike Myers (http://mikemyers.me)  @netnutmike
       Let's Make It Episode 49 (http://letmakeit.tv)
       
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
#include <Wire.h>
#include <dht11.h>

static uint8_t mac[] = { 0x90, 0xA2, 0xDA, 0x0D, 0x3F, 0xB6 };    // MAC address of your device

static uint8_t ip[] = { 10, 232, 1, 251 };

WebServer webserver("", 80);
 
dht11 DHT11(4);



void webDefaultView(WebServer &server, WebServer::ConnectionType type)
{
  P(htmlHead) =
    "<html>"
    "<head>"
    "<title>Test Web Page 1</title>"
    "<style type=\"text/css\">"
    "BODY { font-family: sans-serif }"
    "H1 { font-size: 14pt; }"
    "P  { font-size: 10pt; }"
    "</style>"
    "</head>"
    "<body>";

  server.httpSuccess();
  server.printP(htmlHead);
  
  server.print(F("<H1>Web Default View</H1>"));
  server.print(F("<br><a href=\"/page2\">Click Here</a> to go to page 2 with the form<BR><BR><BR>"));
  
  
  int chk = DHT11.read();          // Read the sensor
  if (chk == 0) {
    server.print(F("<h2>Current Tempterature</h2>"));
    server.print(DHT11.temperature);
    server.print(F("c / "));
    server.print(DHT11.fahrenheit());
    server.print(F("f<br><br>"));
    server.print(DHT11.humidity);
    server.print(F("% Humidity<br><br>"));
  } else 
    Serial.println(chk);
  
  server.print(F("</body></html>"));
}

void defaultCmd(WebServer &server, WebServer::ConnectionType type, char *url_tail, bool tail_complete)
{
  webDefaultView(server, type);  
}

void page2cmd(WebServer &server, WebServer::ConnectionType type, char *url_tail, bool tail_complete)
{
  int i;
  
  P(htmlHead) =
    "<html>"
    "<head>"
    "<title>Test Web Page 2</title>"
    "<style type=\"text/css\">"
    "BODY { font-family: sans-serif }"
    "H1 { font-size: 14pt; }"
    "P  { font-size: 10pt; }"
    "</style>"
    "</head>"
    "<body>";

  server.httpSuccess();
  server.printP(htmlHead);
  
  server.print(F("<H1>Page 2 with form</H1>"));
  
  server.print(F("<div style='width:660px; margin-left:10px;'><form action='/form' method='post'>"));
  
  for (i = 1; i <= 4; ++i) {
    server.print(F("Name #"));
    server.print(i);
    server.print(F(": <input type='text' name='NAME"));
    server.print(i);
    server.print(F("' id='NAME"));
    server.print(i);
    server.print(F("' size='16'><br>"));
  }
    
  server.print(F("<p><input type='submit' value='Submit'/>"));
  server.print(F("</form></div></body></html>"));
}

void formCmd(WebServer &server, WebServer::ConnectionType type, char *url_tail, bool tail_complete)
{
  if (type == WebServer::POST)
  {
    bool repeat;
    char name[16], value[16];
    
    do
    {
      repeat = server.readPOSTparam(name, 16, value, 16);

      String Name = String(name);
      
      if (Name.startsWith("NAME"))  {
        int addr = strtoul(name + 4, NULL, 10);
        
        Serial.print("Name #");
        Serial.print(addr);
        Serial.print(": ");
        Serial.println(value);
      }
    }
    while (repeat);
    
    server.httpSeeOther("/page2");
    
  } else
    page2cmd(server, type, url_tail, tail_complete);
}

void setup()
{
  DHT11.attach(4);                          
  
  Serial.begin(9600);
  
  Ethernet.begin(mac, ip);
  
  //start web server
  webserver.begin();
  webserver.setDefaultCommand(&defaultCmd);    //http://10.232.1.250
  webserver.addCommand("page2", &page2cmd);    //http://10.232.1.250/page2
  webserver.addCommand("form", &formCmd);         //http://10.232.1.250/form
}

void loop()
{
  webserver.processConnection();
}
