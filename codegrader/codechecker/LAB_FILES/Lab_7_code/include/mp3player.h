/*H**********************************************************************
* FILENAME : mp3player.h          DESIGN REF:
*
* DESCRIPTION :
*       Header file to define mp3player class
*
* PUBLIC FUNCTIONS :
*      void   update_lcd_leds_thread();
*      void   adjust_volume();
*      void   timer_ISR();
*      void   no_response();
*      void   get_input_handler();
*      void   pause_button_handler();
*      void   polling_loop();
*      void   thread_starter();
*      void   thread_terminator();
*      float  read_potentiometer();
*
* NOTES :
*       The class defned has functions which are public and private and protected access specifiers for variabales, arrays, etc
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

#ifndef MP3PLAYER_H
#define MP3PLAYER_H

// Include header files
#include "mbed.h"
#include "song.h"       // Song class
#include "NHD_0216HZ.h" // LCD Driver class
#include <string>

// Definitions of pins for specific boards
// Modify these definitions for your own board if not listed in #if or #elif statement
#if (TARGET_NUCLEO_F401RE) || (TARGET_NUCLEO_F091RC) || (TARGET_DISCO_L475VG_IOT01A) || (TARGET_DISCO_F746NG)
#define BUTTON_1 D2
#define BUTTON_2 D3
#define BUTTON_3 D4
#define BUTTON_4 D5
#define RED_LED D6
#define GREEN_LED D7
#define BLUE_LED D8
#define SPEAKER D9
#define SPI_CS D10
#define SPI_MOSI D11
#define SPI_SCLK D13
#define UART_TX D1
#define UART_RX D0
// Definitions declared for Educheck testing purposes
#define THREAD_STACKSIZE 2046
#ifndef MBED_TEST_MODE
//non-test mode
#define PAUSE USER_BUTTON
#define ANALOG_IN A0
#else
//test mode
#define PAUSE D15
#define ANALOG_IN A0 // to change this to a suitable pin, was D14
#endif

#elif TARGET_LPC1768
#define BUTTON_1 p12
#define BUTTON_2 p13
#define BUTTON_3 p15
#define BUTTON_4 p16
#define USER_BUTTON p14
#define RED_LED LED1
#define GREEN_LED LED2
#define BLUE_LED LED3
#define SPEAKER p21
#define SPI_CS p11
#define SPI_MOSI p5
#define SPI_SCLK p7
#define UART_TX p9
#define UART_RX p10
#define ANALOG_IN p17
#define THREAD_STACKSIZE 2046
#define PAUSE USER_BUTTON

#else
error("Undefined target. Please define relevant pins in this header file. ")
#endif

// Namespace and class definition
namespace main_app
{
class mp3player
{
public:
  // Declare constructor
  mp3player();

  // Declare functions
  void update_lcd_leds_thread();
  void adjust_volume();
  void timer_ISR();
  void no_response();
  void get_input_handler();
  void pause_button_handler();
  void polling_loop();
  void thread_starter();
  void thread_terminator();
  float read_potentiometer();

protected:
  // All protected members are accessible in Educheck test player class

  // Declare LCD object of class NHD_0216HZ
  NHD_0216HZ lcd;

// These objects are declared as output during Educheck test mode (Greentea)
#ifndef MBED_TEST_MODE
  DigitalIn pause;
  DigitalIn get_input;
  BusIn song_number;
#else
  DigitalOut pause;
  DigitalOut get_input;
  BusOut song_number;
#endif

  // Define analog object for volume
  AnalogIn volume;

  // Define song object
  Song allsongs[8];

  // Define LED objects
  DigitalOut red;
  DigitalOut green;
  DigitalOut blue;

  // Define speaker object
  PwmOut speaker;

  // Define thread objects
  Thread t1;
  Thread t2;
  Thread t3;

  // Define global singal variables
  int song_index;
  bool is_playing;
  bool wait_for_new_song;
  bool song_finished;
  string lcd_text[2];
  float Volume;
  int k;
  float PotentiometerVal;

private:
  // All private members are not accessible outside the class

  // Define temp variable for song index
  int temp_index;

  // Define the mutex object
  Mutex lcd_mutex;

  // Define ticker and timeout objects
  Ticker timer;
  Timeout delay;
};
} // namespace main_app

#endif
