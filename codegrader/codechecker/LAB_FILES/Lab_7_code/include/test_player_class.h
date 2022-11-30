/*H**********************************************************************
* FILENAME : test_player_class.h         DESIGN REF:
*
* DESCRIPTION :
*       test player class which inherits from mp3player class.
*        Contains setter getter functions to access protected members of
*        mp3player class.
*        Used for Educheck tests.
*
* PUBLIC FUNCTIONS : See below.
*
* NOTES :
*
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

#ifndef TEST_PLAYER_CLASS_H
#define TEST_PLAYER_CLASS_H

#include "mp3player.h"

class test_player_class : public main_app::mp3player
{
public:
    // Declare constructor
    test_player_class();

    // Getter and setter functions to access protected members of inherited class
    int getPausePin();
    void setSongNumber(int selection);
    void setPausePin(int pauseval);
    int getGet_inputPin();
    void setGet_inputPin(int getinputval);
    bool getWait_for_new_song();
    void setWait_for_new_song(bool waitfornewsongval);
    bool getIs_playing();
    void setIs_playing(bool isplayingval);
    int getVolumePin();

    osStatus getThreadStatus(string threadname);

    string getCheck_lcd_data(int rowval);
    string getLcd_text(int val);
    void setLcd_text(int testval, string teststring);

    bool get_redLed_status();
    bool get_greenLed_status();
    bool get_blueLed_status();

    int getSpeakerValue();
    void setSpeakerValue(int speakerVolume);

    bool getSong_finished();
    void setSong_finished(bool isFinished);
    string getSong_index();
    int getSong_length();
    void setSong_index(int index);

    int getVolumeValue();
    void setK(int value);
    float getK();
    float getVolume();
    void setVolume(float VolumeVal);
    float getSpeaker();

    // Function overloading for Educheck testing (Greentea) purposes
    float read_potentiometer(float PotentiometerVal);
};

#endif
