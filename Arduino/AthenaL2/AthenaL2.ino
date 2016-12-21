/*
ATHENA CODE EXAMPLE LED FADDING
 */

int Setting0 = 9;
int Setting1 = 10;
int Setting2 = 11;
int Setting3 = 6;


void setup()  { 
  // initialize serial communications:
  Serial.begin(9600);
  pinMode(4,OUTPUT);
} 



void loop()  { 
  String stringOne = "";  
  int SerialA = 0;
  int VminLED0 = 0;
  int VmxLED0 = 50;
  int VminLED1 = 10;
  int VmxLED1 = 60;
  int VminLED2 = 20;
  int VmxLED2 = 70;
  int VminLED3 = 30;
  int VmxLED3 = 100;
  int LED0 = 0;
  int LED1 = 0;
  int LED2 = 0;
  int LED3 = 0;
  int Pot = 0;
  digitalWrite(4,HIGH);
  // Animacao de 0 a 100% da barra
//  for(int fadeValue = 0 ; fadeValue <= 100; fadeValue +=1) { 
  int fadeValue = 0;
  fadeValue = analogRead(0);
  fadeValue = Pot2Percent(fadeValue);
  if (fadeValue<= VminLED0) { LED0 = 0;}
  else {
    if (fadeValue>= VmxLED0) { LED0 = 255;}
    else { 
     LED0 = CalculateLEDBrightness(fadeValue,VminLED0,VmxLED0);
     Serial.println(LED0);
}
  if (fadeValue<= VminLED1) { LED1 = 0;}
  else {
    if (fadeValue>= VmxLED1) { LED1 = 255;}
    else { LED1 = CalculateLEDBrightness(fadeValue,VminLED1,VmxLED1);}}
 if (fadeValue<= VminLED2) { LED2 = 0;}
  else {
    if (fadeValue>= VmxLED2) { LED2 = 255;}
    else { LED2 = CalculateLEDBrightness(fadeValue,VminLED2,VmxLED2);}}
 if (fadeValue<= VminLED3) { LED3 = 0;}
  else {
    if (fadeValue>= VmxLED3) { LED3 = 255;}
    else { LED3 = CalculateLEDBrightness(fadeValue,VminLED3,VmxLED3);}}

    analogWrite(Setting0,LED0);    
    analogWrite(Setting1,LED1);    
    analogWrite(Setting2,LED2);    
    analogWrite(Setting3,LED3);       
    delay(10); 

  }

//}
//  analogWrite(Setting0,0);
//  analogWrite(Setting1,0);
//  analogWrite(Setting2,0);
//  analogWrite(Setting3,0);
//  delay(1000);     
//  Serial.println(fadeValue);
  }  

  
  
  
int CalculateLEDBrightness(int X, int Vmin, int Vmx) {
//  int Ytotal = ((X-Vmin)/(Vmx-Vmin))*255;
  int Y1 = (X-Vmin);
  int Y2 = (Vmx-Vmin);
  float Y3 = ((float)Y1/(float)Y2)*255;
  return Y3;
}
  
int Pot2Percent(int Potentiometer) {
  int Ys1 = (Potentiometer);
  int Ys2 = 1023;
  float Ys3 = ((float)Ys1/(float)Ys2)*255;
  return Ys3;
}

