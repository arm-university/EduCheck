#ifndef MP3PLAYER_H
#define MP3PLAYER_H

#include "mbed.h"
#include "song.h"
#include "NHD_0216HZ.h"
#include <string>

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

// For testing purposes
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
error("Undefined target. Please define relevant pins in header file. ")
#endif

namespace main_app
{
class mp3player
{
public:
  // Define constructor
  mp3player();

  // Declare Functions
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
  /*All protected members are visible in tests. */

  // Define the LCD display and the Serial
  NHD_0216HZ lcd;
  //BufferedSerial pc;

  // These pins will be set to output during test mode
#ifndef MBED_TEST_MODE
  DigitalIn pause;
  DigitalIn get_input;
  AnalogIn volume;
  BusIn song_number;
#else
  DigitalOut pause;
  DigitalOut get_input;
  AnalogIn volume;
  BusOut song_number;
#endif

  // Define Song
  Song allsongs[8];


  // Define other inputs and outputs
  DigitalOut red;
  DigitalOut green;
  DigitalOut blue;
  PwmOut speaker;

  // Define threads
  Thread t1;
  Thread t2;
  Thread t3;

  // Define global singals
  int song_index;
  bool is_playing;
  bool wait_for_new_song;
  bool song_finished;
  string lcd_text[2];
  float Volume;
  int k;
  float PotentiometerVal;

private:
  
  int temp_index;

  // Define the mutex
  Mutex lcd_mutex;

  // Define ticker and timeout
  Ticker timer;
  Timeout delay;
};
} // namespace main_app

#endif
