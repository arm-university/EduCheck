/*H**********************************************************************
* FILENAME : main.cpp          DESIGN REF:
*
* DESCRIPTION :
*       LCD test implementation. Strings (song name, number and player status) are
*		written to the LCD, these strings are read back and compared to the original
*		string to see if they match.
*
* PUBLIC FUNCTIONS :
*
* NOTES :
*		This test employs Greentea automated testing tool.
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

using namespace main_app;
using namespace utest::v1;
using namespace std;

// Tescase to check LCD functionality by setting a test string and selection
// inputs, reading data written to LCD and verifying result.
static control_t lcd_content_test(const size_t call_count)
{
	// Create a test mp3player object
	test_player_class testplayer;

	// Create test threads since polling_loop is in while(1)
	Thread testThread;
	Thread pollingThread;
	printf("\n[EDUCHECK] Threads created.....\n");

	// Enter test string to verify lcd print
	printf("\n[EDUCHECK] Entering the song name in row 0...\n");
	testplayer.setLcd_text(0, "Do you want to ");
	printf("\n[EDUCHECK] Entering the song name no 4 in row 1...\n");
	testplayer.setLcd_text(1, "play song 4");
	printf("\n[EDUCHECK] Testing thread t1 function now...\n");

	// Start test thread
	printf("\n[EDUCHECK] Starting LCD_LED thread........\n");
	testThread.start(callback(&testplayer, &mp3player::update_lcd_leds_thread));

	// Delay for 500ms
	wait_us(500000);

	// Selecting the song to play
	printf("\n[EDUCHECK] Selecting song 4: Nocturne in E ........\n");
	testplayer.setSongNumber(4);
	printf("\n[EDUCHECK] Pressing button1 to select the song  ........\n");
	testplayer.setGet_inputPin(1);

	// Start polling test thread
	printf("\n[EDUCHECK] Starting polling_loop thread........\n");
	pollingThread.start(callback(&testplayer, &mp3player::polling_loop));

	// Delay for 500ms
	wait_us(500000);

	// Create string that reads the data written to lcd
	string lcd_read0 = testplayer.getCheck_lcd_data(0);
	string lcd_read1 = testplayer.getCheck_lcd_data(1);

	// Delay for 1ms
	wait_us(1000);

	// Use assertions to verify read data
	TEST_ASSERT_EQUAL_STRING_MESSAGE(testplayer.getLcd_text(0).c_str(), lcd_read0.c_str(), "song name row 0 match!");
	TEST_ASSERT_EQUAL_STRING_MESSAGE(testplayer.getLcd_text(1).c_str(), lcd_read1.c_str(), "song name row 1 match!");
	TEST_ASSERT_TRUE_MESSAGE(testplayer.getWait_for_new_song(), "no new song");

	printf("\n[EDUCHECK] PLAY mode: Deassert button now (release)........\n");
	testplayer.setSongNumber(0);
	testplayer.setGet_inputPin(0);

	// Enter test string for song name to verify lcd print
	printf("\n[EDUCHECK] Entering the song name in row 0...\n");
	testplayer.setLcd_text(0, "Nocturne in E ");
	printf("\n[EDUCHECK] Entering the song name in row 1...\n");
	testplayer.setLcd_text(1, "flat -Chopin");
	printf("\n[EDUCHECK] Testing thread t1 function now...\n");
	wait_us(500000);

	printf("\n[EDUCHECK] Pressing button1 to confirm the song  ........\n");
	testplayer.setGet_inputPin(1);

	// Read the data written to lcd
	lcd_read0 = testplayer.getCheck_lcd_data(0);
	lcd_read1 = testplayer.getCheck_lcd_data(1);

	wait_us(500000);

	printf("\n[EDUCHECK] PLAY mode: Deassert button now (release)........\n");
	testplayer.setGet_inputPin(0);

	// Use assertions to verify read data
	TEST_ASSERT_EQUAL_STRING_MESSAGE(testplayer.getLcd_text(0).c_str(), lcd_read0.c_str(), "song name row 0 match!");
	TEST_ASSERT_EQUAL_STRING_MESSAGE(testplayer.getLcd_text(1).c_str(), lcd_read1.c_str(), "song name row 1 match!");

	// Terminate test thread
	pollingThread.terminate();
	TEST_ASSERT_EQUAL_MESSAGE(Thread::Deleted, pollingThread.get_state(), "Test thread not terminated properly");

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
	Case("test LCD content", lcd_content_test)

};

Specification specification(greentea_setup, cases);

int main()
{
	return !Harness::run(specification);
}
