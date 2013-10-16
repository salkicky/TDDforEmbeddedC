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

