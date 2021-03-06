#ifndef D_LightScheduler_H
#define D_LightScheduler_H

/**********************************************************
 *
 * LightScheduler is responsible for ...
 *
 **********************************************************/

#include "TimeService.h"

void LightScheduler_Create(void);
void LightScheduler_Destroy(void);

void LightScheduler_wakeup(void);

void LightScheduler_scheduleTurnOn(int id, DAY day, int minuite_of_day);
void LightScheduler_scheduleTurnOff(int id, DAY day, int minuite_of_day);

#endif  /* D_LightScheduler_H */
