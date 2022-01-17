#include "typedefs.h"

/* Function prototypes, move to separate files during pic implementation */ 
void InitializeSevenSegmentDisplay ( Seven_Seg_Display * disp, 
                                    SEVEN_SEGMENT_POWER_CONFIGURATION pwrCfg,
                                    Shift_Register * shiftReg, 
                                    Digit_Pin_Config * digitConfig);
static void convertNumberInputToShiftRegisterValue( Seven_Seg_Display *val);
static void shiftValueOut( Seven_Seg_Display *val  );
bool WriteSSNumber( Seven_Seg_Display *const disp, 
                                const float value);

static const Digit_Pin_Config digit1Cfg = 
{
    .digit1 = 7,
    .digit2 = 4,
    .digit3 = 5,
    .digit4 = 6
};

static const Shift_Register d1SR = 
{
    .SER = 8,
    .RCLK =  9,
    .SCLK = 10
};

uint16_t rotCounter;
uint32_t rotVector;
 
void rotISR()
{
    rotVector = ( rotVector << 2u ) & 0xCu;
    rotVector |= ( digitalRead(2) ) ? 2: 0;
    rotVector |= ( digitalRead(3) ) ? 1: 0;
//    Serial.println(rotVector);
    switch ( rotVector )
    {
    case 15:
        rotCounter++;
        break;
    case 5:
        rotCounter--;
        break;
    }
}

Seven_Seg_Display display1;


void setup()
{
    InitializeSevenSegmentDisplay( &display1, 
                                    COMMON_ANODE,
                                    &d1SR,
                                    &digit1Cfg);
    attachInterrupt( digitalPinToInterrupt(3), rotISR, RISING);
    Serial.begin(115200);
}

void loop()
{
    // Write rotary encoder value 
//    for ( counter = 0; counter < 9999; counter ++ )
//    {
//        WriteSSNumber ( &display1, counter);
//        delay(20);    
//    }

    WriteSSNumber( &display1, rotCounter);
}
