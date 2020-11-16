/****************************************************
 *
 * Constellation viewer.
 *   Add text
 *
 ****************************************************/
#define UPSIDE_DOWN false
/*************************************
 * ASCII bitmap for draw_rgbstring
 *************************************/
static char ta[][8]={ {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
                      {0x30,0x78,0x78,0x78,0x30,0x00,0x30,0x00},
                      {0x6c,0x6c,0x6c,0x00,0x00,0x00,0x00,0x00},
                      {0x6c,0x6c,0xfe,0x6c,0xfe,0x6c,0x6c,0x00},
                      {0x30,0x7c,0xc0,0x78,0x0c,0xf8,0x30,0x00},
                      {0x00,0xc6,0xcc,0x18,0x30,0x66,0xc6,0x00},
                      {0x38,0x6c,0x38,0x76,0xdc,0xcc,0x76,0x00},
                      {0x60,0x60,0xc0,0x00,0x00,0x00,0x00,0x00},
                      {0x18,0x30,0x60,0x60,0x60,0x30,0x18,0x00},
                      {0x60,0x30,0x18,0x18,0x18,0x30,0x60,0x00},
                      {0x00,0x66,0x3c,0xfe,0x3c,0x66,0x00,0x00},
                      {0x00,0x30,0x30,0xfc,0x30,0x30,0x00,0x00},
                      {0x00,0x00,0x00,0x00,0x00,0x30,0x30,0x60},
                      {0x00,0x00,0x00,0xfc,0x00,0x00,0x00,0x00},
                      {0x00,0x00,0x00,0x00,0x00,0x30,0x30,0x00},
                      {0x06,0x0c,0x18,0x30,0x60,0xc0,0x80,0x00},
                      {0x7c,0xc6,0xc6,0xc6,0xc6,0xc6,0x7c,0x00},
                      {0x30,0x70,0x30,0x30,0x30,0x30,0xfc,0x00},
                      {0x78,0xcc,0x0c,0x38,0x60,0xcc,0xfc,0x00},
                      {0x78,0xcc,0x0c,0x38,0x0c,0xcc,0x78,0x00}, 
                      {0x1c,0x3c,0x6c,0xcc,0xfe,0x0c,0x1e,0x00},
                      {0xfc,0xc0,0xf8,0x0c,0x0c,0xcc,0x78,0x00},
                      {0x38,0x60,0xc0,0xf8,0xcc,0xcc,0x78,0x00},
                      {0xfc,0xcc,0x0c,0x18,0x30,0x30,0x30,0x00},
                      {0x78,0xcc,0xcc,0x78,0xcc,0xcc,0x78,0x00},
                      {0x78,0xcc,0xcc,0x7c,0x0c,0x18,0x70,0x00},
                      {0x00,0x30,0x30,0x00,0x00,0x30,0x30,0x00},
                      {0x00,0x30,0x30,0x00,0x00,0x30,0x30,0x60},
                      {0x18,0x30,0x60,0xc0,0x60,0x30,0x18,0x00},
                      {0x00,0x00,0xfc,0x00,0x00,0xfc,0x00,0x00},
                      {0x60,0x30,0x18,0x0c,0x18,0x30,0x60,0x00},
                      {0x78,0xcc,0x0c,0x18,0x30,0x00,0x30,0x00},
                      {0x7c,0xc6,0xde,0xde,0xde,0xc0,0x78,0x00},
                      {0x38,0x6c,0xc6,0xc6,0xfe,0xc6,0xc6,0x00},
                      {0xfc,0xc6,0xc6,0xfc,0xc6,0xc6,0xfc,0x00},
                      {0x7c,0xc6,0xc6,0xc0,0xc0,0xc6,0x7c,0x00}, 
                      {0xf8,0xcc,0xc6,0xc6,0xc6,0xcc,0xf8,0x00},
                      {0xfe,0xc0,0xc0,0xfc,0xc0,0xc0,0xfe,0x00},
                      {0xfe,0xc0,0xc0,0xfc,0xc0,0xc0,0xc0,0x00},
                      {0x7c,0xc6,0xc0,0xce,0xc6,0xc6,0x7e,0x00},
                      {0xc6,0xc6,0xc6,0xfe,0xc6,0xc6,0xc6,0x00},
                      {0x78,0x30,0x30,0x30,0x30,0x30,0x78,0x00},
                      {0x1e,0x06,0x06,0x06,0xc6,0xc6,0x7c,0x00},
                      {0xc6,0xcc,0xd8,0xf0,0xd8,0xcc,0xc6,0x00},
                      {0xc0,0xc0,0xc0,0xc0,0xc0,0xc0,0xfe,0x00},
                      {0xc6,0xee,0xfe,0xd6,0xc6,0xc6,0xc6,0x00},
                      {0xc6,0xe6,0xf6,0xde,0xce,0xc6,0xc6,0x00},
                      {0x7c,0xc6,0xc6,0xc6,0xc6,0xc6,0x7c,0x00},
                      {0xfc,0xc6,0xc6,0xfc,0xc0,0xc0,0xc0,0x00},
                      {0x7c,0xc6,0xc6,0xc6,0xc6,0xc6,0x7c,0x06},
                      {0xfc,0xc6,0xc6,0xfc,0xc6,0xc6,0xc6,0x00},
                      {0x78,0xcc,0x60,0x30,0x18,0xcc,0x78,0x00},
                      {0xfc,0x30,0x30,0x30,0x30,0x30,0x30,0x00},
                      {0xc6,0xc6,0xc6,0xc6,0xc6,0xc6,0x7c,0x00},
                      {0xc6,0xc6,0xc6,0xc6,0xc6,0x6c,0x38,0x00},
                      {0xc6,0xc6,0xc6,0xd6,0xfe,0xee,0xc6,0x00}, 
                      {0xc6,0xc6,0x6c,0x38,0x6c,0xc6,0xc6,0x00},
                      {0xc2,0xc2,0x66,0x3c,0x18,0x18,0x18,0x00},
                      {0xfe,0x0c,0x18,0x30,0x60,0xc0,0xfe,0x00},
                      {0x3c,0x30,0x30,0x30,0x30,0x30,0x3c,0x00},
                      {0xc0,0x60,0x30,0x18,0x0c,0x06,0x02,0x00},
                      {0x3c,0x0c,0x0c,0x0c,0x0c,0x0c,0x3c,0x00},
                      {0x00,0x38,0x6c,0xc6,0x00,0x00,0x00,0x00},
                      {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xfe},
                      {0x30,0x30,0x18,0x00,0x00,0x00,0x00,0x00},
                      {0x00,0x00,0x7c,0x06,0x7e,0xc6,0x7e,0x00},
                      {0xc0,0xc0,0xfc,0xc6,0xc6,0xe6,0xdc,0x00},
                      {0x00,0x00,0x7c,0xc6,0xc0,0xc0,0x7e,0x00},
                      {0x06,0x06,0x7e,0xc6,0xc6,0xce,0x76,0x00},
                      {0x00,0x00,0x7c,0xc6,0xfe,0xc0,0x7e,0x00},
                      {0x1e,0x30,0x7c,0x30,0x30,0x30,0x30,0x00},
                      {0x00,0x00,0x7e,0xc6,0xce,0x76,0x06,0x7c},
                      {0xc0,0xc0,0xfc,0xc6,0xc6,0xc6,0xc6,0x00},
                      {0x18,0x00,0x38,0x18,0x18,0x18,0x3c,0x00},
                      {0x18,0x00,0x38,0x18,0x18,0x18,0x18,0xf0},
                      {0xc0,0xc0,0xcc,0xd8,0xf0,0xd8,0xcc,0x00},
                      {0x38,0x18,0x18,0x18,0x18,0x18,0x3c,0x00},
                      {0x00,0x00,0xcc,0xfe,0xd6,0xc6,0xc6,0x00},
                      {0x00,0x00,0xfc,0xc6,0xc6,0xc6,0xc6,0x00},
                      {0x00,0x00,0x7c,0xc6,0xc6,0xc6,0x7c,0x00},
                      {0x00,0x00,0xfc,0xc6,0xc6,0xe6,0xdc,0xc0},
                      {0x00,0x00,0x7e,0xc6,0xc6,0xce,0x76,0x06},
                      {0x00,0x00,0x6e,0x70,0x60,0x60,0x60,0x00},
                      {0x00,0x00,0x7c,0xc0,0x7c,0x06,0xfc,0x00},
                      {0x30,0x30,0x7c,0x30,0x30,0x30,0x1c,0x00},
                      {0x00,0x00,0xc6,0xc6,0xc6,0xc6,0x7e,0x00},
                      {0x00,0x00,0xc6,0xc6,0xc6,0x6c,0x38,0x00},
                      {0x00,0x00,0xc6,0xc6,0xd6,0xfe,0x6c,0x00},
                      {0x00,0x00,0xc6,0x6c,0x38,0x6c,0xc6,0x00},
                      {0x00,0x00,0xc6,0xc6,0xce,0x76,0x06,0x7c},
                      {0x00,0x00,0xfc,0x18,0x30,0x60,0xfc,0x00},
                      {0x1c,0x30,0x30,0xe0,0x30,0x30,0x1c,0x00},
                      {0x18,0x18,0x18,0x00,0x18,0x18,0x18,0x00},
                      {0xe0,0x30,0x30,0x1c,0x30,0x30,0xe0,0x00},
                      {0x76,0xdc,0x00,0x00,0x00,0x00,0x00,0x00}
                    };

// Clear display to 'black'
void clear_displ(void)
{
  int n;
  unsigned char wrd[2];
  wrd[0]=wrd[1]=0x00;  
  write_cmdbyt2(0x15,0,127);                   // set OLED start/end X
  write_cmdbyt2(0x75,0,127);                   // set OLED start/end Y
  write_cmd(0x5C);            
  digitalWrite(SPI1_NSS_PIN, LOW);             // set CSN active for SPI transm.
  for (n=0; n<16384; n++) SPI.write(wrd,2);
  digitalWrite(SPI1_NSS_PIN, HIGH);            // set CSN inactive for SPI transm.
}

// convert ASCII string into pixels to set at line 'y'
static void get_strline(char *s,int y,char *l,int slen)
{
  int m,x,n;
  *l=0;
  for (m=0; *s; s++,m++)
  {
    n=(*s)-' '; if (n>95) return;
    if (m*8+8>slen) return;
    for (x=0; x<8; x++)
    {
      if (ta[n][y]&(0x80>>x)) l[x+m*8]=0xff; else l[x+m*8]=0;
    }
  }
}

//   LSByte: word[0]=bbbbbggg
//   MSByte: word[1]=gggrrrrr

static int *rgb2wrd(int rgb)
{
  static int word[2];
  int r,g,b;
  r=(rgb&0xf00)>>7; if (r>1) r|=0x01;
  g=(rgb&0x0f0)>>2; if (g>3) g|=0x03;
  b=(rgb&0x00f)<<1; if (b>1) b|=0x01;
  word[0]=((b<<3)&0xf8) + ((g>>3)&0x07);       // set LSByte word
  word[1]=((g<<5)&0xe0) + ((r&0x1f));          // set MSByte word
  return word;
}

// Add string 'str' at pos. (x,y) on display
static void add_str2arr(int x,int y,int rgb,char *str,bool flip)
{
  char ts[150];
  int fsize,ytxt,i,y0;
  int xstr,ystr;
  int chnkpos;
  int *word;
  char line[128*2];
  fsize=1;
  xstr=strlen(str)*8*fsize;
  ystr=8*fsize;
  word=rgb2wrd(rgb);
  for (y0=0; y0<ystr; y0++)
  {
    int y1=y0;
    if (!flip) y1=ystr-1-y0;
    ytxt=(y1/fsize);
    get_strline(str,ytxt,ts,190);
    for (i=0; i<xstr; i++)
    {
      int i1=i;
      if (flip) i1=xstr-1-i;
      if (ts[i1/fsize])
      {
        line[i*2]  = word[0];//0xff;           // max. white
        line[i*2+1]= word[1];//0xff;
      }
      else
      {
        line[i*2]=0x00;                        // black
        line[i*2+1]=0x00;
      }
    }
    write_cmdbyt2(0x15,x,x+xstr);              // set OLED start/end X               
    write_cmdbyt2(0x75,y+y0,y+y0);             // set OLED start/end Y               
    write_cmd(0x5C);                           //                                    
    digitalWrite(SPI1_NSS_PIN, LOW);           // set CSN active for SPI transm.     
    SPI.write(line,xstr*2);                    // transmit 1 line of 1 dot to OLED    
    digitalWrite(SPI1_NSS_PIN, HIGH);          // set CSN inactive for SPI transm.   
  }
}

#include <stdarg.h>
// Create string from input format and copy to display
void str2oled(int x, int y,int rgb,char *frmt,...)
{
  char xstr[20];
  va_list ap;
  va_start(ap,frmt);
  vsnprintf(xstr,16,frmt,ap);
  
  add_str2arr(x*8,y*8,rgb,xstr,UPSIDE_DOWN); 
}
