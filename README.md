 Constellation viewer.
 ---------------------
 This is software to create a constellation viewer using:
   . STM32_F103 Blue Pill board 
   . 128x128 OLED display with SPI interface
 Luminance variations are used to get a more attractive, 'scope-like' picture.
 
 Compile/upload environment.
 ---------------------------
 Asuming you have already an Arduino environment, you need to add stm32-libs.
 See:
  
   https://wiki.stm32duino.com/index.php?title=Installation
 Libs are found here:
   https://github.com/rogerclarkmelbourne/Arduino_STM32/archive/master.zip

 Unzip at right location; in Arduino, select:
   Board: Geneic STM32F103C series
   Upload method: STLink
 (detailed instructions to add)
 Now the Arduino-environment is ready to process and upload stm32 software.
 
 ===========================================================================
 
 Downloading, programming
 ------------------------
 Currently programming must be done using Arduino-environment. 
 With a few changes the stm32 workbench could also be used (not tested yet).
 Note that installing this workbench is more difficult compared to Arduino.
 (See above, "Compile/upload environment".)

 Steps to do:
 1. In your browser, go to: 
      https://github.com/werkgroep-kunstmanen/constel_viewer
    Click on the green "Clone or download" (right-top).
    Choose "Download zip". 

 2. Unzip the file; note where your files are placed!
      Files will be in a subfolder called 'constel_viewer-master'.

 3. Create in this folder a new subfolder called: (exactly this name!)
      constel_stm32
 
 4. Move all files in constel_viewer-master to this new subfolder.
      (Note: So all .ino and .h files.)

 5. Start Arduino, do 'File->Open'. Browse to the 'constel_stm32' subfolder.
 
 6. Choose constel_stm32.ino.
      NOTE! Arduino should NOT(!) ask to create a subfolder 'constel_stm32'
            because you are already in that subfolder!

 7. Compile and upload the usual way.

===========================================================================

 Hardware.
 ---------
 Clocks:
 By default, clock settings are: (LeafLabs-style board)
   PLLMUL=7 = *9 ==>  9*8 = 72 MHz (cannot be changed after reset!)
   ADCPRE=2 = /6 ==> 72/6 = 12 MHz (cannot be changed?)

 Analog inputs: Depending on inputs PB13/PB12 offset and range are automatically 
 adapted to the input signals, so the constellation fits to the OLED display.
 If this gives too much "wobbling" the offset and range can be fixed (see PB13/PB12 inputs); 
 in that case potmeters are needed at the analog inputs to manually adjust offset and range.
  

 Pinning:
    Analog inputs:
      PA0    ADC I input
      PA1    ADC Q input
 
    OLED connections:
      CPU    OLED
      -----------------------------
      PA5    SCL (SPI clock)
      PA7    SDA (SPI data output)
      PA4    CS  (SPI chip select)
      PB1    DC  (data/control)
      PB0    RES (reset)
  
    Misc. settings: (note: open='1', connected to GND=0)
      PB13	1: use scaling parameters as determined by PB12
      		0: fixed scaling (see constel_stm32.h)

      PB12	1: continuous calculated scaling parameters
      		0: fix scaling to last calculated values
 
      PB14	1: show constellation diagram
      		0: show scaling parameters

      PB15	1: don't add overlay
      		0: add overlay (cross) to constellation diagram
 
      PA8	0: red off
      PA9	0: green off
      PA10	0: blue off

      PA11	0: overlay red off
      PA12	0: overlay green off
      PA15	0: overlay blue off
