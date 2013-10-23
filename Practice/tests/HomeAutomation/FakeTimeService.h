#ifndef D_FakeTimeService_H
#define D_FakeTimeService_H

/**********************************************************
 *
 * FakeTimeService is responsible for ...
 *
 **********************************************************/

#include "TimeService.h"

enum {
	TIME_UNKNOWN
};


/*
void FakeTimeService_Create(void);
void FakeTimeService_Destroy(void);
*/

void FakeTimeService_setMinuite(int minuite);
void FakeTimeService_setDay(DAY day);

#endif  /* D_FakeTimeService_H */
