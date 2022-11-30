/*H**********************************************************************
* FILENAME : test_volume.cpp          DESIGN REF:
*
* DESCRIPTION :
*       Test for volume control functionality in the player.
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
#include "test_player_class.h"
#include <stdio.h>

using namespace utest::v1;
using namespace main_app;

// Testcase that sets volume to a value, reads the value set, and verify that it is equal.
// Test if adjust_volume() changes volume in one way or another
// Volume depends on changing input by a potentiometer
// Potentiometer input and reading capabilities will be mocked
static control_t test_volume(const size_t call_count)
{
    // Create a test mp3player object
    test_player_class testplayer;

    // Create a test thread since adjust_volume() is in while(1) loop
    Thread testThread;
    printf("\n[EDUCHECK] Thread created.....");

    // Define an initial test volume value
    float testvalue = 1.1;

    // Start test thread
    printf("\n[EDUCHECK] Starting thread........\n");
    testThread.start(callback(&testplayer, &test_player_class::adjust_volume));

    printf("\n[EDUCHECK] Checking volume value when potentiometer is turned....");

    // Set is_playing to true
    printf("\n[EDUCHECK] Checking is_playing==true case........\n");
    testplayer.setIs_playing(true);
    testplayer.read_potentiometer(testvalue);

    // Check value using assertion
    // Assertion testing for float requires precision, therefore times value by 0.1
    // Mbed AnalogIn value is in float range of 0.0 to 1.0
    TEST_ASSERT_EQUAL_MESSAGE(0.1 * testvalue, testplayer.getVolume(), "adjust_volume case 1");
    wait_us(500000);

    // Repeat checks for different test volume values
    testvalue = 0;
    testplayer.read_potentiometer(testvalue);
    TEST_ASSERT_EQUAL_MESSAGE(0.1 * testvalue, testplayer.getVolume(), "adjust_volume case 2");
    wait_us(500000);

    testvalue = 2;
    testplayer.read_potentiometer(testvalue);
    TEST_ASSERT_EQUAL_MESSAGE(0.1 * testvalue, testplayer.getVolume(), "adjust_volume case 3");
    wait_us(500000);

    testvalue = 9.9; //somehow breaks with values >10
    testplayer.read_potentiometer(testvalue);
    TEST_ASSERT_EQUAL_MESSAGE(0.1 * testvalue, testplayer.getVolume(), "adjust_volume case 4");
    wait_us(500000);

    testvalue = 1;
    testplayer.read_potentiometer(testvalue);
    TEST_ASSERT_EQUAL_MESSAGE(0.1 * testvalue, testplayer.getVolume(), "adjust_volume case 5");
    wait_us(500000);

    // Repeat checks with is_playing = false
    printf("\n[EDUCHECK] Checking is_playing==false case........\n");
    testplayer.setIs_playing(false);
    testvalue = 1.1;
    testplayer.read_potentiometer(testvalue);
    TEST_ASSERT_EQUAL_MESSAGE(0, testplayer.getSpeaker(), "get_input button assertion case 6");
    wait_us(500000);

    testvalue = 1.6;
    testplayer.read_potentiometer(testvalue);
    TEST_ASSERT_EQUAL_MESSAGE(0, testplayer.getSpeaker(), "get_input button assertion case 7");
    wait_us(500000);

    testvalue = 1.1;
    testplayer.read_potentiometer(testvalue);
    TEST_ASSERT_EQUAL_MESSAGE(0, testplayer.getSpeaker(), "get_input button assertion case 8");
    wait_us(500000);

    testvalue = 10;
    testplayer.read_potentiometer(testvalue);
    TEST_ASSERT_EQUAL_MESSAGE(0, testplayer.getSpeaker(), "get_input button assertion case 9");
    wait_us(500000);

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
    Case("test_volume", test_volume)};

Specification specification(greentea_setup, cases);

int main()
{
    return !Harness::run(specification);
}