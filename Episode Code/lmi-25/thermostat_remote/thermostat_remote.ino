/*############################# REMOTE THERMOSTAT ################################
       This code receives commands from the main thermostat via 9600 baud serial
       connection.  In our demo we are using Zigbee as the wireless serial 
       connection between the 2 sides.  It could be any serial wireless system
       or even a single wire going from the other unit's tx pin to this units
       rx pin.
       
       The protocol used has some very basic preamble and checksum routines just
       to make sure the data recieved is valid.
       
       For reference, here are what the most common colors are in themostat
       wire and what they are used for.
       
       Red -     +24 volts, this is used to power thermostats and also used to
                 indidcate the function needed by causing a contact closure.
             
       Yellow -  First Stage Cooling.  When the 24 volts from the red wire
                 is sent down this wire, the first stage cooling will start.
                 
       Blue -    Second Stage Cooling
       
       Green -   Blower Fan, when 24 volts is sent down this wire, the indoor
                 air blower starts up.
                 
       White -   First Stage Heating, when 24 volts is sent down this wire,
                 the first stage heating starts up.
                 
       Black -   This wire will start up the 2nd stage heating, also sometimes
                 called emergency heat.
                 
       Orange -  Heat pump reversing valve, this should be energized when cooling
                 and therefore should be energized when the yellow or blue wires
                 are energized.
                 
       Brown -   Heat pump reversing valve, this should be energized when heating
                 and therefore should be energized when the white or black wires
                 are energized.
                 
       Pins:
         0 -    RX pin that connects to the ZigBee to receive data.
         1 -    TX pin that connects to the ZigBee to transmit data.
         5 -    Goes high when the inside fan should run, connects to a transistor
                to control a relay that will switch the 24 volts.  (Just an LED in
                our example).
         6 -    Goes high the AC is calling. Connects to a transistor to control a
                relay (LED).  See the wire descriptions above, as there are more than
                one wire needed if you are using a heat pump.
         7 -    Goes high when the heat is calling.  Connects to a transistor to 
                control a relay (LED).  ee the wire descriptions above, as there are 
                more than one wire needed if you are using a heat pump.
         8 -    Goes high when emergency heat is calling.  Connects to a transistor
                to control a relay.

       
       ************************************
       ***        W A R N I N G         ***
       ************************************
       
       Although this project demonstrates how easy it is to create thermostat
       controls, working on live electrical systems with mains is VERY DANGEROUS
       and should not be attempted.  Also, the potential exists that permanent
       damage can be done to your HVAC system.  We cannot assume any 
       responsibility for injury or damage to you or your equipment.  If you
       decide to play with live electricity and HVAC systems, you do so at
       your own risk.
 
   From: Mike Myers (http://mikemyers.me)  @netnutmike
       Let's Make It Episode 25 
       
       http://tech-zen.tv
       
       For the sample code, show notes, contact information and many more 
       videos, visit the show page at http://tech-zen.tv/letsmakeit

       Please subscribe to our YouTube channel or our netcasts at any of 
       your favorite netcast / podcast outlets.

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

//define pins
int fanRunPin = 5;
int acRunPin = 6;
int heatRunPin = 7;
int emHeatRunPin = 8;

// State Machine  
int currentState = 0;

// Define States
const int BEGIN = 0;
const int START = 1;
const int VALUES = 2;
const int CHECKSUM = 3;
const int ENDTRANS = 4;

// Operational variables
int values[5];
int valuePointer = 0;
int chksum;

void setup()
{
  // Set all of the pins modes
  pinMode(fanRunPin, OUTPUT);
  pinMode(acRunPin, OUTPUT);
  pinMode(heatRunPin, OUTPUT);
  pinMode(emHeatRunPin, OUTPUT);
  
  Serial.begin(9600);
}

void loop()
{
  char ch;              //A Place to Store the character we just read
  
  if (Serial.available())      // is there anything to be read from serial port?
  {
    ch = Serial.read();        // read a single character
    switch(currentState)
    {
      case BEGIN:
        if (ch == 'X')
          currentState = START;
        break;
        
      case START:
        if (ch == 'X') 
        {
          currentState = VALUES;
          valuePointer = 0;
        } else {
          currentState = BEGIN;      // Something is wrong, start over
        }
        break;
        
      case VALUES:
        switch(ch)
        {
          case 'X':                  // Something is wrong, start over
            
            currentState = BEGIN;
            break;
            
          case 'z':                  // Something is wrong, start over
            currentState = BEGIN;
            break;
            
          case 'Y':                  // Got Stop, Move to checksum read
            currentState = CHECKSUM;
            break;
            
          default:                   // Read input
            if (ch >= '0' and ch <= '9') {
              values[valuePointer] = ch;
              ++valuePointer;
              if (valuePointer > 4)
                currentState = BEGIN;  // Something is wrong, start over
            }
            break;  
        }
        break;
        
      case CHECKSUM:
        if (ch == 'z')
          currentState = ENDTRANS;    // Got the terminator, move to ENDTRANS
        else
          chksum = ch;                // Store read checksum
        break;
        
      case ENDTRANS:
        if (chksum == calcChecksum())    // if the checksum equals, set the pins
          turnOn((values[0] == '1'), (values[1] == '1'), (values[2] == '1'), (values[3] == '1'));
         
        
        currentState = BEGIN;        // Lets start all over again.
        break;
    }
  }
      
}

//**********************************************************
// calcChecksum
//
// Params:
//      * NONE
//
// Returns:
//      char checksum
//
// Description:
//    This function reads the values read from the serial 
//    port and generates a checksum that is to be compared
//    to the checksum that is received.
//
//**********************************************************
char calcChecksum()
{
  int l;
  int chksumval = 0;
  
  for (l=0; l< 4; ++l)
    if (values[l] == '1')
      chksumval += (l+1);
      
  return (48 + chksumval);
    
}


//**********************************************************
// turnOn
//
// Params:
//      int Fan - 1 = Fan should be on, 0 = Fan should be off
//      int AC - 1 = AC should be on, 0 = AC should be off
//      int Heat - 1 = Heat should be on, 0 = Heat should be off
//      int EmHeat - 1 = Emergency Heat should be on, 0 = Emergency Heat should be off
//
// Returns:
//      * VOID
//
// Description:
//    This function turns on the correct pins based on what 
//    is passed into the function.
//
//**********************************************************
void turnOn(int Fan, int AC, int Heat, int EmHeat)
{
  int runTotal = 0;
  
  if (Fan) 
    digitalWrite(fanRunPin, true);
  else
    digitalWrite(fanRunPin, false);
  
  if (AC) 
    digitalWrite(acRunPin, true);
  else
    digitalWrite(acRunPin, false);

  if (Heat) 
    digitalWrite(heatRunPin, true);
  else
    digitalWrite(heatRunPin, false);
  
  if (EmHeat) 
    digitalWrite(emHeatRunPin, true);
  else
    digitalWrite(emHeatRunPin, false);
  
}

