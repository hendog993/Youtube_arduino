// LED assignments of each row of seven available rows. Used when creating backgrounds.                      
const byte row1[17] =     {6,19,20,33,34,47,48,61,62,75,76,89,90,103,104,117,118};     
const byte row2[18] =    {5,7,18,21,32,35,46,49,60,63,74,77,88,91,102,105,116,119};
const byte row3[19] =  {4,8,17,22,31,36,45,50,59,64,73,78,87,92,101,106,115,120,127};
const byte row4[20] = {0,3,9,16,23,30,37,44,51,58,65,72,79,86,93,100,107,114,121,126};
const byte row5[19] =  {2,10,15,24,29,38,43,52,57,66,71,80,85,94,99,108,113,122,125};
const byte row6[18] =   {1,11,14,25,28,39,42,53,56,67,70,81,84,95,98,109,112,123};
const byte row7[17] =    {12,13,26,27,40,41,54,55,68,69,82,83,96,97,110,111,124};


void LightRowsOppositeandConverge() {
    byte delayt = 20;
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