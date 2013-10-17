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

//// [TEST] 毎日ＰＭ８時にライトをＯＮする
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

// [TEST] 初期化時の内部状態を確認する
TEST(LightScheduler, NoChangeToLightsDuringInitialization)
{
	//LONG_EQUAL(LIGHT_ID_UNKNOWN, LightControllerSpy_getLastId());
	//LONG_EQUAL(LIGHT_STATE_UNKNOWN, LightControllerSpy_getState());
}

// [TEST] If there is no schedule, no event will be happend.
TEST(LightScheduler, NoScheduleNothingHappens)
{
	FakeTimeService_setDay(MONDAY);
	FakeTimeService_setMinute(42);
	LightScheduler_wakeup();
	CHECK_EQUAL(LIGHT_STATE_UNKNOWN, LightControllerSpy_getState());
	CHECK_EQUAL(LIGHT_STATE_UNKNOWN, LightControllerSpy_getLastId());
}
