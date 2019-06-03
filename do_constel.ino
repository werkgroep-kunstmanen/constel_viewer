/****************************************************
 *
 * Constellation viewer.
 *   Loop-function 
 *
 ****************************************************/

#define EOC_BIT 0x02
#define SWSTART_BIT 0x00400000

#ifndef CONSTEL_STM32_HDR
#include "constel_stm32.h"
#endif

// Define  extra pins pins for trying/debugging. May be added to do_constel; will just run one time.
void setup_io()
{
  static int done;
  if (done) return;
  
  pinMode(TEST0, INPUT_PULLUP); // '0': use calibration defined with FIXED_...
  pinMode(TEST1, INPUT_PULLUP); // '0': fix calibration to last value

  pinMode(TEST2, INPUT_PULLUP); // '0': show numeric cal. values
  
  // Next is to change colour of the constellation diagram.
  pinMode(RGB_R, INPUT_PULLUP); // '0': Suppress red
  pinMode(RGB_G, INPUT_PULLUP); // '0': Suppress green
  pinMode(RGB_B, INPUT_PULLUP); // '0': Suppress blue
  done=1;
}

// The loop function
// test(1-0)	do_cal	freeze_cal
// 3		true	false		cont. calibrate
// 1		true	true		fixed cal. params
// 2		false	false		no calibration, predefined offset/slope
// 0		false	true		calibration, predefined offset/slope

void do_calibrate(CALIBRATE *calxy)
{
  calxy->x=((calxy->x)+calxy->xyoffset)*calxy->xyslope;
  calxy->y=((calxy->y)+calxy->xyoffset)*calxy->xyslope;
}

void do_constel()
{
  static CALIBRATE calxy;
  int x,y;
  int integrlen=8192;
  int incval=INCVAL;
  bool do_cal=true;        // true: continuous calibration of X/Y to fit to display; false: fixed calibration
  bool freeze_cal=false;   // true: freeze current calibration
  bool show_cal=false;     // show calibration parameters on display
  bool cal_rdy=false;

  static bool clear=true;
  int rgb=0x0;

  if (digitalRead(TEST0)) do_cal=true;      else do_cal=false;     // dynamic calibration or fixed
  if (digitalRead(TEST1)) freeze_cal=false; else freeze_cal=true;  // freeze calibration
  if (digitalRead(TEST2)) show_cal=false;   else show_cal=true;

  if (digitalRead(RGB_R)) rgb|=0x4;
  if (digitalRead(RGB_G)) rgb|=0x2;
  if (digitalRead(RGB_B)) rgb|=0x1;


  (*ADC1_CR2) |= SWSTART_BIT;   // take new samples
  while (!(*ADC1_SR)&EOC_BIT);  // wait until EOC is set

  x=*ADC1_DR;                   // read ADC1
  y=*ADC2_DR;                   // read ADC2

  calxy.x=x;
  calxy.y=y;

  if (do_cal)
  {
    cal_rdy=calc_cal_xy(&calxy,freeze_cal);
  }
  else
  {
    calxy.xyoffset=FIXED_xyoffset;
    calxy.xyslope =FIXED_xyslope;
    cal_rdy=true;
  }
  
  if (cal_rdy)
  {                             // new calculated calibration
    if (show_cal)
    {
      if (clear)                // clear full display
      {
        clear_displ();
        clear=false;
      }
      str2oled(0,15,"Version=%s",VERSION);
      str2oled(0,13,"%s",COPYRIGHT);
      str2oled(1,7,"o=%d   ",calxy.xyoffset);
      str2oled(1,5,"s=%f   ",calxy.xyslope);
      str2oled(1,3,"xymin=%d  ",calxy.xymin);
      str2oled(1,1,"xyman=%d  ",calxy.xymax);
    }
    else
    {
      clear=true;             // prepare clear for next time 
    }
  }

  do_calibrate(&calxy);       // size constellation to screen

  // only show constel. diagram if calibration data not shown.
  if (!show_cal)
  {
    coll_pix2oled(&calxy, integrlen, incval, rgb);
  }
}
