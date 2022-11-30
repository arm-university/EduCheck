/*H**********************************************************************
* FILENAME : NHD_0216HZ.cpp          DESIGN REF:
*
* DESCRIPTION :
*       NHD_0216HZ class functions are declared.
*
* PUBLIC FUNCTIONS :
*    	void 	shift_out(int data);
*    	void 	init_lcd(void);
*    	void 	write_4bit(int data, int mode);
*    	void 	write_cmd(int data);
*    	void 	write_data(char c);
*    	void 	printf(const char *format, ...);
*    	void 	set_cursor(int column, int row);
*    	void 	clr_lcd(void);
*    	string 	check_lcd_data(int row);
*
* NOTES :
*
*       Copyright (c) 2020 Arm Limited and affiliates.
*       SPDX-License-Identifier: Apache-2.0
*
* AUTHOR :    Arm Education      START DATE :    January 2021
*
* CHANGES :
*
 * REF NO    DATE                WHO                                       DETAIL
 *           January 2021        Arm Education ()      Original Code
*
*H*/

#ifndef NHD_0216HZ_H
#define NHD_0216HZ_H

// Include header files
#include "mbed.h"
#include <string>

// Define constants
#define ENABLE 0x08
#define DATA_MODE 0x04
#define COMMAND_MODE 0x00

#define LINE_LENGTH 0x40
#define TOT_LENGTH 0x80

class NHD_0216HZ
{
public:
	// Declare constructor
	NHD_0216HZ(PinName SPI_CS, PinName SPI_MOSI, PinName SPI_SCLK);

	// Function declaration
	void shift_out(int data);
	void init_lcd(void);
	void write_4bit(int data, int mode);
	void write_cmd(int data);
	void write_data(char c);
	void printf(const char *format, ...);
	void set_cursor(int column, int row);
	void clr_lcd(void);
	string check_lcd_data(int row);

private:
	// All private members cannot be accessed outside of class

	// Define private SPI signals
	DigitalOut _SPI_CS;
	DigitalOut _SPI_MOSI;
	DigitalOut _SPI_SCLK;

	// Define LCD variables
	string lcd_data0;
	string lcd_data1;
	int lcd_row;
	int lcd_col;
};
#endif
