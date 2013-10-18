extern "C"
{
#include "FakeTimeService.h"
}

#include "CppUTest/TestHarness.h"

TEST_GROUP(FakeTimeService)
{
    void setup()
    {
      TimeService_Create();
    }

    void teardown()
    {
       TimeService_Destroy();
    }
};

TEST(FakeTimeService, Create)
{
	Time time;
	TimeService_getTime(&time);
	LONGS_EQUAL(TIME_UNKNOWN, time.minuite_of_day);
	LONGS_EQUAL(TIME_UNKNOWN, time.day_of_week);
}

TEST(FakeTimeService, Set)
{
	Time time;
	FakeTimeService_setMinuite(42);
	FakeTimeService_setDay(SATURDAY);
	TimeService_getTime(&time);
	LONGS_EQUAL(42, time.minuite_of_day);
	LONGS_EQUAL(SATURDAY, time.day_of_week);
}

