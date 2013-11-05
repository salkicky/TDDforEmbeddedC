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
	CHECK_EQUAL(LIGHT_STATE_UNKNOWN, LightControllerSpy_getLastState());
}

TEST(LightControllerSpy, TurnOn)
{
    LightController_TurnOn(1);
    CHECK_EQUAL(1, LightControllerSpy_getLastId());
	CHECK_EQUAL(LIGHT_ON, LightControllerSpy_getLastState());
}

TEST(LightControllerSpy, TurnOff)
{
    LightController_TurnOff(1);
    CHECK_EQUAL(1, LightControllerSpy_getLastId());
	CHECK_EQUAL(LIGHT_OFF, LightControllerSpy_getLastState());
}

TEST(LightControllerSpy, RememberAllLightState)
{
    LightController_TurnOn(0);
    LightController_TurnOn(31);
	CHECK_EQUAL(LIGHT_ON, LightControllerSpy_getLightState(0));
	CHECK_EQUAL(LIGHT_ON, LightControllerSpy_getLightState(31));
}
