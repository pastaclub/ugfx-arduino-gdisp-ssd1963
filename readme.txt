SSD1963 driver for ugfx-arduino
Ported / developed by Dennis Bemmann

An example configuration can be found here:
https://github.com/pastaclub/ugfx-ssd1963-config

To install, copy both this repository and the configuration repository as sub-folders into your Arduino library folder. For an example application, just copy the one from ugfx-arduino and change the driver. This configuration assumes the following wiring for TFT->Teensy 3.2: Backlight=3V3, Reset=23, RS=28, WR=27, RD=33, CS=15, DB_0=15, DB_1=22, DB_2=23, DB_3=9, DB_4=10, DB_5=13, DB_6=11, DB_7=12, DB_8=2, DB_9=14, DB_10=7, DB_11=8, DB_12=6, DB_13=20, DB_14=21, DB_15=5

---

SSD1963 driver modified to handle Displaytech INTXXX displays, which self-initialise.
To use this mode, add:
#define GDISP_SSD1963_NO_INIT     GFXON
...either in the board-specific header file, or in gfxconf.h
