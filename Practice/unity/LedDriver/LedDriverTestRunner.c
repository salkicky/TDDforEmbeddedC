#include "unity_fixture.h"

TEST_GROUP_RUNNER(LedDriver)
{
    RUN_TEST_CASE(LedDriver, LedsOffAfterCreate);

    RUN_TEST_CASE(LedDriver, TurnOnLedOne);
    RUN_TEST_CASE(LedDriver, TurnOffLedOne);

    RUN_TEST_CASE(LedDriver, TurnOnMultipleLeds);
    RUN_TEST_CASE(LedDriver, TurnOffAnyLeds);

    RUN_TEST_CASE(LedDriver, AllOn);
    RUN_TEST_CASE(LedDriver, AllOff);

    RUN_TEST_CASE(LedDriver, LedMemoryIsNotReadable);

    RUN_TEST_CASE(LedDriver, UpperAndLowerBounds);
    RUN_TEST_CASE(LedDriver, OutOfBoundsChangesNothing);

}

