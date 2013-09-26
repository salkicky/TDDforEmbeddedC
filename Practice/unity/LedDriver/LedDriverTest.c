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
    RuntimeErrorStub_reset();
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
    LedDriver_TurnAllOn();
    LedDriver_TurnOff(8);
    TEST_ASSERT_EQUAL_HEX16(0xFF7F, virtual_leds);
}


TEST(LedDriver, AllOn)
{
    LedDriver_TurnAllOn();
    TEST_ASSERT_EQUAL_HEX16(0xFFFF, virtual_leds);
}


TEST(LedDriver, AllOff)
{
    LedDriver_TurnAllOff();
    TEST_ASSERT_EQUAL_HEX16(0x0000, virtual_leds);
}


TEST(LedDriver, LedMemoryIsNotReadable)
{
    virtual_leds = 0xffff;
    LedDriver_TurnOn(8);
    TEST_ASSERT_EQUAL_HEX16(0x0080, virtual_leds);
}

// 境界条件のテスト max, min
TEST(LedDriver, UpperAndLowerBounds)
{
    LedDriver_TurnOn(1);
    LedDriver_TurnOn(16);
    TEST_ASSERT_EQUAL_HEX16(0x8001, virtual_leds);
}

// 境界条件のテスト TurnOn
TEST(LedDriver, OutOfBoundsTurnOnDoesNoHarm)
{
    LedDriver_TurnOn(-1);
    LedDriver_TurnOn(0);
    LedDriver_TurnOn(17);
    LedDriver_TurnOn(3141);
    TEST_ASSERT_EQUAL_HEX16(0, virtual_leds);
}

// 境界条件のテスト TurnOff
TEST(LedDriver, OutOfBoundsTurnOffDoesNoHarm)
{
    LedDriver_TurnAllOn();
    LedDriver_TurnOff(-1);
    LedDriver_TurnOff(0);
    LedDriver_TurnOff(17);
    LedDriver_TurnOff(3141);
    TEST_ASSERT_EQUAL_HEX16(0xffff, virtual_leds);
}

// Check RuntimeError  TurnOn
TEST(LedDriver, CheckErrorMessageOfOutOfBoubdsTurnOn)
{
	LedDriver_TurnOn(-1);
    TEST_ASSERT_EQUAL_STRING("LED Driver : out-of-bounds LED", RuntimeErrorStub_getLastError());
    TEST_ASSERT_EQUAL(-1, RuntimeErrorStub_getLastParameter());
}

// Check RuntimeError  TurnOff
TEST(LedDriver, CheckErrorMessageOfOutOfBoubdsTurnOff)
{
    LedDriver_TurnAllOn();
	LedDriver_TurnOff(17);
    TEST_ASSERT_EQUAL_STRING("LED Driver : out-of-bounds LED", RuntimeErrorStub_getLastError());
    TEST_ASSERT_EQUAL(-1, RuntimeErrorStub_getLastParameter());
}

// get led status is on?
TEST(LedDriver, isOn)
{
    TEST_ASSERT_FALSE(LedDriver_isOn(11));
    LedDriver_TurnOn(11);
    TEST_ASSERT_TRUE(LedDriver_isOn(11));
}

// get led status is off?
TEST(LedDriver, isOff)
{
    TEST_ASSERT_TRUE(LedDriver_isOff(1));
}

// Check RuntimeError isOn
TEST(LedDriver, CheckErrorMessageOfOutOfBoubdsIsOn)
{
	LedDriver_isOn(17);
    TEST_ASSERT_EQUAL_STRING("LED Driver : out-of-bounds LED", RuntimeErrorStub_getLastError());
    TEST_ASSERT_EQUAL(-1, RuntimeErrorStub_getLastParameter());
}

// Check OutOfBoundsLedsAreAlwaysOff
TEST(LedDriver, OutOfBoundsLedsAreAlwaysOff)
{
    TEST_ASSERT_TRUE(LedDriver_isOff(0));
    TEST_ASSERT_TRUE(LedDriver_isOff(17));
    TEST_ASSERT_FALSE(LedDriver_isOn(0));
    TEST_ASSERT_FALSE(LedDriver_isOn(17));
}

// turn off multiple Leds
TEST(LedDriver, TurnOffMultipleLeds)
{
    LedDriver_TurnAllOn();
    LedDriver_TurnOff(9);
    LedDriver_TurnOff(8);
    TEST_ASSERT_EQUAL_HEX16( (UINT16)(~(0x0180)), virtual_leds);
}
