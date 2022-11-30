#include "mbed.h"
#include "mp3player.h"
#include "song_def.h"
#include "song.h"
#include <string>

using namespace std;
using namespace main_app;

// Constructor definition
mp3player::mp3player() : lcd(SPI_CS, SPI_MOSI, SPI_SCLK), // instantiate the lcd object
                         pause(PAUSE),
                         get_input(BUTTON_1),
                         volume(ANALOG_IN),
                         allsongs{FUR_ELISE, CANNON_IN_D, MINUET_IN_G_MAJOR, TURKISH_MARCH, NOCTRUNE_IN_E_FLAT, WALTZ_NO2, SYMPHONY_NO5, EINE_KLEINE_NACHTAMUSIK},
                         song_number(BUTTON_2, BUTTON_3, BUTTON_4),
                         red(RED_LED),
                         green(GREEN_LED),
                         blue(BLUE_LED),
                         speaker(SPEAKER),
                         t1(osPriorityNormal, THREAD_STACKSIZE),
                         t2(osPriorityNormal, THREAD_STACKSIZE),
                         t3(osPriorityNormal, THREAD_STACKSIZE)
{
    printf("\n[EDUCHECK] Created mp3class...\n");

    // Initialize LCD
    lcd.init_lcd();
    lcd.clr_lcd();

    // Set variables to initial values
    song_index = 0;
    is_playing = false;
    wait_for_new_song = false;
}

// Update LCD
void mp3player::update_lcd_leds_thread()
{
    while (1)
    {
        lcd_mutex.lock();
        lcd.clr_lcd();
        lcd.set_cursor(0, 0);
        lcd.printf(lcd_text[0].c_str());
        lcd.set_cursor(0, 1);
        lcd.printf(lcd_text[1].c_str());
        lcd_mutex.unlock();

        red.write(!is_playing);
        blue.write(is_playing);
        green.write(wait_for_new_song);

        wait_us(500000);
        //ThisThread::sleep_for(500ms);
    }
}

// Adjust the volume of the speaker
void mp3player::adjust_volume()
{
    while (1)
    {
        if (is_playing == true)
            Volume = 0.1 * volume.read();
        else
            speaker.write(0);
        wait_us(500000);
        //ThisThread::sleep_for(500ms);
    }
}

// Define the ticker ISR
void mp3player::timer_ISR()
{
    if (is_playing == true)
    {
        if (k < allsongs[song_index].length)
        {

            // Set the PWM duty cycle to zero, if there is a sound pause
            if (*(allsongs[song_index].note + k) == No)
                speaker.write(0);
            // Set the PWM period, which determines the note of the sound
            else
            {
                speaker.period(0.001 * (*(allsongs[song_index].note + k)));
                speaker.write(Volume);
            }

            k++;

            // Set the time for the next ticker interrupt
            timer.attach(callback(this, &mp3player::timer_ISR), ((*(allsongs[song_index].beat + k) / 3) + (allsongs[song_index].tempo / 2)));
        }
        else
        {
            // If the musical piece is finished, start again
            k = 0;
            speaker.write(0);
        }
    }
}

// Define pause button handler
void mp3player::pause_button_handler()
{
    if (wait_for_new_song == false)
        is_playing = !is_playing;
}

// Define no response
void mp3player::no_response()
{
    lcd_text[0] = allsongs[song_index].name1;
    lcd_text[1] = allsongs[song_index].name2;
    wait_for_new_song = false;
}

// Define get input handler
void mp3player::get_input_handler()
{
    if (wait_for_new_song == false)
    {
        wait_for_new_song = true;
        temp_index = song_number.read();
        lcd_text[0] = "Do you want to ";
        lcd_text[1] = "play song " + to_string(temp_index);
        delay.attach(callback(this, &mp3player::no_response), 5s);
    }
    else
    {
        wait_for_new_song = false;
        song_index = temp_index;
        k = 0;
        lcd_text[0] = allsongs[song_index].name1;
        lcd_text[1] = allsongs[song_index].name2;
        is_playing = true;
        //Initialize the time ticker
        timer.attach(callback(this, &mp3player::timer_ISR), 100ms);
    }
}

// Define polling loop pause and get_input buttons
void mp3player::polling_loop()
{
    bool pressed_get_input = false;
    bool pressed_pause = false;
    while (1)
    {
        if (pause.read() && !pressed_pause)
        //if (!pause.read() && !pressed_pause)
        {
            pause_button_handler();
            pressed_pause = true;
        }
        if (pause.read())
            pressed_pause = false;
        if (get_input.read() && !pressed_get_input)
        {
            pressed_get_input = true;
            get_input_handler();
        }
        if (!get_input.read())
            pressed_get_input = false;

        wait_us(500000);
        //ThisThread::sleep_for(500ms);
    }
}

// Define function to start all threads
void mp3player::thread_starter()
{
    t1.start(callback(this, &mp3player::update_lcd_leds_thread));
    t2.start(callback(this, &mp3player::adjust_volume));
    t3.start(callback(this, &mp3player::polling_loop));
}

// Define function to terminate all threads
void mp3player::thread_terminator()
{
    t1.terminate();
    t2.terminate();
    t3.terminate();
}
