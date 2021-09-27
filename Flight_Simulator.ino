#include <LiquidCrystal.h>
/*      Interface Control
 * ========= Analog Pins =========         
 * pin A0 - Potentionmeter Input       
 * pin A1 - Joystick Input VRx       
 * pin A2 - Joystick Input VRy       
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

// LCD Pins 
#define lcd_rs 22
#define lcd_e  23
#define lcd_d4 24
#define lcd_d5 25
#define lcd_d6 26
#define lcd_d7 27

// Pot Input pin
#define throttle_in A0

// Rotary Encoder Pins
#define rotEnc_dt 2
#define rotEnc_clk 3

// Joy Stick Pins
#define js_vrx A1
#define js_vry A2
#define js_sw  4

// Digital Output
#define status_light 12


// Object Declarations 
LiquidCrystal lcd ( lcd_rs, lcd_e, lcd_d4, lcd_d5, lcd_d6, lcd_d7 );

void setup() {
  // set up the LCD's number of columns and rows:
   Serial.begin( 9600 );
  lcd.begin( 16, 2 );
  pinMode( js_vrx, INPUT );
  pinMode( js_vry, INPUT );
  pinMode( js_sw , INPUT );
  pinMode( rotEnc_dt, INPUT );
  pinMode( rotEnc_clk, INPUT );
 
}

void loop() {
 
  lcd.setCursor( 0, 1 );
  // print the number of seconds since reset:
  lcd.print( millis() / 1000 );

  input_test();
}


int32_t input_test () {
    // Create local variables and test validity of input data. 

    
    Serial.print ( "Analog Input Pot : " ) ;
    Serial.print ( analogRead( throttle_in ) ) ;
    Serial.print( "    Joystick X :" ) ;
    Serial.print ( analogRead ( js_vrx ) ) ;
 
    Serial.print( "    Joystick Y :" ) ;
    Serial.print ( analogRead ( js_vry ) ) ;
    Serial.print( "    Joystick SW :" ) ;
    Serial.print ( digitalRead ( js_sw ) ) ;
        Serial.print ( "\n " );
    return 0;
}
