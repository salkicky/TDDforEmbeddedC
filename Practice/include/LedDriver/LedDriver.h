#ifndef LED_DRIVER_H
#define LED_DRIVER_H

#include "RuntimeErrorStub.h"
#include "type.h"

void LedDriver_Create(UINT16 * address);
void LedDriver_TurnOn(int led_number);
void LedDriver_TurnOff(int led_number);
void LedDriver_TurnAllOn(void);
void LedDriver_TurnAllOff(void);

#endif
