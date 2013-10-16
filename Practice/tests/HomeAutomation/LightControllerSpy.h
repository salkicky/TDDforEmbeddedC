#ifndef D_LightControllerSpy_H
#define D_LightControllerSpy_H

#include "LightController.h"

/**********************************************************
 *
 * LightControllerSpy is responsible for ...
 *
 **********************************************************/

enum {
		LIGHT_STATE_UNKNOWN = -1
};

enum {
		LIGHT_ID_UNKNOWN = -1
};

int LightControllerSpy_getLastId(void);
int LightControllerSpy_getState(void);

#endif  /* D_FakeLightControllerSpy_H */
