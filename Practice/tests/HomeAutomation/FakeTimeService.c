#include "FakeTimeService.h"

static Time _time;

void TimeService_Create(void)
{
	_time.minute_of_day = TIME_UNKNOWN;
	_time.day_of_week = TIME_UNKNOWN;
}

void TimeService_Destroy(void)
{
}

void TimeService_getTime(Time *time)
{
	*time = _time;
}

/*-----------------------------------*/
void FakeTimeService_setMinute(long minute)
{
	_time.minute_of_day = minute;
}

void FakeTimeService_setDay(enum WEEK_DAY day)
{
	_time.day_of_week = day;
}


