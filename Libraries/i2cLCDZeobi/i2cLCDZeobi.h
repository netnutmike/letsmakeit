/*############################## I2C LCD LIBRARY ##############################
       
       This library was modified by Mike Myers.  I am not sure where the 
		original library came from.
		
		To Use this library you will need to know the address of the I2C
		for the LCD.  There are many variations of LCD Backpacks used
		on Parallel LCD's to save the number of pins needed.
		
		In addition, documentation on these LCD Backpacks is poor if you
		can even find it.
		
		To help, we have create an I2C scanner sketch for Arduino that will
		help you find the address that is used for your LCD Backpack.  You can
		download the sketch at:
		http://tech-zen.tv/episodes/shows/make-it-work/episodes/all-about-the-stinkin-lcds-let-s-make-it-lmi71
		or by going to our Github address:
		https://github.com/netnutmike/letsmakeit/tree/master/Episode%20Code
		and looking for lmi-71
       
       If you are in need of an I2C LCD backback for your parallel LCD or want an
       LCD with a backback already on it, you can get one of ours by going to
       http://zeobi.com.  Our LCD backpacks come with a default address but you
       can easily change the address if you have a conflict with the default
       address.  Something that is unique to our LCD backpacks.
      
 
   From: Mike Myers (http://mikemyers.me)  @netnutmike
       Let's Make It Episode 71 (http://tech-zen.tv/index.php/shows/let-s-make-it/)
       
       http://tech-zen.tv
       
       For the sample code, show notes, contact information and many more 
       videos, visit the show page at http://tech-zen.tv/letsmakeit

       Please subscribe to our YouTube channel or our netcasts at any of 
       your favorite netcast / podcast outlets.

       We normally record Let's Make It live on Wednesday evenings around 
       7pm eastern. You can watch it live by going to tech-zen.tv and clicking 
       the live link at the top of the page.

       We also have a community setup for our viewers and listeners. You can 
       join the community by going to community.tech-zen.tv.

       We love input on what you would like to know or if you have an idea for 
       a new Let's Make it episode, you can contact us via email or phone at 
       the show information page.
################################################################################*/



#ifndef i2cLCDZeobi_h

#define i2cLCDZeobi_h



#include <inttypes.h>

#include "Print.h" 

#include <Wire.h>



// commands

#define LCD_CLEARDISPLAY 0x01

#define LCD_RETURNHOME 0x02

#define LCD_ENTRYMODESET 0x04

#define LCD_DISPLAYCONTROL 0x08

#define LCD_CURSORSHIFT 0x10

#define LCD_FUNCTIONSET 0x20

#define LCD_SETCGRAMADDR 0x40

#define LCD_SETDDRAMADDR 0x80



// flags for display entry mode

#define LCD_ENTRYRIGHT 0x00

#define LCD_ENTRYLEFT 0x02

#define LCD_ENTRYSHIFTINCREMENT 0x01

#define LCD_ENTRYSHIFTDECREMENT 0x00



// flags for display on/off control

#define LCD_DISPLAYON 0x04

#define LCD_DISPLAYOFF 0x00

#define LCD_CURSORON 0x02

#define LCD_CURSOROFF 0x00

#define LCD_BLINKON 0x01

#define LCD_BLINKOFF 0x00



// flags for display/cursor shift

#define LCD_DISPLAYMOVE 0x08

#define LCD_CURSORMOVE 0x00

#define LCD_MOVERIGHT 0x04

#define LCD_MOVELEFT 0x00



// flags for function set

#define LCD_8BITMODE 0x10

#define LCD_4BITMODE 0x00

#define LCD_2LINE 0x08

#define LCD_1LINE 0x00

#define LCD_5x10DOTS 0x04

#define LCD_5x8DOTS 0x00



// flags for backlight control

#define LCD_BACKLIGHT 0x08

#define LCD_NOBACKLIGHT 0x00



#define En B00000100  // Enable bit
#define Bl B00001000  // Enable bit

#define Rw B00000010  // Read/Write bit pin 5

#define Rs B00000001  // Register select bit pin 4



class i2cLCDZeobi : public Print {

public:

  i2cLCDZeobi(uint8_t lcd_Addr,uint8_t lcd_cols,uint8_t lcd_rows);

  void begin(uint8_t cols, uint8_t rows, uint8_t charsize = LCD_5x8DOTS );

  void clear();

  void home();

  void noDisplay();

  void display();

  void noBlink();

  void blink();

  void noCursor();

  void cursor();

  void scrollDisplayLeft();

  void scrollDisplayRight();

  void printLeft();

  void printRight();

  void leftToRight();

  void rightToLeft();

  void shiftIncrement();

  void shiftDecrement();

  void noBacklight();

  void backlight();

  void autoscroll();

  void noAutoscroll(); 

  void createChar(uint8_t, uint8_t[]);

  void setCursor(uint8_t, uint8_t); 

  virtual size_t write(uint8_t);

  void command(uint8_t);

  void init();



////compatibility API function aliases

void blink_on();						// alias for blink()

void blink_off();       					// alias for noBlink()

void cursor_on();      	 					// alias for cursor()

void cursor_off();      					// alias for noCursor()

void setBacklight(uint8_t new_val);				// alias for backlight() and nobacklight()

void load_custom_character(uint8_t char_num, uint8_t *rows);	// alias for createChar()

void printstr(const char[]);



////Unsupported API functions (not implemented in this library)

uint8_t status();

void setContrast(uint8_t new_val);

uint8_t keypad();

void setDelay(int,int);

void on();

void off();

uint8_t init_bargraph(uint8_t graphtype);

void draw_horizontal_graph(uint8_t row, uint8_t column, uint8_t len,  uint8_t pixel_col_end);

void draw_vertical_graph(uint8_t row, uint8_t column, uint8_t len,  uint8_t pixel_col_end);

	 



private:

  void init_priv();

  void send(uint8_t, uint8_t);

  void write4bits(uint8_t);

  void expanderWrite(uint8_t);

  void pulseEnable(uint8_t);

  uint8_t _Addr;

  uint8_t _displayfunction;

  uint8_t _displaycontrol;

  uint8_t _displaymode;

  uint8_t _numlines;

  uint8_t _cols;

  uint8_t _rows;

  uint8_t _backlightval;

};



#endif

