// Sweep
// by BARRAGAN <http://barraganstudio.com> 
// This example code is in the public domain.


#include <Servo.h> 
 
Servo myservo;  // create servo object to control a servo 
                // a maximum of eight servo objects can be created 
 
int pos = 0;    // variable to store the servo position 
int madg =100;
int Serv = 70;
String inString = "";   
int buttonPin = A1;
const int ledPin = 13;
const int wemo = 7;
const int servopin = 8;
int a = 0;


 
void setup() 
{ 
  pinMode(buttonPin, INPUT);
  pinMode(wemo, INPUT);
  pinMode(ledPin, OUTPUT);
  myservo.attach(servopin);  // attaches the servo on pin 9 to the servo object 
//  myservo.write(Serv);
//  delay(300);
  myservo.detach();
  Serial.begin(9600);
  delay(1000);
  Serial.println("Dispenser NINA");
  delay(3000);
  Serial.println("GO");
} 
 
 
void loop() 
{ 
  
   while (Serial.available()>0) {
    int inChar = Serial.read();
    if (isDigit(inChar)) { // convert the incoming byte to a char and add it to the string:
      inString += (char)inChar;
    }
    // if you get a newline, print the string,
    // then the string's value:
    if (inChar == '\n') {
      Serial.print("Value:");
      Serial.println(inString.toInt());
     Serial.print("String: ");
     Serial.println(inString);
   // clear the string for new input:
    Serv = inString.toInt();
    inString = "";
    }
 }
  myservo.detach();
  delay(100);
  if (digitalRead(buttonPin)==LOW) {
       myservo.attach(servopin);
       myservo.write(Serv);
       Serial.println("Dispensando Local");
       digitalWrite(ledPin, HIGH);
       delay(2000);
       a = 90-Serv;
       myservo.write(a+90);
       digitalWrite(ledPin, LOW);
       delay(2000);
       myservo.write(90);
   }
 if (digitalRead(wemo)==LOW) {
       Serial.println("Wemo mandou mensagem!");
       delay(500);
       myservo.attach(servopin);
       myservo.write(Serv);
       Serial.println("Dispensando via Internet!");
       digitalWrite(ledPin, HIGH);
       delay(2500);
       a = 90-Serv;
       myservo.write(a+90);
       digitalWrite(ledPin, LOW);
       delay(2000);
       myservo.write(90);
       delay(100);
 }
} 
