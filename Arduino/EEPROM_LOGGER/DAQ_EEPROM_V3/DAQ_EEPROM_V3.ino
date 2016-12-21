/*
DAQ_EEPROM
Descricao: rograma para Leitura de um canal ANALOGICO e gravar na EEPROM.
O intervalo de leitura do canal analogico eh determinado pela variaval DAQ_TIME, e o canal lido eh o ANALOG 0
A versao V3 grava em 2bytes cada valor analogico lido, dando mais resolucao, mas ocupando mais memoria

Autor: Joao E Borges
Data Ult Modificacao: 9-mai-2014


// there are 1024 bytes in the ATmega328 EEPROM
 // 512 bytes on the ATmega168 and ATmega8, 4 KB (4096 bytes) on the ATmega1280 and ATmega2560
 
*/


#include <EEPROM.h>

int addr = 1;                   // the current address in the EEPROM we're going to write to
int sensor_pin = 0;             // the analog pin for temp sensor
int sensor_reading = 0.0;       // variable to store the value coming from the sensor
float vref = 5;                // variable to store the voltage reference used
int acquisition_timer = 1000;   // variable to control the time between updates (in ms),300000 = 5 min intervals
int loop_counter = 0;
int bytemax = 1024;             // adjust this value for your eeprom memory limit
boolean flag  = false;
int LED = 13;


/*SETUP ROUTINE */
void setup() {
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW);          //LED OFF INITIALLY
  pinMode(7, OUTPUT);
  digitalWrite(7, HIGH);
  pinMode(sensor_pin, INPUT );    // set temp sensor pin as an input
 // analogReference(DEFAULT);        // set the analog reference to the 5V internal reference
  delay(5000);
  Serial.println("APLICACAO DE OPEX - LEITURA SENSOR para TEMPERATURA PU ");
  //Check_EEPROM();
}




void loop() {
  
//  delay(1000);

        // Se Flag = true, quer dizer que a memoria esta LIMPA, e podemos comecar o DAQ a partir da posicao 01
        // se Flag = false, quer dizer que a memoria nao esta limpa e que deve-se enviar os dados a serial
  if (digitalRead(8)) {
    int sensor_reading = analogRead(sensor_pin);               // stores the digitized (0 - 1023) analog reading
    Serial.println(sensor_reading);
    if (loop_counter <= bytemax) {     // if the eeprom is not full 
  //     int val = sensor_reading / 4;    // divide by 4 to store in one byte (EEPROM)
       int val = highByte(sensor_reading);
       EEPROM.write(addr, val);          // write the value to the appropriate byte of the EEPROM
       addr = addr + 1;
       val = lowByte(sensor_reading);
       EEPROM.write(addr,val);
       EEPROM.write(0,loop_counter);
       addr = addr + 1;                  // advance to the next address.
       delay (acquisition_timer);
  } 
    else {  
      digitalWrite(LED, HIGH);
    }
    loop_counter++;

  }
    else {
      digitalWrite(LED, HIGH);
      Serial.println("INICIO DOS DADOS");
      for (int i = 1; i < 1024; i=i+2) {
           int HB = EEPROM.read(i);
           int LB = EEPROM.read(i+1);
           int TEXT_2_Print = (HB<<8) + LB;
         Serial.println(TEXT_2_Print);
       }
      delay(20000);   }
}








/*
void Check_EEPROM()
{
  int zz = EEPROM.read(0);
  if (zz == 0) {
    EEPROM.write(0, 135);    // If 100 is written in position 0, erase it, and proceed with DAQ, not data retrieval
    digitalWrite(13, HIGH);  //LED ON means DAQ will be activated
    delay(1000);
    flag = true;
  }
    else {
      flag = false;
    }
  }
  */
