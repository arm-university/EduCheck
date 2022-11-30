#ifndef TEST_PLAYER_CLASS_H
#define TEST_PLAYER_CLASS_H

#include "mp3player.h"

class test_player_class : public main_app::mp3player
{
public:
    // Define constructor
    test_player_class();

    // Getter and setter functions
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
    //void setVolumePin(int volumeval);
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

    //overloaded for testing purposes
    float read_potentiometer(float PotentiometerVal);

};

#endif
