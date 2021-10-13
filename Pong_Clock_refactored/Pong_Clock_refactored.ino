/*        ARDUINO PONG CLOCK 
 *        Author: Henry Gilbert
 *        Date Created: July 21st 2020
 *        Date refactored: 4 March 2021
 *        Essential Engineering 

 TODO Include validity checks at the beginning of functions. 
 TDOO Add rotary encoder functionality 

3/8 background colors not updating correctly 
 */


#include <FastLED.h>
#define LED_PIN     2       // LED Pin for controlling LED address 
#define NUM_LEDS    128     // Defining the number of addressable LEDs used in the circuit 
#define CLOCK_MODE 6        // Pin definition for the clock mode digital input. 
#define SET_TIME 7          // Pin definition for the set time mode digital input. 
#define PATTERN A0          // Pin definition for the potentiometer/pattern set analog input. 

#define MILLISECONDS_IN_HOUR     3600000
#define MILLISECONDS_IN_DAY      86400000
#define MILLISECONDS_IN_MINUTE   60000

 
// ************************************************  GLOBAL VARIABLES AND STRUCTURES  ************************************************
CRGB leds[NUM_LEDS];      // Array creation of leds - allows the LED to be address using array [] notation. 


typedef struct TIME_t TIME_t;
typedef struct FROZEN_t FROZEN_t;
typedef struct THAWED_t THAWED_t;
typedef struct BACKGROUND_COLOR_t BACKGROUND_COLOR_t;


struct BACKGROUND_COLOR_t {
    byte red_value;
    byte green_value;
    byte blue_value;
} *background_ptr = NULL;    // TODO is this even necessary? 


struct TIME_t {
    uint16_t timeCounter;
    uint16_t minutesCounter;        // Counts total minutes elapsed since program start. Can exceed 60. Rolls over around 72000 automatically. Only 
                                    // Var serviced directly by millis(). 
    uint16_t rolloverCounter;       // Number of rollovers to convert to 24 hour time. 
    uint16_t hoursCounter;    // Used to subtract and standardize/normaize millis for actual operation, when millis become huge. 
    bool resetFlag;
    byte d0;               // 10s digit of hour 
    byte d1;               //  1s digit of hour
    byte d2;               // 10s digit of minute
    byte d3;               //  1s digit of minute 
} *masterTime = NULL;    


struct FROZEN_t {
    byte switch_1;           // Time mode vs pattern mode 
    short int pot;
} *frozenPtr = NULL;


const byte nums [10][12] = {
                            {1,1,0,1,1,1,0,0,0,1,1,1},      // zero 
                            {0,0,0,0,0,1,0,1,0,1,1,1},      // one 
                            {1,0,1,1,1,1,0,1,0,1,1,0},      // two
                            {1,0,1,0,1,1,0,1,0,1,1,1},      // three
                            {1,1,1,0,1,0,1,1,0,0,1,0},      // four 
                            {1,1,1,0,1,1,0,1,0,1,0,1},      // five
                            {0,0,1,1,1,1,0,1,1,1,0,1},      // six
                            {1,0,0,0,1,0,1,1,0,1,1,0},      // seven 
                            {1,1,1,1,1,1,0,1,0,1,1,1},      // eight    
                            {1,1,1,0,1,0,1,1,0,1,1,0},      // nine 
                         };


const byte digits[4][12] = {
        {7,8,9,10,11,14,15,16,17,18,22,24},                 // leds in the 1st digit 
        {35,36,37,38,39, 42,43,44,45,46,50,52},             // leds in the 2nd digit 
        {77,78,79,80,81,84,85,86,87,88,92,94},              // leds in the 3rd digit 
        {105,106,107,108,109,112,113,114,115,116,120,122},  // leds in the 4th digit 
};



/* LED assignment of the clock perimeter 
const byte perimeter[] = {0,2,1,12,13,26,27,40,41,54,55,68,69,82,83,96,97,110,111,124,123,125,126,127,119,118,117,
                  104,103,90,89,76,75,62,61,48,47,34,33,20,19,6,5,4}; */

// ************************************************ END GLOBALS ********************************************************              


// ************************************************ TIME FUNCTIONS *****************************************************


// Eventually pass in time pointer and construct the array at runtime like below. 
void write_time( byte digit1, byte digit2, byte digit3, byte digit4 ){
    byte time_values[4] = {digit1, digit2, digit3, digit4}; 
    bool val = true;
    write_constant_color_background(val);
    for (int i=0; i<4; i++) {
        for (int j=0; j<12; j++) {
            if (nums[time_values[i]][j] == 1){
            leds[digits[i][j]] = CRGB(255,0,255);
            }
        }
    }
    FastLED.show();
}


// ********************************************* END TIME FUNCTIONS ***************************************************


void write_constant_color_background(bool write_on){
    // Might be better to just hard code this. Unless additinoal functionality will be added 
    // to change the colors at runtime. 
    for (int i=0; i<NUM_LEDS; i++){
        leds[i] = CRGB(255,0,0);
    }
    if (write_on == true) FastLED.show();

}


void initialize_inputs( TIME_t *timePointer ) {
    // Set background values to desired background pointer values


    // Set frozen pointer values 


    /* Initialize time structure */
    timePointer->d0 = 0;
    timePointer->d1 = 1;
    timePointer->d2 = 2;
    timePointer->d3 = 3;
    timePointer->timeCounter = 0;
    timePointer->minutesCounter = 0;
    timePointer->resetFlag = true;

}


void service_inputs( FROZEN_t *inputPointer ) {
    inputPointer->switch_1 = digitalRead(SET_TIME);
    inputPointer->pot = analogRead(PATTERN);
    // Add rotary encoder. 
}


/*
struct TIME_t {
    uint16_t timeCounter;       // Increments by 1 everytime 1 minute has passed. Resets at 60. 
    uint16_t minutesCounter;   // Counts total minutes elapsed since program start. Can exceed 60. Rolls over around 72000 automatically. Only 
                                // Var serviced directly by millis(). 
    uint16_t rolloverCounter;
    uint16_t totalMinutesPassed;   // Used to subtract and standardize/normaize millis for actual operation, when millis become huge. 
    bool resetFlag;
    byte d0;               // 10s digit of hour 
    byte d1;               //  1s digit of hour
    byte d2;               // 10s digit of minute
    byte d3;               //  1s digit of minute 
} *masterTime = NULL;    
*/ 


void service_time( TIME_t * timePointer ){
    // Create a temp var to sample minutes elapsed? Need an intermediate variable that can relate to 
    // millis without exceeding 60, and use the same calculation 
    timePointer->timeCounter = millis();
    timePointer->rolloverCounter = floor( (timePointer->timeCounter) / (MILLISECONDS_IN_DAY) );      // ALlows rollover for day, can subtract from time to get 
    timePointer->minutesCounter = floor( ( (timePointer->timeCounter)/ 60000) - ( (timePointer->rolloverCounter) * MILLISECONDS_IN_MINUTE)  );


    // convertMinutesToHoursAndMinutes( timePointer );

}


extern void convertMinutesToHoursAndMinutes(TIME_t *timePointer){

}


// ************************************************ MAIN FUNCTIONS ************************************************
void setup() {
    Serial.begin(9600);
    pinMode( SET_TIME, INPUT );     
    pinMode( PATTERN, INPUT );
    FastLED.addLeds<WS2812, LED_PIN, GRB>( leds, NUM_LEDS );
    FastLED.setMaxPowerInVoltsAndMilliamps( 5,500 );
    FastLED.clear();
    FastLED.show();
}
uint16_t time1;

void loop() { 
    initialize_inputs( masterTime ); 

    while (true) {
    service_time(masterTime);
    time1 = masterTime->timeCounter;
    Serial.println(time1);


    }


}

// ************************************************ END MAIN FUNCTIONS ************************************************





