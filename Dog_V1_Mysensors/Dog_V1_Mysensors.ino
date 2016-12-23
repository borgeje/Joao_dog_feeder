/**
 *******************************
 *
 * REVISION HISTORY
 * Version 1.0 - Joao E Borges
 * 
 * DESCRIPTION
 *    DOG FEEDER system, using mysensors as the connectivity method. A servo motor
 *    is connected to arduino Pin 8 and controls the food dispensing. 
 *    
 ********************
 *
 *     The MySensors Arduino library handles the wireless radio link and protocol
 * between your home built sensors/actuators and HA controller of choice.
 * The sensors forms a self healing radio network with optional repeaters. Each
 * repeater and gateway builds a routing tables in EEPROM which keeps track of the
 * network topology allowing messages to be routed to nodes.
 * Copyright (C) 2013-2015 Sensnology AB
 * Full contributor list: https://github.com/mysensors/Arduino/graphs/contributors
 * Documentation: http://www.mysensors.org
 * Support Forum: http://forum.mysensors.org
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation.
************************************************************
 */ 

// Basic Configuration - alwyas keep
#define MY_DEBUG                  // Enable debug prints to serial monitor
#define MY_RADIO_NRF24            // Enable and select radio type attached
#define MY_REPEATER_FEATURE       // Enabled repeater feature for this node

//Libraries, some are project specific
#include <SPI.h>
#include <MySensors.h>
#include <Bounce2.h>
#include <Servo.h> 
#include <DHT.h>                  // library for temp and humidity sensor
//#include <SimpleTimer.h>          // library for a simple timer 

// Project Configuration, pins and other defines
#define LED_PIN  6                 // Arduino Digital I/O pin number for relay 
#define BUTTON_PIN  2              // Arduino Digital I/O pin number for button 
#define CHILD_ID_Servo 1           // Id of the sensor child
#define CHILD_ID_TEMP 2             // iD for temperature reporting
#define CHILD_ID_HUM 3
#define ON 1
#define OFF 0
#define SERVO_DIGITAL_PIN 8
#define DETACH_DELAY 900          // Tune this to let your movement finish before detaching the servo
#define DHT_DATA_PIN 3            // Set this to the pin you connected the DHT's data pin to
#define SENSOR_TEMP_OFFSET 0      // Set this offset if the sensor has a permanent small offset to the real temperatures

// Some additional definitons and INSTANCES creation
MyMessage msgServo(CHILD_ID_Servo,V_LIGHT);
MyMessage msgTemp(CHILD_ID_TEMP, V_TEMP);
MyMessage msgHum(CHILD_ID_HUM, V_HUM);
//SimpleTimer Timer1;               // Creating instance of TIMER 
Servo Servo_Dispenser;            // create servo object to control a servo   
Bounce Local_dispense_button = Bounce();  // create instance of debounced button
DHT dht;                          // Creating instance of DHT

//VARIABLES
int oldValue=0;
int a = 0;                        //intermediate variable for servo backandforth math // Servo moves around 90                       
// Sleep time between sensor updates (in milliseconds) // Must be >1000ms for DHT22 and >2000ms for DHT11
static const uint64_t UPDATE_INTERVAL = 30000;
// Force sending an update of the temperature after n sensor reads
// i.e. the sensor would force sending an update every UPDATE_INTERVAL*FORCE_UPDATE_N_READS [ms]
static const uint8_t FORCE_UPDATE_N_READS = 10;
float lastTemp;                   // variable to hold last read temperature
float lastHum;                    // variable to hold last read humidity
uint8_t nNoUpdatesTemp;           // keeping track of # of reqdings 
uint8_t nNoUpdatesHum;
bool metric = true;               // metric or imperial?







void setup()  
{  
  pinMode(BUTTON_PIN,INPUT);                 // Setup the button
  digitalWrite(BUTTON_PIN,HIGH);             // Activate internal pull-up
  Local_dispense_button.attach(BUTTON_PIN);  // After setting up the button, setup debouncer
  Local_dispense_button.interval(5);
  digitalWrite(LED_PIN, OFF);               // Make sure LED is off at startup
  pinMode(LED_PIN, OUTPUT);                 // Then set LED pins in output mode

 // NOT USED CODE - Set relay to last known state (using eeprom storage) 
 // state = loadState(CHILD_ID_Servo);
 // digitalWrite(LED_PIN, state?RELAY_ON:RELAY_OFF);

  Servo_Dispenser.attach(SERVO_DIGITAL_PIN);  // attaches the servo on pin  to the servo object 
  Servo_Dispenser.detach();
  dht.setup(DHT_DATA_PIN); // set data pin of DHT sensos
  wait(1000);
//  Timer1.setInterval(UPDATE_INTERVAL,ReadTemp_n_Humidity);
  sleep(5000);            // Give DHT sensor some time to setup
}







void presentation()  
{
  sendSketchInfo("Joao_Feeder", "1.0");   // Send the sketch version information to the gateway and Controller
  present(CHILD_ID_Servo, S_BINARY);      // Register all sensors to gw (they will be created as child devices)
  present(CHILD_ID_TEMP, S_TEMP);         // Registar Temperature to gw
  present(CHILD_ID_HUM, S_HUM);           // Register Humidity to gw
  metric = getConfig().isMetric;          // get configuration from the controller on UNIT system
}




/*
*  Example on how to asynchronously check for new messages from gw
*/
void loop() 
{
//  Timer1.run();
  Local_dispense_button.update();
  int value = Local_dispense_button.read();   //Get the update value
  if (value != oldValue && value==0) {
     send(msgServo.set(value?false:true), true); // Send new state and request ack back
    }
  oldValue = value;

  ReadTemp_n_Humidity();
  
  wait(500);
//  sleep(UPDATE_INTERVAL);  // Sleep for a while to save energy
  sleep(BUTTON_PIN, CHANGE, UPDATE_INTERVAL);

} 
 

