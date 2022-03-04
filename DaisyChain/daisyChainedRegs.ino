#include "types.h"

/*
 * init function
 * writeByte
 */

void SR595N_init( Shift_Register_595N * const sr )
{
    pinMode( sr->SER, OUTPUT);
    pinMode( sr->RCLK, OUTPUT);
    pinMode( sr->SCLK, OUTPUT);
}

/* Byte value, and write LSB to data pin , pulse SCLK, shift value by >> 1, repeat 8x. Pulse OUT REG
 * 0b11011011
 */
void SR595N_writeVal ( const Shift_Register_595N * const sr , uint16_t val )
{
    uint8_t counter;
    byte shiftVal;

    for ( counter = 0; counter < NUM_BITS_IN_2BY ; counter++ )
    {
        shiftVal = ( val & 0x01 );
        digitalWrite ( sr->SER, shiftVal );
        digitalWrite ( sr->SCLK, HIGH);
        digitalWrite ( sr->SCLK, LOW);
        val = val >> 1;
    }
    digitalWrite ( sr->RCLK, HIGH);
    digitalWrite ( sr->RCLK, LOW);
}

Shift_Register_595N sr1 = 
{
    .SER = 4,
    .RCLK = 5,
    .SCLK = 6
};

void setup()
{
    SR595N_init ( &sr1 );
    Serial.begin(115200);
}


void shiftPattern( const Shift_Register_595N * const sr  ) 
{
    uint16_t val = 0x01;
    uint8_t counter;

    for ( counter = 0; counter < NUM_BITS_IN_2BY; counter++ )
    {
        SR595N_writeVal (sr, val );
        val = val << 1;
        delay(100);
    }

    val = 0x8000;
    for ( counter = 0; counter < NUM_BITS_IN_2BY; counter++ )
    {
        SR595N_writeVal (sr, val );
        val = val >> 1;
        delay(100);
    }


    
}
void loop()
{
shiftPattern (&sr1);
}
