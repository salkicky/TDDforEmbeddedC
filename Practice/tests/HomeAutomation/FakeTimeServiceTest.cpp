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
	LONGS_EQUAL(TIME_UNKNOWN, time.minute_of_day);
	LONGS_EQUAL(TIME_UNKNOWN, time.day_of_year);
}

