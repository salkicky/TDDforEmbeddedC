#include "LightControllerSpy.h"

static long state;
static long id;

long LightControllerSpy_getLastId(void)
{
	return id;	
}

long LightControllerSpy_getState(void)
{
	return state;
}


