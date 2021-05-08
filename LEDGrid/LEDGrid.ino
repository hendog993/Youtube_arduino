/*
 * Project goals:
 * 1. Write images using large format and calculate bytes/data used
 * 2. Write compression algorithm and calculate bytes saved
 * 3. Write decompression algorithm to rewrite original image
 * 
 * 
 */


/*Compression format
 * 
 * per 
 * per row: [2 bit command][6 bit num columns]
 * 
 * 
 */




#include <FastLED.h>
#include <stdint.h>


#define LED_PIN 2
#define NUM_LEDS 60
CRGB leds[NUM_LEDS];
#define RESOLUTION_X 10
#define RESOLUTION_Y 6



byte pixel_data[60] = 
{
  0,1,2,3,4,5,6,7,8,9,
  19,18,17,16,15,14,13,12,11,10,
  20,21,22,23,24,25,26,27,28,29,
  39,38,37,36,35,34,33,32,31,30,
  40,41,42,43,44,45,46,47,48,49,
  59,58,57,56,55,54,53,52,51,50
};


typedef struct COMPRESSED_OBJECT {

  
} COMPRESSED_OBJECT;

uint8_t pixel_buffer;

int32_t compress_object() {
  int32_t s32_returnval = 1;
  return s32_returnval;
}

int32_t decompress_object() {
  int32_t s32_returnval = 1;
  return s32_returnval;
}

int32_t decompress_single_row() {
  int32_t s32_returnval = 1;
  return s32_returnval;
}


typedef byte pixel [3];
pixel r0c0 = {100,0,100};


void setup() {
    FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
    FastLED.setMaxPowerInVoltsAndMilliamps(5, 300);
    FastLED.clear();
    FastLED.show();
    Serial.begin(9600);
}


void loop() {

  leds[2] = CRGB(r0c0[0], r0c0[1],r0c0[2]);
    FastLED.show();
}
