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

// [TEST] 初期化時の内部状態を確認する
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

// [TEST] 毎日ＰＭ８時にライトをONする設定をして、まだ時間が来ない
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
