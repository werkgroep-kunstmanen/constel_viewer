/****************************************************
 *
 * Constellation viewer.
 *   header file 
 *
 ****************************************************/
#ifndef CONSTEL_STM32_HDR
#define CONSTEL_STM32_HDR

#define VERSION "2022.1"

// Fixed calibration parameters
#define FIXED_xyoffset -1850
#define FIXED_xyslope  0.07

// Add main() if not compiled with Arduino
#define USE_ARDUINO 1

// SPI pins STM32
#define SPI1_NSS_PIN PA4    // SPI_1 Chip Select pin to OLED display
#define SPI1_DC_PIN  PB1    // data/control pin to OLED display
#define RESET_PIN    PB0    // reset pin to OLED display

// Other pins STM32
#define TEST0 PB12          // use cal. 'FIXED_xyoffset/FIXED_xyslope'
#define TEST1 PB13          // fix calibration
#define TEST2 PB14          // show numeric cal. values
#define OVERL PB15          // overlay on/off
#define C_R   PA8           // constel. red
#define C_G   PA9           // constel. green
#define C_B   PA10          // constel. blue
#define A_R   PA11          // axis red
#define A_G   PA12          // axis green
#define A_B   PA15          // axis blue


// Values OLED
#define INCVAL 2            // increment val. of OLED pixel (
#define XY_SIZE 128         // width/height display
#define LUM_MAX 63          // max. lum. display

#define MIN(a,b) ((a) < (b)? (a) : (b))
#define MAX(a,b) ((a) > (b)? (a) : (b))
#define ABS(a) ((a)<0? (-1*(a)) : (a))


typedef struct calibrate
{
  int x,y;
  int xymin,xymax;
  int xyoffset;
  float xyslope;
} CALIBRATE;

#endif
