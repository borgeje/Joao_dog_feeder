void receive(const MyMessage &message) {
  // We only expect one type of message from controller. But we better check anyway.
  if (message.isAck()) {
     Serial.println("This is an ack from gateway");
  }

  if (message.type == V_LIGHT) {
     state = message.getBool();      // Change relay state
     digitalWrite(RELAY_PIN, state?RELAY_ON:RELAY_OFF);
     saveState(CHILD_ID, state);  // Store state in eeprom
    
     // Write some debug info
     Serial.print("Incoming change for sensor:");
     Serial.print(message.sensor);
     Serial.print(", New status: ");
     Serial.println(message.getBool());
   } 
}
