/*                                FLIGHT SIMULATOR PROJECT
 *                        Authors : Henry Gilbert and Kolby Baas
 *                        Date    : 10/1/2021
 *                        
 * 
 * 
 *  
 * 
 *                                  |
                                    |
                                    |
                                  .-'-.
                                 ' ___ '
                       ---------'  .-.  '---------
       _________________________'  '-'  '_________________________
        ''''''-|---|--/    \==][^',_m_,'^][==/    \--|---|-''''''
                      \    /  ||/   H   \||  \    /
                       '--'   OO   O|O   OO   '--'
 * 
 * 
 * 
 * 
 */



// TODO figure out what rotary encoder will do. Right now it has no real purpose. - can be input for lat, lon, heading, etc. 
// TODO figure out what aircraft criteria to add - stall, going too fast, etc. 
// TODO major software config - transmit serial data to instrument panel bus to Arduino NANO, which controlls stepper motors for instruments. 
// TODO instrument design - proof of concept. 
// TODO - figure out crash criteria. 
// TODO build Kolby a circuit so he can test things . 


#include <LiquidCrystal.h>


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
#define clock_status 12
#define crash_status 5 
#define grounded_status 6

// =================== END PIN DECLARATIONS ====================



// =================== OBJECT  DECLARATIONS ====================
LiquidCrystal lcd ( lcd_rs, lcd_e, lcd_d4, lcd_d5, lcd_d6, lcd_d7 );


// =================== END OBJECT  DECLARATIONS ====================


// =================== STRUCT  DECLARATIONS ====================

typedef struct Frozen_Data_t {
    // Analog Data
    uint16_t yoke_x ;
    uint16_t yoke_y ;
    uint16_t analog_pot ;
    bool     stick_switch ; // joystick switch

} Frozen_Data;

Frozen_Data flsim_inputs ;

typedef struct Thawed_Data_t {
    // TODO figure out these uits/types, what do they need to be in.
    // TODO should we include here things like grounded, landing gear down, etc. Maybe make that a separate struct. 
    float ground_speed ;          // knots - 
    float true_airspeed ; 
    float altitude ;          // feet 
    float pitch ;             // degrees
    float roll ;              // degrees
    float yaw ;               // degrees
    float heading ;           // degrees
    float rate_of_climb ;     // feet per second 
} Thawed_Data ;

Thawed_Data flight_status ;

typedef struct Aircraft_Situation_t {
    bool isLandingGearDown = false ; 
    bool isGrounded ; 
    uint16_t fuel_level ; 
    float latitude ; 
    float longitude ; 
    float oat ; 
    float tat ; 
} Aircraft_Situation ; 

Aircraft_Situation aircraft_situation ; 
// TODO maybe consider a naming convention to avoid confusion with these names. They aren't exactly unambigious. 

// =================== END STRUCT DECLARATIONS ====================




// =================== GLOBAL VARS DECLARATIONS ====================

// TODO These are based off random google searches for a Cessna 172 . Let's follow a formal plane model when we get a chance. 
int32_t count ; // Rotary Encoder Count. 
#define MAX_AIRSPEED 176      // knots
#define MAX_PITCH_DELTA 2     // degrees per second 
#define MAX_ROLL_DELTA  3     // degrees per second
#define MAX_RATE_OF_CLIMB 721  // feet per minute 
#define MAX_ALTITUDE    14000  // feet 
#define MAX_ACCELERATION 150   // ft/s2



// =================== END GLOBAL VARS DECLARATIONS ====================


// =================== FUNCTION DECLARATIONS ====================
/*
  function: service_frozen_data ()
  inputs : pointer to frozen struct
  return : status for success -
    uint16_t yoke_x ;
    uint16_t yoke_y ;
    uint16_t analog_pot ;
*/

int32_t service_frozen_data ( Frozen_Data * frozenPtr )

{
    int32_t s32_returnval = 0x0004;  // Automatic failure condition, return  val for bad data.
   
    // Read input values
    uint16_t x_val = analogRead ( js_vrx ) ;
    uint16_t y_val = analogRead ( js_vry ) ;
    uint16_t thr_val = analogRead ( throttle_in ) ;
    bool sw_val = digitalRead ( js_sw ) ;
  
    if (  ( x_val < 0 ||  x_val > 1024 )  ||      // Joystick X axis failure condition. Can't be outside of 0-1024.
          ( y_val < 0 ||  y_val > 1024 )  ||      // Joystick Y axis failure condition. Can't be outside of 0-1024.
          ( thr_val < 0 ||  thr_val > 1024 ) ||   // Pot axis failure condition. Can't be outside of 0-1024.
          ( (sw_val < 0 ) || (sw_val > 1 ) )      // Switch failure condition - can't be anything not zero or one.
       )
    {
      return s32_returnval ; // Invalid input values - exit function.
    }
  
    s32_returnval = 1 ; // Success
  
    // Store values into pointer struct .
    frozenPtr->yoke_x = x_val ;
    frozenPtr->yoke_y = y_val ;
    frozenPtr->analog_pot = thr_val ;
    frozenPtr->stick_switch = sw_val ;
  
    return s32_returnval ;
}

/* function - thaw_data
   input - frozen data pointer, thawed data pointer
   return - success or fail code 0x0003
   Description - calls each subfunction for portion of thawed data that must be serviced and stores values in struct. 
   Heirarchy of Data - acceleration comes first, then pitch, roll, TODO verify this with governing equations . 
   
*/

// TODO add criteria for crash - crash resets all simulation and asserts red LED status light
// TODO add stall criteria 
// TODO add wind  criteria 
// TODO rotary encoder - add input for wind vector calculation to add criteria for adjusted airspeed - engine speed derivative ? 

int32_t thaw_data ( Frozen_Data * frozenPtr ,
                    Thawed_Data * thawedPtr )

{
    int32_t s32_returnval = 0x0003 ; // Error code for thawed data function
  
    if ( ( frozenPtr == NULL ) ||
         ( thawedPtr == NULL ) )
    {
      return s32_returnval ;
    }
  
    // Call sub functions for each successive thawed data point
  
    s32_returnval = 0 ;  // Set intermediate return val for secondary part of function.
  
    s32_returnval &= thaw_true_airspeed ( frozenPtr , thawedPtr ) ;
    //s32_returnval &= thaw_groundspeed ( frozenPtr , thawedPtr ) ;
   // s32_returnval &= thaw_pitch ( frozenPtr ) ;
   // s32_returnval &= thaw_roll ( frozenPtr ) ;
   // s32_returnval &= thaw_altitude ( frozenPtr ) ;
    //s32_returnval &= thaw_heading ( frozenPtr ) ;
   // s32_returnval &= thaw_yaw ( frozenPtr ) ;
  
    return s32_returnval ;
}









/* function - thaw_true_airpseed 
   input -  pointer to frozen data , pointer to thawed data. 
   return - success/error code 
   Description - calculates the new airspeed based on throttle input. Since there is always a constant decelleration, 
                 the formula for airspeed is : 
                 V = airspeed
                 T = period = 50ms (config data)
                 D = Decelleration - constant (think of cars, as they are rolling there is a constant applied decelleration. 
                                     A car will stop moving if you quit applying acceleration
                 P = potentiometer value - 0-1024
                 A = alpha coefficient for converting pot value into standard offset 
                 Vnew = Vold + T(AP-D)     OR dV = T(AP-D) . 
                 The max change in velocity should be 10 knots per second (this must be fine tuned). This is per SECOND.
                 Per calculation, aka per 50 ms, dV max = 10/20 = 0.5. D=5/20 = .25
                        .5 = (A*P-.25). 
                        .75 = A*P. At max accel, P = 1024. So A, the offset value, equals 0.00073. 
                 At max throttle, dV = +10 kts/second
                 At min throttle, dV = -5  kts/second 
                 
*/

int32_t thaw_true_airspeed (Frozen_Data * frozenPtr,  Thawed_Data * thawedPtr )
{
    int32_t s32_returnval = 0x0005 ; // Error code for thaw airspeed function

    if (  ( frozenPtr == NULL ) ||
          ( thawedPtr == NULL ) ) 
    {
        return s32_returnval ; // Error - can't have null pointers. TODO necessary because of initial check ? TODO 
    }

    // TODO make these global variables? Are they going to be used elsewhere? 
    float old_airspeed = thawedPtr->true_airspeed;
    float A = 0.00073f;
    float D = .25f;
    
    thawedPtr->true_airspeed = old_airspeed + (A * frozenPtr->analog_pot - D);   // TODO update this. I don't like adding things directly to a struct if the values aren't right initially 

    // Limit the airspeed between the min 0 and the max 176. 
    if ( thawedPtr->true_airspeed  > MAX_AIRSPEED ) thawedPtr->true_airspeed  = MAX_AIRSPEED ; 
    if ( thawedPtr->true_airspeed  < 0 ) thawedPtr->true_airspeed  = 0 ; 

    s32_returnval = 0; // Exit success 
    
    return s32_returnval ;
}










/* function - thaw_groundspeed 
   input - frozen Pointer and thawed Pointer 
   return - exit success or failure 
   Description - calculates groundspeed as a function of airspeed 
*/

int32_t thaw_groundspeed ( Frozen_Data * frozenPtr,  Thawed_Data * thawedPtr ) 

{
    if (  ( frozenPtr == NULL ) ||
          ( thawedPtr == NULL ) ) 
    {
        return s32_returnval ; // Error - can't have null pointers. TODO necessary because of initial check ? TODO 
    }

    


    s32_returnval = 0; // Exit success 
    
    return s32_returnval ;
}



/* function - 
   input - 
   return - 
   Description - 
*/

int32_t thaw_pitch ( Thawed_Data * thawedPtr )
{
    int32_t s32_returnval = 0x0006 ; // Error code for thaw pitch function
    return s32_returnval ;
}

/* function - 
   input - 
   return - 
   Description - 
*/

int32_t thaw_roll ( Thawed_Data * thawedPtr )
{
    int32_t s32_returnval = 0x0007 ; // Error code for thaw roll function
    return s32_returnval ;
}


/* function - 
   input - 
   return - 
   Description - 
*/

int32_t thaw_altitude ( Thawed_Data * thawedPtr )
{
    int32_t s32_returnval = 0x0008 ; // Error code for thaw altitude function
    return s32_returnval ;
}

/* function - 
   input - 
   return - 
   Description - 
*/

int32_t thaw_heading ( Thawed_Data * thawedPtr )
{
    int32_t s32_returnval = 0x0009 ; // Error code for thaw heading function
    return s32_returnval ;
}


/* function - 
   input - 
   return - 
   Description - 
*/

int32_t thaw_yaw ( Thawed_Data * thawedPtr )
{
    int32_t s32_returnval = 0x000A ; // Error code for thaw altitude function
    return s32_returnval ;
}

/*
   function - service_rotary_encoder
   input -
*/


int32_t service_rotary_encoder ( int32_t * counter  ) {
    
}

// ==================== END FUNCTION DECLARATIONS ==================







// ==================== DEBUG FUNCTIONS ======================

/*
*   Function : read_frozen_struct 
*   Description : debug function - prints data 
*/
int32_t read_frozen_struct ( Frozen_Data * frozenPtr ) {
    Serial.print ( "Yoke X: ") ;
    Serial.print ( frozenPtr->yoke_x ) ;
    Serial.print ( "    Yoke Y: ") ;
    Serial.print ( frozenPtr->yoke_y ) ;
    Serial.print ( "    Throttle In : ") ;
    Serial.print ( frozenPtr->analog_pot ) ;
    Serial.print ( "\n ") ;
}

void print_raw_inputs () {

    // Print the analog input potentiometer/throttle value
    Serial.print ( "Analog Input Pot : " ) ;
    Serial.print ( analogRead( throttle_in ) ) ;
  
    // Print the x input of the joy stick
    Serial.print( "    Joystick X :" ) ;
    Serial.print ( analogRead ( js_vrx ) ) ;
  
    // Print the y input of the joy stick
    Serial.print( "    Joystick Y :" ) ;
    Serial.print ( analogRead ( js_vry ) ) ;
  
    // Print the switch value of the joy stick
    Serial.print( "    Joystick SW :" ) ;
    Serial.print ( digitalRead ( js_sw ) ) ;
  
    // Rotary Encoder Inputs
    Serial.print ( "   Rotary CLK:  " ) ;
    Serial.print ( digitalRead ( rotEnc_clk ) ) ;
  
    Serial.print ( "   Rotary DT:   " ) ;
    Serial.print ( digitalRead ( rotEnc_dt ) ) ;
  
    Serial.print ( "\n " );

}
// ==================== END DEBUG FUNCTIONS ======================









// =================== MAIN FUNCTIONS  ====================


// Timer Variables // 
unsigned long startMillis;  //some global variables available anywhere in the program
unsigned long currentMillis;
const unsigned long period = 50;  //the value is a number of milliseconds
int32_t error_code ; 

void setup() {
    // set up the LCD's number of columns and rows:
    Serial.begin( 9600 );
    lcd.begin( 16, 2 );

    // Joy stick inputs 
    pinMode( js_vrx, INPUT );
    pinMode( js_vry, INPUT );
    pinMode( js_sw , INPUT );
    pinMode (13, OUTPUT ) ;
    
    // Rotary Encoder inputs 
    pinMode( rotEnc_dt, INPUT_PULLUP );
    pinMode( rotEnc_clk, INPUT_PULLUP );
    pinMode ( rotEnc_sw, INPUT_PULLUP ) ;

    // Rotary Encoder interrupt routines
    attachInterrupt( digitalPinToInterrupt( rotEnc_dt ) , service_rotary_encoder , CHANGE );
    attachInterrupt( digitalPinToInterrupt( rotEnc_clk ) , service_rotary_encoder , CHANGE );
    
    pinMode( clock_status, OUTPUT );
 
    startMillis = millis();
}

int counter = 0;

void loop() {

    currentMillis = millis();  //get the current "time" (actually the number of milliseconds since the program started)
    if ( currentMillis - startMillis >= period )  //test whether the period has elapsed
    
    {
        lcd.setCursor(0,0);
        // ================= BEGIN MAIN EXECUTION CODE  ====================== 
        digitalWrite(clock_status, !digitalRead(clock_status));  // Display the state of the timer - leave for debug purposes 
        error_code = service_frozen_data ( &flsim_inputs) ;
        read_frozen_struct ( &flsim_inputs ) ;                      // Debug function - not critical to operation 
        thaw_data ( &flsim_inputs , &flight_status) ;
        counter += 1 ;
        lcd.print(counter);
        
    
        // =================   END MAIN EXECUTION CODE ======================
        
        startMillis = currentMillis;  //IMPORTANT to save the start time of the current LED state.
    
    }
  
}


// =================== END MAIN FUNCTIONS  ====================
