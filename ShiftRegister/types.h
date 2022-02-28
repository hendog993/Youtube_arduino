#define NUM_BITS_IN_BYTE 8

typedef struct Shift_Register_t_595N_t
{
    byte SER;
    byte RCLK;
    byte SCLK;
} Shift_Register_595N;

typedef struct Shift_Register_165_t
{
    byte CLK;
    byte CLK_INH;
    byte QH;
    byte SHLD;
}Shift_Register_165;
