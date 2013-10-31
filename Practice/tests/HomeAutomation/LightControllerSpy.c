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

void LightController_TurnOn(int id)
{
    _id = id;
    _last_state = LIGHT_ON;
}

void LightController_TurnOff(int id)
{
    _id = id;
    _last_state = LIGHT_OFF;
}

int LightControllerSpy_getLastId(void)
{
	return _id;	
}

int LightControllerSpy_getLastState(void)
{
	return _last_state;
}

int LightControllerSpy_getLightState(int id)
{
    return LIGHT_STATE_UNKNOWN;

}
