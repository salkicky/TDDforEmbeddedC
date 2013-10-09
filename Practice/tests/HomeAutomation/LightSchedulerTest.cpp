extern "C"
{
#include "LightScheduler.h"
}

#include "CppUTest/TestHarness.h"

TEST_GROUP(LightScheduler)
{
    void setup()
    {
      LightScheduler_Create();
    }

    void teardown()
    {
       LightScheduler_Destroy();
    }
};

//TEST(LightScheduler, Create)
//{
//  FAIL("Start here");
//}

//// [TEST] $BKhF|#P#M#8;~$K%i%$%H$r#O#N$9$k(B
//TEST(LighScheduler, ScheduleOneEverydayNotTimeYet)
//{
//	LightScheduler_scheduleTurnOn(1, EVERYDAY, 60 * 20);
//	FakeTimeService_setDay(MONDAY);
//	FakeTimeService_setMinuite(60 * 20 -1);
//	LightScheduler_wakeup();
//
//	LONG_EQUAL(LIGHT_ID_UNKNOWN, LightSchedulerSpy_getLastId());
//	LONG_EQUAL(LIGHT_STATE_UNKNOWN, LightSchedulerSpy_getState());
//}

// [TEST] $B=i4|2=;~$NFbIt>uBV$r3NG'$9$k(B
TEST(LightScheduler, NoChangeToLightsDuringInitialization)
{
	//LONG_EQUAL(LIGHT_ID_UNKNOWN, LightControllerSpy_getLastId());
	//LONG_EQUAL(LIGHT_STATE_UNKNOWN, LightControllerSpy_getState());
}
