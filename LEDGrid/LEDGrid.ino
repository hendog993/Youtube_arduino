/*
 * Project goals:
 * 1. Write images using large format and calculate bytes/data used
 * 2. Write compression algorithm and calculate bytes saved
 * 3. Write decompression algorithm to rewrite original image
 */


/*
 * Progression
 * 1. Get structure format
 * 2. Draw RGB only (255) images
 * 3. Compress and decompress properly.
 * 4. Calculate bytes saved 
 */


/*Compression format
 * 6 rows of 10 values 
 * per 
 * per row: [4 bit number (max is 10) 4 bit map to color: RED BLUE GREEN or OFF] 
 * 
 */


#include <FastLED.h>
#include <stdint.h>

#define LED_PIN 2
#define NUM_LEDS 60
CRGB leds[NUM_LEDS];
#define RESOLUTION_X 10
#define RESOLUTION_Y 6

// Image format: should simply be an array of bytes.
// 60 pixels, 3 RGB values, 180 bytes total. 
typedef byte image[180];

// Single row format test. 

image pic1 = {233,243,101, 23,10,56, 43,65,700, 63,12,90, 12,12,12, 44,44,44, 101,206, 43, 12,90, 72, 12,12,12,51,55,90};
image * picptr = &pic1;


byte GetLengthOfImage (image imgPtr ) {

  return sizeof(imgPtr) / sizeof(imgPtr[0]);
  
}


int32_t imgCheckFormatValid(image  imagePointer ) 
{
  
  int32_t s32_returnval = 1;
  byte lengthOfArray = GetLengthOfImage(imagePointer);
  Serial.println(lengthOfArray);
  if (imagePointer == NULL || 
      lengthOfArray > 180
    )
  {
      s32_returnval = 0;
      return s32_returnval;
  }
  
  // Iterate through and check if any value is greater than 255. If yes, exit routine and return error. 
  for (int i = 0; i < lengthOfArray ; i++) {
    if ( imagePointer[i] > 255 ) {
      s32_returnval = 0;
      return s32_returnval;
    }
  } 
  
  return s32_returnval;
}


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

void GetPtrAndIncBufferPtr() {

  
}


int32_t WriteImage ( image  imgPtr )
{
  int32_t s32_returnval;
  s32_returnval &= imgCheckFormatValid(imgPtr);
  
}

void setup() {
    FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
    FastLED.setMaxPowerInVoltsAndMilliamps(5, 300);
    FastLED.clear();
    FastLED.show();
    Serial.begin(9600);
}


void loop() {
  
  int32_t val = imgCheckFormatValid(pic1);
}
