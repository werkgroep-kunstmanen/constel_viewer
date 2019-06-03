/****************************************************
 *
 * Constellation viewer.
 *   Translation of I/Q voltage to X/Y position at OLED
 *
 ****************************************************/
#include <malloc.h>

#ifndef CONSTEL_STM32_HDR
#include "constel_stm32.h"
#endif

// Clip to max. OLED resolution
int clip(int n)
{
  n=MIN(n,(XY_SIZE-1));
  n=MAX(n,0);
  return n; 
}

// Auto calibrate X and Y
//   do_cal    : calibrate
//   freeze_cal: freeze offset/slope
//   do_dbg: show cal. numbers
//   sldrmpl: only adapt slope/offset if slope changes more than this value.
// Note: doesn't work properly (yet).
//
#define CNTMAX 10000
bool calc_cal_xy(CALIBRATE *calxy,bool freeze_cal)
{
  static int xymin,xymax;
  static int cnt;
  static int xyoffset,xyoffset_use=0;
  static float xyslope=0.,xyslope_use=1.;

  xymin=MIN(xymin,(calxy->x));
  xymin=MIN(xymin,(calxy->y));

  xymax=MAX(xymax,(calxy->x));
  xymax=MAX(xymax,(calxy->y));

  if (xymax<=xymin) xymax=xymin+1;
  cnt++;

  if ((cnt>=CNTMAX)  || (xyslope==0.))
  {
    if ((!freeze_cal)  || (xyslope==0.))
    {
      xyoffset=-1*xymin;
      xyslope=(float)(XY_SIZE-1)/(float)(xymax-xymin);
      xyoffset_use=xyoffset;
      xyslope_use=xyslope;
    }
    calxy->xymin=xymin;
    calxy->xymax=xymax;
    calxy->xyoffset=xyoffset_use;
    calxy->xyslope=xyslope_use;
    cnt=0;
    xymin=8192; xymax=0;
    return true;
  }
  return false;
}

// Collect/integrate (x,y) pairs
// After integration: copy array content to OLED
// Max. luminance is 31 (# bits for green: 5) (see LUM_MAX in header file)
// Resol. 64x64 (128x128 too big for stm32f103)

#define SARR 64                    // size mem: SARR x SARR (max. 128)
#define DDSARR (XY_SIZE/SARR)      // size dot

// Pixel at (x,y)
// integrlen=# integration steps
// incval = slope integration
// note: LUMMAX reached after LUMMAX/incval steps.

// Copy content xyarr to OLED
static void xyarr2oled(unsigned char *xyarr,int rgb)
{
  int xx,yy,xxx,yyy;
  unsigned char *p;
  char www[DDSARR*2];
  unsigned char word[2],r,g,b,lum;
  
  write_cmdbyt2(0x15,0,XY_SIZE-1);               // set OLED start/end X
  write_cmdbyt2(0x75,0,XY_SIZE-1);               // set OLED start/end Y
  write_cmd(0x5C);                               //
  digitalWrite(SPI1_NSS_PIN, LOW);               // set CSN active for SPI transm.

  for (yy=0; yy<SARR; yy++)                      // mem Y dir.
  {
    for (yyy=0; yyy<DDSARR; yyy++)               // # y per dot; repeat or DDSARR lines
    {
      for (xx=0; xx<SARR; xx++)                  // mem X dir.; one line
      {  
        p=xyarr+yy*SARR+xx;                      // get value from mem
        lum=*p;

        r=lum>>1;                                // red   value: 0...15 (lum: 0...31)
        g=lum>>0;                                // green value: 0...31
        b=lum>>1;                                // blue  value: 0...15
        if (!(rgb&4)) r=0;
        if (!(rgb&2)) g=0;
        if (!(rgb&1)) b=0;
        word[0]=((b<<3)&0xf8) + ((g>>3)&0x0f);   // set LSByte word
        word[1]=((g<<5)&0xe0) + ((r&0x1f));      // set MSByte word

        for (xxx=0; xxx<DDSARR; xxx++)           // copy lum for one dot-line in array
        {
          www[xxx*2]=word[0];
          www[xxx*2+1]=word[1];
        }
        SPI.write(www,DDSARR*2);                 // transmit 1 line of 1 dot to OLED
      }
    }
  }
  digitalWrite(SPI1_NSS_PIN, HIGH);              // set CSN inactive for SPI transm.
}

// Collect/integrate pixels (pixel at calxy->x, calxy->y) and write to OLED after integration
void coll_pix2oled(CALIBRATE *calxy,int integrlen,int incval,int rgb)
{
  static unsigned char *xyarr,*p;
  static int integr;
  int x,y;
  x=calxy->x;
  y=calxy->y;

  // allocate mem for SARR x SARR pixels
  if (xyarr==NULL) xyarr=(unsigned char *)malloc(SARR*SARR);

  // size x,y to mem-size
  x/=DDSARR;
  y/=DDSARR;

  if ((x>=0) && (x<SARR) && (y>=0) && (y<SARR))
  {
    // pointer to mem for pos. (x,y)
    p=xyarr+y*SARR+x;

    // increment pos. (x,y), clip to XY_SIZE
    if (*p >= (LUM_MAX-incval))
      *p=LUM_MAX;
    else
      (*p)+=incval;
  }

  integr++;

  // write mem to display afer integration time
  if (integr>=integrlen)
  {
    xyarr2oled(xyarr,rgb);
   // reset integration and array
    integr=0;
    memset(xyarr,0,SARR*SARR);                     // reset array for next integration
  }
}

