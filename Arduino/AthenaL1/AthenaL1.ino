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
} 



void loop()  { 
  String stringOne = "";  
  int SerialA = 0;
  int VminLED0 = 0;
  int VmxLED0 = 100;
  int VminLED1 = 25;
  int VmxLED1 = 50;
  int VminLED2 = 50;
  int VmxLED2 = 75;
  int VminLED3 = 75;
  int VmxLED3 = 100;
  int LED0 = 0;
  int LED1 = 0;
  int LED2 = 0;
  int LED3 = 0;
  // Animacao de 0 a 100% da barra
  for(int fadeValue = 0 ; fadeValue <= 100; fadeValue +=1) { 

  if (fadeValue<= VminLED0) { LED0 = 0;}
  else {
    if (fadeValue>= VmxLED0) { LED0 = 255;}
    else { 
     LED0 = CalculateLEDBrightness(fadeValue,VminLED0,VmxLED0);
}
  Serial.println(LED0);
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
    delay(50); 
//    String Parte1 = String("LED 0 = ");
//    String fadeV = String(fadeValue);
//    String serialAString = String(SerialA);
//    String Parte2 = String(" --  LED 1 = ");
//    stringOne =  String(Parte1 + fadeV + Parte2 + serialAString);
//    Serial.println(stringOne); 
 //   Serial.println(LED0);  
  }}
  analogWrite(Setting0,0);
  analogWrite(Setting1,0);
  analogWrite(Setting2,0);
  analogWrite(Setting3,0);
  delay(2000);                
  }  

  
  
  
int CalculateLEDBrightness(int X, int Vmin, int Vmx) {
  int Ytotal = ((X-Vmin)/(Vmx-Vmin))*255;
  return Ytotal;
}
  


