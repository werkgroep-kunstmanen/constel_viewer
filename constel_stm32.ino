/****************************************************
 *
 * Constellation viewer.
 *   Main part. 
 *
 ****************************************************/
#ifndef CONSTEL_STM32_HDR
#include "constel_stm32.h"
#endif

void setup() 
{
  setup_spi();
  setup_oled();
  setup_iq_adc();
  setup_io();
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
