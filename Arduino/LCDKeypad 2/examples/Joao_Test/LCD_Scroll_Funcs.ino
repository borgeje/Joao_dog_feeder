void ScrollText (int sdelay) {
  String outp;
  int sline=0;
  for (int i=0; i<ScrollTextLength; i++) {
    sline=i;
    lcd.setCursor(0, 0);
    outp=Texto_A_rolar_1[sline];
    lcd.print(outp);
    sline=i+1;
    if (sline>=ScrollTextLength) sline = 0;
    lcd.setCursor(0, 1);
    outp=Texto_A_rolar_1[sline];
    lcd.print(outp);
    delay(sdelay);
  }
}

void Scroll_Left (String outp) {
// int pos=16;
// outp = "Bem Vindo!! ";
 lcd.setCursor(10,0);
 lcd.print("q merda");
 delay(1000);
// Serial.println(pos);
 for (int x = 16; x > -1; x--) {
   delay(50);
   Serial.println(x);
   lcd.setCursor(x,0);
   lcd.print(outp);
   delay(150);
 }
}
