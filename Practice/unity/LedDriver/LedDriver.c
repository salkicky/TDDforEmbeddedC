#include <stdlib.h>
#include "LedDriver.h"

#define ALL_LEDS_OFF    0
#define ALL_LEDS_ON     ~(ALL_LEDS_OFF) 

//-- static variable -------------------------------
static UINT16   *led_address;


//-- prototype --------------------------------------
static UINT16 convertLedNumberToBit(int led_numer);


//-- PUBLIC ---------------------------------------
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
    *led_address &= ~(convertLedNumberToBit(led_number));
}

// TurnOn All LEDs
void LedDriver_TurnAllOn(void)
{
    *led_address = ALL_LEDS_ON;
}

// TurnOff All LEDs
void LedDriver_TurnAllOff(void)
{
    *led_address = ~(ALL_LEDS_ON);
}


//--- PRIVATE ------------------------------------------
// convert LED number to bit
UINT16 convertLedNumberToBit(int led_number)
{
    return (1 << (led_number - 1));
}
