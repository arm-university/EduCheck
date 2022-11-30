#if !MBED_TEST_MODE

#include "mbed.h"
#include "mp3player.h"
#include <string>
using namespace std;
using namespace main_app;

/*----------------------------------------------------------------------------
 MAIN function
 *----------------------------------------------------------------------------*/
//#if !MBED_TEST_MODE
int main()
{
    // create mp3player object called player
    mp3player player;
    // Initialise and clear the LCD display
    player.player_init();
    player.set_input_pins(RUN_ON_BOARD);

    // player.lcd->init_lcd();
    // player.lcd->clr_lcd();
    // player.lcd.init_lcd();
    // player.lcd.clr_lcd();
    // initalize pc 9600 bd //////////////////////////////////////////////////

    //Start all threads
    player.thread_starter();

    // test if USER_BUTTON works
    // DigitalOut myled(LED1);
    // if (pause->read() == 1)
    // {
    //     myled = 1;
    // }
    // else
    // {
    //     myled = 0;
    // }

    // __enable_irq();
    //Initialize the interrupt handler
    // pause.rise(&pause_button_handler);
    // pause.rise(&get_input_handler);
    /*
    pc.printf("Choose a song:\r\n");
    for (int i = 0; i < 8; i++)
    {
        pc.printf("     %d %s %s %s %s\r\n", i, " - ", allsongs[i].name1.c_str(), " ", allsongs[i].name2.c_str());
    }
    pc.printf("Using the Buttons 2 to 4, insert the song number in binary form\r\n");
    pc.printf("Then press on Button 1 and release all the buttons\r\n");
    */

    // printf("Choose a song:\r\n");
    // for (int i = 0; i < 8; i++)
    // {
    //     printf("     %d %s %s %s %s\r\n", i, " - ", allsongs[i].name1.c_str(), " ", allsongs[i].name2.c_str());
    // }
    // printf("Using the Buttons 2 to 4, insert the song number in binary form\r\n");
    // printf("Then press on Button 1 and release all the buttons\r\n");

    // Wait for timer interrupt
    while (1)
    {
        __WFI();
    }
}
#endif