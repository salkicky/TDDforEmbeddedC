extern "C"
{
#include "LightControllerSpy.h"
}

#include "CppUTest/TestHarness.h"

TEST_GROUP(LightControllerSpy)
{
    void setup()
    {
      LightController_Create();
    }

    void teardown()
    {
       LightController_Destroy();
    }
};

TEST(LightControllerSpy, Create)
{
	CHECK_EQUAL(LIGHT_ID_UNKNOWN, LightControllerSpy_getLastId());
	CHECK_EQUAL(LIGHT_STATE_UNKNOWN, LightControllerSpy_getState());
}

TEST(LightControllerSpy, TurnOn)
{
    LightController_TurnOn(1);
    CHECK_EQUAL(1, LightControllerSpy_getLastId());
	CHECK_EQUAL(LIGHT_STATE_TURN_ON, LightControllerSpy_getState());
}

TEST(LightControllerSpy, TurnOff)
{
    LightController_TurnOff(1);
    CHECK_EQUAL(1, LightControllerSpy_getLastId());
	CHECK_EQUAL(LIGHT_STATE_TURN_OFF, LightControllerSpy_getState());
}
