/*############################# THERMOSTAT ################################
       This code is a basic thermostat that can control an HVAC system
       that has controls for Fan, AC, Heat and Emergency Heat.  It has
       many of the features of modern thermostats including automatic
       emergency heat, farenheight or celcius.
       
       This thermostat also has the ability to remote control a furnace or
       AC unit wirelessly using Zigbee.  Any wireless technology that can
       transmit serial data is supported.  You could even run a single wire
       from the tx of the main unit to the rx of the remote unit.
       
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
         3 -    Connects to the Temp Down button.  Button press connects pin to
                GND.  Pin is configured as INPUT_PULLUP.
         4 -    Connects to the Temp Up button.  Button press connects pin to
                GND.  Pin is configured as INPUT_PULLUP.
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
         9 -    Connects to the Mode button.  Button press connects pin to GND.  Pin
                is configured as INPUT_PULLUP.
         11 -   Connects to temperature sensor data pin.
         
       
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

// Include the libraries that we need
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <dht11.h>

//Defaults for the thermostat
int coolTemp = 72;                // The default startup temperature for AC
int minCoolTemp = 60;             // This is the coolest the thermostat can be set to
int heatTemp = 70;                // This is the default startup temperature for heat
int maxHeatTemp = 85;             // This is the warmest the thermostat can be set to
int emergencyHeatDegrees = 3;     // This is the value that is used to set when the automatic emergency heat kicks in
int runMode = 0;                  // This is the default startup mode (AUTO)
bool measurementMode = false;     // This is the default startup Measurement system (Farenheight)

// Operational variables
char ctmp[10];                    // Character Array used to create the current mode and temp string
int currentTemperature;           // Stores current temperature
int waitingLoop = 0;              // Used to keep track of how long since last read and keypress

//define pins
int modeButton = 9;
int tempDownButton = 3;
int tempUpButton = 4;
int fanRunPin = 5;
int acRunPin = 6;
int heatRunPin = 7;
int emHeatRunPin = 8;

int maxModes = 6;

//define modes
char modes[][8]={
    "Auto",
    "Fan",
    "Cool",
    "Heat",
    "Em Heat",
    "Options"
};

LiquidCrystal_I2C lcd(0x3F,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display
dht11 DHT11(12);

void setup()
{
  DHT11.attach(11);                          //Attached temperature sensor to pin 11
  
  // Set all of the pins modes
  pinMode(modeButton, INPUT_PULLUP);
  pinMode(tempDownButton, INPUT_PULLUP);
  pinMode(tempUpButton, INPUT_PULLUP);
  pinMode(fanRunPin, OUTPUT);
  pinMode(acRunPin, OUTPUT);
  pinMode(heatRunPin, OUTPUT);
  pinMode(emHeatRunPin, OUTPUT);
  
  lcd.init();                      // initialize the lcd 
  lcd.init();
  lcd.backlight();                 // Light It Up
  
  Serial.begin(9600);              // Startup Serial for remote control
}

void loop()
{
  //check for any keypresses
  if (!digitalRead(modeButton))    // Mode Button
  {
    waitingLoop = 0;               // Reset wait time so our changes do not take immediate effect
    lcd.setCursor(0,3);            // Clear out the current mode text
    lcd.print("        ");
    lcd.setCursor(5,2);
    lcd.print("               ");
    ++runMode;                     // Toggle run mode to next mode and go back to first mode if at end
    if (runMode > (maxModes - 1))
      runMode = 0;
  }
  
  if (!digitalRead(tempUpButton))  // Temperature Up Button
  {
    waitingLoop = 0;               // Reset wait time so our changes do not take immediate effect
    if (runMode == 5) {            // If in Options mode, set measruement to celcius and clear the 
       measurementMode = true;     // old temperature
       lcd.setCursor(13,0);
       lcd.print("     ");
    }
    else
      increaseSetTemperature();    // Increase the temperature of the current mode
  }
  
  if (!digitalRead(tempDownButton))  // Temperature Down Button
  {
    waitingLoop = 0;               // Reset wait time so our changes do not take immediate effect
    if (runMode != 5)              
      decreaseSetTemperature();    // Decrease the temperature of the current mode
     else {                        // If in Options mode, set measurement to Farenheight and clear
       measurementMode = false;    // the old temperature
       lcd.setCursor(13,0);
       lcd.print("     ");
     }
  }
  int chk = DHT11.read();          // Read the sensor
  
  switch (chk)
  {
    case 0:                        // All good, no errors reading the sensor
       
      lcd.setCursor(0,0);          // Display the temperature
      lcd.print("Temperature: ");
      if (measurementMode) {        // In Celcius
        lcd.print(DHT11.temperature);
        lcd.print("c");
      } else                        // in Farenheight
        lcd.print(DHT11.fahrenheit());
      currentTemperature = DHT11.fahrenheit();  // Remember current temperature
      lcd.setCursor(0,1);                       // Display Humidity
      lcd.print("Humidity: ");
      lcd.print(DHT11.humidity);
      lcd.print("%  ");
      lcd.setCursor(0,2);
      lcd.print("Mode: ");                      // Display Mode
      lcd.print(modes[runMode]);
      //lcd.print(" @ ");
      lcd.print(currentSettings());
      break;
      
    //default:                                  //uncomment if errors are being generated reading the sensor
      //lcd.print("ERROR          ");
      //lcd.setCursor(0,0);
      //lcd.print(chk);
  }
  
  //waiting loop to wait 5 seconds after a change is made to make adjustments
  ++waitingLoop;             
  if (waitingLoop >= 25) {
    waitingLoop = 0;
    takeAction();
  }
  
  delay(200);    // Checking 5 times a second.
  
}

//**********************************************************
// currentSettings
//
// Params:
//      * NONE
//
// Returns:
//    Char pointer to string with mode and temp settings
//
// Description:
//    This function returns a pointer to a string that 
//    contains the temperature settings for the current
//    mode.  The text that is returned is displayed
//    right after the current mode.
//**********************************************************
char* currentSettings()
{
  int ncooltemp, nheattemp;
  
  //first set the cooltemp and heattemp based on the celcius / farenheight setting
  if (measurementMode) {
    ncooltemp = (coolTemp - 32) * .555555556;
    nheattemp = (heatTemp - 32) * .555555556;
  } else {
    ncooltemp = coolTemp;
    nheattemp = heatTemp;
  }
  switch (runMode)
  {
    case 0:                // Mode Auto, show low and high temp
      sprintf(ctmp, " @ %d/%d", ncooltemp, nheattemp);
      break;
      
    case 1:                // Mode fan, show no temp
      sprintf(ctmp, "");
      break;
      
    case 2:                // Mode cool, show cool temp
      sprintf(ctmp, " @ %d", ncooltemp);
      break;
      
    case 3:                // Mode Heat, show heat temp
      sprintf(ctmp, " @ %d", nheattemp);
      break;
      
    case 4:                // Mode Emergency Heat, show heat temp
      sprintf(ctmp, " @ %d", nheattemp);
      break;
      
    case 5:                // Mode Options, show no temp
      sprintf(ctmp, "");
      break;
  }
  
  return ctmp;
}

//**********************************************************
// increaseSetTemperature
//
// Params:
//      * NONE
//
// Returns:
//      * VOID
//
// Description:
//    This function will increase the current temperature
//    setting by one degree for current mode.
//
//    This function was created for ease of reading the
//    code.  This one function will determine based on the
//    mode what needs to change, so the code in the keypress
//    area can remain simple and easy to read.
//**********************************************************
void increaseSetTemperature()
{
  switch (runMode)
  {
    case 0:
      ++heatTemp;
      if (heatTemp > maxHeatTemp)
        heatTemp = maxHeatTemp;
      break;
      
    case 2:
      ++coolTemp;
      if (coolTemp > maxHeatTemp)
        coolTemp = maxHeatTemp;
      break;
      
    case 3:
      ++heatTemp;
      if (heatTemp > maxHeatTemp)
        heatTemp = maxHeatTemp;
      break;
      
    case 4:
      ++heatTemp;
      if (heatTemp > maxHeatTemp)
        heatTemp = maxHeatTemp;
      break;
  }
}

//**********************************************************
// decreaseSetTemperature
//
// Params:
//      * NONE
//
// Returns:
//      * VOID
//
// Description:
//    This function will decrease the current temperature
//    setting by one degree for current mode.
//
//    This function was created for ease of reading the
//    code.  This one function will determine based on the
//    mode what needs to change, so the code in the keypress
//    area can remain simple and easy to read.
//**********************************************************
void decreaseSetTemperature()
{
  switch (runMode)
  {
    case 0:
      --coolTemp;
      if (coolTemp < minCoolTemp)
        coolTemp = minCoolTemp;
      break;
      
    case 2:
      --coolTemp;
      if (coolTemp < minCoolTemp)
        coolTemp = minCoolTemp;
      break;
      
    case 3:
      --heatTemp;
      if (heatTemp < minCoolTemp)
        heatTemp = minCoolTemp;
      break;
      
    case 4:
      --heatTemp;
      if (heatTemp < minCoolTemp)
        heatTemp = minCoolTemp;
      break;
  }
}

//**********************************************************
// takeAction
//
// Params:
//      * NONE
//
// Returns:
//      * VOID
//
// Description:
//    This function is called every 5 seconds when no there
//    are no keypresses, or 5 seconds after the last 
//    kepress.
//
//    It determines based on the current mode and current
//    temperature and setting what should be running.
//
//    Based upon that determination it calls the turnOn
//    function to activate the correct pins which in turn
//    activate the correct relays to notify the HVAC system
//    what it should be doing.
//**********************************************************
void takeAction()
{
  switch (runMode)
  {
    case 0:
      
      if (currentTemperature < heatTemp) {
        if (currentTemperature < (heatTemp-emergencyHeatDegrees))
          turnOn(true, false, false, true);
        else
          turnOn(true, false, true, false);
      } else if (currentTemperature > coolTemp) {
        turnOn(true, true, false, false);
      } else {
        turnOn(false, false, false, false);
      }
      break;
      
    case 1:
      turnOn(true, false, false, false);
      break;
      
    case 2:
      if (currentTemperature > coolTemp) {
        turnOn(true, true, false, false);
      } else {
        turnOn(false, false, false, false);
      }
      
      break;
      
    case 3:
      if (currentTemperature < heatTemp) {
        if (currentTemperature < (heatTemp-emergencyHeatDegrees))
          turnOn(true, false, false, true);
        else
          turnOn(true, false, true, false);
      } else {
        turnOn(false, false, false, false);
      }
      break;
      
    case 4:
      if (currentTemperature < heatTemp) {
        turnOn(true, false, false, true);
      } else {
        turnOn(false, false, false, false);
      }
      break;
      
    default:
      turnOn(false, false, false, false);
      break;
  }
}

//**********************************************************
// takeAction
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
//    This functions serves 2 different purposes, one it
//    turns on the correct pins based on what is passed
//    into the function.
//
//    The second purpose is to send the serial data out the
//    serial port to the remote controls.
//
//    The protocol that is used to send the remote settings
//    is pretty basic and consists of a 2 character preamble
//    a one character stop, one character checksum and a one
//    character terminator.
//
//    The format is XX####Y#z.  The XX is the preamble, the
//    next 4 # are the 1 or 0 based upon the pin status.
//    These numbers follow the input to the turnOn function
//    and therefore are Fan, AC, Heat and EmHeat.
//
//    The Y is the stop, the next # is the single 
//    digit checksum and the z is the terminator.
//
//    The checksum is generated by adding together the
//    position values of data starting with the first 
//    position of 1.  For example, if the data was 1010
//    Meaning the Fan and Heat were on, the checksum would
//    be 4 (1 for fan and 3 for heat).
//
//    Also, required is a CR/LF at the end of the data
//    packet.
//**********************************************************
void turnOn(int Fan, int AC, int Heat, int EmHeat)
{
  int runTotal = 0;
  
  Serial.print("XX");              //Preamble
  if (Fan) {
    digitalWrite(fanRunPin, true);  // turn on fan, send a 1 for on and add 1 to the checksum
    Serial.print("1");
    runTotal += 1;
  } else {
    digitalWrite(fanRunPin, false);
    Serial.print("0");
  }
    
  if (AC) {
    digitalWrite(acRunPin, true);  // turn on AC, send a 1 for AC on and add 2 to the checksum
    Serial.print("1");
    runTotal += 2;
  } else {
    digitalWrite(acRunPin, false);
    Serial.print("0");
  }
    
  if (Heat) {
    digitalWrite(heatRunPin, true);  // turn on Heat, send a 1 for heat on and add 3 to the checksum
    Serial.print("1");
    runTotal += 3;
  } else {
    digitalWrite(heatRunPin, false);
    Serial.print("0");
  }
    
  if (EmHeat) {
    digitalWrite(emHeatRunPin, true);  // turn on emergency heat, send a 1 for emergency heat and add 4 to the checksum
    Serial.print("1");
    runTotal += 4;
  } else {
    digitalWrite(emHeatRunPin, false);
    Serial.print("0");
  }
  
  Serial.print("Y");                  // Send Stop
  Serial.print(runTotal);             // Send Checksum
  Serial.println("z");                // Send terminator and CR/LF
}

