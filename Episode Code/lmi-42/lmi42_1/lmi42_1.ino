/*############################## COUNTDOWN TIMER ##################################
       This sketch takes input from a keypad to enter the number of minutes and
       seconds to count down.  When the countdown starts an LED that represents
       a relay will turn on.  Once the countdown is complete the LED will turn
       off.
       
       The user can enter times using a keypad in MM:SS format.  The # starts
       the countdown.  The * will clear the time and also stop the current
       countdown once it starts.
       
       To read the keypad input that is is a 4x4 input, we are using a
       library from the arduino website called Keypad.  You can download this
       library at: http://arduino.cc/playground/Code/Keypad

 
   From: Mike Myers (http://mikemyers.me)  @netnutmike
       Let's Make It Episode 42 (http://letmakeit.tv)
       
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

//constants for Control Pin
int controlPin = 13;

char currentTimeValue[4];
int currentState = 1;
int timerSeconds = 0;
int lpcnt = 0;

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
  
  // Print a message to the LCD.
  lcd.backlight();
  
  displayCodeEntryScreen();
  
  //setup and turn off relay
  pinMode(controlPin, OUTPUT);
  digitalWrite(controlPin, LOW);
  
  currentTimeValue[0]='0';
  currentTimeValue[1]='0';
  currentTimeValue[2]='0';
  currentTimeValue[3]='0';
  showEnteredTime();
  
}

void loop()
{
  int l;
  char tempVal[3];
  
  char key = keypad.getKey();
  
  if (int(key) != 0 and currentState == 1) {
    
    switch (key) {
      case '*':
        relayStatus(false);
        currentTimeValue[0]='0';
        currentTimeValue[1]='0';
        currentTimeValue[2]='0';
        currentTimeValue[3]='0';
        showEnteredTime();
        currentState = 1;
        lpcnt = 0;
        timerSeconds = 0;
        break;
        
      case '#':
        tempVal[0] = currentTimeValue[0];
        tempVal[1] = currentTimeValue[1];
        tempVal[2] = 0;
        
        timerSeconds = atol(tempVal) * 60;
        
        tempVal[0] = currentTimeValue[2];
        tempVal[1] = currentTimeValue[3];
        tempVal[2] = 0;
        
        timerSeconds = timerSeconds + atol(tempVal);
        currentState = 2;
        break;
         
      default:
        currentTimeValue[0] = currentTimeValue[1];
        currentTimeValue[1] = currentTimeValue[2];
        currentTimeValue[2] = currentTimeValue[3];
        currentTimeValue[3] = key;
        showEnteredTime();
        break;
    }
  }
  
  if (currentState == 2) {
    if (int(key) != 0) {
        if (key == '*') {
          relayStatus(false);
          displayCodeEntryScreen();
          currentTimeValue[0]='0';
          currentTimeValue[1]='0';
          currentTimeValue[2]='0';
          currentTimeValue[3]='0';
          showEnteredTime();
          currentState = 1;
          lpcnt = 0;
          timerSeconds = 0;
        }
    } else {
      if (lpcnt > 9) {
        lpcnt = 0;
        --timerSeconds;
        showCountdown();
        
        if (timerSeconds <= 0) {
          currentState = 1;
          relayStatus(false);
          displayCodeEntryScreen();
          showEnteredTime();
        } else {
          relayStatus(true);
        }
      }
      
      ++lpcnt;
      delay(100);
    }
  }
}

void showEnteredTime()
{
  lcd.setCursor(14,3);
  lcd.print(currentTimeValue[0]);
  lcd.print(currentTimeValue[1]);
  lcd.print(":");
  lcd.print(currentTimeValue[2]);
  lcd.print(currentTimeValue[3]);
}

void relayStatus(bool state)
{
  if (state) 
    digitalWrite(controlPin, HIGH);
  else
    digitalWrite(controlPin, LOW);
}

void showCountdown()
{
  char timest[6];
  
  lcd.setCursor(0,0);
  lcd.print("********************");
  lcd.setCursor(0,1);
  lcd.print("** COUNTING DOWN  **");
  lcd.setCursor(0,2);
  lcd.print("**      ");
  sprintf(timest, "%d:%.2d", (timerSeconds/60), (timerSeconds - ((timerSeconds/60)*60)));
  lcd.print(timest);
  lcd.print("      **");
  lcd.setCursor(0,3);
  lcd.print("********************");
  
}

void displayCodeEntryScreen()
{
  clearScreen();
  lcd.setCursor(0,0);
  lcd.print("Let's Make It Count");
  lcd.setCursor(0,1);
  lcd.print("Down Time...");
  lcd.setCursor(0,2);
  lcd.print("Enter Time mm:ss:");
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
