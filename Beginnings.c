
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

typedef unsigned char byte;

long long t;
time_t start, end;

typedef struct Time_t {
	uint8_t rolloverCounter;
	uint8_t hoursCounter;
	uint16_t minutesCounter;
	uint32_t secondsCounter;
} Time_t;


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
	masterTimePtr->rolloverCounter = (uint8_t)  (time1 / NUM_MS_IN_DAY ) ;
	masterTimePtr->hoursCounter    = (uint8_t)  (  (time1 - masterTimePtr->rolloverCounter * NUM_MS_IN_DAY ) / ( NUM_MS_IN_HOUR  ) );
	masterTimePtr->minutesCounter  = (uint16_t) ( ((time1 - masterTimePtr->rolloverCounter * NUM_MS_IN_DAY ) / ( NUM_MS_IN_MINUTE ) ) - ( masterTimePtr->hoursCounter )*NUM_MIN_IN_HOUR );
	masterTimePtr->secondsCounter  = (uint32_t) ( ((time1 - masterTimePtr->rolloverCounter * NUM_MS_IN_DAY ) / ( NUM_MS_IN_SECOND ) ) - ( masterTimePtr->hoursCounter )*NUM_SEC_IN_HOUR - ( masterTimePtr->minutesCounter*NUM_SEC_IN_MINUTE ));
	return 1;
}

int32_t printMasterTimerContents(Time_t* masterTimePtr) {
	printf(" Time Rollover: %u   Seconds Counter: %llu      Minutes Counter: %u      Hours Coutner %u \n ", 
		masterTimePtr->rolloverCounter, masterTimePtr->secondsCounter,	 masterTimePtr->minutesCounter, masterTimePtr->hoursCounter);
	return 1;
}

int main()
{
	Time_t* masterTimer;
	start = clock();
	createMasterTimerPointer(&masterTimer);
	while (1) {
		end = clock();
		t = (end - start)* 10; // milli seconds, long long 64 bit type. 
		updateMasterTimer(&masterTimer, t);
		printf("%llu", t);
		printMasterTimerContents(&masterTimer);
	}
}

