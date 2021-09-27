#include <LiquidCrystal.h>
/*      Interface Control
 * ========= Analog Pins =========         
 * pin A0 - Potentionmeter Input       
 *       
 *       
 * ========= Digital Pins =========      
 * pin  2 - Rotary Encoder DT      !! Interrupt Driven Pin
 * pin  3 - Rotary Encoder CLK     !! Interrupt Driven Pin
 * pin  4 - Joy Stick SW
 * pin 11 - Rotary Encoder SW 
 * pin 12 - Status Light 
 * pin 22 - LCD RS
 * pin 23 - LCD E
 * pin 24 - LCD D4
 * pin 25 - LCD D5
 * pin 26 - LCD D6
 * pin 27 - LCD D7
 */







// =================== PIN DECLARATIONS ====================
/*
 * LCD Pins
 */

#define lcd_rs 22
#define lcd_e  23
#define lcd_d4 24
#define lcd_d5 25
#define lcd_d6 26
#define lcd_d7 27

LiquidCrystal lcd ( lcd_rs, lcd_e, lcd_d4, lcd_d5, lcd_d6,lcd_d7);

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("hello, world!");
}

void loop() {
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);
  // print the number of seconds since reset:
  lcd.print(millis() / 1000);
}
