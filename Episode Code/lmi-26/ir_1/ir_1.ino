/*############################# IR REMOTE CONTROL ################################
       This week we built a learning remote control using and IR detector and an IR
       emitter.  This first sketch shows how to read in IR codes and save them
       to an EEPROM so that they can be put back using an IR LED.
       
 
   From: Mike Myers (http://mikemyers.me)  @netnutmike
       Let's Make It Episode 26 
       
       http://tech-zen.tv
       
       For the sample code, show notes, contact information and many more 
       videos, visit the show page at http://tech-zen.tv/letsmakeit

       Please subscribe to our YouTube channel (http://youtube.com/techzentv) or our 
       netcasts at any of your favorite netcast / podcast outlets.

       We normally record Let's Make It live on Monday evenings around 
       9pm eastern. You can watch it live by going to tech-zen.tv and clicking 
       the live link at the top of the page.

       We also have a community setup for our viewers and listeners. You can 
       join the community by going to community.tech-zen.tv.

       We love input on what you would like to know or if you have an idea for 
       a new Let's Make it episode, you can contact us via email or phone at 
       the show information page.
       
       In fact, the subject of this show was done at the request of a viewer.
################################################################################*/

#include <EEPROM.h>
#include <IRremote.h>

//pin the IR receiver is connected to
int irRxPin = 9;

//frequency
int f = 38;

//define the class variables
IRrecv irrecv(irRxPin);
IRsend irsend;

//define results structure
decode_results results;

//global variables
int codeLength = 0;
int currentCode = 0;

void setup()
{
  // the serial port is used to see what is happening with the serial monitor
  Serial.begin(9600);
  
  //print to serial port with options
  Serial.println("0-9 to set memory position, s - sends");
  Serial.println("0s - sends pos 0, 2s - sends pos 2");
  
  //start IR receiver
  irrecv.enableIRIn();
  
  //set the startup default code
  setCodeMemory(0);
}

void loop()
{
  //look for something on the serial port
  if (Serial.available()) 
  {
    char ch = Serial.read();
    if (ch >= '0' && ch <= '9')      //set memory position
      setCodeMemory(ch - '0');
    else if (ch == 's')              //send code
      sendIR();
  }
  
  //look for incoming ir code to save
  if (irrecv.decode(&results))
  {
    storeCode();
    irrecv.resume();                //you must resume receive after a code is received
  }
}

//=======================================================
//
// Function: setCodeMemory
//
// Inputs:
//    int x - the memory position to set the position to
//
// Returns:
//     void
//
//======================================================
void setCodeMemory(int x)
{
  currentCode = x;
  Serial.print("Set current code memory to: ");
  Serial.println(currentCode);
  irrecv.resume();
}

//=======================================================
//
// Function: storeCode
//
// Inputs:
//    * none
//
// Returns:
//     void
//
//======================================================
void storeCode()
{
  //Write the code to EEPROM, first byte contains the length
  int startIndex = currentCode * (RAWBUF + 1);
  int len = results.rawlen - 1;
  EEPROM.write(startIndex, (unsigned byte)len);
  for (int i = 0; i<len; ++i)
  {
    if (results.rawbuf[i] > 255)
    {
      EEPROM.write(startIndex + i + 1, 255);
    } else {
      EEPROM.write(startIndex + i + 1, results.rawbuf[i]);
    }
  }
  Serial.print("Saved code, length: ");
  Serial.println(len);
}


//=======================================================
//
// Function: sendIR
//
// Inputs:
//     * none
//
// Returns:
//     void
//
//======================================================
void sendIR()
{
  int startIndex = currentCode * (RAWBUF + 1);
  int len = EEPROM.read(startIndex);
  unsigned int code[RAWBUF];
  for (int i=0; i<len; ++i)
  {
    int pulseLen = EEPROM.read(startIndex + i + 2);
    if (i % 2) {
      code[i] = pulseLen * USECPERTICK + MARK_EXCESS;
    } else {
      code[i] = pulseLen * USECPERTICK - MARK_EXCESS;
    }
  }
  irsend.sendRaw(code, len, f);
  Serial.print("Send Code Length: ");
  Serial.println(len);
}
