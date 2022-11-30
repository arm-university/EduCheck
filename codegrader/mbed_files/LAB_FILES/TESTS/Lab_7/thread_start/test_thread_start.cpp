/*
 * Copyright (c) 2020 Arm Limited and affiliates.
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
#include "utest/utest.h"
#include "unity/unity.h"
#include "greentea-client/test_env.h"
#include <stdio.h>
#include "test_player_class.h"

using namespace utest::v1;
using namespace main_app;

static control_t test_thread_starter(const size_t call_count)
{
    /* Test that threads start if thread_starter() is called */
    /* Test that threads start if thread_terminator() works */

    // Create a test mp3player object
    test_player_class testplayer;

    // Check that there shouldn't be any threads running
    printf("/n[EDUCHECK] Checking that there is no running threads...");
    TEST_ASSERT_EQUAL_MESSAGE(Thread::Deleted, testplayer.getThreadStatus("t1"), "Thread t1 assertion at reset");
    TEST_ASSERT_EQUAL_MESSAGE(Thread::Deleted, testplayer.getThreadStatus("t2"), "Thread t2 assertion at reset");
    TEST_ASSERT_EQUAL_MESSAGE(Thread::Deleted, testplayer.getThreadStatus("t3"), "Thread t3 assertion at reset");

    // Call thread_starter function
    printf("/n[EDUCHECK] Calling thread starter function now...");
    testplayer.thread_starter();

    // Check status of threads
    printf("/n[EDUCHECK] Checking that threads are running...");
    TEST_ASSERT_EQUAL_MESSAGE(Thread::Ready, testplayer.getThreadStatus("t1"), "Thread t1 running assertion");
    TEST_ASSERT_EQUAL_MESSAGE(Thread::Ready, testplayer.getThreadStatus("t2"), "Thread t2 running assertion");
    TEST_ASSERT_EQUAL_MESSAGE(Thread::Ready, testplayer.getThreadStatus("t3"), "Thread t3 running assertion");

    // Terminate threads before test exits
    testplayer.thread_terminator();

    // Check if properly terminated
    TEST_ASSERT_EQUAL_MESSAGE(Thread::Deleted, testplayer.getThreadStatus("t1"), "Thread t1 assertion at reset");
    TEST_ASSERT_EQUAL_MESSAGE(Thread::Deleted, testplayer.getThreadStatus("t2"), "Thread t2 assertion at reset");
    TEST_ASSERT_EQUAL_MESSAGE(Thread::Deleted, testplayer.getThreadStatus("t3"), "Thread t3 assertion at reset");

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

    Case("test_thread_starter", test_thread_starter)};

Specification specification(greentea_setup, cases);

int main()
{
    return !Harness::run(specification);
}
