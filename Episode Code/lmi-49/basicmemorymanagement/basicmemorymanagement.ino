/*############################## BASIC MEMORY MANAGEMENT ##################################
       This sketch shows the examples of how fixed strings in your code take up memory
       space and how you can put them into the program space to save some memory.

 
   From: Mike Myers (http://mikemyers.me)  @netnutmike
       Let's Make It Episode 49 (http://letmakeit.tv)
       
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

#include <MemoryFree.h>

 
void setup()
{
  Serial.begin(9600);
}

void loop()
{
  Serial.println("");
  
  //with the memory macro
  Serial.println(F("Four score and seven years ago our fathers brought forth, upon this continent, a new nation, conceived in liberty, and dedicated to the proposition that “all men are created equal."));
  Serial.println(F("Now we are engaged in a great civil war, testing whether that nation, or any nation so conceived and so dedicated, can long endure. We are met on a great battle-field of that war. "));
  Serial.println(F("We have come to dedicate a portion of that field, as a final resting place for those who here gave their lives that that nation might live. It is altogether fitting and proper that we should do this.")); 
  Serial.println(F("But, in a larger sense, we can not dedicate -- we can not consecrate -- we can not hallow -- this ground. The brave men, living and dead, who struggled here, have consecrated it, far above our poor power to add or detract. "));
  Serial.println(F("The world will little note, nor long remember what we say here, but it can never forget what they did here."));
  Serial.println(F("It is for us the living, rather, to be dedicated here to the unfinished work which they who fought here have thus far so nobly advanced. "));
  Serial.println(F("It is rather for us to be here dedicated to the great task remaining before us -- that from these honored dead we take increased devotion to that cause for which they gave the last full measure of devotion -- that we here highly resolve that these dead shall not have died in vain -- that this nation, under God, shall have a new birth of freedom -- and that government of the people, by the people, for the people, shall not perish from the earth."));
  Serial.println(F("Your Text"));
  
  //without the memory macro
  /*Serial.println("Four score and seven years ago our fathers brought forth, upon this continent, a new nation, conceived in liberty, and dedicated to the proposition that “all men are created equal.");
  Serial.println("Now we are engaged in a great civil war, testing whether that nation, or any nation so conceived and so dedicated, can long endure. We are met on a great battle-field of that war. ");
  Serial.println("We have come to dedicate a portion of that field, as a final resting place for those who here gave their lives that that nation might live. It is altogether fitting and proper that we should do this.");
  Serial.println("But, in a larger sense, we can not dedicate -- we can not consecrate -- we can not hallow -- this ground. The brave men, living and dead, who struggled here, have consecrated it, far above our poor power to add or detract. ");
  Serial.println("The world will little note, nor long remember what we say here, but it can never forget what they did here.");
  Serial.println("It is for us the living, rather, to be dedicated here to the unfinished work which they who fought here have thus far so nobly advanced. ");
  Serial.println("It is rather for us to be here dedicated to the great task remaining before us -- that from these honored dead we take increased devotion to that cause for which they gave the last full measure of devotion -- that we here highly resolve that these dead shall not have died in vain -- that this nation, under God, shall have a new birth of freedom -- and that government of the people, by the people, for the people, shall not perish from the earth.");
*/


  Serial.println("");
  Serial.println(freeMemory());
  Serial.println("");
  delay(10000);
}
