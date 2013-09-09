#include "unity_fixture.h"

TEST_GROUP_RUNNER(LedDriver)
{
    RUN_TEST_CASE(LedDriver, LedsOffAfterCreate);
    RUN_TEST_CASE(LedDriver, LedsTurnOnOne);
    RUN_TEST_CASE(LedDriver, LedsTurnOffOne);
}

