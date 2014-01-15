/*############################# LEARNING REMOTE CONTROL ################################
       This week we built a learning remote control using and IR detector and an IR
       emitter.  We can program the remote control and play back by simply pressing
       a button.
       
       We also introduce for the first time the ability to write to EEPROM on the 
       arduino.
 
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

//buttons for the remote (pin they are connected to)
int button1 = 4;
int button2 = 5;
int button3 = 6;
int button4 = 7;

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
  
  //setup button pins
  pinMode(button1, INPUT_PULLUP);
  pinMode(button2, INPUT_PULLUP);
  pinMode(button3, INPUT_PULLUP);
  pinMode(button4, INPUT_PULLUP);
  
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
    if (ch >= '0' && ch <= '9')        //set memory position
      setCodeMemory(ch - '0');
    else if (ch == 's')                //send code
      sendIR(currentCode);
    
  }
  
  //look for button presses
  if (!digitalRead(button1))
    sendIR(0);
    
  if (!digitalRead(button2))
    sendIR(1);
    
  if (!digitalRead(button3))
    sendIR(2);
    
  if (!digitalRead(button4))
    sendIR(3);
  
  //look for incoming ir code to save
  if (irrecv.decode(&results))
  {
    storeCode();
    irrecv.resume();    //you must resume receive after a code is received
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
//     int codeNumber - Code number to send
//
// Returns:
//     void
//
//======================================================
void sendIR(int codeNumber)
{
  int startIndex = codeNumber * (RAWBUF + 1);
  int len = EEPROM.read(startIndex);
  unsigned int code[RAWBUF];
  for (int i=0; i<len; ++i)
  {
    int pulseLen = EEPROM.read(startIndex + i + 2);
    if (i % 2)
      code[i] = pulseLen * USECPERTICK + MARK_EXCESS;
    else
      code[i] = pulseLen * USECPERTICK - MARK_EXCESS;
  }
  irsend.sendRaw(code, len, f);
  Serial.print("Send Code Length: ");
  Serial.println(len);
}
