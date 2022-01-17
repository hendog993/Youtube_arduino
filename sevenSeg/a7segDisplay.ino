#define MAX_VALUE_TO_WRITE 9999 
#define MAX_POSSIBLE_VALUES_TO_WRITE 10
#define NUM_DIGITS 4 
// Listen MSB on the left. These are shfiteed
static uint8_t digitArray[4]; // this is populated based on configuration data to make the digit iterable. 

static const uint8_t writeTable[MAX_POSSIBLE_VALUES_TO_WRITE] = 
{
    0b11111100, // zero 
    0b01100000, // one 
    0b11011010, // two  
    0b11110010, // three
    0b01100110, // four 
    0b10110110, // five 
    0b10111110, // six 
    0b11100000, // seven
    0b11111110, // eight 
    0b11100110, // nine 
}; // set these up with 1 as active high. follow standard convention then set later as configuration 

void InitializeSevenSegmentDisplay ( Seven_Seg_Display * disp, 
                                    SEVEN_SEGMENT_POWER_CONFIGURATION pwrCfg,
                                    Shift_Register * shiftReg, 
                                    Digit_Pin_Config * digitConfig)
{
    // Parameter checks 
    if ((NULL == disp)||
        (NULL == shiftReg) ||
        (NULL == digitConfig))
    {
        return; // Invalid params 
    }
    /* Common anode is active LOW, common cathode is active HIGH  */
    disp->segmentON = ( pwrCfg == COMMON_ANODE ) ? 0: 1;
    disp->segmentOFF = ( pwrCfg == COMMON_ANODE ) ? 1: 0;

    /* Common anode requires digits actie HIGH. Cathode requires digits active LOW */
    disp->enableDigit = ( pwrCfg == COMMON_ANODE ) ? 1: 0;
    disp->disableDigit = ( pwrCfg == COMMON_ANODE ) ? 0: 1;

    /* Setup shift register with display */ 
    disp->sr = shiftReg;
    disp->digitCfg = digitConfig;
    
    // TODO run parameter checks on these pins, ensure they aren't jank.
    
    pinMode ( shiftReg->SCLK, OUTPUT);
    pinMode ( shiftReg->SER, OUTPUT);
    pinMode ( shiftReg->RCLK, OUTPUT);

    pinMode ( digitConfig->digit1, OUTPUT);
    pinMode ( digitConfig->digit2, OUTPUT);
    pinMode ( digitConfig->digit3, OUTPUT);
    pinMode ( digitConfig->digit4, OUTPUT);

    /* Setup iterable array for digit configs */
    digitArray[0] = digitConfig->digit1;
    digitArray[1] = digitConfig->digit2;
    digitArray[2] = digitConfig->digit3;
    digitArray[3] = digitConfig->digit4;
}

/* Primary write function that hands all other function calls  */
// TODO implement floating point and decimal point 
bool WriteSSNumber( Seven_Seg_Display *const disp, 
                        const float value)
{
    uint16_t tempValue = uint16_t (value + 0.5) ; // Create a local copy of the input float value 
    
    if (( NULL == disp ) || 
       (tempValue > MAX_VALUE_TO_WRITE ) || 
       ( tempValue < 0))
    {
        return false; // Error, invalid value  
    }

    // Decompose floating point number 
    uint8_t numDigitsInNumber = log10(tempValue) + 1 ; // Digit cant be zero because func would have exited 
    uint8_t writeArray[NUM_DIGITS] = {0,0,0,0}; // Must zero the array upon restart - verify this is required. 
    uint8_t writeIndex = 3; // Start the write index at the end of the write array. 
    
    while ( numDigitsInNumber > 0)
    {
        writeArray[writeIndex] = ( tempValue  %10 );
        tempValue = tempValue / 10;
        writeIndex--;
        numDigitsInNumber--;
    }
    WriteSevenSegmentValue ( disp, writeArray );
}

/* Primary segment digit write. Assumes the value has been translated into a valid write array */
static void WriteSevenSegmentValue(Seven_Seg_Display *const disp,
                                    const uint8_t * const writeArray)
{
    // todo add checks 
    uint8_t digitCounter;
    uint16_t delayVal = 1;
    uint8_t sval;
    /* For every digit in the digit array (4) */
    for ( digitCounter = 0; digitCounter < NUM_DIGITS; digitCounter++)
    {
        /* Extract the value from the write array corresponding to the segment decoded value */ 
        sval = writeTable[writeArray[digitCounter]];  // nth digit from input array. Extracts value from global write table 
        for (int counter = 0; counter < 8; counter++ )
        {
            shiftValueOut ( disp->sr, (sval & 0x1 ) ? disp->segmentON :disp->segmentOFF );
            sval = sval >> 1;
        }
        /* Pulse the refresh clock on the shift register */
        digitalWrite(disp->sr->RCLK, HIGH);
        digitalWrite(disp->sr->RCLK, LOW);
        /* Enable then disable the digit after a specified delay */
        digitalWrite (digitArray[digitCounter], disp->enableDigit);
        delay(delayVal);
        digitalWrite (digitArray[digitCounter], disp->disableDigit);
    }
}


/* Shifts a single bit out to the shift register. Only real "shift register" function. */
/* Can eventually implement further functionality based on SR. But this is all we need right now  */
static inline void shiftValueOut( const Shift_Register *const  sr, const uint8_t value )
{
    digitalWrite(sr->SER, value);
    digitalWrite(sr->SCLK, HIGH);
    digitalWrite(sr->SCLK, LOW);
}
