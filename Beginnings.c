
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

#define NUM_MS_IN_DAY 86400000
#define NUM_MS_IN_SECOND 1000
#define NUM_MS_IN_MINUTE 60000
#define NUM_MS_IN_HOUR 3600000
#define NUM_MIN_IN_HOUR 60
#define NUM_SEC_IN_MINUTE 60
#define NUM_SEC_IN_HOUR 3600

long long t;
uint64_t start, end;

typedef struct Time_t {
	uint64_t rolloverCounter;
	uint64_t hoursCounter;
	uint64_t minutesCounter;
	uint64_t secondsCounter;
} Time_t;

/* typedef struct Time_t {
	uint8_t rolloverCounter;
	uint8_t hoursCounter;
	uint16_t minutesCounter;
	uint32_t secondsCounter;
} Time_t;*/

// Function prototypes
int32_t updateMasterTimer(Time_t* masterTimePtr, long long time1);
int32_t createMasterTimerPointer(Time_t* masterTimerPointer);
int32_t printMasterTimerContents(Time_t* masterTimePtr);

int32_t createMasterTimerPointer(Time_t* masterTimerPointer) {
	masterTimerPointer->rolloverCounter = 0;
	masterTimerPointer->minutesCounter = 0;
	masterTimerPointer->hoursCounter = 0;
	masterTimerPointer->secondsCounter = 0;
	return 1;
}

int32_t updateMasterTimer(Time_t* masterTimePtr, long long time1) {
	// Converts milliseconds into seconds, and the appropriate time values.
	// Casts the types to match the correct value. 
	masterTimePtr->rolloverCounter =  (time1 / NUM_MS_IN_DAY ) ;
	masterTimePtr->hoursCounter    =  (  (time1 - masterTimePtr->rolloverCounter * NUM_MS_IN_DAY ) / ( NUM_MS_IN_HOUR  ) );
	masterTimePtr->minutesCounter  =  ( ((time1 - masterTimePtr->rolloverCounter * NUM_MS_IN_DAY ) / ( NUM_MS_IN_MINUTE ) ) - ( masterTimePtr->hoursCounter )*NUM_MIN_IN_HOUR );
	masterTimePtr->secondsCounter  =  ( ((time1 - masterTimePtr->rolloverCounter * NUM_MS_IN_DAY ) / ( NUM_MS_IN_SECOND ) ) - ( masterTimePtr->hoursCounter )*NUM_SEC_IN_HOUR - ( masterTimePtr->minutesCounter*NUM_SEC_IN_MINUTE ));
	return 1;
}

int32_t printMasterTimerContents(Time_t* masterTimePtr) {
	printf(" Time Rollover: %llu   Seconds Counter: %llu      Minutes Counter: %llu      Hours Coutner %llu \n ", 
		masterTimePtr->rolloverCounter, masterTimePtr->secondsCounter,	 masterTimePtr->minutesCounter, masterTimePtr->hoursCounter);
	return 1;
}

int32_t potentiometer_adjust_background_color(int pot_input) {

	// Pot input ranges from 0-1024. Make the background color scalable RGB. 
	// Rainbow: violet blue green yellow orange red 
	/*
	violet: 255 0 255
	blue    0   0 255
	green   0  255 0
	yellow 255 255 0 
	orange 255  165  0
	red    255   0   0
	Have the time colors white. 

	TODO Design new patterns. 
	TODO: make clock only write/refresh time when something changes. No point in constantly refreshing everything all the time. 

	
	
	
	
	*/






}



int main()
{
	Time_t* masterTimer;
	start = clock();
	createMasterTimerPointer(&masterTimer);
	
	while (1) {
		end = clock();
		t = (end - start); // milli seconds, long long 64 bit type. 
		updateMasterTimer(&masterTimer, t);
		printf("%llu", t);
		printMasterTimerContents(&masterTimer);
	}
}

