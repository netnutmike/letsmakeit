/*############################## RGB COLOR CYCLER ################################
       This sketch loops through all of the color combinations that are available
       with RGB.  It is controlling 3 pins that have transistors attached to them
       with an RGB color strip atteched to them.

 
   From: Mike Myers (http://mikemyers.me)  @netnutmike
       Let's Make It Episode 44 (http://letmakeit.tv)
       
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

const int redPin =  2;
const int greenPin =  3;
const int bluePin =  4;


void setup() {
  // set the digital pin as output:
  pinMode(redPin, OUTPUT);   
  pinMode(greenPin, OUTPUT); 
  pinMode(bluePin, OUTPUT); 
}

void loop()
{
  int l1, l2;
  
  for (l1=0; l1<=255; l1=l1+5) {
    analogWrite(greenPin, l1);
    
    for(l2=0; l2<=255; ++l2) {
      analogWrite(redPin, l2);
      delay(10);
    }
    
    for(l2=0; l2<=255; ++l2) {
      analogWrite(bluePin, l2);
      delay(10);
    }
    
    for(l2=255; l2>=0; --l2) {
      analogWrite(redPin, l2);
      delay(10);
    }
    
    for(l2=255; l2>=0; --l2) {
      analogWrite(bluePin, l2);
      delay(10);
    }
    
    for(l2=0; l2<=255; ++l2) {
      analogWrite(bluePin, l2);
      analogWrite(redPin, l2);
      delay(10);
    }
    
    for(l2=255; l2>=0; --l2) {
      analogWrite(redPin, l2);
      analogWrite(bluePin, l2);
      delay(10);
    }
    
    delay(1000);
  }
}

