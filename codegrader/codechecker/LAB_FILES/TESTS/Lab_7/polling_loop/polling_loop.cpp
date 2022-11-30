/*H**********************************************************************
* FILENAME : polling_loop.cpp          DESIGN REF:
*
* DESCRIPTION :
*       Test to determine if the play, pause, and get input button control the player state.
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

// Testcase to check if is_playing and wait_for_new_song are correct based on
// test object pause and get_input signals
static control_t polling_loop(const size_t call_count)
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

    // Check results using assertions
    printf("\n[EDUCHECK] Checking is_playing value at start........\n");
    TEST_ASSERT_EQUAL_MESSAGE(true, testplayer.getIs_playing(), "is_playing assertion at pause=0");

    // pause = 1 (button pressed)
    printf("\n[EDUCHECK] Checking pause_button_handler........\n");
    testplayer.setPausePin(1);
    TEST_ASSERT_EQUAL_MESSAGE(1, testplayer.getPausePin(), "pause button assertion");
    TEST_ASSERT_EQUAL_MESSAGE(0, testplayer.getGet_inputPin(), "get_input button assertion");
    // Add wait time as polling_loop has wait time
    wait_us(500000);
    wait_us(500000);
    printf("\n[EDUCHECK] PAUSE mode: Checking ........\n");
    TEST_ASSERT_EQUAL_MESSAGE(true, testplayer.getIs_playing(), "is_playing assertion at pause=1");

    // pause = 0 (button is released)
    printf("\n[EDUCHECK] PAUSE mode: Deassert button now (release)........\n");
    testplayer.setPausePin(0);
    TEST_ASSERT_EQUAL_MESSAGE(0, testplayer.getPausePin(), "pause button assertion");
    TEST_ASSERT_EQUAL_MESSAGE(0, testplayer.getGet_inputPin(), "get_input button assertion");
    // Add wait time as polling_loop has wait time
    wait_us(500000);
    wait_us(500000);
    printf("\n[EDUCHECK] PAUSE mode: Checking ........\n");
    TEST_ASSERT_EQUAL_MESSAGE(false, testplayer.getIs_playing(), "is_playing assertion at pause=0");

    // Check if is_playing does not change after some time
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
    printf("\n[EDUCHECK] PLAY mode........\n");
    TEST_ASSERT_EQUAL_MESSAGE(true, testplayer.getIs_playing(), "is_playing assertion at play=0");

    // Check if is_playing does not change after some time
    wait_us(500000);
    wait_us(500000);
    wait_us(500000);
    wait_us(500000);
    wait_us(500000);
    printf("\n[EDUCHECK] Checking ........\n");
    TEST_ASSERT_EQUAL_MESSAGE(true, testplayer.getIs_playing(), "is_playing assertion at pause=0");

    // button pressed
    printf("\n[EDUCHECK] Checking get_input_handler........\n");
    testplayer.setGet_inputPin(0);
    TEST_ASSERT_EQUAL_MESSAGE(0, testplayer.getGet_inputPin(), "pause button assertion");
    TEST_ASSERT_EQUAL_MESSAGE(0, testplayer.getPausePin(), "get_input button assertion");
    // Add wait time as polling_loop has wait time
    wait_us(500000);
    wait_us(500000);
    printf("\n[EDUCHECK] PAUSE mode........\n");
    TEST_ASSERT_EQUAL_MESSAGE(false, testplayer.getWait_for_new_song(), "is_playing assertion at pause=1");

    // button is released
    printf("\n[EDUCHECK] PAUSE mode: Deassert button now (release)........\n");
    testplayer.setGet_inputPin(1);
    TEST_ASSERT_EQUAL_MESSAGE(1, testplayer.getGet_inputPin(), "pause button assertion");
    TEST_ASSERT_EQUAL_MESSAGE(0, testplayer.getPausePin(), "get_input button assertion");
    // Add wait time as polling_loop has wait time
    wait_us(500000);
    wait_us(500000);
    printf("\n[EDUCHECK] PAUSE mode........\n");
    TEST_ASSERT_EQUAL_MESSAGE(true, testplayer.getWait_for_new_song(), "is_playing assertion at pause=0");

    // Check if is_playing does not change after some time
    wait_us(500000);
    wait_us(500000);
    wait_us(500000);
    wait_us(500000);
    wait_us(500000);
    printf("\n[EDUCHECK] Checking is_playing value at after button released........\n");
    TEST_ASSERT_EQUAL_MESSAGE(true, testplayer.getWait_for_new_song(), "is_playing assertion at pause=0");

    // button pressed
    printf("\n[EDUCHECK] PLAY mode: Setting button now ........\n");
    testplayer.setGet_inputPin(0);
    TEST_ASSERT_EQUAL_MESSAGE(0, testplayer.getGet_inputPin(), "pause button assertion");
    TEST_ASSERT_EQUAL_MESSAGE(0, testplayer.getPausePin(), "get_input button assertion");
    // Add wait time as polling_loop has wait time
    wait_us(500000);
    wait_us(500000);
    printf("\n[EDUCHECK] PLAY mode........\n");
    TEST_ASSERT_EQUAL_MESSAGE(true, testplayer.getWait_for_new_song(), "is_playing assertion at play=1");

    // button is released
    printf("\n[EDUCHECK] PLAY mode: Deassert button now (release)........\n");
    testplayer.setGet_inputPin(1);
    TEST_ASSERT_EQUAL_MESSAGE(1, testplayer.getGet_inputPin(), "pause button assertion");
    TEST_ASSERT_EQUAL_MESSAGE(0, testplayer.getPausePin(), "get_input button assertion");
    // Add wait time as polling_loop has wait time
    wait_us(500000);
    wait_us(500000);
    printf("\n[EDUCHECK] PLAY mode: Checking is_playing value at after button released........\n");
    TEST_ASSERT_EQUAL_MESSAGE(true, testplayer.getWait_for_new_song(), "is_playing assertion at play=0");

    // Check if is_playing does not change after some time
    wait_us(500000);
    wait_us(500000);
    wait_us(500000);
    wait_us(500000);
    wait_us(500000);
    printf("\n[EDUCHECK] Checking is_playing value at after button released........\n");
    TEST_ASSERT_EQUAL_MESSAGE(true, testplayer.getWait_for_new_song(), "is_playing assertion at pause=0");

    // Terminate test thread
    testThread.terminate();
    TEST_ASSERT_EQUAL_MESSAGE(Thread::Deleted, testThread.get_state(), "Test thread not terminated properly");

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
    Case("polling_loop", polling_loop)};

Specification specification(greentea_setup, cases);

int main()
{
    return !Harness::run(specification);
}
