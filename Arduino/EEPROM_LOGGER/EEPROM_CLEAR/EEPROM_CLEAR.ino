/*
 * EEPROM Clear
 *
 * Sets all of the bytes of the EEPROM to 0.
 * This example code is in the public domain.

 */

#include <EEPROM.h>

void setup()
{
  // write a 0 to all 1024 bytes of the EEPROM
  // there are 1024 bytes in the ATmega328 EEPROM
  // 512 bytes on the ATmega168 and ATmega8
  // 4 KB (4096 bytes) on the ATmega1280 and ATmega2560
  for (int i = 0; i < 1024; i++)
    EEPROM.write(i, 0);
    
  EEPROM.write(0, 100); // FLAG to know it has been cleared
  // turn the LED on when we're done
  digitalWrite(13, HIGH);
}

void loop()
{
  delay(1000);
}
