/*
 * EEPROM Read
 *
 * Reads the value of each byte of the EEPROM and prints it 
 * to the computer.
 * This example code is in the public domain.
 */

#include <EEPROM.h>

// start reading from the first byte (address 0) of the EEPROM
int address = 0;
byte value;

void setup()
{
  // initialize serial and wait for port to open:
  Serial.begin(9600);
}

void loop()
{
  // read a byte from the current address of the EEPROM
  for (address=0; address <= 25; ++address) {
    Serial.write(EEPROM.read(address));
    Serial.print(", ");
  }

  Serial.println();
  Serial.println();
    
  delay(1000);
}
