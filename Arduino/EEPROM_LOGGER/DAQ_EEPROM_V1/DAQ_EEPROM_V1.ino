/*
DAQ_EEPROM
Descricao: rograma para Leitura de um canal ANALOGICO e gravar na EEPROM.
O intervalo de leitura do canal analogico eh determinado pela variaval DAQ_TIME, e o canal lido eh o ANALOG 0

Autor: Joao E Borges
Data Ult Modificacao: 9-mai-2014

*/


#include <EEPROM.h>

int addr = 0;                   // the current address in the EEPROM we're going to write to
int sensor_pin = 0;             // the analog pin for temp sensor
int sensor_reading = 0.0;       // variable to store the value coming from the sensor
float vref = 4.85;              // variable to store the voltage reference used
                                // using a separate thermometer tweak vref value to fine tune the displayed temperature

int fahrenheit = 0;                                 
int centigrade = 0;             // variable to store the centigrade temperature
int acquisition_timer = 500;   // variable to control the time between updates (in ms)
                                // 300000 = 5 min intervals
int loop_counter = 0;
int bytemax = 1024;             // adjust this value for your eeprom memory limit
                                // there are 1024 bytes in the ATmega328 EEPROM
                                // 512 bytes on the ATmega168 and ATmega8
                                // 4 KB (4096 bytes) on the ATmega1280 and ATmega2560

void setup() {
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  pinMode(sensor_pin, INPUT );    // set LM34 temp sensor pin as an input
  analogReference(DEFAULT);        // set the analog reference to the 5V internal reference
  delay(1000);
}

void loop() {
  
  delay(1000);

  Serial.println("APLICACAO DE OPEX - LEITURA SENSOR para TEMPERATURA PU ");
  READEE(); 
  
  int sensor_reading = analogRead(sensor_pin);               // stores the digitized (0 - 1023) analog reading from the LM34
  float fahrenheit = (100.0 * sensor_reading * vref)/1023;   // calculates the actual fahrenheit temperature
  float centigrade = ((fahrenheit-32)/1.8);                  //conversion to degrees C

   
 // if the eeprom is not full 
   if (loop_counter <= bytemax) {
   
 // divide by 4 because analog inputs range from 0 to 1023 and
 // each byte of the EEPROM can only hold a value from 0 to 255.
   int val = sensor_reading / 4;

 // write the value to the appropriate byte of the EEPROM.
 // these values will remain there when the board is turned off.
   EEPROM.write(addr, val);

 // advance to the next address.
 // there are 1024 bytes in the ATmega328 EEPROM
 // 512 bytes on the ATmega168 and ATmega8, 4 KB (4096 bytes) on the ATmega1280 and ATmega2560
  addr = addr + 1;
  delay (acquisition_timer);
  }
  
    else {
    
    }
    loop_counter++;


}




void READEE()
{
}


void Check_EEPROM()
{
  int zz = EEPROM.read(0);
  if (zz == 100) {
    EEPROM.write(0, 135);    // If 100 is written in position 0, erase it, and proceed with DAQ, not data retrieval
    digitalWrite(13, HIGH);  //LED ON means DAQ will be activated
  }
    else {
      
    }
  }
