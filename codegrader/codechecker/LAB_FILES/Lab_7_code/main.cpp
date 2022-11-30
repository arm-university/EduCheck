/*H**********************************************************************
* FILENAME : main.cpp          DESIGN REF:
*
* DESCRIPTION :
*       Mp3player main function called at start of program
*       if not in Educheck test mode (MBED test mode is switched off).
*       Compile and run this file when doing normal flashing and running
*       on development board.
*
* PUBLIC FUNCTIONS : None.
*
* NOTES :
*       This file does not run the test defined by EduCheck. It simply initializes the
*       player, sets the pins to run on the development board and starts the thread for the player.
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

// Only compile and run this when not in Educheck test mode
// (e.g normal flashing and running on board without Greentea)
#if !MBED_TEST_MODE

// Include header files
#include "mbed.h"
#include "mp3player.h"
#include <string>
using namespace std;
using namespace main_app;

int main()
{
    // Create mp3player object called player
    mp3player player;

    // Initialise and clear the LCD display
    player.player_init();
    player.set_input_pins(RUN_ON_BOARD);

    // Start all threads
    player.thread_starter();

    // Wait for timer interrupt
    while (1)
    {
        __WFI();
    }
}
#endif