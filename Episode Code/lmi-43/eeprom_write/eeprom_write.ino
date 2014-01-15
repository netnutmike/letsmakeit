/*
 * EEPROM Write
 *
 * Stores values read from analog input 0 into the EEPROM.
 * These values will stay in the EEPROM when the board is
 * turned off and may be retrieved later by another sketch.
 */

#include <EEPROM.h>

// the current address in the EEPROM (i.e. which byte
// we're going to write to next)
int addr = 0;

void setup()
{
  writeEEprom();
}

void loop()
{
  
}

void writeEEprom()
{
  EEPROM.write(0, 'L');
  EEPROM.write(1, 'e');
  EEPROM.write(2, 't');
  EEPROM.write(3, 's');
  EEPROM.write(4, ' ');
  EEPROM.write(5, 'M');
  EEPROM.write(6, 'a');
  EEPROM.write(7, 'k');
  EEPROM.write(8, 'e');
  EEPROM.write(9, ' ');
  EEPROM.write(10, 'I');
  EEPROM.write(11, 't');
  EEPROM.write(12, '!');
}
