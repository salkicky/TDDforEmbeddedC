#include "FakeTimeService.h"

static Time *_tp;

void TimeService_Create(void)
{
}

void TimeService_Destroy(void)
{
}

void TimeService_getTime(Time *time)
{
	_tp = time;

	_tp->minute_of_day = TIME_UNKNOWN;
	_tp->day_of_year = TIME_UNKNOWN;
}

/*-----------------------------------*/
void FakeTimeService_setMinute(long minute)
{
	_tp->minute_of_day = minute;
}

void FakeTimeService_setDay(enum WEEK_DAY day)
{
	_tp->day_of_year = day;
}


