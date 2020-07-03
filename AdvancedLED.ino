#include <FastLED.h>
#define LED_PIN 2
#define NUM_LEDS 128

CRGB leds[NUM_LEDS];

void setup() {
    FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
    FastLED.setMaxPowerInVoltsAndMilliamps(5, 500);
    FastLED.clear();
    FastLED.show();
    Serial.begin(9600);
}

void rainbow_right_to_left() {
// RED 

for (int i=0; i<12; i++){
    leds[i] = CRGB(255, 7*i, 0);
    delay(20);
    FastLED.setBrightness(50+i);
    FastLED.show();
}

// Orange
for (int i=12; i<24; i++){
  leds[i] = CRGB(255, 77+7*i, 0);
  delay(20);
  FastLED.setBrightness(50+i);
  FastLED.show();
}

// YELLOW
for (int i=24; i<36; i++){
  leds[i] = CRGB(255-(i-24)*23, 255, 0);
  delay(20);
  FastLED.setBrightness(50+i);
  FastLED.show();
}

// GREEN
for (int i=36; i<48; i++){
  leds[i] = CRGB(2, 255-(i-36)*23, (i-36)*23);
  delay(20);
  FastLED.setBrightness(50+i);
  FastLED.show();
}

// BLUE
for (int i=48; i<60; i++){
  leds[i] = CRGB((i-48)*23, 0, 255);
  delay(20);
  FastLED.setBrightness(50+i);
  FastLED.show();
}
// PURPLE 


FastLED.clear();
delay(600);
FastLED.show();
  
}

void flashing_changing_color() {
for (int i=0; i<NUM_LEDS; i++){
  // Teal color
  leds[i] = CRGB(0, 200, 255);
}
FastLED.show();
for (int i=30; i<100; i++) {
FastLED.setBrightness(i);
delay(5);
FastLED.show();
}
for (int i=100; i>30; i--) {
  FastLED.setBrightness(i);
delay(5);
FastLED.show();
}
FastLED.clear();

for (int i=0; i<NUM_LEDS; i++){
  // Teal color
  leds[i] = CRGB(255, 0 , 255);
}
FastLED.show();
for (int i=30; i<100; i++) {
FastLED.setBrightness(i);
delay(5);
FastLED.show();
}
for (int i=100; i>30; i--) {
  FastLED.setBrightness(i);
delay(5);
FastLED.show();
}
FastLED.clear();

for (int i=0; i<NUM_LEDS; i++){
  // Teal color
  leds[i] = CRGB(255, 200, 0);
}
FastLED.show();
for (int i=30; i<100; i++) {
FastLED.setBrightness(i);
delay(5);
FastLED.show();
}
for (int i=100; i>30; i--) {
  FastLED.setBrightness(i);
delay(5);
FastLED.show();
}
FastLED.clear();

for (int i=0; i<NUM_LEDS; i++){
  // Teal color
  leds[i] = CRGB(200, 120, 120);
}
FastLED.show();
for (int i=30; i<100; i++) {
FastLED.setBrightness(i);
delay(5);
FastLED.show();
}
for (int i=100; i>30; i--) {
  FastLED.setBrightness(i);
delay(5);
FastLED.show();
}
FastLED.clear();
  
}

void start_from_middle() {
    for (int i=0; i<NUM_LEDS; i++) {
        leds[64+i] = CRGB(100, 100-i, 200-2*i);
        leds[64-i] = CRGB(100, 100-i, 5+4*i);
        FastLED.show();
        delay(20);
        FastLED.clear();
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



















  

void RandomLEDandColor() {
leds[random(128)] = CRGB(random(255), random(255), random(255));
leds[random(128)] = CRGB(random(255), random(255), random(255));
leds[random(128)] = CRGB(random(255), random(255), random(255));
leds[random(128)] = CRGB(random(255), random(255), random(255));
leds[random(128)] = CRGB(random(255), random(255), random(255));
FastLED.show();
delay(100);
FastLED.clear();


  
}


int row1[17] = {6,19,20,33,34,47,48,61,62,75,76,89,90,103,104,117,118};
int row2[18] = {5,7,18,21,32,35,46,49,60,63,74,77,88,91,102,105,116,119};
int row3[19] = {4,8,17,22,31,36,45,50,59,64,73,78,87,92,101,106,115,120,127};
int row4[20] = {0,3,9,16,23,30,37,44,51,58,65,72,79,86,93,100,107,114,121,126};
int row5[19] = {2,10,15,24,29,38,43,52,57,66,71,80,85,94,99,108,113,122,125};
int row6[18] = {1,11,14,25,28,39,42,53,56,67,70,81,84,95,98,109,112,123};
int row7[17] = {12,13,26,27,40,41,54,55,68,69,82,83,96,97,110,111,124};


void LightRowsOppositeandConverge() {
// First row go L -> R
for (int i=0; i<17; i++) {
  leds[row1[i]] = CRGB(255,0,0);
  FastLED.show();
  delay(5);
}
// Bottom Row
for (int i=17; i>0; i--) {
  leds[row7[i]] = CRGB(0,0,255);
  FastLED.show();
  delay(5);
}

// 2nd row from top: L->R 
for (int i=0; i<18; i++) {
  leds[row2[i]] = CRGB(255,167,0);
  FastLED.show();
  delay(5);
}
// 2nd row from bottom; R->L
for (int i=18; i>0; i--) {
  leds[row6[i]] = CRGB(255,0,255);
  FastLED.show();
  delay(5);
}

// 3rd row from top L->R
for (int i=0; i<19; i++) {
  leds[row3[i]] = CRGB(0,255,0);
  FastLED.show();
  delay(5);
}
// 3rd row from bottom r -> L
for (int i=19; i>0; i--) {
  leds[row5[i]] = CRGB(0,160,160);
  FastLED.show();
  delay(5);
}
// Center Row 
for (int i=0; i<10; i++) {
  leds[row4[10+i]] = CRGB(255,255,255);
  leds[row4[10-i]] = CRGB(255,255,255);
  FastLED.show();
  delay(5);
}
delay(400);
FastLED.clear();
FastLED.show();

}

int lights1[30] = {5,7,18,21,32,22,23,29,28 , 46,50,51,57,56,58,65,63,73,72,80,81,
                88,92,93,99,98,102,101,94,84};
int lights2[10] = {49,59,58,65,72,74,78,79,85,84}; 
int lights3[46]  = {5,8,9,15,14,25,28,29,23,22,18,39,42,43,37,36,32, 56,57,51,50,
                46,49,60,64,65,58,51,71,70, 74,77,88,87,86,94,95, 119, 
                116,105,106,100,108,109,112,123};
int lights4[39] = {5,8,9,15,14,16,23,21,31,30,38,39, 35,45,44,52,53, 67,66,58,
                59,49,60,63,73,72,80,81,105,102,91,92,86,94,95,98,108,107,100};
                
               
void GrandFinale() {
for (int i=0; i<30; i++) {
  leds[lights1[i]] = CRGB(255,255,255);
  FastLED.show();
  delay(100);
}
FastLED.clear();
FastLED.show();

for (int i=0; i<10; i++) {
  leds[lights2[i]] = CRGB(255,255,255);
  FastLED.show();
  delay(100);
}
FastLED.clear();
FastLED.show();
for (int i=0; i<46; i++) {
  leds[lights3[i]] = CRGB(255,255,255);
  FastLED.show();
  delay(100);
}
FastLED.clear();
FastLED.show();
for (int i=0; i<39; i++) {
  leds[lights4[i]] = CRGB(255,255,255);
  FastLED.show();
  delay(100);
}
FastLED.clear();
FastLED.show();
delay(2000);
}




















void loop() {
    PongMovingRainbow();
}
