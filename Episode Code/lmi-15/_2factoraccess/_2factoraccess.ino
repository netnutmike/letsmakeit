/*############################## RFID LOCK ##################################
       This sketch reads from a parallax RFID reader the TAG ID and compares
       it to an array of valid RFID tags and their owners.  If a match is found
       then it waits for the input of the secret code.  If the correct code 
       is entered then it grants access.
       
       This is a simulation of a real life 2 factor authentication method for
       accessing secured areas.

 
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
#include <Keypad.h>

//constants for LEDs and Pins
int greenLED = 12;
int redLED = 13;
const int RFIDEnablePin = 2;

//set our employees
const byte numEmployees = 4;

// Array values are TAG ID, First Name, Last Name, Secret Code
char *employees[][4] = {
  {"04162C5775","Mike","Myers","1234"},
  {"0F0296AEE7","Dennis","Hawkins","9876"},
  {"0F0296AF66","Michelle","Myers","2580"},
  {"0F0296AEE8","John","Gibert","1245"}
};

//setup the state table states
int currentState = 1;                 // State variable initialized to state 1 (read card)
const int waitingForTagID = 1;        // Waiting for Card input
const int waitingForPasscode = 2;     // Waiting for keypad input

// Misc Global Variables
char* ourCode;                        // Used to store the secret code for the user who's RFID was read
int currentPosition = 0;              // Used to remember the location of the code input
int  val = 0;                         // Used in reading the card
char code[10];                        // The TAG ID of the card
int bytesread = 0;                    // Used in reading the card
int currentEmployee;                  // The current employee being worked is stored here
long myTimer;                          // Used for the code entry timeout

// The name of the location for this reader.  This is displayed in the serial output
const char locationName[] = "Let's Make It Studio A";

//define the keypad
const byte rows = 4;
const byte cols = 4;

char keys[rows][cols] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[rows] = {11,10,9,8};
byte colPins[cols] = {7,6,5,4};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, rows, cols);

LiquidCrystal_I2C lcd(0x3F,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display

void setup()
{
  lcd.init();                       // initialize the lcd 
  lcd.init();
  delay(500);
  
  lcd.backlight();                  // Turn on backlight for LCD.
  delay(500);
  
  Serial.begin(2400);               // The RFID reader outputs at a whopping 2400 Baud
  
  pinMode(RFIDEnablePin, OUTPUT);   // Set digital pin 2 as OUTPUT to connect it to the RFID /ENABLE pin 
  
  //setup and turn off both LEDs
  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  digitalWrite(redLED, LOW);
  digitalWrite(greenLED, LOW);
  
  displayTagScanScreen();          //Put up default screen for reading the tags
  
}

void loop()
{
  int l;
  int empid;
  
  switch (currentState) 
  {
    case waitingForTagID:
      digitalWrite(RFIDEnablePin, LOW);      // Enable RFID Reader
      
      if(Serial.available() > 0) {           // if data available from reader 
        if((val = Serial.read()) == 10) {    // check for header 
          bytesread = 0; 
          
          while(bytesread<10) {              // read 10 digit code 
            if( Serial.available() > 0) { 
              val = Serial.read(); 
              if((val == 10)||(val == 13)) { // if header or stop bytes before the 10 digit reading 
                break;                       // stop reading 
              } 
              code[bytesread] = val;         // add the digit           
              bytesread++;                   // ready to read next digit  
            } 
          } 
          
          if(bytesread == 10) {              // if 10 digit read is complete 
            // Check to see if tag is valid and attached to an employee
            
            code[10] = '\0';                // Add null at end to terminate the string
             empid = getEmployee(code);     // Get the employee id of the tag read, -1 means no match
             if (empid == -1) {
               digitalWrite(RFIDEnablePin, HIGH);  // Turn off RFID Reader
               invalidCard();                      // Display invalid card message
               digitalWrite(RFIDEnablePin, LOW);   // Turn on RFID reader
             } else {
               currentEmployee = empid;            // Store for future use
               displayCodeEntryScreen(employees[empid][1]);  //Display code entry screen with first name of employee
               currentState = waitingForPasscode;            // Change the state to waiting for passcode entry
               ourCode = employees[empid][3];                // Place the employee secret code into the code entry value
               clearSerial();                                // Clear any extra data on the serial port
               myTimer = millis();
             }
          } 
          
          bytesread = 0; 
          
        } 
      }
      break;
      
    case waitingForPasscode:
      digitalWrite(RFIDEnablePin, HIGH);                    // Disable the RFID reader while doing code input
      char key = keypad.getKey();
  
      if (int(key) != 0) {
        
        // Reset timeout timer to current time
        myTimer = millis();
        
        // Clear the asterisk area for code entry
        lcd.setCursor(14,3);
        lcd.print("    ");
        lcd.setCursor(14,3);
        
        // display asterisk for each code entered
        for (l=0; l<=currentPosition; ++l)
        {
          lcd.print("*");
        }
        
        // check to see if the key pressed matches the next digit in the code
        if (key == ourCode[currentPosition])
          {
            ++currentPosition;
            if (currentPosition == 4)
            {
              logEmployee(currentEmployee, true);
              unlockDoor();
              currentPosition = 0;
              currentState = waitingForTagID;
              clearSerial();
            }
          } else {
            // Does not match so it is an invalid code
            logEmployee(currentEmployee, false);          // Log to the serial port the failue
            invalidCode();                                // Display invalid code screen
            currentPosition = 0;                          // Set the read position back to 0
            currentState = waitingForTagID;               // Change the state back to waiting for RFID read
            clearSerial();                                // Clear and junk that is on the serial port
          }
      } else {
        if ((myTimer+10000) <= millis()) {
            //no key pressed for timeout period
            
            codeEntryTimeout();                                // Display invalid code screen
            currentPosition = 0;                          // Set the read position back to 0
            currentState = waitingForTagID;               // Change the state back to waiting for RFID read
            clearSerial();
            
        }
      }
  }
}

/***********************************************************************************************
  FUNCTION: getEmployee
  
  RETURNS: 
    The array element id of the employee that matches the RFID TAG.  If no employee matches
    then -1 is returned.
    
  INPUTS:
    tagID (char)  : The value read from the RFID TAG
    
  COMMENTS:
    This function will take the tag id that was read from the RFID reader and loop through all
    employees looking for a match.  When it finds a match it returnes the element id for that
    employee.
    
    If all employees have been read without a match, it returns -1 for no match
    
***********************************************************************************************/    
int getEmployee(char tagID[])
{
    int l;
    
    for (l=0; l<numEmployees; ++l)
    {
      if (strcmp(tagID, employees[l][0]) == 0) 
        return l;
    }
    
    return -1;
}

/***********************************************************************************************
  FUNCTION: logEmployee
  
  RETURNS: 
    NOTHING (void)
    
  INPUTS:
    empid (int)        : This is the employee id or element number from the employee array
    grantAccess (int)  : If the emplyee was granted access then this is true, if the employee
                         was denied access then this is false.
    
  COMMENTS:
    This function simply outputs to the serial port if a user was granted or denied access,
    the user name and the location of this reader.
    
    This function could be cleaned up by using sprintf to create a combined employee name (FOR),
    the TO: as well.  But it was quick and used what we have talked about so far.
    
***********************************************************************************************/
void logEmployee(int empid, int grantedAccess)
{
  if (grantedAccess)
    Serial.println("ACCESS GRANTED:");
  else
    Serial.println("ACCESS DENIED:");
  Serial.print("  TO: ");
  Serial.println(locationName);
  Serial.print("  FOR: ");
  Serial.print(employees[empid][1]);
  Serial.print(" ");
  Serial.println(employees[empid][2]);
  Serial.println(" ");
  Serial.println(" ");
}

/***********************************************************************************************
  FUNCTION: clearSerial
  
  RETURNS: 
    NOTHING (void)
    
  INPUTS:
    NONE
    
  COMMENTS:
    This function simply reads any data on the serial port until there is no more data.  It
    is basically throwing away any extra input on the serial port effectivly clearing it.
    
***********************************************************************************************/
void clearSerial()
{
  while (Serial.available() > 0) {
    Serial.read();
  }
}

void invalidCode()
{
  digitalWrite(redLED, HIGH);
  clearScreen();
  lcd.setCursor(0,0);
  lcd.print("********************");
  lcd.setCursor(0,1);
  lcd.print("** ACCESS DENIED! **");
  lcd.setCursor(0,2);
  lcd.print("**  INVALID CODE  **");
  lcd.setCursor(0,3);
  lcd.print("********************");
  
  delay(5000);
  digitalWrite(redLED, LOW);
  displayTagScanScreen();
}

void invalidCard()
{
  digitalWrite(redLED, HIGH);
  clearScreen();
  lcd.setCursor(0,0);
  lcd.print("********************");
  lcd.setCursor(0,1);
  lcd.print("** ACCESS DENIED! **");
  lcd.setCursor(0,2);
  lcd.print("**  INVALID CARD  **");
  lcd.setCursor(0,3);
  lcd.print("********************");
  
  delay(5000);
  digitalWrite(redLED, LOW);
  displayTagScanScreen();
}

void unlockDoor()
{
  digitalWrite(greenLED, HIGH);
  clearScreen();
  lcd.setCursor(0,0);
  lcd.print("********************");
  lcd.setCursor(0,1);
  lcd.print("** ACCESS GRANTED **");
  lcd.setCursor(0,2);
  lcd.print("**   WELCOME!!    **");
  lcd.setCursor(0,3);
  lcd.print("********************");
  
  //add any code to unlock the door here
  delay(5000);
  digitalWrite(greenLED, LOW);
  displayTagScanScreen();
}

void codeEntryTimeout()
{
  digitalWrite(redLED, HIGH);
  clearScreen();
  lcd.setCursor(0,0);
  lcd.print("********************");
  lcd.setCursor(0,1);
  lcd.print("**   CODE ENTRY   **");
  lcd.setCursor(0,2);
  lcd.print("**   TIMEOUT!!    **");
  lcd.setCursor(0,3);
  lcd.print("********************");
  
  //add any code to unlock the door here
  delay(5000);
  digitalWrite(greenLED, LOW);
  displayTagScanScreen();
}

void displayTagScanScreen()
{
  clearScreen();
  lcd.setCursor(0,0);
  lcd.print("Let's Make It Two");
  lcd.setCursor(0,1);
  lcd.print("Factor Auth Project");
  lcd.setCursor(2,3);
  lcd.print("Scan Tag...");
}

void displayCodeEntryScreen(char *firstName)
{
  clearScreen();
  lcd.setCursor(0,0);
  lcd.print("Welcome");
  lcd.setCursor(8,0);
  lcd.print(firstName);
  lcd.setCursor(0,2);
  lcd.print("Please Enter Your");
  lcd.setCursor(1,3);
  lcd.print("Secret Code:");
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

