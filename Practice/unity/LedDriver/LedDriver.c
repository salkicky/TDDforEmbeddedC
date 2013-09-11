#include <stdlib.h>
#include "LedDriver.h"


//-- static variable -------------------------------
static UINT16   *led_address;


//-- prototype --------------------------------------
static UINT16 convertLedNumberToBit(int led_numer);


//-- function ---------------------------------------
// Create, and initialize LEDs
void LedDriver_Create(UINT16 * address)
{
    led_address = address;
    *led_address = 0;
}

// TurnOn LED
void LedDriver_TurnOn(int led_number)
{
    *led_address |= convertLedNumberToBit(led_number); 
}

// Turn off LED
void LedDriver_TurnOff(int led_number)
{
    *led_address = 0;
}

// convert LED number to bit
UINT16 convertLedNumberToBit(int led_number)
{
    return (1 << (led_number - 1));
}
