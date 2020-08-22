/* Project milestones
 *  7/8 Added airspeed, pitch, and roll validation. All perform within specified limits. 
 *  7/9 Added altitude, rate of climb. 
 *  TODO: NEED to verify 10 calc/second clock and how to improvise. 
 *  TODO: NEED to verify some form of "crash" metric. Currently can have zero altitude and nonzero pitch/roll.
 *        thaw_data sees questionable, need to get more formal idea of validation. 
 * 
 * TODO: Add TAXI mode to change heading when grounded. 
 */

#include <LiquidCrystal.h>
#define MAX_PITCH 12
#define MAX_ROLL 60
#define MAX_AIRSPEED 135
#define KNOTS 6078

// ================= LCD Pins =================
const short int lcd_rs =  52;  
const short int lcd_e  =  53;
const short int lcd_d4 =  48;
const short int lcd_d5 =  49;
const short int lcd_d6 =  50;
const short int lcd_d7 =  51;

// ================= Yoke/Joystick Pins =================
const short int yk_vrx = A3;
const short int yk_vry = A2;
const short int yk_sw  = 7;

// ================ Throttle Pot ================
const short int throttle = A0;

// =============== second potentiometer ===========
const short int lcd_selector = A1; 

// =============== Object declarations =================
LiquidCrystal lcd(lcd_rs, lcd_e, lcd_d4, lcd_d5, lcd_d6, lcd_d7);

// Data Structures
struct {
    int    FROZEN_THROTTLE;
    float  FROZEN_YOKE_X;
    float  FROZEN_YOKE_Y;
    int    FROZEN_YOKE_CLICK;
} FROZEN_FLIGHT_CONTROLS;

struct {
    float altitude = 0;      // feet
    float airspeed = 60;    // knots
    float pitch = 0;       // degrees  || Max is 12, min is -12
    float roll = 0;        // degrees  || Max is 60, min is -60
    float heading = 0;     // Should be programmable, and can change on the ground. 
    float rate_of_climb;   // ft/min    , calculated from airspeed and pitch 
} THAWED_FLIGHT_DATA;

struct {
    bool is_grounded = true;
    bool is_landing_gear_down = true;
    bool has_crashed = false;
    int cabin_pressure;
    //Derived measurements 
    int lat;
    int lon;
    int oat;
} AIRCRAFT_SITUATION;

struct {
    bool landing_gear_down;
    bool power_down;
    bool test_instruments;
    bool hold_heading;
    bool hold_altitude;
    bool hold_airspeed;
} CONTROL_PANEL_IN ;

// =============== INSTRUMENT SECTION 

struct {} ADI;
struct {} ALTIMETER; 
struct {} AIRSPEED; 
struct {} HEADING;

int lcd_selection;
// LCD Information 
void potentiometer_converter(int value) {
    // Converts the potentiometer value into a selection to display on LCD. 
    lcd.clear();
    if (value < 50) {
        lcd.print("Altitude");
        lcd.setCursor(0,1);
        lcd.print(THAWED_FLIGHT_DATA.altitude);
    }
    else if (value < 300) {
        lcd.print("Rate of climb ");
        lcd.setCursor(0,1);
        lcd.print(THAWED_FLIGHT_DATA.rate_of_climb);
    }
    else if (value < 600) {
        lcd.print("AIRSPEED");
        lcd.setCursor(0,1);
        lcd.print(THAWED_FLIGHT_DATA.airspeed);
    }
    else if (value < 800) {
        lcd.print("ROLL");
        lcd.setCursor(0,1);
        lcd.print(THAWED_FLIGHT_DATA.roll);
    }
    else if (value < 1000) {
        lcd.print("PITCH");
        lcd.setCursor(0,1);
        lcd.print(THAWED_FLIGHT_DATA.pitch);
    }
}

float deg2rad(float deg) {
    // Function converting degree measurement to radians
    return deg * 1000/57296;
}

// DATA INPUT INTO FROZEN STRUCTURES 

void store_frozen() {
    FROZEN_FLIGHT_CONTROLS.FROZEN_THROTTLE = analogRead(throttle);    // Throttle input
    FROZEN_FLIGHT_CONTROLS.FROZEN_YOKE_X = analogRead(yk_vrx);        // 
    FROZEN_FLIGHT_CONTROLS.FROZEN_YOKE_Y = analogRead(yk_vry);
}

// DATA Validation, from frozen to thawed
void thaw_flight_data() {
    // Run takeoff criteria function; make sure grounded status can not turn back to true unless landing. 
    if (THAWED_FLIGHT_DATA.airspeed > 70 && FROZEN_FLIGHT_CONTROLS.FROZEN_YOKE_Y < 360 ) AIRCRAFT_SITUATION.is_grounded = false;
    thaw_airspeed();
    thaw_heading();
    // These calculations can ONLY occur if the aircraft is NOT on the ground (in the air).
    if ( AIRCRAFT_SITUATION.is_grounded == false) {
        thaw_pitch();
        thaw_roll();
        thaw_rate_of_climb();
        thaw_altitude();
    }
}

void thaw_airspeed() {
    // Take the potentiometer input and convert into acceleartion.
    // Stores the information in the THAWED data structure to send to
    // data validation. 
    
    // TODO: Clean this up, I don't like it. 
    float acceleration = 800.0;
    THAWED_FLIGHT_DATA.airspeed += (FROZEN_FLIGHT_CONTROLS.FROZEN_THROTTLE)/acceleration - .8;
    if (THAWED_FLIGHT_DATA.airspeed > MAX_AIRSPEED) THAWED_FLIGHT_DATA.airspeed = MAX_AIRSPEED;
    if (THAWED_FLIGHT_DATA.airspeed < 0) THAWED_FLIGHT_DATA.airspeed = 0;
}

void thaw_heading() {
  
}

void thaw_pitch() {
    // On maximum yoke, pitch should change at 2 degrees per second. To modify pitch rate,
    // change the pitch_delta. Currently per calculation, 0.02 degrees can be + or - based on
    // pitch_delta (FRZN-527 * 0.00038) = 0.05, 10 calculations per second gives 0.02 mod/sec. 
     
    // Process: Subtract the frozen data by 528 to zero default position, then multiply 
    //          by pitch_delta for linear conversion of 0.2 degrees per 1/10 second. 
    // Pitch has MAX of 12 degrees, MIN of -12 degrees. 
    
    float updated_pitch;
    const float pitch_delta = -0.00038;
    THAWED_FLIGHT_DATA.pitch += (FROZEN_FLIGHT_CONTROLS.FROZEN_YOKE_Y-527)*pitch_delta;
    if (THAWED_FLIGHT_DATA.pitch > MAX_PITCH ) THAWED_FLIGHT_DATA.pitch = MAX_PITCH;
    if (THAWED_FLIGHT_DATA.pitch < - MAX_PITCH ) THAWED_FLIGHT_DATA.pitch = - MAX_PITCH;
}

void thaw_roll() {
    // On maximum yoke, roll should change at 3 degrees per second. To modify roll rate,
    // change the roll_delta. Currently per calculation, .3 degrees can be + or - based on
    // roll_delta (FRZN -511 * 0.000587 ) = 0.3 , 10 calculations per second gives 3 deg/sec. 
     
    // Process: Subtract the frozen data by 511 to zero default position, then multiply 
    //          by roll_delta for linear conversion of 0.3 degrees per 1/10 second. 
    // ROLL has MAX of 60 degrees, MIN of --60 degrees. 
    
    float updated_roll;
    const float roll_delta = 0.000587;
    
    THAWED_FLIGHT_DATA.roll += (FROZEN_FLIGHT_CONTROLS.FROZEN_YOKE_X-511)*roll_delta;
    if (THAWED_FLIGHT_DATA.roll > MAX_ROLL ) THAWED_FLIGHT_DATA.roll = MAX_ROLL;
    if (THAWED_FLIGHT_DATA.roll < - MAX_ROLL ) THAWED_FLIGHT_DATA.roll = - MAX_ROLL;
}

void thaw_rate_of_climb() {
    // Calculate rate of climb in feet per minute
    // Airspeed -- Knots      , 1 knot = 101.269 ft/min. 
    THAWED_FLIGHT_DATA.rate_of_climb = (THAWED_FLIGHT_DATA.airspeed)*101.269* tan(deg2rad(THAWED_FLIGHT_DATA.pitch));
}

void thaw_altitude() {
    // Take rate of climb, and calculate updated altitude. 
    THAWED_FLIGHT_DATA.altitude += THAWED_FLIGHT_DATA.rate_of_climb / 600 ;
    if (THAWED_FLIGHT_DATA.altitude < 0) THAWED_FLIGHT_DATA.altitude = 0;
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

void serial_test_debug() {
    // Print airspeed, pitch, roll
    Serial.print("Airspeed   ");
    Serial.print(THAWED_FLIGHT_DATA.airspeed);
    Serial.print("     Pitch     ");
    Serial.print(THAWED_FLIGHT_DATA.pitch);
    Serial.print("     Roll  READING    ");
    Serial.print(THAWED_FLIGHT_DATA.roll);
    Serial.print("     Rate of climb      ");
    Serial.print(THAWED_FLIGHT_DATA.rate_of_climb);
    Serial.print("     Altitude    ");
    Serial.print(THAWED_FLIGHT_DATA.altitude);
    Serial.println("");
}

void loop() {
    lcd.setCursor(0,0);
    store_frozen();
    potentiometer_converter(analogRead(A1));   
    thaw_flight_data();
    serial_test_debug();
    delay(100);
}
