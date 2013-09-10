#include <stdlib.h>
#include "LedDriver.h"

static UINT16   *led_address;

void LedDriver_Create(UINT16 * address)
{
    led_address = address;
    *led_address = 0;
}

void LedDriver_TurnOn(int led_number)
{
    *led_address = 1;
}

void LedDriver_TurnOff(int led_number)
{
    *led_address = 0;
}
