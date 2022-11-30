/*
 * Copyright (c) 2020 Arm Limited and affiliates.
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
#include "utest/utest.h"
#include "unity/unity.h"
#include "greentea-client/test_env.h"
#include "test_player_class.h"
#include <stdio.h>

using namespace main_app;
using namespace utest::v1;
using namespace std;

static control_t test_play_song_successful(const size_t call_count)
{
    /* Test if variable is_playing is set - this should then activate if statement in ISR */

    // Create a test mp3player object
    test_player_class testplayer;

    Thread testThread;
    printf("\n[EDUCHECK] Thread created.....");

    // Set up initial variables to run timer ISR function correctly
    printf("\n[EDUCHECK] Setting required variables.....");
    testplayer.setIs_playing(true);
    testplayer.setSong_finished(false);
    testplayer.setSong_index(0);
    testplayer.setSpeakerValue(1);
    testplayer.setK(0);

    printf("\n[EDUCHECK] Song to be checked is Fur Elise.....");
    // Retrieve song name - Fur Elise should be at index 0 of the song array
    TEST_ASSERT_EQUAL_STRING("Fur Elise -", testplayer.getSong_index().c_str());
    TEST_ASSERT_EQUAL_MESSAGE(8, testplayer.getSong_length(), "song length equal");

    // Start thread going through timer_ISR
    testThread.start(callback(&testplayer, &mp3player::timer_ISR));

    // timer_ISR has only just begun, so the song should not yet be finished playing
    TEST_ASSERT_EQUAL_MESSAGE(false, testplayer.getSong_finished(), "Song not finished");

    wait_us(10000000);

    // Ensure is_playing is set to true so that the main logic for playing the song starts
    TEST_ASSERT_EQUAL_MESSAGE(true, testplayer.getIs_playing(), "is_playing assertion");

    // Run tests that should check variables once the musical piece is finished
    // At the end of the song, the k variable and speaker should be set to 0.
    TEST_ASSERT_EQUAL_MESSAGE(0, testplayer.getSpeakerValue(), "speaker should be 0 at end of song");
    TEST_ASSERT_EQUAL_MESSAGE(0, testplayer.getK(), "k should be 0 at end of song");

    // Check that the song_finished flag has been set to true at the end of the song
    TEST_ASSERT_EQUAL_MESSAGE(true, testplayer.getSong_finished(), "Song not finished");

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
    Case("test_play_song_successful", test_play_song_successful)
    };

Specification specification(greentea_setup, cases);

int main()
{
    return !Harness::run(specification);
}
