#ifndef D_LightScheduler_H
#define D_LightScheduler_H

/**********************************************************
 *
 * LightScheduler is responsible for ...
 *
 **********************************************************/

#include "LightController.h"
#include "TimeService.h"

void LightScheduler_Create(void);
void LightScheduler_Destroy(void);

void LightScheduler_wakeup(void);

#endif  /* D_FakeLightScheduler_H */
