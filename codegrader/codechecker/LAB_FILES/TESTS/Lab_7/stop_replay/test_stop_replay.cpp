/*H**********************************************************************
* FILENAME : test_stop_replay.cpp          DESIGN REF:
*
* DESCRIPTION :
*       Testcases to determine that the stop and replay functionality works.
*       Also specifically tests functionality of pause_button_handler().
*
* PUBLIC FUNCTIONS :
*
* NOTES :
*		This test employs Greentea automated testing tool.
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

#include "mbed.h"
#include "utest/utest.h"
#include "unity/unity.h"
#include "greentea-client/test_env.h"
#include <stdio.h>
#include "test_player_class.h"

using namespace main_app;
using namespace utest::v1;
using namespace std;

// Testcase to check happens if Pause Button is "pressed"/set */
// Test sequence: i) reset ii) pause iii) play */
// Check if is_playing works based on pause button */
// Dependent on polling_loop() */
// The pause button is the play button. Pause and play
// toggles between each button press */
static control_t test_reset_pause_play_sequence(const size_t call_count)
{
    // Create a test mp3player object
    test_player_class testplayer;

    // Create a test thread since polling_loop is in while(1)
    Thread testThread;
    printf("\n[EDUCHECK] Thread created.....");

    // Set pause and get_input buttons to zero
    printf("\n[EDUCHECK] Setting pause and get_input buttons to zero...");
    testplayer.setPausePin(0);
    testplayer.setGet_inputPin(0);
    // Check results using assertions
    TEST_ASSERT_EQUAL_MESSAGE(0, testplayer.getPausePin(), "pause button assertion");
    TEST_ASSERT_EQUAL_MESSAGE(0, testplayer.getGet_inputPin(), "get_input button assertion");

    // Set default signals when out of reset
    printf("\n[EDUCHECK] Setting signals to default .....");
    testplayer.setWait_for_new_song(false);
    testplayer.setIs_playing(false);

    // Start test thread
    printf("\n[EDUCHECK] Starting thread........\n");
    testThread.start(callback(&testplayer, &mp3player::polling_loop));

    // Double check pause and get_input is as expected at reset
    TEST_ASSERT_EQUAL_MESSAGE(0, testplayer.getPausePin(), "pause button assertion");
    TEST_ASSERT_EQUAL_MESSAGE(0, testplayer.getGet_inputPin(), "get_input button assertion");

    printf("\n[EDUCHECK] Checking is_playing value at start........\n");
    TEST_ASSERT_EQUAL_MESSAGE(true, testplayer.getIs_playing(), "is_playing assertion at pause=0");

    // pause = 1 (button pressed)
    printf("\n[EDUCHECK] PAUSE mode: Setting button now........\n");
    testplayer.setPausePin(1);
    TEST_ASSERT_EQUAL_MESSAGE(1, testplayer.getPausePin(), "pause button assertion");
    TEST_ASSERT_EQUAL_MESSAGE(0, testplayer.getGet_inputPin(), "get_input button assertion");
    // Add wait time as polling_loop has wait time
    wait_us(500000);
    wait_us(500000);
    printf("\n[EDUCHECK] PAUSE mode: Checking is_playing value at after button set........\n");
    TEST_ASSERT_EQUAL_MESSAGE(true, testplayer.getIs_playing(), "is_playing assertion at pause=1");

    // pause = 0 (button is released)
    printf("\n[EDUCHECK] PAUSE mode: Deassert button now (release)........\n");
    testplayer.setPausePin(0);
    TEST_ASSERT_EQUAL_MESSAGE(0, testplayer.getPausePin(), "pause button assertion");
    TEST_ASSERT_EQUAL_MESSAGE(0, testplayer.getGet_inputPin(), "get_input button assertion");
    // Add wait time as polling_loop has wait time
    wait_us(500000);
    wait_us(500000);
    printf("\n[EDUCHECK] PAUSE mode: Checking is_playing value at after button released........\n");
    TEST_ASSERT_EQUAL_MESSAGE(false, testplayer.getIs_playing(), "is_playing assertion at pause=0");

    // Check if is_playing dos not change after some time
    wait_us(500000);
    wait_us(500000);
    wait_us(500000);
    wait_us(500000);
    wait_us(500000);
    printf("\n[EDUCHECK] Checking is_playing value at after button released........\n");
    TEST_ASSERT_EQUAL_MESSAGE(false, testplayer.getIs_playing(), "is_playing assertion at pause=0");

    // Play (button pressed)
    printf("\n[EDUCHECK] PLAY mode: Setting button now ........\n");
    testplayer.setPausePin(1);
    TEST_ASSERT_EQUAL_MESSAGE(1, testplayer.getPausePin(), "pause button assertion");
    TEST_ASSERT_EQUAL_MESSAGE(0, testplayer.getGet_inputPin(), "get_input button assertion");
    // Add wait time as polling_loop has wait time
    wait_us(500000);
    wait_us(500000);
    printf("\n[EDUCHECK] PLAY mode: Checking is_playing value at after button set........\n");
    TEST_ASSERT_EQUAL_MESSAGE(false, testplayer.getIs_playing(), "is_playing assertion at play=1");

    // pause = 0 (button is released)
    printf("\n[EDUCHECK] PLAY mode: Deassert button now (release)........\n");
    testplayer.setPausePin(0);
    TEST_ASSERT_EQUAL_MESSAGE(0, testplayer.getPausePin(), "pause button assertion");
    TEST_ASSERT_EQUAL_MESSAGE(0, testplayer.getGet_inputPin(), "get_input button assertion");
    // Add wait time as polling_loop has wait time
    wait_us(500000);
    wait_us(500000);
    printf("\n[EDUCHECK] PLAY mode: Checking is_playing value at after button released........\n");
    TEST_ASSERT_EQUAL_MESSAGE(true, testplayer.getIs_playing(), "is_playing assertion at play=0");

    // Check if is_playing dos not change after some time
    wait_us(500000);
    wait_us(500000);
    wait_us(500000);
    wait_us(500000);
    wait_us(500000);
    printf("\n[EDUCHECK] Checking is_playing value at after button released........\n");
    TEST_ASSERT_EQUAL_MESSAGE(true, testplayer.getIs_playing(), "is_playing assertion at pause=0");

    // Terminate test thread
    testThread.terminate();
    TEST_ASSERT_EQUAL_MESSAGE(Thread::Deleted, testThread.get_state(), "Test thread not terminated properly");

    return CaseNext;
}

// Testcase to check if pause_button_handler() toggles is_playing correctly
static control_t test_pause_button_handler(const size_t call_count)
{
    // Create a test mp3player object
    test_player_class testplayer;

    // Check default signals out of reset
    printf("\n[EDUCHECK] Setting default signals at reset .....");
    testplayer.setWait_for_new_song(false);
    testplayer.setIs_playing(false);

    // Checks that is_playing toggles when wait_for_new_song == false
    testplayer.pause_button_handler();
    TEST_ASSERT_EQUAL_MESSAGE(true, testplayer.getIs_playing(), "is_playing assertion 1");
    testplayer.pause_button_handler();
    TEST_ASSERT_EQUAL_MESSAGE(false, testplayer.getIs_playing(), "is_playing assertion 2");

    // Checks that is_playing does not toggle when wait_for_new_song == true
    printf("\n[EDUCHECK] Setting wait_for_new_song .....");
    testplayer.setWait_for_new_song(true);
    testplayer.pause_button_handler();
    TEST_ASSERT_EQUAL_MESSAGE(false, testplayer.getIs_playing(), "is_playing assertion 3");
    testplayer.pause_button_handler();
    TEST_ASSERT_EQUAL_MESSAGE(false, testplayer.getIs_playing(), "is_playing assertion 4");

    // Checks that is_playing retoggles when wait_for_new_song == false
    printf("\n[EDUCHECK] Deassert wait_for_new_song .....");
    testplayer.setWait_for_new_song(false);
    testplayer.pause_button_handler();
    TEST_ASSERT_EQUAL_MESSAGE(true, testplayer.getIs_playing(), "is_playing assertion 5");
    testplayer.pause_button_handler();
    TEST_ASSERT_EQUAL_MESSAGE(false, testplayer.getIs_playing(), "is_playing assertion 6");

    return CaseNext;
}

utest::v1::status_t greentea_setup(const size_t number_of_cases)
{
    // Here, we specify the timeout (60s) and the host test (a built-in host test or the name of our Python file)
    GREENTEA_SETUP(60, "default_auto");

    return greentea_test_setup_handler(number_of_cases);
}

// List of test cases in this file
Case cases[] = {
    Case("test_reset_pause_play_sequence", test_reset_pause_play_sequence),
    Case("test_pause_button_handler", test_pause_button_handler)};

Specification specification(greentea_setup, cases);

int main()
{
    return !Harness::run(specification);
}
