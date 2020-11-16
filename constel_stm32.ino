/****************************************************
 *
 * Constellation viewer.
 *   Main part. 
 *
 ****************************************************/
#include "constel_stm32.h"

void print_start()
{
  clear_displ();
  str2oled(0,15,0xff0,(char *)"Constel. Viewer");
  str2oled(0,13,0xff0,(char *)"Version=%s",VERSION);
  str2oled(0, 9,0xfff,(char *)"werkgroep");
  str2oled(0, 7,0xfff,(char *)"Kunstmanen");
  delay(5000);
}

void setup() 
{
  setup_spi();
  setup_oled();
  setup_iq_adc();
  setup_io();
  print_start();
}

void loop()
{
  do_constel();
}

#if USE_ARDUINO == 0
int main(void)
{
  setup();
  while (1)
  {
    loop();
  }
}
#endif
