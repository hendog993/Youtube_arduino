/* Shift register files */
typedef struct Shift_Register_t
{
    const uint8_t SER;
    const uint8_t RCLK;
    const uint8_t SCLK;
} Shift_Register;

/* Seven segment configuration values  */
typedef enum SEVEN_SEGMENT_POWER_CONFIGURATION_t
{
    COMMON_ANODE,
    COMMON_CATHODE
} SEVEN_SEGMENT_POWER_CONFIGURATION;

typedef struct Digit_Pin_Config_t
{
    const uint8_t digit1;
    const uint8_t digit2;
    const uint8_t digit3;
    const uint8_t digit4;
} Digit_Pin_Config;

typedef struct Seven_Seg_Display_t
{
    /* segment and digit enables are set from power config enum 8*/
    uint8_t segmentON;
    uint8_t segmentOFF;
    uint8_t enableDigit;
    uint8_t disableDigit;
    Shift_Register * sr; 
    const Digit_Pin_Config * digitCfg;
        
} Seven_Seg_Display;

/* Rotary Encoder struct  */

 typedef struct Rotary_Encoder_t
 {
    uint32_t counts;
    uint8_t pinA;
    uint8_t pinB;
    uint8_t pinSW;
    uint8_t pulseConfig;
 } Rotary_Encoder;
