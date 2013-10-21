extern "C"
{
#include "LightScheduler.h"
#include "LightControllerSpy.h"
#include "FakeTimeService.h"
}

#include "CppUTest/TestHarness.h"

TEST_GROUP(LightScheduler)
{
    void setup()
    {
		TimeService_Create();
		LightController_Create();
		LightScheduler_Create();
    }

    void teardown()
    {
       LightScheduler_Destroy();
	   LightController_Destroy();
	   TimeService_Destroy();
    }
};

//TEST(LightScheduler, Create)
//{
//  FAIL("Start here");
//}

// [TEST] $B=i4|2=;~$NFbIt>uBV$r3NG'$9$k(B
TEST(LightScheduler, NoChangeToLightsDuringInitialization)
{
	LONGS_EQUAL(LIGHT_ID_UNKNOWN, LightControllerSpy_getLastId());
	LONGS_EQUAL(LIGHT_STATE_UNKNOWN, LightControllerSpy_getState());
}

// [TEST] If there is no schedule, no event will be happend.
TEST(LightScheduler, NoScheduleNothingHappens)
{
	FakeTimeService_setDay(MONDAY);
	FakeTimeService_setMinuite(42);
	LightScheduler_wakeup();
	CHECK_EQUAL(LIGHT_STATE_UNKNOWN, LightControllerSpy_getState());
	CHECK_EQUAL(LIGHT_STATE_UNKNOWN, LightControllerSpy_getLastId());
}

// [TEST] $BKhF|#P#M#8;~$K%i%$%H$r(BON$B$9$k@_Dj$r$7$F!"$^$@;~4V$,Mh$J$$(B
TEST(LightScheduler, ScheduleOnEverydayNotTimeYet)
{
	LightScheduler_scheduleTurnOn(1, EVERYDAY, 60 * 20);
	FakeTimeService_setDay(MONDAY);
	FakeTimeService_setMinuite(60 * 20 -1);
	LightScheduler_wakeup();

	LONGS_EQUAL(LIGHT_ID_UNKNOWN, LightControllerSpy_getLastId());
	LONGS_EQUAL(LIGHT_STATE_UNKNOWN, LightControllerSpy_getState());
}

// [TEST] turn on every day.
TEST(LightScheduler, ScheduleOnEverydayItsTime)
{
    LightScheduler_scheduleTurnOn(1, EVERYDAY, 60*20);
    FakeTimeService_setDay(MONDAY);
    FakeTimeService_setMinuite(60*20);
    LightScheduler_wakeup();

    LONGS_EQUAL(1, LightControllerSpy_getLastId());
	LONGS_EQUAL(LIGHT_ON, LightControllerSpy_getState());
}

// [TEST] turn off every day.
TEST(LightScheduler, ScheduleOffEverydayItsTime)
{
    LightScheduler_scheduleTurnOff(1, EVERYDAY, 60*20);
    FakeTimeService_setDay(MONDAY);
    FakeTimeService_setMinuite(60*20);
    LightScheduler_wakeup();

    LONGS_EQUAL(1, LightControllerSpy_getLastId());
	LONGS_EQUAL(LIGHT_OFF, LightControllerSpy_getState());
}
