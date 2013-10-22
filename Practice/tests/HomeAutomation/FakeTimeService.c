#include "FakeTimeService.h"

static Time _time;

void TimeService_Create(void)
{
	_time.minuite_of_day = TIME_UNKNOWN;
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
void FakeTimeService_setMinuite(long minuite)
{
	_time.minuite_of_day = minuite;
}

void FakeTimeService_setDay(DAY day)
{
	_time.day_of_week = day;
}


