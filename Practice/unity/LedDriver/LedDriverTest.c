#include "unity_fixture.h"
#include <stdlib.h>
#include "LedDriver.h"

TEST_GROUP(LedDriver);

static UINT16   virtual_leds;

/* SET UP */
TEST_SETUP(LedDriver)
{
    LedDriver_Create(&virtual_leds);
}

/* TEAR DOWN */
TEST_TEAR_DOWN(LedDriver)
{
}

/*--------------------------------------------*/
TEST(LedDriver, LedsOffAfterCreate)
{
    TEST_ASSERT_EQUAL_HEX16(0, virtual_leds);
}


TEST(LedDriver, TurnOnLedOne)
{
    LedDriver_TurnOn(1);
    TEST_ASSERT_EQUAL_HEX16(1, virtual_leds); 
}


TEST(LedDriver, TurnOffLedOne)
{
    LedDriver_TurnOn(1);
    LedDriver_TurnOff(1);
    TEST_ASSERT_EQUAL_HEX16(0, virtual_leds); 
}

TEST(LedDriver, TurnOnMultipleLeds)
{
    LedDriver_TurnOn(9);
    LedDriver_TurnOn(8);
    TEST_ASSERT_EQUAL_HEX16(0x0180, virtual_leds);
}

TEST(LedDriver, TurnOffAnyLeds)
{
    LedDriver_TurnOn(9);
    LedDriver_TurnOn(8);
    LedDriver_TurnOff(8);
    TEST_ASSERT_EQUAL_HEX16(0x0100, virtual_leds);
}
