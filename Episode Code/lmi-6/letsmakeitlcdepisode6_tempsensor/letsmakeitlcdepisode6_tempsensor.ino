

// include the library code:
#include <LiquidCrystal.h>
#include <dht11.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
dht11 DHT11(12

void setup() {
  DHT11.attach(12);
  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Let's Make It...");
  
  delay(1000);
}

void loop() {
  
  int chk = DHT11.read();
  
  lcd.setCursor(0,1);
  switch (chk)
  {
    case 0: 
      lcd.print("OK             "); 
      break;
    
    case -1: 
      lcd.print("Checksum error"); 
      break;
    
    case -2: 
      lcd.print("Time out error"); 
      break;
    
    default: 
      lcd.print("Unknown error"); 
      break;
  }
  
  lcd.setCursor(0,0);
  lcd.print("Humidity: ");
  lcd.print(DHT11.humidity);
  lcd.print(" %  ");
  
  
  // delay at the end of the full loop:
  delay(4000);
  
  lcd.setCursor(0,0);
  lcd.print("Temp: ");
  lcd.print(DHT11.temperature);
  lcd.print(" (C)    ");
  
  delay(4000);
  
  lcd.setCursor(0,0);
  lcd.print("Temp: ");
  lcd.print(DHT11.fahrenheit());
  lcd.print(" (F)    ");
  
  delay(4000);

}

