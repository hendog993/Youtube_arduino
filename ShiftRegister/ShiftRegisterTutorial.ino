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

void SR165_init( Shift_Register_165 * const sr )
{
    pinMode(sr->CLK, OUTPUT);
    pinMode(sr->CLK_INH, OUTPUT);
    pinMode(sr->QH, INPUT);
    pinMode(sr->SHLD , OUTPUT);

    // Default states 
    digitalWrite ( sr-> SHLD, HIGH);
    digitalWrite ( sr->CLK_INH, HIGH);
    digitalWrite ( sr->CLK, LOW);
}

/* Byte value, and write LSB to data pin , pulse SCLK, shift value by >> 1, repeat 8x. Pulse OUT REG
 * 0b11011011
 */
void SR595N_writeByte ( const Shift_Register_595N * const sr , byte val )
{
    uint8_t counter;
    byte shiftVal;

    for ( counter = 0; counter < NUM_BITS_IN_BYTE ; counter++ )
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

/* To read a byte, capture all inputs to SR ( 
 * 
 */
void SR165_readByte ( const Shift_Register_165 * const sr,
                      uint8_t * const readVal)
{
    // Pulse SHLD to transfer data inside the SR 
    digitalWrite( sr->SHLD, LOW);
    digitalWrite( sr->SHLD, HIGH);

    // Set CLKINH low, 
    digitalWrite ( sr->CLK_INH, LOW);

    // Loop through SR 8 times to transfer value bit by bit 
    uint8_t counter;
    uint8_t shiftVal = 0x0;
    for ( counter = 0; counter < NUM_BITS_IN_BYTE ; counter++ )
    {
        digitalWrite( sr->CLK, HIGH);
        digitalWrite(sr->CLK, LOW);
        shiftVal |=  ( digitalRead(sr->QH) & 0x01);
        shiftVal = ( shiftVal << 1 ) ;
    }
    digitalWrite (sr->CLK_INH, HIGH);
    *readVal = shiftVal;
}

Shift_Register_595N sr1 = 
{
    .SER = 4,
    .RCLK = 5,
    .SCLK = 6
};

Shift_Register_165 sr2 = 
{
    .CLK = 9,
    .CLK_INH = 8,
    .QH = 10,
    .SHLD = 7
};

void setup()
{
    SR595N_init ( &sr1 );
    SR165_init ( &sr2 );
    Serial.begin(115200);
}

uint8_t readVal = 0;
void loop()
{
    SR595N_writeByte ( &sr1, 0x3);
    SR165_readByte ( &sr2, &readVal);
    Serial.println(readVal);
    delay(100);
}
