extern "C"
{
#include "LightScheduler.h"
#include "LightControllerSpy.h"
#include "FakeTimeService.h"
}

#include "CppUTest/TestHarness.h"

/* ------------------------------- */

/**************************************************
 * Helper : $B:G8e$N%i%$%HA`:n>uBV$r%A%'%C%/$9$k(B
 **************************************************/
static void _checkLightState(int expected_id, int expected_state)
{
	LONGS_EQUAL(expected_id, LightControllerSpy_getLastId());
	LONGS_EQUAL(expected_state, LightControllerSpy_getState());
}

/**************************************************
 * Helper : FakeTimeService$B$X;~4V$r%;%C%H$9$k(B
 **************************************************/
static void _setFakeTime(DAY day, long minuite_of_day)
{
    FakeTimeService_setDay(day);
    FakeTimeService_setMinuite(minuite_of_day);
}
/* ------------------------------- */
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
	_checkLightState(LIGHT_ID_UNKNOWN, LIGHT_STATE_UNKNOWN);
}

// [TEST] If there is no schedule, no event will be happend.
TEST(LightScheduler, NoScheduleNothingHappens)
{
	_setFakeTime(MONDAY, 42);

	LightScheduler_wakeup();
	_checkLightState(LIGHT_ID_UNKNOWN, LIGHT_STATE_UNKNOWN);
}

// [TEST] $BKhF|#P#M#8;~$K%i%$%H$r(BON$B$9$k@_Dj$r$7$F!"$^$@;~4V$,Mh$J$$(B
TEST(LightScheduler, ScheduleOnEverydayNotTimeYet)
{
	LightScheduler_scheduleTurnOn(1, EVERYDAY, 60 * 20);

	_setFakeTime(MONDAY, 60*20-1);
	LightScheduler_wakeup();

	_checkLightState(LIGHT_ID_UNKNOWN, LIGHT_STATE_UNKNOWN);
}

// [TEST] turn on every day.
TEST(LightScheduler, ScheduleOnEverydayItsTime)
{
    LightScheduler_scheduleTurnOn(1, EVERYDAY, 60*20);

	_setFakeTime(MONDAY, 60*20);
    LightScheduler_wakeup();

	_checkLightState(1, LIGHT_ON);
}

// [TEST] turn off every day.
TEST(LightScheduler, ScheduleOffEverydayItsTime)
{
    LightScheduler_scheduleTurnOff(1, EVERYDAY, 60*20);

	_setFakeTime(MONDAY, 60*20);
    LightScheduler_wakeup();

	_checkLightState(1, LIGHT_OFF);
}
