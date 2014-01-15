/*############################## SECRET KEYCODE ##################################
       This sketch takes input from a keypad for s secret code.  If the code is
       entered correctly it turns on a green LED to simulate access granted and
       displays on the LCD access granted.
       
       If an invalid code is entered, the red LED is lit and access denied is
       displayed on the LCD.
       
       To read the keypad input that is is a 4x4 input, we are using a
       library from the arduino website called Keypad.  You can download this
       library at: http://arduino.cc/playground/Code/Keypad

 
   From: Mike Myers (http://mikemyers.me)  @netnutmike
       Let's Make It Episode 6 (http://tech-zen.tv/index.php/shows/let-s-make-it/episodes/59-sensor-fun-with-arduino-1-massive-failure-but-4-successes-let-s-make-it-episode-6)
       
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

//constants for LEDs
int greenLED = 12;
int redLED = 13;

//set our code
char* ourCode = "1234";
int currentPosition = 0;

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
  lcd.init();                      // initialize the lcd 
  //lcd.init();
  
  // Print a message to the LCD.
  lcd.backlight();
  
  displayCodeEntryScreen();
  
  //setup and turn off both LEDs
  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  digitalWrite(redLED, LOW);
  digitalWrite(greenLED, LOW);
  
}

void loop()
{
  int l;
  
  char key = keypad.getKey();
  
  if (int(key) != 0) {
    lcd.setCursor(14,3);
    lcd.print("    ");
    lcd.setCursor(14,3);
    
    for (l=0; l<=currentPosition; ++l)
    {
      lcd.print("*");
    }
    
    if (key == ourCode[currentPosition])
      {
        ++currentPosition;
        if (currentPosition == 4)
        {
          unlockDoor();
          currentPosition = 0;
        }
      } else {
        invalidCode();
        currentPosition = 0;
      }
    
    
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
  displayCodeEntryScreen();
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
  displayCodeEntryScreen();
}

void displayCodeEntryScreen()
{
  clearScreen();
  lcd.setCursor(0,0);
  lcd.print("Let's Make It Secret");
  lcd.setCursor(0,1);
  lcd.print("Code Project...");
  lcd.setCursor(0,2);
  lcd.print("Enter Secret Code:");
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

