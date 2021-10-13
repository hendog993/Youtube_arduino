#include <Arduino.h>
#include <stdint.h>



/*      Interface Control
     ========= Analog Pins =========
     pin A0 - Potentionmeter Input
     pin A1 - Joystick Input VRx
     pin A2 - Joystick Input VRy
  
     ========= Digital Pins =========
     pin  2 - Rotary Encoder DT      !! Interrupt Driven Pin
     pin  3 - Rotary Encoder CLK     !! Interrupt Driven Pin
     pin  4 - Joy Stick SW
     pin  5 - Crash status 
     pin  6 - Grounded/airborne status 
     ping 7 - Stall Warning 
   
     pin 11 - Rotary Encoder SW
     pin 12 - Status Light
     pin 22 - LCD RS
     pin 23 - LCD E
     pin 24 - LCD D4
     pin 25 - LCD D5
     pin 26 - LCD D6
     pin 27 - LCD D7
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

// Rotary Encoder Pins - all pins are interrupt capable 
#define rotEnc_dt 2
#define rotEnc_clk 3
#define rotEnc_sw 18 

// Joy Stick Pins
#define js_vrx A1
#define js_vry A2
#define js_sw  4

// Digital Output
#define clock_status_out 12
#define crash_status_out 5 
#define airborne_status_out 6
#define stall_warning_out 7 
#define landing_gear_out 




// Digital Inputs 
#define landing_gear_up 0
 

// =================== END PIN DECLARATIONS ====================
