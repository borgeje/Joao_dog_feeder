/*
  AnalogReadSerial
  Reads an analog input on pin 0, prints the result to the serial monitor.
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.

 This example code is in the public domain.
 */
  long int i=0;
// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  int i = 0;
}

// the loop routine runs over and over again forever:
void loop() {

  // read the input on analog pin 0:
  int sensorValue = analogRead(A0);
  int sensorValue1 = analogRead(A1);
  // print out the value you read:
  Serial.print(i);
  Serial.print(" ");
  Serial.print(sensorValue);
  Serial.print(" ");
  Serial.println(sensorValue1);
  i=i+1;
  delay(1000);        // delay in between reads for stability
}