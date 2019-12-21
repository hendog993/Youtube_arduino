/*  =====================================
   Arduino 1602 LCD Tutorial
   Date: 12-21-2019
   Author: Henry Gilbert
   =====================================
     _______________________________________________________________
    |                   1602 LCD Pin Diagram                        |
    |                                                               |
    |VSS  VDD  VO  RS  RW  E  D0  D1  D2  D3  D4  D5  D6  D7  A  K  |
    |_______________________________________________________________|

    GND: VSS, RW, K
    5V: VDD, V0, A
          "V0" runs through a potentiometer
          "A" uses a 220 Ohm resistor
    Arduino: RS, E D3, D4, D5, D6,


    Must include <LiquidCrystal.h>
    Object constructor:
    LiquidCrystal <objectName> lcd(rs, e, d4, d5, d6, d7)

    Code required in setup:
        lcd.begin(r,c)  --> If using a 16x4

    Methods:

    lcd.clear()
    lcd.setCursor(r, c)
    lcd.print()
*/


#include <LiquidCrystal.h>
int rs = 2;
int e = 3;
int d4 = 4;
int d5 = 5;
int d6 = 6;
int d7 = 7;

LiquidCrystal lcd(rs, e, d4, d5, d6, d7);



void setup(){
lcd.begin(16, 2);
}

int n = 0;

void loop() {
  lcd.setCursor(0,0);
  delay(1000);
  n+= 1;
  lcd.print(n);
}
