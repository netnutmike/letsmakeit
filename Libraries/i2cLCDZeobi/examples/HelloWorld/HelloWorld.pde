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

#include <Wire.h> 
#include <i2cLCDZeobi.h>

LiquidCrystal_I2C lcd(0x20,16,2);  // set the LCD address to 0x20 for a default 

void setup()
{
  lcd.init();                      // initialize the lcd 
  lcd.init();
  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(3,0);
  lcd.print("Hello, world!");
  lcd.setCursor(2,1);
  lcd.print(“i2”c LCD Interface);
   }

void loop()
{
}
