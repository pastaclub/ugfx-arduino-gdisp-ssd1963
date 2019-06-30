/*
 * This file is subject to the terms of the GFX License. If a copy of
 * the license was not distributed with this file, you can obtain one at:
 *
 *              http://ugfx.io/license.html
 */

#ifndef _GDISP_LLD_BOARD_H
#define _GDISP_LLD_BOARD_H

static const LCD_Parameters	DisplayTimings[] = {
	// You need one of these array elements per display
	{
		480, 272,												// Panel width and height
		2, 2, 41,												// Horizontal Timings (back porch, front porch, pulse)
		CALC_PERIOD(480,2,2,41),				// Total Horizontal Period (calculated from above line)
		2, 2, 10,												// Vertical Timings (back porch, front porch, pulse)
		CALC_PERIOD(272,2,2,10),				// Total Vertical Period (calculated from above line)
		CALC_FPR(480,272,2,2,41,2,2,10,60ULL),	// FPR - the 60ULL is the frames per second. Note the ULL!
		// gFalse,											// Flip horizontally
		// gFalse												// Flip vertically
	},
};

// For a multiple display configuration we would put all this in a structure and then
//	set g->board to that structure.

/**
 * @brief	The GPIO pin config
 *
 * @details	This block of defines tell your driver how you wired your display
 *			controller to your MCU. Please change them accordingly.
 *
 * For 8-bit data bus, pins DB_8 to DB_15 are used.
 *
 * Teensy 3.0 pin definitions created by Dawnmist
 * http://forum.pjrc.com/threads/18002-Teensy-3-0-driving-an-SSD1289-with-utft?p=34719&viewfull=1#post34719
 *
 * There's 3 alternative sets of pin definitions that can be used with the
 * Teensy 3 using this header file. Which one is used is controlled by setting
 * the PORTS define to one of "USE_C_D_PORTS", "USE_B_D_PORTS" or
 * "USE_USER_PORTS".
 * 
 * For LCDs with 16 bit data busses:
 *
 * If PORTS = USE_B_D_PORTS:
 *   - Port B 0-3,16-19 and Port D 0-7 will be used. This is slightly slower
 *     than USE_C_D_PORTS, because we need to do the write to port B in 2 steps
 *     (clear pins 0-3,16-19, then set those pins to match our data). Port D
 *     access is still a single write. This means it takes 3 writes to the pins
 *     instead of the 2 used in USE_C_D_PORTS - but it leaves the SPI port pins
 *     available for use, so gives the fastest result when you need to use an
 *     SD Card/something on the SPI bus as well.
 *     Port D (0-7) = DB_8=2, DB_9=14, DB_10=7, DB_11=8, DB_12=6, DB_13=20, DB_14=21, DB_15=5
 *     Port B (0-3,16-19) = DB_0=16, DB_1=17, DB_2=19, DB_3=18, DB_4=0, DB_5=1, DB_6=32, DB_7=25
 *
 * If PORTS = USE_C_D_PORTS:
 *   - Port C 0-7 and Port D 0-7 will be used. Because these are the bottom
 *     8 pins of each port, we can write to them in one write cycle each. This
 *     is the fastest screen data write - but Port C's pins conflict with the
 *     SPI port, so you won't have access to hardware SPI. If you're using an
 *     SD Card, you will *need* the hardware SPI. This setting should only be
 *     used when hardware SPI is *not* needed.
 *     Port D (0-7) = DB_8=2, DB_9=14, DB_10=7, DB_11=8, DB_12=6, DB_13=20, DB_14=21, DB_15=5
 *     Port C (0-7) = DB_0=15, DB_1=22, DB_2=23, DB_3=9, DB_4=10, DB_5=13, DB_6=11, DB_7=12
 *
 * If PORTS = USE_USER_PORTS
 *   - This allows you to define your own set of pins to use. Since we're not
 *     collating them into groupings that can have their writes optimized, it
 *     will take 16 write cycles to write out the data for one pixel. However,
 *     it also gives you the most flexibility in which pins you use for the
 *     LCD data bus. If high-speed/optimized data writes is not important to you
 *     but simplicity of wiring layout is (or if the above options conflict with
 *     something else you're using on the teensy), you can use this setting to
 *     set the pins where-ever you'd like them to be. By default it's set to
 *     pins DB0-DB15 = 0-15. You should modify the "DB_0" through to "DB_15"
 *     defines to match the pins you wish to use.
 * 
 * For LCDs with 8 bit data busses:
 * Use the pin defines for DB_8 to DB_15 to connect to your LCD. This puts them
 * on Port D in both the USE_C_D_PORTS and USE_B_D_PORTS settings, making those
 * two settings equivalent (and a single write to set the pins on the bus).
 */
#define USE_USER_PORTS 0
#define USE_C_D_PORTS 1
#define USE_B_D_PORTS 2

// set which data pin definitions to use
// (only uncomment 1 of these 3 lines)
#define PORTS  USE_B_D_PORTS
//#define PORTS  USE_C_D_PORTS
//#define PORTS  USE_USER_PORTS

#if (PORTS == USE_USER_PORTS)
	#pragma message("Using user-defined pins")
	#define GDISP_DB_0 0
	#define GDISP_DB_1 1
	#define GDISP_DB_2 2
	#define GDISP_DB_3 3
	#define GDISP_DB_4 4
	#define GDISP_DB_5 5
	#define GDISP_DB_6 6
	#define GDISP_DB_7 7
	#define GDISP_DB_8 8
	#define GDISP_DB_9 9
	#define GDISP_DB_10 10
	#define GDISP_DB_11 11
	#define GDISP_DB_12 12
	#define GDISP_DB_13 13
	#define GDISP_DB_14 14
	#define GDISP_DB_15 15
#elif (PORTS == USE_C_D_PORTS)
	#pragma message("Using Ports C&D - pins should be connected to:\nDB_0=15, DB_1=22, DB_2=23, DB_3=9, DB_4=10, DB_5=13, DB_6=11, DB_7=12\nDB_8=2, DB_9=14, DB_10=7, DB_11=8, DB_12=6, DB_13=20, DB_14=21, DB_15=5\nIf using a display with an 8-bit bus, use connections to DB_8 to DB_15")
	#define GDISP_DB_0 15
	#define GDISP_DB_1 22
	#define GDISP_DB_2 23
	#define GDISP_DB_3 9
	#define GDISP_DB_4 10
	#define GDISP_DB_5 13
	#define GDISP_DB_6 11
	#define GDISP_DB_7 12
	#define GDISP_DB_8 2
	#define GDISP_DB_9 14
	#define GDISP_DB_10 7
	#define GDISP_DB_11 8
	#define GDISP_DB_12 6
	#define GDISP_DB_13 20
	#define GDISP_DB_14 21
	#define GDISP_DB_15 5
#elif (PORTS == USE_B_D_PORTS)
	#if defined(__MK64FX512__) || defined(__MK66FX1M0__)
	  #pragma message("Using Ports B&D - pins should be connected to:\nDB_0=16, DB_1=17, DB_2=19, DB_3=18, DB_4=0, DB_5=1, DB_6=29, DB_7=30\nDB_8=2, DB_9=14, DB_10=7, DB_11=8, DB_12=6, DB_13=20, DB_14=21, DB_15=5\nIf using a display with an 8-bit bus, use connections to DB_8 to DB_15")
	  #define GDISP_DB_6 29
	  #define GDISP_DB_7 30
	#else
	  #pragma message("Using Ports B&D - pins should be connected to:\nDB_0=16, DB_1=17, DB_2=19, DB_3=18, DB_4=0, DB_5=1, DB_6=32, DB_7=25\nDB_8=2, DB_9=14, DB_10=7, DB_11=8, DB_12=6, DB_13=20, DB_14=21, DB_15=5\nIf using a display with an 8-bit bus, use connections to DB_8 to DB_15")
	  #define GDISP_DB_6 32
	  #define GDISP_DB_7 25
	#endif
	#define GDISP_DB_0 16
	#define GDISP_DB_1 17
	#define GDISP_DB_2 19
	#define GDISP_DB_3 18
	#define GDISP_DB_4 0
	#define GDISP_DB_5 1
	#define GDISP_DB_8 2
	#define GDISP_DB_9 14
	#define GDISP_DB_10 7
	#define GDISP_DB_11 8
	#define GDISP_DB_12 6
	#define GDISP_DB_13 20
	#define GDISP_DB_14 21
	#define GDISP_DB_15 5
#endif

/* Non-data pins */
#include "ugfx-arduino-gdisp-ssd1963.h"
#define GDISP_RESET       ssd1963_pins.reset
#define GDISP_CS					ssd1963_pins.cs
#define GDISP_RS					ssd1963_pins.rs
#define GDISP_WR					ssd1963_pins.wr
#define GDISP_RD					ssd1963_pins.rd

/* Macros for controlling the display pins */

#define Set_CS    digitalWriteFast(GDISP_CS,    0); // palSetPad(   GDISP_CMD_PORT, GDISP_CS);
#define Clr_CS    digitalWriteFast(GDISP_CS,    1); // palClearPad( GDISP_CMD_PORT, GDISP_CS);
#define Set_RS    digitalWriteFast(GDISP_RS,    0); // palSetPad(   GDISP_CMD_PORT, GDISP_RS);
#define Clr_RS    digitalWriteFast(GDISP_RS,    1); // palClearPad( GDISP_CMD_PORT, GDISP_RS);
#define Set_WR    digitalWriteFast(GDISP_WR,    0); // palSetPad(   GDISP_CMD_PORT, GDISP_WR);
#define Clr_WR    digitalWriteFast(GDISP_WR,    1); // palClearPad( GDISP_CMD_PORT, GDISP_WR);
#define Set_RD    digitalWriteFast(GDISP_RD,    0); // palSetPad(   GDISP_CMD_PORT, GDISP_RD);
#define Clr_RD    digitalWriteFast(GDISP_RD,    1); // palClearPad( GDISP_CMD_PORT, GDISP_RD);

#define Set_RESET digitalWriteFast(GDISP_RESET, 0);
#define Clr_RESET digitalWriteFast(GDISP_RESET, 1);


static GFXINLINE void init_board(GDisplay *g) {

	// As we are not using multiple displays we set g->board to NULL as we don't use it.
	g->board = 0;

	switch(g->controllerdisplay) {
	case 0:											// Set up for Display 0
    // Serial.println("init board");
    pinMode(GDISP_RESET, OUTPUT);
	  //IOBus busCMD = {GDISP_CMD_PORT, (1 << GDISP_CS) | (1 << GDISP_RS) | (1 << GDISP_WR) | (1 << GDISP_RD), 0};
		// palSetBusMode(&busCMD, PAL_MODE_OUTPUT_PUSHPULL);
    pinMode(GDISP_CS,    OUTPUT);
    pinMode(GDISP_RS,    OUTPUT);
    pinMode(GDISP_WR,    OUTPUT);
    pinMode(GDISP_RD,    OUTPUT);
    // IOBus busDATA = {GDISP_CMD_PORT, 0xFFFFF, 0};
		// palSetBusMode(&busDATA, PAL_MODE_OUTPUT_PUSHPULL);
	  pinMode(GDISP_DB_0,  OUTPUT);
	  pinMode(GDISP_DB_1,  OUTPUT);
	  pinMode(GDISP_DB_2,  OUTPUT);
	  pinMode(GDISP_DB_3,  OUTPUT);
	  pinMode(GDISP_DB_4,  OUTPUT);
	  pinMode(GDISP_DB_5,  OUTPUT); 
	  pinMode(GDISP_DB_6,  OUTPUT);
 	  pinMode(GDISP_DB_7,  OUTPUT);
    pinMode(GDISP_DB_8,  OUTPUT);
    pinMode(GDISP_DB_9,  OUTPUT);
    pinMode(GDISP_DB_10, OUTPUT);
    pinMode(GDISP_DB_11, OUTPUT);
    pinMode(GDISP_DB_12, OUTPUT);
    pinMode(GDISP_DB_13, OUTPUT);
    pinMode(GDISP_DB_14, OUTPUT);
    pinMode(GDISP_DB_15, OUTPUT);
		break;
	}
}

static GFXINLINE void post_init_board(GDisplay *g) {
	(void) g;
}

static GFXINLINE void setpin_reset(GDisplay *g, gBool state) {
	(void) g;
	(void) state;
  if(state) { Set_RESET; } else { Clr_RESET; }
}

static GFXINLINE void acquire_bus(GDisplay *g) {
	(void) g;
	Set_CS;
}

static GFXINLINE void release_bus(GDisplay *g) {
	(void) g;
	Clr_CS;
}

static GFXINLINE void write_index(GDisplay *g, gU16 index) {
	(void) g;
	Set_RS; Clr_RD; Set_WR;

	//palWritePort(GDISP_DATA_PORT, index);

	char cl = index&(0xff);        // low byte of index
	char ch = index&(0xff00) >> 8; // high byte of index

#if (PORTS == USE_C_D_PORTS)
	*(volatile uint8_t *)(&GPIOD_PDOR) = ch;
	*(volatile uint8_t *)(&GPIOC_PDOR) = cl;
#elif (PORTS == USE_B_D_PORTS)
	*(volatile uint8_t *)(&GPIOD_PDOR) = ch;
	// clear data lines B0-3,B16-19
	GPIOB_PCOR = 0x000F000F;
	// set data lines 0-3,16-19 if set in cl
  GPIOB_PSOR = (0x0F & cl) | ((cl >> 4) << 16);
#else
	((ch & 0x80) != 0) ? digitalWriteFast(GDISP_DB_15, HIGH) : digitalWriteFast(GDISP_DB_15, LOW);
	((ch & 0x40) != 0) ? digitalWriteFast(GDISP_DB_14, HIGH) : digitalWriteFast(GDISP_DB_14, LOW);
	((ch & 0x20) != 0) ? digitalWriteFast(GDISP_DB_13, HIGH) : digitalWriteFast(GDISP_DB_13, LOW);
	((ch & 0x10) != 0) ? digitalWriteFast(GDISP_DB_12, HIGH) : digitalWriteFast(GDISP_DB_12, LOW);
	((ch & 0x08) != 0) ? digitalWriteFast(GDISP_DB_11, HIGH) : digitalWriteFast(GDISP_DB_11, LOW);
	((ch & 0x04) != 0) ? digitalWriteFast(GDISP_DB_10, HIGH) : digitalWriteFast(GDISP_DB_10, LOW);
	((ch & 0x02) != 0) ? digitalWriteFast(GDISP_DB_9,  HIGH) : digitalWriteFast(GDISP_DB_9,  LOW);
	((ch & 0x01) != 0) ? digitalWriteFast(GDISP_DB_8,  HIGH) : digitalWriteFast(GDISP_DB_8,  LOW);
	((cl & 0x80) != 0) ? digitalWriteFast(GDISP_DB_7,  HIGH) : digitalWriteFast(GDISP_DB_7,  LOW);
	((cl & 0x40) != 0) ? digitalWriteFast(GDISP_DB_6,  HIGH) : digitalWriteFast(GDISP_DB_6,  LOW);
	((cl & 0x20) != 0) ? digitalWriteFast(GDISP_DB_5,  HIGH) : digitalWriteFast(GDISP_DB_5,  LOW);
	((cl & 0x10) != 0) ? digitalWriteFast(GDISP_DB_4,  HIGH) : digitalWriteFast(GDISP_DB_4,  LOW);
	((cl & 0x08) != 0) ? digitalWriteFast(GDISP_DB_3,  HIGH) : digitalWriteFast(GDISP_DB_3,  LOW);
	((cl & 0x04) != 0) ? digitalWriteFast(GDISP_DB_2,  HIGH) : digitalWriteFast(GDISP_DB_2,  LOW);
	((cl & 0x02) != 0) ? digitalWriteFast(GDISP_DB_1,  HIGH) : digitalWriteFast(GDISP_DB_1,  LOW);
	((cl & 0x01) != 0) ? digitalWriteFast(GDISP_DB_0,  HIGH) : digitalWriteFast(GDISP_DB_0,  LOW);
#endif
	// pulse_low(P_WR, B_WR);
	//digitalWriteFast(GDISP_WR, LOW);
	//digitalWriteFast(GDISP_WR, HIGH);

	Clr_WR;
}

static GFXINLINE void write_data(GDisplay *g, gU16 data) {
	(void) g;
	Clr_RS; Clr_RD; Set_WR;

	// palWritePort(GDISP_DATA_PORT, data);

	char cl = data&(0xff);        // low byte of data
	char ch = data&(0xff00) >> 8; // high byte of data

#if (PORTS == USE_C_D_PORTS)
	*(volatile uint8_t *)(&GPIOD_PDOR) = ch;
	*(volatile uint8_t *)(&GPIOC_PDOR) = cl;
#elif (PORTS == USE_B_D_PORTS)
	*(volatile uint8_t *)(&GPIOD_PDOR) = ch;
	// clear data lines B0-3,B16-19
	GPIOB_PCOR = 0x000F000F;
	// set data lines 0-3,16-19 if set in cl
  GPIOB_PSOR = (0x0F & cl) | ((cl >> 4) << 16);
#else
	((ch & 0x80) != 0) ? digitalWriteFast(GDISP_DB_15, HIGH) : digitalWriteFast(GDISP_DB_15, LOW);
	((ch & 0x40) != 0) ? digitalWriteFast(GDISP_DB_14, HIGH) : digitalWriteFast(GDISP_DB_14, LOW);
	((ch & 0x20) != 0) ? digitalWriteFast(GDISP_DB_13, HIGH) : digitalWriteFast(GDISP_DB_13, LOW);
	((ch & 0x10) != 0) ? digitalWriteFast(GDISP_DB_12, HIGH) : digitalWriteFast(GDISP_DB_12, LOW);
	((ch & 0x08) != 0) ? digitalWriteFast(GDISP_DB_11, HIGH) : digitalWriteFast(GDISP_DB_11, LOW);
	((ch & 0x04) != 0) ? digitalWriteFast(GDISP_DB_10, HIGH) : digitalWriteFast(GDISP_DB_10, LOW);
	((ch & 0x02) != 0) ? digitalWriteFast(GDISP_DB_9,  HIGH) : digitalWriteFast(GDISP_DB_9,  LOW);
	((ch & 0x01) != 0) ? digitalWriteFast(GDISP_DB_8,  HIGH) : digitalWriteFast(GDISP_DB_8,  LOW);
	((cl & 0x80) != 0) ? digitalWriteFast(GDISP_DB_7,  HIGH) : digitalWriteFast(GDISP_DB_7,  LOW);
	((cl & 0x40) != 0) ? digitalWriteFast(GDISP_DB_6,  HIGH) : digitalWriteFast(GDISP_DB_6,  LOW);
	((cl & 0x20) != 0) ? digitalWriteFast(GDISP_DB_5,  HIGH) : digitalWriteFast(GDISP_DB_5,  LOW);
	((cl & 0x10) != 0) ? digitalWriteFast(GDISP_DB_4,  HIGH) : digitalWriteFast(GDISP_DB_4,  LOW);
	((cl & 0x08) != 0) ? digitalWriteFast(GDISP_DB_3,  HIGH) : digitalWriteFast(GDISP_DB_3,  LOW);
	((cl & 0x04) != 0) ? digitalWriteFast(GDISP_DB_2,  HIGH) : digitalWriteFast(GDISP_DB_2,  LOW);
	((cl & 0x02) != 0) ? digitalWriteFast(GDISP_DB_1,  HIGH) : digitalWriteFast(GDISP_DB_1,  LOW);
	((cl & 0x01) != 0) ? digitalWriteFast(GDISP_DB_0,  HIGH) : digitalWriteFast(GDISP_DB_0,  LOW);
#endif
	// pulse_low(P_WR, B_WR);
	//digitalWriteFast(GDISP_WR, LOW);
	//digitalWriteFast(GDISP_WR, HIGH);

	Clr_WR;
}

#endif /* _GDISP_LLD_BOARD_H */
