/*        ARDUINO PONG CLOCK 
 *        Author: Henry Gilbert
 *        Date Created: July 20th 
 *        Essential Engineering 
 */
 
#include <FastLED.h>
#define LED_PIN     2       // LED Pin for controlling LED address 
#define NUM_LEDS    128     // Defining the number of addressable LEDs used in the circuit 
#define CLOCK_MODE 6        // Pin definition for the clock mode digital input. 
#define SET_TIME 7          // Pin definition for the set time mode digital input. 
#define PATTERN A0          // Pin definition for the potentiometer/pattern set analog input. 
 
// ************************************************  GLOBAL VARIABLES AND STRUCTURES  ************************************************
CRGB leds[NUM_LEDS];      // Array creation of leds - allows the LED to be address using array [] notation. 
int clock_mode_reading;   // Switch input reading for clock mode (display time vs show pattern)
int set_time_reading;     // Switch input reading for set time mode. Changes how fast time increases. 
int pattern_setting;      // Analog potentiometer reading for pattern mode. Changes which pattern is displayed. 
int d1 = 0;               // 10s digit of hour 
int d2 = 0;               //  1s digit of hour
int d3 = 0;               // 10s digit of minute
int d4 = 1;               //  1s digit of minute 

// LED assignments of each individual digit of time. Currently not used for purposes other than debugging. 
int first_digit[12]  = {7, 8, 9, 10, 11, 14, 15, 16, 17, 18, 22, 24};
int second_digit[12] = {35, 36, 37, 38, 39, 42, 43, 44, 45, 46, 50, 52};
int third_digit[12]  = {77, 78, 79, 80, 81, 84, 85, 86, 87, 88, 92, 94};
int fourth_digit[12] = {105, 106, 107, 108, 109, 112, 113, 114, 115, 116, 120, 122};
int background[78]   = {0,1,2,3,4,5,6,13,19,29,21,22,25,26,27,28,30,31,32,33,34, 40,41,47,48,49,51,53,
                       54,55,56,57,58,69,60,61,62,63,65,67,68,69, 70,71,72,73,74,75,76, 82,83, 89, 90,
                       91,93,95,96,97,98,99,100,101,102,103,104,111,117,118,119,121,123,124,125,126,127};

// LED assignments of each row of seven available rows. Used when creating backgrounds.                      
int row1[17] =     {6,19,20,33,34,47,48,61,62,75,76,89,90,103,104,117,118};     
int row2[18] =    {5,7,18,21,32,35,46,49,60,63,74,77,88,91,102,105,116,119};
int row3[19] =  {4,8,17,22,31,36,45,50,59,64,73,78,87,92,101,106,115,120,127};
int row4[20] = {0,3,9,16,23,30,37,44,51,58,65,72,79,86,93,100,107,114,121,126};
int row5[19] =  {2,10,15,24,29,38,43,52,57,66,71,80,85,94,99,108,113,122,125};
int row6[18] =   {1,11,14,25,28,39,42,53,56,67,70,81,84,95,98,109,112,123};
int row7[17] =    {12,13,26,27,40,41,54,55,68,69,82,83,96,97,110,111,124};

// LED assignment of the clock perimeter 
int perimeter[] = {0,2,1,12,13,26,27,40,41,54,55,68,69,82,83,96,97,110,111,124,123,125,126,127,119,118,117,
                  104,103,90,89,76,75,62,61,48,47,34,33,20,19,6,5,4}; 

// ************************************************ END GLOBALS ********************************************************              

// ************************************************ BACKGROUND PATTERNS ************************************************

void LightRowsOppositeandConverge() {
    int delayt = 20;
    // RED First row :left to right
    for (int i=0; i<17; i++) {
        leds[row1[i]] = CRGB(255,0,0);
        FastLED.show();
        delay(delayt);
    }
    
    //  PURPLE Seventh Row: right to left 
    for (int i=16; i>=0; i--) {
        leds[row7[i]] = CRGB(255,0,255);
        FastLED.show();
        delay(delayt);
    }
    
    // ORANGE Second Row: left to right 
    for (int i=0; i<18; i++) {
        leds[row2[i]] = CRGB(255,60,0);
        FastLED.show();
        delay(delayt);
    }
    
    // BLUE Sixth Row: right to left 
    for (int i=17; i>=0; i--) {
        leds[row6[i]] = CRGB(0,0,255);
        FastLED.show();
        delay(delayt);
    }
    
    // YELLOW Third row: left to right 
    for (int i=0; i<19; i++) {
        leds[row3[i]] = CRGB(255,255,0);
        FastLED.show();
        delay(delayt);
    }
    
    // GREEN Fifth row: right to left 
    for (int i=18; i>=0; i--) {
        leds[row5[i]] = CRGB(0,255,0);
        FastLED.show();
        delay(delayt);
    }
    
    // WHITE 4th Row 
    for (int i=0; i<10; i++) {
        leds[row4[10+i]] = CRGB(255,255,255);
        leds[row4[10-i]] = CRGB(255,255,255);
        FastLED.show();
        delay(delayt);
    }
    leds[row4[0]] = CRGB(255,255,255);
    FastLED.show();
    int FastLED_fade_counter;
    for ( int i = 0; i < NUM_LEDS; i++ )
          {
            leds[i].maximizeBrightness(FastLED_fade_counter);  // 'FastLED_fade_counter' How high we want to fade up to 255 = maximum.
            FastLED.show();
            FastLED_fade_counter ++ ;   // Increment
          }
    
    delay(50);
    FastLED.clear();
    FastLED.show();
}

void RandomLEDandColor() {
    leds[random(128)] = CRGB(random(255), random(255), random(255));
    leds[random(128)] = CRGB(random(255), random(255), random(255));
    leds[random(128)] = CRGB(random(255), random(255), random(255));
    leds[random(128)] = CRGB(random(255), random(255), random(255));
    leds[random(128)] = CRGB(random(255), random(255), random(255));
    leds[random(128)] = CRGB(random(255), random(255), random(255));
    leds[random(128)] = CRGB(random(255), random(255), random(255));
    leds[random(128)] = CRGB(random(255), random(255), random(255));
    leds[random(128)] = CRGB(random(255), random(255), random(255));
    leds[random(128)] = CRGB(random(255), random(255), random(255));
    leds[random(128)] = CRGB(random(255), random(255), random(255));
    leds[random(128)] = CRGB(random(255), random(255), random(255));
    FastLED.show();
    delay(200);
    FastLED.clear();
}

void PongMovingRainbow() {
    // Red to Orange
    for (int i=0; i<NUM_LEDS; i++ ) {
        leds[i] = CRGB(255, i, 0);
        delay(2);
        FastLED.show();
    }
    
    // Orange to Yellow 
    for (int i=0; i<NUM_LEDS; i++ ) {
        leds[i] = CRGB(255-i, 128, 0);
        delay(2);
        FastLED.show();
    }
    // Yellow to Green 
    for (int i=0; i<NUM_LEDS; i++ ) {
        leds[i] = CRGB(128-i, 128+i, 0);
        delay(2);
        FastLED.show();
    }
    // Green to Blue 
    for (int i=0; i<NUM_LEDS; i++ ) {
        leds[i] = CRGB(0, 256-2*i, 2*i);
        delay(2);
        FastLED.show();
    }
    // Blue to Violet 
    for (int i=0; i<NUM_LEDS; i++ ) {
        leds[i] = CRGB(128+i, 0, 2*i);
        delay(2);
        FastLED.show();
    }
}

void constant_background_color(int red, int green, int blue) {
    for (int i=0; i<NUM_LEDS; i++) {
        leds[i] = CRGB(red, green, blue);
    }
}

void clock_background_gradient() {
    for (int i=0; i<NUM_LEDS; i++) {
        leds[i] = CRGB(0, 0, 0);
    }
}

// ******************************************** END BACKGROUND PATTERNS ************************************************


// ************************************************ TIME FUNCTIONS *****************************************************

/* Method: write_digit_one, write_digit_two, write_digit_three, write_digit_four 
 * Inputs: number - the value the user wishes to write to the digit
 *         red    - the RGB   Red value the user wishes to color the digit 
 *         green  - the RGB Green value the user wishes to color the digit 
 *         blue   - the RGB  Blue value the user wishes to color the digit 
 * Outputs: None 
 * Description:  Performs a switch function based on the "number" input. Each digit writes the correspond LED based on the desired number. The LED numbers are 
 *               stored in the global section under the "leds" array. 
 */

void write_digit_one(int number, int red, int green, int blue) {
     
    switch (number) {
        case 1: 
            leds[14] = CRGB(red,green,blue);
            leds[24] = CRGB(red,green,blue);
            leds[16] = CRGB(red,green,blue);
            leds[22] = CRGB(red,green,blue);
            leds[18] = CRGB(red,green,blue);
            FastLED.show();
            break;
        case 2: 
            leds[7] =  CRGB(red,green,blue);
            leds[18] = CRGB(red,green,blue);
            leds[22] = CRGB(red,green,blue);
            leds[16] = CRGB(red,green,blue);
            leds[9] =  CRGB(red,green,blue);
            leds[10] = CRGB(red,green,blue);
            leds[11] = CRGB(red,green,blue);
            leds[14] = CRGB(red,green,blue);
            FastLED.show();
            break;
        case 3: 
            leds[7] =  CRGB(red,green,blue);
            leds[18] = CRGB(red,green,blue);
            leds[22] = CRGB(red,green,blue);
            leds[16] = CRGB(red,green,blue);
            leds[9] =  CRGB(red,green,blue);
            leds[24] = CRGB(red,green,blue);
            leds[14] = CRGB(red,green,blue);
            leds[11] = CRGB(red,green,blue);
            FastLED.show();
            break;
        case 4: 
            leds[7] =  CRGB(red,green,blue);
            leds[8] =  CRGB(red,green,blue);
            leds[9] =  CRGB(red,green,blue);
            leds[16] = CRGB(red,green,blue);
            leds[22] = CRGB(red,green,blue);
            leds[15] = CRGB(red,green,blue);
            leds[11] = CRGB(red,green,blue);
            FastLED.show();
            break;
         case 5:
            leds[7] =  CRGB(red,green,blue);
            leds[18] = CRGB(red,green,blue);
            leds[8] =  CRGB(red,green,blue);
            leds[9] =  CRGB(red,green,blue);
            leds[16] = CRGB(red,green,blue);
            leds[24] = CRGB(red,green,blue);
            leds[11] = CRGB(red,green,blue);
            leds[14] = CRGB(red,green,blue);
            FastLED.show();
            break;
         case 6:
            leds[18] = CRGB(red,green,blue);
            leds[17] = CRGB(red,green,blue);
            leds[9] =  CRGB(red,green,blue);
            leds[16] = CRGB(red,green,blue);
            leds[10] = CRGB(red,green,blue);
            leds[24] = CRGB(red,green,blue);
            leds[11] = CRGB(red,green,blue);
            leds[14] = CRGB(red,green,blue);
            FastLED.show();
            break;
         case 7:
            leds[7] =  CRGB(red,green,blue);
            leds[18] = CRGB(red,green,blue);
            leds[22] = CRGB(red,green,blue);
            leds[16] = CRGB(red,green,blue);
            leds[15] = CRGB(red,green,blue);
            leds[11] = CRGB(red,green,blue);
            FastLED.show();
            break;
         case 8:
            leds[7] =  CRGB(red,green,blue);
            leds[18] = CRGB(red,green,blue);
            leds[8] =  CRGB(red,green,blue);
            leds[22] = CRGB(red,green,blue);
            leds[9] =  CRGB(red,green,blue);
            leds[16] = CRGB(red,green,blue);
            leds[10] = CRGB(red,green,blue);
            leds[24] = CRGB(red,green,blue);
            leds[11] = CRGB(red,green,blue);
            leds[14] = CRGB(red,green,blue);
            FastLED.show();
            break;
         case 9:
            leds[7] =  CRGB(red,green,blue);
            leds[18] = CRGB(red,green,blue);
            leds[8] =  CRGB(red,green,blue);
            leds[22] = CRGB(red,green,blue);
            leds[9] =  CRGB(red,green,blue);
            leds[16] = CRGB(red,green,blue);
            leds[15] = CRGB(red,green,blue);
            leds[11] = CRGB(red,green,blue);
            FastLED.show();
            break;
         case 0:
            leds[7] =  CRGB(red,green,blue);
            leds[18] = CRGB(red,green,blue);
            leds[8] =  CRGB(red,green,blue);
            leds[22] = CRGB(red,green,blue);
            leds[10] = CRGB(red,green,blue);
            leds[24] = CRGB(red,green,blue);
            leds[11] = CRGB(red,green,blue);
            leds[14] = CRGB(red,green,blue);
            FastLED.show();
            break;
         default:
            break;
        };
}

void write_digit_two(int number, int red, int green, int blue) {
    switch (number) {
        case 1:
            leds[46] = CRGB(red,green,blue);
            leds[50] = CRGB(red,green,blue);
            leds[44] = CRGB(red,green,blue);
            leds[52] = CRGB(red,green,blue);
            leds[42] = CRGB(red,green,blue);
            FastLED.show();
            break;
        case 2:
            leds[35] = CRGB(red,green,blue);
            leds[46] = CRGB(red,green,blue);
            leds[50] = CRGB(red,green,blue);
            leds[44] = CRGB(red,green,blue);
            leds[37] = CRGB(red,green,blue);
            leds[38] = CRGB(red,green,blue);
            leds[39] = CRGB(red,green,blue);
            leds[42] = CRGB(red,green,blue);
            FastLED.show();
            break;
        case 3:
            leds[35] = CRGB(red,green,blue);
            leds[46] = CRGB(red,green,blue);
            leds[50] = CRGB(red,green,blue);
            leds[44] = CRGB(red,green,blue);
            leds[37] = CRGB(red,green,blue);
            leds[52] = CRGB(red,green,blue);
            leds[39] = CRGB(red,green,blue);
            leds[42] = CRGB(red,green,blue);
            FastLED.show();
            break;
        case 4:
            leds[35] = CRGB(red,green,blue);
            leds[36] = CRGB(red,green,blue);
            leds[37] = CRGB(red,green,blue);
            leds[44] = CRGB(red,green,blue);
            leds[50] = CRGB(red,green,blue);
            leds[43] = CRGB(red,green,blue);
            leds[39] = CRGB(red,green,blue);
            FastLED.show();
            break;
        case 5:
            leds[46] = CRGB(red,green,blue);
            leds[35] = CRGB(red,green,blue);
            leds[36] = CRGB(red,green,blue);
            leds[37] = CRGB(red,green,blue);
            leds[44] = CRGB(red,green,blue);
            leds[52] = CRGB(red,green,blue);
            leds[42] = CRGB(red,green,blue);
            leds[39] = CRGB(red,green,blue);
            FastLED.show();
            break;
      case 6:
            leds[46] = CRGB(red,green,blue);
            leds[45] = CRGB(red,green,blue);
            leds[37] = CRGB(red,green,blue);
            leds[38] = CRGB(red,green,blue);
            leds[39] = CRGB(red,green,blue);
            leds[42] = CRGB(red,green,blue);
            leds[52] = CRGB(red,green,blue);
            leds[44] = CRGB(red,green,blue);
            FastLED.show();
            break;
      case 7:
            leds[35] = CRGB(red,green,blue);
            leds[46] = CRGB(red,green,blue);
            leds[50] = CRGB(red,green,blue);
            leds[44] = CRGB(red,green,blue);
            leds[43] = CRGB(red,green,blue);
            leds[39] = CRGB(red,green,blue);
            FastLED.show();
            break;
      case 8:
            leds[35] = CRGB(red,green,blue);
            leds[46] = CRGB(red,green,blue);
            leds[36] = CRGB(red,green,blue);
            leds[50] = CRGB(red,green,blue);
            leds[37] = CRGB(red,green,blue);
            leds[44] = CRGB(red,green,blue);
            leds[38] = CRGB(red,green,blue);
            leds[52] = CRGB(red,green,blue);
            leds[39] = CRGB(red,green,blue);
            leds[42] = CRGB(red,green,blue);
            FastLED.show();
            break;
      case 9:
            leds[35] = CRGB(red,green,blue);
            leds[46] = CRGB(red,green,blue);
            leds[50] = CRGB(red,green,blue);
            leds[44] = CRGB(red,green,blue);
            leds[43] = CRGB(red,green,blue);
            leds[39] = CRGB(red,green,blue);
            leds[36] = CRGB(red,green,blue);
            leds[37] = CRGB(red,green,blue);
            FastLED.show();
            break;
      case 0:
            leds[35] = CRGB(red,green,blue);
            leds[46] = CRGB(red,green,blue);
            leds[36] = CRGB(red,green,blue);
            leds[50] = CRGB(red,green,blue);
            leds[38] = CRGB(red,green,blue);
            leds[52] = CRGB(red,green,blue);
            leds[39] = CRGB(red,green,blue);
            leds[42] = CRGB(red,green,blue);
            FastLED.show();
            break;
      default:
            break;
      };  
}

void write_digit_three(int number, int red, int green ,int blue) {
    
    switch (number) {
        case 1:
            leds[88] = CRGB(red,green,blue);
            leds[92] = CRGB(red,green,blue);
            leds[86] = CRGB(red,green,blue);
            leds[94] = CRGB(red,green,blue);
            leds[84] = CRGB(red,green,blue);
            FastLED.show();
            break;
        case 2:
            leds[77] = CRGB(red,green,blue);
            leds[88] = CRGB(red,green,blue);
            leds[92] = CRGB(red,green,blue);
            leds[86] = CRGB(red,green,blue);
            leds[79] = CRGB(red,green,blue);
            leds[80] = CRGB(red,green,blue);
            leds[81] = CRGB(red,green,blue);
            leds[84] = CRGB(red,green,blue);
            FastLED.show();
            break;
        case 3:
            leds[77] = CRGB(red,green,blue);
            leds[88] = CRGB(red,green,blue);
            leds[92] = CRGB(red,green,blue);
            leds[86] = CRGB(red,green,blue);
            leds[79] = CRGB(red,green,blue);
            leds[94] = CRGB(red,green,blue);
            leds[84] = CRGB(red,green,blue);
            leds[81] = CRGB(red,green,blue);
            FastLED.show();
            break;
        case 4:
            leds[77] = CRGB(red,green,blue);
            leds[78] = CRGB(red,green,blue);
            leds[79] = CRGB(red,green,blue);
            leds[86] = CRGB(red,green,blue);
            leds[92] = CRGB(red,green,blue);
            leds[85] = CRGB(red,green,blue);
            leds[81] = CRGB(red,green,blue);
            FastLED.show();
            break;
        case 5:
            leds[88] = CRGB(red,green,blue);
            leds[77] = CRGB(red,green,blue);
            leds[78] = CRGB(red,green,blue);
            leds[79] = CRGB(red,green,blue);
            leds[86] = CRGB(red,green,blue);
            leds[94] = CRGB(red,green,blue);
            leds[84] = CRGB(red,green,blue);
            leds[81] = CRGB(red,green,blue);
            FastLED.show();
            break;
        case 6:
            leds[88] = CRGB(red,green,blue);
            leds[87] = CRGB(red,green,blue);
            leds[79] = CRGB(red,green,blue);
            leds[80] = CRGB(red,green,blue);
            leds[81] = CRGB(red,green,blue);
            leds[84] = CRGB(red,green,blue);
            leds[94] = CRGB(red,green,blue);
            leds[86] = CRGB(red,green,blue);
            FastLED.show();
            break;
        case 7:
            leds[77] = CRGB(red,green,blue);
            leds[88] = CRGB(red,green,blue);
            leds[92] = CRGB(red,green,blue);
            leds[86] = CRGB(red,green,blue);
            leds[85] = CRGB(red,green,blue);
            leds[81] = CRGB(red,green,blue);
            FastLED.show();
            break;
        case 8:
            leds[77] = CRGB(red,green,blue);
            leds[78] = CRGB(red,green,blue);
            leds[88] = CRGB(red,green,blue);
            leds[92] = CRGB(red,green,blue);
            leds[79] = CRGB(red,green,blue);
            leds[86] = CRGB(red,green,blue);
            leds[80] = CRGB(red,green,blue);
            leds[94] = CRGB(red,green,blue);
            leds[84] = CRGB(red,green,blue);
            leds[81] = CRGB(red,green,blue);
            FastLED.show();
            break;
        case 9:
            leds[77] = CRGB(red,green,blue);
            leds[88] = CRGB(red,green,blue);
            leds[92] = CRGB(red,green,blue);
            leds[78] = CRGB(red,green,blue);
            leds[79] = CRGB(red,green,blue);
            leds[86] = CRGB(red,green,blue);
            leds[85] = CRGB(red,green,blue);
            leds[81] = CRGB(red,green,blue);
            FastLED.show();
            break;
        case 0:
            leds[77] = CRGB(red,green,blue);
            leds[88] = CRGB(red,green,blue);
            leds[78] = CRGB(red,green,blue);
            leds[92] = CRGB(red,green,blue);
            leds[80] = CRGB(red,green,blue);
            leds[94] = CRGB(red,green,blue);
            leds[81] = CRGB(red,green,blue);
            leds[84] = CRGB(red,green,blue);
            FastLED.show();
            break;
        default:
            break;
    };
}

void write_digit_four(int number, int red, int green, int blue) {

    switch (number) {
        case 1:
            leds[116] = CRGB(red, green, blue);
            leds[120] = CRGB(red, green, blue);
            leds[114] = CRGB(red, green, blue);
            leds[122] = CRGB(red, green, blue);
            leds[112] = CRGB(red, green, blue);
            FastLED.show();
            break;
        case 2:
            leds[105] = CRGB(red, green, blue);
            leds[116] = CRGB(red, green, blue);
            leds[120] = CRGB(red, green, blue);
            leds[107] = CRGB(red, green, blue);
            leds[114] = CRGB(red, green, blue);
            leds[108] = CRGB(red, green, blue);
            leds[109] = CRGB(red, green, blue);
            leds[112] = CRGB(red, green, blue);
            FastLED.show();
            break;
        case 3:
            leds[105] = CRGB(red, green, blue);
            leds[116] = CRGB(red, green, blue);
            leds[120] = CRGB(red, green, blue);
            leds[107] = CRGB(red, green, blue);
            leds[114] = CRGB(red, green, blue);
            leds[122] = CRGB(red, green, blue);
            leds[109] = CRGB(red, green, blue);
            leds[112] = CRGB(red, green, blue);
            FastLED.show();
            break;
        case 4:
            leds[105] = CRGB(red, green, blue);
            leds[106] = CRGB(red, green, blue);
            leds[107] = CRGB(red, green, blue);
            leds[120] = CRGB(red, green, blue);
            leds[114] = CRGB(red, green, blue);
            leds[113] = CRGB(red, green, blue);
            leds[109] = CRGB(red, green, blue);
            FastLED.show();
            break;
        case 5:
            leds[105] = CRGB(red, green, blue);
            leds[116] = CRGB(red, green, blue);
            leds[106] = CRGB(red, green, blue);
            leds[107] = CRGB(red, green, blue);
            leds[114] = CRGB(red, green, blue);
            leds[122] = CRGB(red, green, blue);
            leds[109] = CRGB(red, green, blue);
            leds[112] = CRGB(red, green, blue);
            FastLED.show();
            break;
        case 6:
            leds[116] = CRGB(red, green, blue);
            leds[115] = CRGB(red, green, blue);
            leds[107] = CRGB(red, green, blue);
            leds[114] = CRGB(red, green, blue);
            leds[108] = CRGB(red, green, blue);
            leds[122] = CRGB(red, green, blue);
            leds[109] = CRGB(red, green, blue);
            leds[112] = CRGB(red, green, blue);
            FastLED.show();
            break;
        case 7:
            leds[105] = CRGB(red, green, blue);
            leds[116] = CRGB(red, green, blue);
            leds[120] = CRGB(red, green, blue);
            leds[114] = CRGB(red, green, blue);
            leds[114] = CRGB(red, green, blue);
            leds[113] = CRGB(red, green, blue);
            leds[109] = CRGB(red, green, blue);
            FastLED.show();
            break;
        case 8:
            leds[105] = CRGB(red, green, blue);
            leds[116] = CRGB(red, green, blue);
            leds[106] = CRGB(red, green, blue);
            leds[120] = CRGB(red, green, blue);
            leds[107] = CRGB(red, green, blue);
            leds[114] = CRGB(red, green, blue);
            leds[108] = CRGB(red, green, blue);
            leds[122] = CRGB(red, green, blue);
            leds[109] = CRGB(red, green, blue);
            leds[112] = CRGB(red, green, blue);
            FastLED.show();
            break;
        case 9:
            leds[105] = CRGB(red, green, blue);
            leds[116] = CRGB(red, green, blue);
            leds[106] = CRGB(red, green, blue);
            leds[120] = CRGB(red, green, blue);
            leds[107] = CRGB(red, green, blue);
            leds[114] = CRGB(red, green, blue);
            leds[113] = CRGB(red, green, blue);
            leds[109] = CRGB(red, green, blue);
            FastLED.show();
            break;
        case 0:
            leds[105] = CRGB(red, green, blue);
            leds[116] = CRGB(red, green, blue);
            leds[106] = CRGB(red, green, blue);
            leds[120] = CRGB(red, green, blue);
            leds[108] = CRGB(red, green, blue);
            leds[122] = CRGB(red, green, blue);
            leds[109] = CRGB(red, green, blue);
            leds[112] = CRGB(red, green, blue);
            FastLED.show();
            break;
        default:
            break;
    };
}

/* Method: write_time
 * Inputs: a, b, c, d. These values are the time digit values correspond to time in the format ab:cd, where ab is the hour, and cd is the minute. 
 * Outputs: None 
 * Description: Set the time based on the values input. The stack variables r, g, and b1 are the color the user wishes to set the numbers. These inputs 
 *              call the methods to write the individual digits based on the calculated time. 
 */

void write_time(int a, int b, int c, int d ) {  
int r = 255;
int g = 43;
int b1 = 12;  
    leds[66] = CRGB(r,g,b1);
    leds[64] = CRGB(r,g,b1);
    write_digit_one  (a, r, g, b1);
    write_digit_two  (b, r, g, b1);
    write_digit_three(c, r, g, b1);
    write_digit_four (d, r, g, b1);
}

/* Method: update_time
 * Inputs: _delay : Time to be delayed before incrementing the minute hand. If the clock is in set time mode, the delay is 50 miliseconds, otherwise, 
 *                  the delay is 60,000 miliseconds, or 60 seconds. This allows the minute hand to increase by 1 every 60 seconds. 
 * Outputs: None 
 * Description: Calls the FastLED.show() method, sets the background to a constant color, then calls the write_time method to write the time to the clock.
 *              The minute ones digit, or d4, increments by 1 after every iteration. This iteration is delayed by either 50 miliseconds during set time mode, 
 *              or every 60,000 (60 seconds) during standard mode. The code allows the time to update according to 12 hour format. This prevents the clock
 *              from displaying values that are impossible with 12 hour format (18:87, 01:74, etc). 
 */

void update_time(long int _delay) {
    FastLED.show();
    constant_background_color(2,7,70);
    write_time(d1,d2,d3,d4);
    
    delay(_delay);
    d4 += 1;
    
    if (d4 > 9) {
        d4 = 0;
        d3 += 1;
    }
    if (d3 == 6) {
        d3 = 0;
        d2 += 1;
    }
    if (d2 == 3 && d1 == 1) {
        d2 =1;
        d1 = 0;
    } 
    if (d2 == 10) {
        d2 = 0;
        d1 += 1;
    }  
    if (d1 == 2) {
        d1 == 0;
    }
    if (d2 == 2){
        if (d1 == 1) {
            d2 == 0;
            d1 == 0;
        }
    }    
}

// ********************************************* END TIME FUNCTIONS ***************************************************


// ************************************************ MAIN FUNCTIONS ************************************************
void setup() {
    Serial.begin(9600);
    pinMode(SET_TIME, INPUT);
    pinMode(CLOCK_MODE, INPUT);
    pinMode(PATTERN, INPUT);
    FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
    FastLED.setMaxPowerInVoltsAndMilliamps(5,500);
    FastLED.clear();
    FastLED.show();
}

void loop() { 

// Step 1. Take all initial measurements from mode switch, time swich, and 
// potentiometer, and store them in respective variables. 
    
    set_time_reading = digitalRead(SET_TIME);
    clock_mode_reading = digitalRead(CLOCK_MODE);
    pattern_setting = analogRead(PATTERN);


// Step 2. Configure LEDs based on switch reading. General logic, is that if the clock is in 
// pattern mode, display a pattern that the user can change with the potentiometer. If the 
// clock is in time mode, update the time every 60 seconds. If the user is in time mode 
// and the set time switch is enabled, update the time every 300 milliseconds to allow the 
// user to set the time. Flip the switch back to turn on refresh rate to 60 seconds. 

// This would really work best with parallel computing, because here it is easy to get stuck 
// in the 60 second loop with no idea what the state of the buttons is. 

// clock_mode_reading == 1      --> Background mode 
// clock_mode_reading == 0      --> Time mode 
// set_time_reading   == 1      --> Fast refresh to set precise time 
// set_time_reading   == 0      --> 60 second refresh rate for time. 

    
    if (clock_mode_reading == 1) {
    // Analog read pot setting for background 
        if (pattern_setting < 300) {
            FastLED.clear();
            FastLED.show();
            LightRowsOppositeandConverge();
        }
        else if (pattern_setting < 600) {
            FastLED.clear();
            FastLED.show();
            PongMovingRainbow();
        }
        else if (pattern_setting < 1000) {
            FastLED.clear();
            FastLED.show();
            RandomLEDandColor();
        }
    }
    
    if (clock_mode_reading == 0) {
        if (set_time_reading == 1) {
            update_time(50);
        }
        else {
            update_time(60000);
        }
    }   
}

// ************************************************ END MAIN FUNCTIONS ************************************************
