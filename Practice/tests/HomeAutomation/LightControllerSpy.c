#include "LightControllerSpy.h"

static int _last_state;
static int _id;

void LightController_Create(void)
{
    _id = LIGHT_ID_UNKNOWN;
    _last_state = LIGHT_STATE_UNKNOWN;
}

void LightController_Destroy(void)
{
}

int LightControllerSpy_getLastId(void)
{
	return _id;	
}

int LightControllerSpy_getState(void)
{
	return _last_state;
}


