#ifndef D_LightControllerSpy_H
#define D_LightControllerSpy_H

#include "LightController.h"

/**********************************************************
 *
 * LightControllerSpy is responsible for ...
 *
 **********************************************************/
#define MAX_LIGHT_ID    50

enum LIGHT_STATE {
	LIGHT_STATE_UNKNOWN = -1,
    LIGHT_ON,
	LIGHT_OFF
};
typedef enum LIGHT_STATE LIGHT_STATE;

enum LIGHT_ID {
	LIGHT_ID_UNKNOWN = -1
};
typedef enum LIGHT_ID LIGHT_ID;

int LightControllerSpy_getLastId(void);
int LightControllerSpy_getLastState(void);
int LightControllerSpy_getLightState(int id);

#endif  /* D_FakeLightControllerSpy_H */
