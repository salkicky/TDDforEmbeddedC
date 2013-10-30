#include "FakeTimeService.h"

static Time _time;
static WAKEUP_CALLBACK _callback;
static int _period;

/* ----------------------------------------- 
 * Fake
 * ----------------------------------------- */
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

void TimeService_setPeriodicAlarmInSeconds(int seconds, WAKEUP_CALLBACK callback)
{
    _period = seconds;
    _callback = callback;
}

void TimeService_cancelPeriodicAlarmInSeconds(int seconds, WAKEUP_CALLBACK callback)
{
    if ((_period == seconds) && (_callback == callback)) {
        _period = 0;
        _callback = (void *)0;
    }
}

/* ----------------------------------------- 
 * Test interface 
 * ----------------------------------------- */
void FakeTimeService_setMinuite(int minuite)
{
	_time.minuite_of_day = minuite;
}

void FakeTimeService_setDay(DAY day)
{
	_time.day_of_week = day;
}

WAKEUP_CALLBACK FakeTimeService_getAlarmCallback(void)
{
    return _callback;
}

int FakeTimeService_getAlarmPeriod(void)
{
    return _period;
}

