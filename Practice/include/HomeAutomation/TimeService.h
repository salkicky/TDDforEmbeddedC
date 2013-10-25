#ifndef D_TimeService_H
#define D_TimeService_H

/**********************************************************
 *
 * TimeService is responsible for ...
 *
 **********************************************************/

typedef struct {
	int	minuite_of_day;
	int	day_of_week;
} Time;
	
enum DAY {
	SUNDAY=0, MONDAY, TUESDAY, WEDNSDAY, THURSDAY, FRIDAY, SATURDAY,
    EVERYDAY, WEEKEND,
    NONE
};

typedef enum DAY DAY;

void TimeService_Create(void);
void TimeService_Destroy(void);

void TimeService_getTime(Time *time);

#endif  /* D_TimeService_H */
