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
 *
 * Created by Joao E Borges
 * Copyright (C) 2013-2015 Sensnology AB
 * Full contributor list: https://github.com/mysensors/Arduino/graphs/contributors
 *
 * Documentation: http://www.mysensors.org
 * Support Forum: http://forum.mysensors.org
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation.
 */ 


#define MY_DEBUG // Enable debug prints to serial monitor
#define MY_RADIO_NRF24 // Enable and select radio type attached
#define MY_REPEATER_FEATURE // Enabled repeater feature for this node

#include <SPI.h>
#include <MySensors.h>
#include <Bounce2.h>
#include <Servo.h> 

#define RELAY_PIN  4  // Arduino Digital I/O pin number for relay 
#define BUTTON_PIN  3  // Arduino Digital I/O pin number for button 
#define CHILD_ID 1   // Id of the sensor child
#define RELAY_ON 1
#define RELAY_OFF 0

Servo myservo;  // create servo object to control a servo 
int pos = 0;    // variable to store the servo position 
int madg =100;
int Serv = 70;
String inString = "";   
int buttonPin = A1;
const int ledPin = 13;
const int wemo = 7;
const int servopin = 8;
int a = 0;

Bounce BUTTON = Bounce(); 
int oldValue=0;
bool state;

MyMessage msg(CHILD_ID,V_LIGHT);

void setup()  
{  
  pinMode(BUTTON_PIN,INPUT);        // Setup the button
  digitalWrite(BUTTON_PIN,HIGH);   // Activate internal pull-up
  // After setting up the button, setup debouncer
  BUTTON.attach(BUTTON_PIN);
  BUTTON.interval(5);

  digitalWrite(RELAY_PIN, RELAY_OFF); // Make sure relays are off when starting up
  pinMode(RELAY_PIN, OUTPUT);         // Then set relay pins in output mode

   // Set relay to last known state (using eeprom storage) 
  state = loadState(CHILD_ID);
  digitalWrite(RELAY_PIN, state?RELAY_ON:RELAY_OFF);

  pinMode(buttonPin, INPUT);
  pinMode(wemo, INPUT);
  pinMode(ledPin, OUTPUT);
  myservo.attach(servopin);  // attaches the servo on pin  to the servo object 
  myservo.detach();
  Serial.println("Dispenser NINA");
  delay(3000);
  Serial.println("GO");

}







void presentation()  {
  sendSketchInfo("Relay & Button", "1.0");  // Send the sketch version information to the gateway and Controller
  present(CHILD_ID, S_LIGHT);  // Register all sensors to gw (they will be created as child devices)
}




/*
*  Example on how to asynchronously check for new messages from gw
*/
void loop() 
{
  BUTTON.update();
  int value = BUTTON.read();   //Get the update value
  if (value != oldValue && value==0) {
      send(msg.set(state?false:true), true); // Send new state and request ack back
  }
  oldValue = value;

} 
 

