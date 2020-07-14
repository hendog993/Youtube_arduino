#include <FastLED.h>
#include <IRremote.h>
#define LED_PIN     2
#define NUM_LEDS    128
#define IR_PIN 5
CRGB leds[NUM_LEDS];
 
// GLOBALS 
// LED assignments of each digit.
int first_digit[12]  = {7, 8, 9, 10, 11, 14,15,16,17,18, 22, 24};
int second_digit[12] = {35,36,37,38,39,42,43,44,45,46, 50, 52};
int third_digit[12]  = {77, 78, 79, 80, 81, 84, 85, 86, 87, 88, 92, 94};
int fourth_digit[12] = {105,106,107,108,109, 112,113,114,115,116, 120, 122};
int background[78]   = {0,1,2,3,4,5,6,13,19,29,21,22,25,26,27,28,30,31,32,33,34, 40,41,47,48,49,51,53,
                       54,55,56,57,58,69,60,61,62,63,65,67,68,69, 70,71,72,73,74,75,76, 82,83, 89, 90,
                       91,93,95,96,97,98,99,100,101,102,103,104,111,117,118,119,121,123,124,125,126,127};
                       
int row1[17] = {6,19,20,33,34,47,48,61,62,75,76,89,90,103,104,117,118};
int row2[18] = {5,7,18,21,32,35,46,49,60,63,74,77,88,91,102,105,116,119};
int row3[19] = {4,8,17,22,31,36,45,50,59,64,73,78,87,92,101,106,115,120,127};
int row4[20] = {0,3,9,16,23,30,37,44,51,58,65,72,79,86,93,100,107,114,121,126};
int row5[19] = {2,10,15,24,29,38,43,52,57,66,71,80,85,94,99,108,113,122,125};
int row6[18] = {1,11,14,25,28,39,42,53,56,67,70,81,84,95,98,109,112,123};
int row7[17] = {12,13,26,27,40,41,54,55,68,69,82,83,96,97,110,111,124};

int perimeter[] = {0,2,1,12,13,26,27,40,41,54,55,68,69,82,83,96,97,110,111,124,123,125,126,127,119,118,117,
                  104,103,90,89,76,75,62,61,48,47,34,33,20,19,6,5,4}; 

// END GLOBALS               

// LED Order for writing certain digits. 

void write_digit_one(int number) {
switch (number) {
    case 1: 
        leds[14] = CRGB(255,0,0);
        leds[24] = CRGB(255,0,0);
        leds[16] = CRGB(255,255,255);
        leds[22] = CRGB(255,255,255);
        leds[18] = CRGB(255,255,255);
        FastLED.show();
        break;
    case 2: 
        leds[7] =  CRGB(255,255,255);
        leds[18] = CRGB(255,255,255);
        leds[22] = CRGB(255,255,255);
        leds[16] = CRGB(255,255,255);
        leds[9] =  CRGB(255,255,255);
        leds[10] = CRGB(255,255,255);
        leds[11] = CRGB(255,255,255);
        leds[14] = CRGB(255,255,255);
        FastLED.show();
        break;
    case 3: 
        leds[7] = CRGB(255,255,255);
        leds[18] = CRGB(255,255,255);
        leds[22] = CRGB(255,255,255);
        leds[16] = CRGB(255,255,255);
        leds[9] = CRGB(255,255,255);
        leds[24] = CRGB(255,255,255);
        leds[14] = CRGB(255,255,255);
        leds[11] = CRGB(255,255,255);
        FastLED.show();
        break;
    case 4: 
        leds[7] = CRGB(255,255,255);
        leds[8] = CRGB(255,255,255);
        leds[9] = CRGB(255,255,255);
        leds[16] = CRGB(255,255,255);
        leds[22] = CRGB(255,255,255);
        leds[15] = CRGB(255,255,255);
        leds[11] = CRGB(255,255,255);
        FastLED.show();
        break;
     case 5: 
        leds[7] = CRGB(255,255,255);
        leds[18] = CRGB(255,255,255);
        leds[8] = CRGB(255,255,255);
        leds[9] = CRGB(255,255,255);
        leds[16] = CRGB(255,255,255);
        leds[24] = CRGB(255,255,255);
        leds[11] = CRGB(255,255,255);
        leds[14] = CRGB(255,255,255);
        FastLED.show();
        break;
     case 6: 
        leds[18] = CRGB(255,255,255);
        leds[17] = CRGB(255,255,255);
        leds[9] = CRGB(255,255,255);
        leds[16] = CRGB(255,255,255);
        leds[10] = CRGB(255,255,255);
        leds[24] = CRGB(255,255,255);
        leds[11] = CRGB(255,255,255);
        leds[14] = CRGB(255,255,255);
        FastLED.show();
        break;
     case 7: 
        leds[7] = CRGB(255,255,255);
        leds[18] = CRGB(255,255,255);
        leds[22] = CRGB(255,255,255);
        leds[16] = CRGB(255,255,255);
        leds[15] = CRGB(255,255,255);
        leds[11] = CRGB(255,255,255);
        FastLED.show();
        break;
     case 8: 
        leds[7] = CRGB(255,255,255);
        leds[18] = CRGB(255,255,255);
        leds[8] = CRGB(255,255,255);
        leds[22] = CRGB(255,255,255);
        leds[9] = CRGB(255,255,255);
        leds[16] = CRGB(255,255,255);
        leds[10] = CRGB(255,255,255);
        leds[24] = CRGB(255,255,255);
        leds[11] = CRGB(255,255,255);
        leds[14] = CRGB(255,255,255);
        FastLED.show();
        break;
      case 9: 
        leds[7] = CRGB(255,255,255);
        leds[18] = CRGB(255,255,255);
        leds[8] = CRGB(255,255,255);
        leds[22] = CRGB(255,255,255);
        leds[9] = CRGB(255,255,255);
        leds[16] = CRGB(255,255,255);
        leds[15] = CRGB(255,255,255);
        leds[11] = CRGB(255,255,255);
        FastLED.show();
        break;
     case 0: 
        leds[7] = CRGB(255,255,255);
        leds[18] = CRGB(255,255,255);
        leds[8] = CRGB(255,255,255);
        leds[22] = CRGB(255,255,255);
        leds[10] = CRGB(255,255,255);
        leds[24] = CRGB(255,255,255);
        leds[11] = CRGB(255,255,255);
        leds[14] = CRGB(255,255,255);
        FastLED.show();
        break;


        
    default:
        break;
    };
}
void write_digit_two(int number) {
  switch (number) {
    case 1: 
        leds[46] = CRGB(255,255,255);
        leds[50] = CRGB(255,255,255);
        leds[44] = CRGB(255,255,255);
        leds[52] = CRGB(255,255,255);
        leds[42] = CRGB(255,255,255);
        FastLED.show();
        break;
    case 2: 
        leds[35] = CRGB(255,255,255);
        leds[46] = CRGB(255,255,255);
        leds[50] = CRGB(255,255,255);
        leds[44] = CRGB(255,255,255);
        leds[37] = CRGB(255,255,255);
        leds[38] = CRGB(255,255,255);
        leds[39] = CRGB(255,255,255);
        leds[42] = CRGB(255,255,255);
        FastLED.show();
        break;
    case 3: 
        leds[35] = CRGB(255,255,255);
        leds[46] = CRGB(255,255,255);
        leds[50] = CRGB(255,255,255);
        leds[44] = CRGB(255,255,255);
        leds[37] = CRGB(255,255,255);
        leds[52] = CRGB(255,255,255);
        leds[39] = CRGB(255,255,255);
        leds[42] = CRGB(255,255,255);
        FastLED.show();
        break;
    case 4: 
        leds[35] = CRGB(255,255,255);
        leds[36] = CRGB(255,255,255);
        leds[37] = CRGB(255,255,255);
        leds[44] = CRGB(255,255,255);
        leds[50] = CRGB(255,255,255);
        leds[43] = CRGB(255,255,255);
        leds[39] = CRGB(255,255,255);
        FastLED.show();
        break;
     case 5: 
        leds[46] = CRGB(255,255,255);
        leds[35] = CRGB(255,255,255);
        leds[36] = CRGB(255,255,255);
        leds[37] = CRGB(255,255,255);
        leds[44] = CRGB(255,255,255);
        leds[52] = CRGB(255,255,255);
        leds[42] = CRGB(255,255,255);
        leds[39] = CRGB(255,255,255);
        FastLED.show();
        break;
     case 6: 
        leds[46] = CRGB(255,255,255);
        leds[45] = CRGB(255,255,255);
        leds[37] = CRGB(255,255,255);
        leds[38] = CRGB(255,255,255);
        leds[39] = CRGB(255,255,255);
        leds[42] = CRGB(255,255,255);
        leds[52] = CRGB(255,255,255);
        leds[44] = CRGB(255,255,255);
        FastLED.show();
        break;
     case 7: 
        leds[35] = CRGB(255,255,255);
        leds[46] = CRGB(255,255,255);
        leds[50] = CRGB(255,255,255);
        leds[44] = CRGB(255,255,255);
        leds[43] = CRGB(255,255,255);
        leds[39] = CRGB(255,255,255);
        FastLED.show();
        break;
     case 8: 
        leds[35] = CRGB(255,255,255);
        leds[46] = CRGB(255,255,255);
        leds[36] = CRGB(255,255,255);
        leds[50] = CRGB(255,255,255);
        leds[37] = CRGB(255,255,255);
        leds[44] = CRGB(255,255,255);
        leds[38] = CRGB(255,255,255);
        leds[52] = CRGB(255,255,255);
        leds[39] = CRGB(255,255,255);
        leds[42] = CRGB(255,255,255);
        FastLED.show();
        break;
      case 9: 
        leds[35] = CRGB(255,255,255);
        leds[46] = CRGB(255,255,255);
        leds[50] = CRGB(255,255,255);
        leds[44] = CRGB(255,255,255);
        leds[43] = CRGB(255,255,255);
        leds[39] = CRGB(255,255,255);
        leds[36] = CRGB(255,255,255);
        leds[37] = CRGB(255,255,255);
        FastLED.show();
        break;
     case 0: 
        leds[35] = CRGB(255,255,255);
        leds[46] = CRGB(255,255,255);
        leds[36] = CRGB(255,255,255);
        leds[50] = CRGB(255,255,255);
        leds[38] = CRGB(255,255,255);
        leds[52] = CRGB(255,255,255);
        leds[39] = CRGB(255,255,255);
        leds[42] = CRGB(255,255,255);
        FastLED.show();
        break;
    default:
        break;
    };
}
void write_digit_three(int number) {
  switch (number) {
    case 1: 
        leds[88] = CRGB(255,255,255);
        leds[92] = CRGB(255,255,255);
        leds[86] = CRGB(255,255,255);
        leds[94] = CRGB(255,255,255);
        leds[84] = CRGB(255,255,255);
        FastLED.show();
        break;
    case 2: 
        leds[77] = CRGB(255,255,255);
        leds[88] = CRGB(255,255,255);
        leds[92] = CRGB(255,255,255);
        leds[86] = CRGB(255,255,255);
        leds[79] = CRGB(255,255,255);
        leds[80] = CRGB(255,255,255);
        leds[81] = CRGB(255,255,255);
        leds[84] = CRGB(255,255,255);
        FastLED.show();
        break;
    case 3: 
        leds[77] = CRGB(255,255,255);
        leds[88] = CRGB(255,255,255);
        leds[92] = CRGB(255,255,255);
        leds[86] = CRGB(255,255,255);
        leds[79] = CRGB(255,255,255);
        leds[94] = CRGB(255,255,255);
        leds[84] = CRGB(255,255,255);
        leds[81] = CRGB(255,255,255);
        FastLED.show();
        break;
    case 4: 
        leds[77] = CRGB(255,255,255);
        leds[78] = CRGB(255,255,255);
        leds[79] = CRGB(255,255,255);
        leds[86] = CRGB(255,255,255);
        leds[92] = CRGB(255,255,255);
        leds[85] = CRGB(255,255,255);
        leds[81] = CRGB(255,255,255);
        FastLED.show();
        break;
     case 5: 
        leds[88] = CRGB(255,255,255);
        leds[77] = CRGB(255,255,255);
        leds[78] = CRGB(255,255,255);
        leds[79] = CRGB(255,255,255);
        leds[86] = CRGB(255,255,255);
        leds[94] = CRGB(255,255,255);
        leds[84] = CRGB(255,255,255);
        leds[81] = CRGB(255,255,255);
        FastLED.show();
        break;
     case 6: 
        leds[88] = CRGB(255,255,255);
        leds[87] = CRGB(255,255,255);
        leds[79] = CRGB(255,255,255);
        leds[80] = CRGB(255,255,255);
        leds[81] = CRGB(255,255,255);
        leds[84] = CRGB(255,255,255);
        leds[94] = CRGB(255,255,255);
        leds[86] = CRGB(255,255,255);
        FastLED.show();
        break;
     case 7: 
        leds[77] = CRGB(255,255,255);
        leds[88] = CRGB(255,255,255);
        leds[92] = CRGB(255,255,255);
        leds[86] = CRGB(255,255,255);
        leds[85] = CRGB(255,255,255);
        leds[81] = CRGB(255,255,255);
        FastLED.show();
        break;
     case 8: 
        leds[77] = CRGB(255,255,255);
        leds[78] = CRGB(255,255,255);
        leds[88] = CRGB(255,255,255);
        leds[92] = CRGB(255,255,255);
        leds[79] = CRGB(255,255,255);
        leds[86] = CRGB(255,255,255);
        leds[80] = CRGB(255,255,255);
        leds[94] = CRGB(255,255,255);
        leds[84] = CRGB(255,255,255);
        leds[81] = CRGB(255,255,255);
        FastLED.show();
        break;
      case 9: 
        leds[77] = CRGB(255,255,255);
        leds[88] = CRGB(255,255,255);
        leds[92] = CRGB(255,255,255);
        leds[78] = CRGB(255,255,255);
        leds[79] = CRGB(255,255,255);
        leds[86] = CRGB(255,255,255);
        leds[85] = CRGB(255,255,255);
        leds[81] = CRGB(255,255,255);
        FastLED.show();
        break;
     case 0: 
        leds[77] = CRGB(255,255,255);
        leds[88] = CRGB(255,255,255);
        leds[78] = CRGB(255,255,255);
        leds[92] = CRGB(255,255,255);
        leds[80] = CRGB(255,255,255);
        leds[94] = CRGB(255,255,255);
        leds[81] = CRGB(255,255,255);
        leds[84] = CRGB(255,255,255);
        FastLED.show();
        break;
    default:
        break;
    };
}
void write_digit_four(int number) {
  switch (number) {
    case 1: 
        leds[116] = CRGB(255,255,255);
        leds[120] = CRGB(255,255,255);
        leds[114] = CRGB(255,255,255);
        leds[122] = CRGB(255,255,255);
        leds[112] = CRGB(255,255,255);
        FastLED.show();
        break;
    case 2: 
        leds[105] = CRGB(255,255,255);
        leds[116] = CRGB(255,255,255);
        leds[120] = CRGB(255,255,255);
        leds[107] = CRGB(255,255,255);
        leds[114] = CRGB(255,255,255);
        leds[108] = CRGB(255,255,255);
        leds[109] = CRGB(255,255,255);
        leds[112] = CRGB(255,255,255);
        FastLED.show();
        break;
    case 3: 
        leds[105] = CRGB(255,255,255);
        leds[116] = CRGB(255,255,255);
        leds[120] = CRGB(255,255,255);
        leds[107] = CRGB(255,255,255);
        leds[114] = CRGB(255,255,255);
        leds[122] = CRGB(255,255,255);
        leds[109] = CRGB(255,255,255);
        leds[112] = CRGB(255,255,255);
        FastLED.show();
        break;
    case 4: 
        leds[105] = CRGB(255,255,255);
        leds[106] = CRGB(255,255,255);
        leds[107] = CRGB(255,255,255);
        leds[120] = CRGB(255,255,255);
        leds[114] = CRGB(255,255,255);
        leds[113] = CRGB(255,255,255);
        leds[109] = CRGB(255,255,255);
        FastLED.show();
        break;
     case 5: 
        leds[105] = CRGB(255,255,255);
        leds[116] = CRGB(255,255,255);
        leds[106] = CRGB(255,255,255);
        leds[107] = CRGB(255,255,255);
        leds[114] = CRGB(255,255,255);
        leds[122] = CRGB(255,255,255);
        leds[109] = CRGB(255,255,255);
        leds[112] = CRGB(255,255,255);
        FastLED.show();
        break;
     case 6: 
        leds[116] = CRGB(255,255,255);
        leds[115] = CRGB(255,255,255);
        leds[107] = CRGB(255,255,255);
        leds[114] = CRGB(255,255,255);
        leds[108] = CRGB(255,255,255);
        leds[122] = CRGB(255,255,255);
        leds[109] = CRGB(255,255,255);
        leds[112] = CRGB(255,255,255);
        FastLED.show();
        break;
     case 7: 
        leds[105] = CRGB(255,255,255);
        leds[116] = CRGB(255,255,255);
        leds[120] = CRGB(255,255,255);
        leds[114] = CRGB(255,255,255);
        leds[114] = CRGB(255,255,255);
        leds[113] = CRGB(255,255,255);
        leds[109] = CRGB(255,255,255);
        FastLED.show();
        break;
     case 8: 
        leds[105] = CRGB(255,255,255);
        leds[116] = CRGB(255,255,255);
        leds[106] = CRGB(255,255,255);
        leds[120] = CRGB(255,255,255);
        leds[107] = CRGB(255,255,255);
        leds[114] = CRGB(255,255,255);
        leds[108] = CRGB(255,255,255);
        leds[122] = CRGB(255,255,255);
        leds[109] = CRGB(255,255,255);
        leds[112] = CRGB(255,255,255);
        FastLED.show();
        break;
      case 9: 
        leds[105] = CRGB(255,255,255);
        leds[116] = CRGB(255,255,255);
        leds[106] = CRGB(255,255,255);
        leds[120] = CRGB(255,255,255);
        leds[107] = CRGB(255,255,255);
        leds[114] = CRGB(255,255,255);
        leds[113] = CRGB(255,255,255);
        leds[109] = CRGB(255,255,255);
        FastLED.show();
        break;
     case 0: 
        leds[105] = CRGB(255,255,255);
        leds[116] = CRGB(255,255,255);
        leds[106] = CRGB(255,255,255);
        leds[120] = CRGB(255,255,255);
        leds[108] = CRGB(255,255,255);
        leds[122] = CRGB(255,255,255);
        leds[109] = CRGB(255,255,255);
        leds[112] = CRGB(255,255,255);
        FastLED.show();
        break;
    default:
        break;
    };
}

// War eagle lights 
int war[] = {
7,17,16,24,25,28,39,42,53,38,30,31,21,35,45,44,52,
67,66,58,59,49,60,63,73,72,80,81,65,
95,94,86,87,77,88,91,102,106,100,93,108,109};

int eagle[] = {
5,8,9,15,14,25,28,16,23,7,18, // E
32,36,37,43,42,35,46,59,51,44,57,56, // A
63,60,49,59,58,66,67,70,81,80,72,65, // G
77,87,86,94,95,                      // L
105,102,91,101,100,108,109,112,123,107,114}; // E

void war_eagle() {
// BLUE WHITE ORANGE order of assign  Blue background, orange letters, white perimeter. 
// Blue 12,35,64
// Orange 242,101,34
// Write war

   // Blue 
    for (int i=0; i<NUM_LEDS; i++) {
        leds[i] = CRGB(12,35,64);     
    }
    FastLED.show();
    delay(500);
    
  // white 
    for (int i=0; i<44; i++) {
        leds[perimeter[i]] = CRGB(255,255,255);     
    }
    FastLED.show();
    delay(500);
    
  // Orange 
    for (int i=0; i<(sizeof(war)/sizeof(war[0]))  ; i++) {
        leds[war[i]] = CRGB(242,101,34);     
    }
    FastLED.show();
    delay(5000);

// Write Eagle 
// Blue 
    for (int i=0; i<NUM_LEDS; i++) {
        leds[i] = CRGB(12,35,64);     
    }
    FastLED.show();
    delay(500);
    
  // white 
    for (int i=0; i<44; i++) {
        leds[perimeter[i]] = CRGB(255,255,255);     
    }
    FastLED.show();
    delay(500);
    
  // Orange 
    for (int i=0; i<(sizeof(eagle)/sizeof(eagle[0]))  ; i++) {
        leds[eagle[i]] = CRGB(242,101,34);     
    }
    FastLED.show();
    delay(5000);
}

// END WAR EAGLE 



int rotary_encoder_reading;

// ROTARY ENCODER INPUT FUNCTION 
void read_rotary_encoder() {


  
}

// Switch input function 

// BACKGROUND PATTERNS 
void RandomLEDandColor() {
      leds[random(128)] = CRGB(random(255), random(255), random(255));
      leds[random(128)] = CRGB(random(255), random(255), random(255));
      leds[random(128)] = CRGB(random(255), random(255), random(255));
      leds[random(128)] = CRGB(random(255), random(255), random(255));
      leds[random(128)] = CRGB(random(255), random(255), random(255));
      leds[random(128)] = CRGB(random(255), random(255), random(255));
      leds[random(128)] = CRGB(random(255), random(255), random(255));
      leds[random(128)] = CRGB(random(255), random(255), random(255));
      FastLED.show();
      delay(800);
      FastLED.clear();
}

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
    
    delay(400);
    FastLED.clear();
    FastLED.show();
}

void constant_background_color(int red, int green, int blue) {
    for (int i=0; i<NUM_LEDS; i++) {
        leds[i] = CRGB(red, green, blue);
    }
}

void PongMovingRainbow() {
// Red
for (int i=0; i<NUM_LEDS; i++ ) {
    leds[i] = CRGB(255, i, 0);
    delay(2);
    FastLED.show();
}

// Orange
for (int i=0; i<NUM_LEDS; i++ ) {
    leds[i] = CRGB(255-i, 128, 0);
    delay(2);
    FastLED.show();
}
// Yellow
for (int i=0; i<NUM_LEDS; i++ ) {
    leds[i] = CRGB(128-i, 128+i, 0);
    delay(2);
    FastLED.show();
}
// Green
for (int i=0; i<NUM_LEDS; i++ ) {
    leds[i] = CRGB(0, 256-2*i, 2*i);
    delay(2);
    FastLED.show();
}
// Blue
for (int i=0; i<NUM_LEDS; i++ ) {
    leds[i] = CRGB(128+i, 0, 2*i);
    delay(2);
    FastLED.show();
}
// Violet
  
}

// END BACKGROUND PATTERNS 

void write_time(int a, int b, int c, int d ) {
    leds[66] = CRGB(255,255,255);
    leds[64] = CRGB(255,255,255);
    write_digit_one(a);
    write_digit_two(b);
    write_digit_three(c);
    write_digit_four(d);
}

void setup() {
    Serial.begin(9600);
    FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
 
    //irrecv.enableIRIn();
    //irrecv.blink13(true);
    FastLED.setMaxPowerInVoltsAndMilliamps(5,500);
    FastLED.clear();
    FastLED.show();
    
}

void unit_test_numbers() {
  for (int i=0; i<10; i++) {
      constant_background_color(0,255-10*i,10*i);
      write_time(i,i,i,i);
      delay(900);
      FastLED.clear();
      FastLED.show();
    }
}

void gradual_gradient_shift() {
int delay1 = 500;  
    for (int i=0; i<NUM_LEDS; i++) {
        leds[i] = CRGB(255,0,0);
    }
    FastLED.show();
    delay(delay1);
    for (int i=0; i<NUM_LEDS; i++) {
        leds[i] = CRGB(255,160,0);
    }
    FastLED.show();
    delay(delay1);
    for (int i=0; i<NUM_LEDS; i++) {
        leds[i] = CRGB(255,0,255);
    }
    FastLED.show();
    delay(delay1);
    for (int i=0; i<NUM_LEDS; i++) {
        leds[i] = CRGB(60,200,200);
    }
    FastLED.show();
    delay(delay1);
    for (int i=0; i<NUM_LEDS; i++) {
        leds[i] = CRGB(150,10,255);
    }
    FastLED.show();
    delay(delay1);
    for (int i=0; i<NUM_LEDS; i++) {
        leds[i] = CRGB(90,180,90);
    }
    FastLED.show();
    delay(delay1);
}

int d1 = 1;
int d2 = 0;
int d3 = 1;
int d4 = 2;

void update_time() {
  FastLED.show();
    constant_background_color(255,0,255);
    write_time(d1,d2,d3,d4);
    
    delay(60000);
    d4 += 1;
    
    if (d4 == 10) {
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
    d1 += 1;}
    
          
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

void loop() { 
  update_time();



   
}
