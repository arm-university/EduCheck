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

void test_LED_status(){
	// Create a test mp3player object
	test_player_class testplayer;

	// Set input pins first
	//testplayer.set_input_pins(TEST_WITH_GREENTEA);

	// Initiate variables in class
	//testplayer.player_init();

	// Create a test thread since polling_loop is in while(1)
	Thread testThread;
	printf("\n[EDUCHECK] Thread created.....");
 	ThisThread::sleep_for(10ms);

	// Start test thread
	printf("\n[EDUCHECK] Starting thread........\n");
	testThread.start(callback(&testplayer, &mp3player::update_lcd_leds_thread));

	//delay for 500ms
	wait_us(500000);

	//Test input
	printf("\n[EDUCHECK] Testing LED status when song is playing...");
  testplayer.setIs_playing(true);

  //printf("[EDUCHECK]: Starting thread\n");
//	t1.start(update_lcd_led_thread);
	ThisThread::sleep_for(500ms);
	if(!testplayer.getIs_playing()){
			printf("\n[EDUCHECK] Checking Red-LED status when not playing...\n");
		TEST_ASSERT_EQUAL_MESSAGE(1,testplayer.get_redLed_status(),"Failed to update red led status when not playing");
		ThisThread::sleep_for(500ms);
				printf("\n[EDUCHECK] Checking blue-LED status when not playing...\n");
		TEST_ASSERT_FALSE_MESSAGE(testplayer.get_blueLed_status(),"Failed to update blue led status when not playing");
		ThisThread::sleep_for(500ms);
	}else{
				printf("\n[EDUCHECK] Checking Red-LED status when playing...\n");
		TEST_ASSERT_EQUAL_MESSAGE(0,testplayer.get_redLed_status(),"Failed to update red led status when playing");
		ThisThread::sleep_for(500ms);
				printf("\n[EDUCHECK] Checking Blue-LED status when playing...\n");
		TEST_ASSERT_TRUE_MESSAGE(testplayer.get_blueLed_status(),"Failed to update blue led status when playing");
		ThisThread::sleep_for(500ms);

	}

	if(testplayer.getWait_for_new_song()){
			printf("\n[EDUCHECK] Checking Green-LED status when waiting for a new song...\n");
		TEST_ASSERT_EQUAL_MESSAGE(1,testplayer.get_greenLed_status(),"Failed to update green led status when waiting for a new song");
		ThisThread::sleep_for(500ms);
	}else{
				printf("\n[EDUCHECK] Checking Green-LED status when not waiting for a new song...\n");
		TEST_ASSERT_EQUAL_MESSAGE(0,testplayer.get_greenLed_status(),"Failed to update green led status when not waiting for a new song");
		ThisThread::sleep_for(500ms);

	}

	// Terminate test thread
	testThread.terminate();
	TEST_ASSERT_EQUAL_MESSAGE(Thread::Deleted, testThread.get_state(), "Test thread not terminated properly");

}


utest::v1::status_t greentea_setup(const size_t number_of_cases)
{
	// Here, we specify the timeout (60s) and the host test (a built-in host test or the name of our Python file)
	GREENTEA_SETUP(60, "default_auto");

	return greentea_test_setup_handler(number_of_cases);
}

// List of test cases in this file
Case cases[] = {
	//Case("Update lcd test", test_update_lcd),
	Case("Led Status test", test_LED_status)
};

Specification specification(greentea_setup, cases);

int main()
{
	return !Harness::run(specification);
}
