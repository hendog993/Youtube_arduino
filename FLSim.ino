#include <LiquidCrystal.h>



// ================= LCD Pins =================
const short int lcd_rs =  52;  
const short int lcd_e  =  53;
const short int lcd_d4 =  48;
const short int lcd_d5 =  49;
const short int lcd_d6 =  50;
const short int lcd_d7 =  51;

// ================= Yoke/Joystick Pins =================
const short int yk_vrx = A2;
const short int yk_vry = A3;
const short int yk_sw = 7;

// ================ Throttle Pot ================
const short int throttle = A0;

// =============== second potentiometer ===========
const short int lcd_selector = A1; 

// =============== Object declarations =================
LiquidCrystal lcd(lcd_rs, lcd_e, lcd_d4, lcd_d5, lcd_d6, lcd_d7);

// Data Structures
struct {
    int FROZEN_THROTTLE;
    float FROZEN_YOKE_X;
    float FROZEN_YOKE_Y;
    int FROZEN_YOKE_CLICK;
} FLIGHT_INPUTS;


struct {
  int airspeed;
  int pitch;
  int roll;
  int yaw;
  int altitude;
  int ias;
  int oat;
  int iat;
} FLIGHT_DATA;

int lcd_selection;
 

// LCD Information 
void potentiometer_converter(int value) {
lcd.clear();
    if (value < 50) {
      lcd.print("Throttle: ");
      lcd.setCursor(0,1);
      lcd.print(FLIGHT_INPUTS.FROZEN_THROTTLE);
    }
    else if (value < 300) {
      lcd.print("YOKE X: ");
      lcd.setCursor(0,1);
      lcd.print(FLIGHT_INPUTS.FROZEN_YOKE_X);
    }
    else if (value < 600) {
      lcd.print("YOKE Y: ");
      lcd.setCursor(0,1);
      lcd.print(FLIGHT_INPUTS.FROZEN_YOKE_Y);
    }
    else if (value < 800) {
      lcd.print("Case 4");
    }
    else if (value < 1000) {
      lcd.print("Case 5");
    }
}



void store_frozen() {
FLIGHT_INPUTS.FROZEN_THROTTLE = analogRead(throttle);
    FLIGHT_INPUTS.FROZEN_YOKE_X = analogRead(yk_vrx);
    FLIGHT_INPUTS.FROZEN_YOKE_Y = analogRead(yk_vry);
}

 
void setup() {
    lcd.begin(16,2);
    pinMode (throttle, INPUT);
    pinMode(yk_vrx, INPUT);
    pinMode(yk_vry, INPUT);
    pinMode(yk_sw, INPUT);
    pinMode(lcd_selector, INPUT);
    Serial.begin(9600);
}


void loop() {
    lcd.setCursor(0,0);
    store_frozen();
    potentiometer_converter(analogRead(A1));   
    Serial.println(analogRead(yk_vrx));
    delay(100);
}
