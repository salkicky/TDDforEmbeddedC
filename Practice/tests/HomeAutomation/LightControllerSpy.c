#include "LightControllerSpy.h"

static int _last_state;
static int _id;
static int _light_state[MAX_LIGHT_ID];

void LightController_Create(void)
{
    int i;

    _id = LIGHT_ID_UNKNOWN;
    _last_state = LIGHT_STATE_UNKNOWN;

    for (i = 0; i < MAX_LIGHT_ID; i++) {
        _light_state[i] = LIGHT_STATE_UNKNOWN;
    }
}

void LightController_Destroy(void)
{
}

void LightController_TurnOn(int id)
{
    _id = id;
    _last_state = LIGHT_ON;

    _light_state[_id] = _last_state;
}

void LightController_TurnOff(int id)
{
    _id = id;
    _last_state = LIGHT_OFF;

    _light_state[_id] = _last_state;
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
    return _light_state[id];

}
