/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.
 
  This example code is in the public domain.
 */
 
// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
int led = 13;
int k = 0;

// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  pinMode(led, OUTPUT);  
  Serial.begin(9600);  
}

// the loop routine runs over and over again forever:
void loop() {
  digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(10);               // wait for a second
  digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
  delay(10);               // wait for a second
  int X = CalculateLEDBrightness(k,0,100);
  String Str0 = String("k = ");
  String Str1 = String(k);
  String Str2 = String("   ... X = ");
  String Str3 = String(X);
  String StrTotal = String(Str0 + Str1 + Str2 + Str3);
//  Serial.println(StrTotal);
//  Serial.println(k);
  k = k+1;
}


  
int CalculateLEDBrightness(int X, int Vmin, int Vmx) {
  int Y1 = (X-Vmin);
  int Y2 = (Vmx-Vmin);
  float Y3 = ((float)Y1/(float)Y2)*255;
  Serial.println(Y3);
  return Y1;
}
