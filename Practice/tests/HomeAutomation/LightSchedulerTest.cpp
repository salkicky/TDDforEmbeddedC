extern "C"
{
#include "LightScheduler.h"
#include "LightControllerSpy.h"
#include "FakeTimeService.h"
}

#include "CppUTest/TestHarness.h"

/* ======================================================================== */

/**************************************************
 * Helper : 最後のライト操作状態をチェックする
 **************************************************/
static void _checkLightState(int expected_id, int expected_state)
{
    if (expected_id == LIGHT_ID_UNKNOWN)
    {
        LONGS_EQUAL(expected_id, LightControllerSpy_getLastId());
        LONGS_EQUAL(expected_state, LightControllerSpy_getLastState());
    }
    else 
    {
        LONGS_EQUAL(expected_state, LightControllerSpy_getLightState(expected_id));
    }
}

/**************************************************
 * Helper : 現在時刻をセットする
 **************************************************/
static void _setTime(DAY day, long minuite_of_day)
{
    FakeTimeService_setDay(day);
    FakeTimeService_setMinuite(minuite_of_day);
}

/* ======================================================================== */
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

// [TEST] 初期化時の内部状態を確認する
TEST(LightScheduler, NoChangeToLightsDuringInitialization)
{
	_checkLightState(LIGHT_ID_UNKNOWN, LIGHT_STATE_UNKNOWN);
}

// [TEST] If there is no schedule, no event will be happend.
TEST(LightScheduler, NoScheduleNothingHappens)
{
	_setTime(MONDAY, 42);

	LightScheduler_wakeup();
	_checkLightState(LIGHT_ID_UNKNOWN, LIGHT_STATE_UNKNOWN);
}

// [TEST] 毎日ＰＭ８時にライトをONする設定をして、まだ時間が来ない
TEST(LightScheduler, ScheduleOnEverydayNotTimeYet)
{
	LightScheduler_scheduleTurnOn(1, EVERYDAY, 60 * 20);

	_setTime(MONDAY, 60*20-1);
	LightScheduler_wakeup();

	_checkLightState(LIGHT_ID_UNKNOWN, LIGHT_STATE_UNKNOWN);
}

// [TEST] turn on every day.
TEST(LightScheduler, ScheduleOnEverydayItsTime)
{
    LightScheduler_scheduleTurnOn(1, EVERYDAY, 60*20);

	_setTime(MONDAY, 60*20);
    LightScheduler_wakeup();

	_checkLightState(1, LIGHT_ON);
}

// [TEST] turn off every day.
TEST(LightScheduler, ScheduleOffEverydayItsTime)
{
    LightScheduler_scheduleTurnOff(1, EVERYDAY, 60*20);

	_setTime(MONDAY, 60*20);
    LightScheduler_wakeup();

	_checkLightState(1, LIGHT_OFF);
}

// [TEST] schedule Tuesday, and now is Monday.
TEST(LightScheduler, ScheduleTuesdayButItsMonday)
{
    LightScheduler_scheduleTurnOn(3, TUESDAY, 1200);
	_setTime(MONDAY, 60*20);
    LightScheduler_wakeup();

	_checkLightState(LIGHT_ID_UNKNOWN, LIGHT_STATE_UNKNOWN);
}

// [TEST] schedule Tuesday, and now is Tursday
TEST(LightScheduler, ScheduleTuesdayItsTime)
{
    LightScheduler_scheduleTurnOn(3, TUESDAY, 1200);
	_setTime(TUESDAY, 60*20);
    LightScheduler_wakeup();

	_checkLightState(3, LIGHT_ON);
}

// [TEST] schedule Weekend, but its Friday 
TEST(LightScheduler, ScheduleWeekendButItsFriday)
{
    LightScheduler_scheduleTurnOn(3, WEEKEND, 1200);
	_setTime(FRIDAY, 60*20);
    LightScheduler_wakeup();

	_checkLightState(LIGHT_ID_UNKNOWN, LIGHT_STATE_UNKNOWN);
}

// [TEST] schedule Weekend, but its time
TEST(LightScheduler, ScheduleWeekendItsSaturday)
{
    LightScheduler_scheduleTurnOn(3, WEEKEND, 1200);
	_setTime(SATURDAY, 60*20);
    LightScheduler_wakeup();

	_checkLightState(3, LIGHT_ON);
}
// [TEST] schedule Weekend, but its time
TEST(LightScheduler, ScheduleWeekendItsSunday)
{
    LightScheduler_scheduleTurnOn(3, WEEKEND, 1200);
	_setTime(SUNDAY, 60*20);
    LightScheduler_wakeup();

	_checkLightState(3, LIGHT_ON);
}

TEST(LightScheduler, ScheduleTwoEventsAtTheSameTime)
{
    LightScheduler_scheduleTurnOn(3, SUNDAY, 1200);
    LightScheduler_scheduleTurnOn(12, SUNDAY, 1200);

    _setTime(SUNDAY, 1200);

    LightScheduler_wakeup();

    _checkLightState(3, LIGHT_ON);
    _checkLightState(12, LIGHT_ON);
}

/* ============================================================== */
TEST_GROUP(LightSchedulerInitAndCleanup)
{
    void setup() {}

    void teardown() {}
};

// [TEST] set periodic callback to TimeService
TEST(LightSchedulerInitAndCleanup, CreateStartOneMinuiteAlarm)
{
    LightScheduler_Create();
    POINTERS_EQUAL((void *)LightScheduler_wakeup,
                    (void *)FakeTimeService_getAlarmCallback());
    LONGS_EQUAL(60, FakeTimeService_getAlarmPeriod());
    LightScheduler_Destroy();
}

// [TEST] reset callback from TimeService
TEST(LightSchedulerInitAndCleanup, DestroyCancelOneMinuiteAlarm)
{
    LightScheduler_Create();
    LightScheduler_Destroy();

    POINTERS_EQUAL((void *)0,
                    (void *)FakeTimeService_getAlarmCallback());

}
