/*H**********************************************************************
* FILENAME : NHD_0216HZ.cpp          DESIGN REF:
*
* DESCRIPTION :
*       test player class which inherits from mp3player class.
*        Define setter getter functions to access protected members of
*        mp3player class.
*        Used for Educheck tests.
*
* PUBLIC FUNCTIONS :
*
* NOTES :
*       Defines the tests functions in the class
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

#include "test_player_class.h"

// Constructor defintion
test_player_class::test_player_class()
{
    printf("\n[EDUCHECK] Created test_player_class object...\n");
}

// Get pause value
int test_player_class::getPausePin()
{
    return pause.read();
}

// Set song number
void test_player_class::setSongNumber(int selection)
{
    song_number = selection;
}
// Set pause value for testing
void test_player_class::setPausePin(int pauseval)
{
    pause.write(pauseval);
}

// Get speaker value
int test_player_class::getSpeakerValue()
{
    return speaker.read();
}

// Set speaker value
void test_player_class::setSpeakerValue(int speakerVolume)
{
    Volume = speakerVolume;
}

// Get get_input value
int test_player_class::getGet_inputPin()
{
    return get_input.read();
}

// Set get_input value for testing
void test_player_class::setGet_inputPin(int getinputval)
{
    get_input.write(getinputval);
}

// Get wait_for_new_song value
bool test_player_class::getWait_for_new_song()
{
    return wait_for_new_song;
}

// Set wait_for_new_song value for testing
void test_player_class::setWait_for_new_song(bool waitfornewsongval)
{
    wait_for_new_song = waitfornewsongval;
}

// Get is_playing value
bool test_player_class::getIs_playing()
{
    return is_playing;
}

// Set is_playing value for testing
void test_player_class::setIs_playing(bool isplayingval)
{
    is_playing = isplayingval;
}

// Get is_playing value
bool test_player_class::getSong_finished()
{
    return song_finished;
}

// Get is_playing value
void test_player_class::setSong_finished(bool isFinished)
{
    song_finished = isFinished;
}

// Get song_index value
string test_player_class::getSong_index()
{
    return allsongs[song_index].name1;
}

// Get song_index value
int test_player_class::getSong_length()
{
    return allsongs[song_index].length;
}

// Set song_index value
void test_player_class::setSong_index(int index)
{
    song_index = index;
}

// Get volume pin value
int test_player_class::getVolumePin()
{
    return volume.read();
}

// Get volume pin value
int test_player_class::getVolumeValue()
{
    return Volume;
}

// Get volume pin value
void test_player_class::setK(int value)
{
    k = value;
}

// Get volume pin value
float test_player_class::getK()
{
    return k;
}

// Get thread state according to thread name string
osStatus test_player_class::getThreadStatus(string threadname)
{
    if (threadname == "t1")
    {
        return t1.get_state();
    }
    else if (threadname == "t2")
    {
        return t2.get_state();
    }
    else if (threadname == "t3")
    {
        return t3.get_state();
    }
    else
        error("Wrong threadname specified.");
}

// Get lcd_data for testing
string test_player_class::getCheck_lcd_data(int rowval)
{
    return lcd.check_lcd_data(rowval);
}

// Get lcd_text for testing
string test_player_class::getLcd_text(int val)
{
    return lcd_text[val];
}

// Set lcd_text for testing
void test_player_class::setLcd_text(int testval, string teststring)
{
    lcd_text[testval] = teststring;
}

// Get red LCD status
bool test_player_class::get_redLed_status()
{
    return red.read();
}

// Get blue LCD status
bool test_player_class::get_blueLed_status()
{
    return blue.read();
}

// Get green LCD status
bool test_player_class::get_greenLed_status()
{
    return green.read();
}

// Get Volume for testing
float test_player_class::getVolume()
{
    return Volume;
}

// Set Volume for testing
void test_player_class::setVolume(float VolumeVal)
{
    Volume = VolumeVal;
}

// Get the overloaded read_potentiometer() value
float test_player_class::read_potentiometer(float PotentiometerVal)
{
    return PotentiometerVal;
}

// Get speaker value
float test_player_class::getSpeaker()
{
    return speaker;
}
