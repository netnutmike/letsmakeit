/*############### ARDUNIO AS A USB KEYBOARD AND MOUSE ##################
       
       **NOTE: This sketch will only work on Arduino Leonardo, Arduino
               Mico or Duo as it requires special hardware to emulate
               a USB mouse or keyboard.
       
       This code is reading the input from an XY joystick and converting
       it into mouse movement that is sent to the computer as a USB 
       mouse.  Pressing the joystick button simulates pressing the mouse
       button.
       
       There are also 4 buttons that demonstrate how to send in USB
       keyboard buttons.
       
       For Details on the available keyboard and mouse functions visit:
        http://arduino.cc/en/Reference/MouseKeyboard

       
       For Details on the special key codes that are available visit:
        http://arduino.cc/en/Reference/KeyboardModifiers
 
   From: Mike Myers (http://mikemyers.me)  @netnutmike
       Let's Make It Episode 34 (http://tech-zen.tv/index.php/shows/let-s-make-it/)
       
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

int xPin = A0;    // select the input pin for the potentiometer
int yPin = A1;
int mouseButton = 6;

int xValue = 0;  // variable to store the value coming from the sensor
int yValue = 0;

int xMove;
int yMove;

int button1 = 2;
int button2 = 3;
int button3 = 4;
int button4 = 5;

void setup() {
  pinMode(mouseButton, INPUT_PULLUP); 
  pinMode(button1, INPUT_PULLUP);
  pinMode(button2, INPUT_PULLUP);
  pinMode(button3, INPUT_PULLUP);
  pinMode(button4, INPUT_PULLUP);
  pinMode(13, OUTPUT);
  Mouse.begin();
  Keyboard.begin();
}

void loop() {
  
  // read the values from the joystick:
  xValue = analogRead(xPin);    //up and down
  yValue = analogRead(yPin);    //left and right
  
  //check to see if the x axis has changed more than 5 in either direction
  //this is done as a safety because the joystick does not always return
  //to dead center
  if (xValue <= 510 || xValue >= 520)
    xMove = map(xValue, 0, 1023, -40, 40);      //map the x axis value to the mouse movement values
  else
    xMove = 0;
  
  //check to see if the x axis has changed more than 5 in either direction
  //this is done as a safety because the joystick does not always return
  //to dead center
  if (yValue <= 510 || yValue >= 520)
    yMove = map(yValue, 0, 1023, -40, 40);      //map the y axis value to the mouse movement values
  else
    yMove = 0;
  
  //Only move the mouse if there is a need to do so
  if (yMove != 0 || xMove !=0)
    Mouse.move(yMove, xMove);
  
  //Check if the joytick button is pressed and if so send a mouse click
  if (!digitalRead(mouseButton))
    Mouse.click();
    
  //Read the first button, if pressed, send a capital A as the keyboard
  if (!digitalRead(button1))
    Keyboard.write('A');
    
  //If the 2nd button is pressed, send a sequence of characters as the keyboard
  if (!digitalRead(button2))
    Keyboard.print("This is a sequence of Characters");
    
  //If button 3 is pressed, simulate holding down the left shift button and sending a lowercase b
  if (!digitalRead(button3))
  {
    Keyboard.press(KEY_LEFT_SHIFT);
    Keyboard.press('b');
    Keyboard.releaseAll();
  }
  
  //If button 4 is pressed, simulate holding down the left GUI (windows key on windows 
  // and CMD on a mac) and pressing v for paste
  if (!digitalRead(button4))
  {
    Keyboard.press(KEY_LEFT_GUI);
    Keyboard.press('v');
    Keyboard.releaseAll();
  }
  
    
  delay(100);                  
}
