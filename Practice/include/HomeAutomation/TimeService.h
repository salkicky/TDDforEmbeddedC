#ifndef D_TimeService_H
#define D_TimeService_H

/**********************************************************
 *
 * TimeService is responsible for ...
 *
 **********************************************************/

typedef struct {
	long	minute_of_day;
	long	day_of_week;
} Time;
	
enum WEEK_DAY {
	SUNDAY, MONDAY, TUESDAY, WEDNSDAY, THURSDAY, FRYDAY, SATURDAY,
    EVERYDAY
};

void TimeService_Create(void);
void TimeService_Destroy(void);

void TimeService_getTime(Time *time);

#endif  /* D_FakeTimeService_H */
