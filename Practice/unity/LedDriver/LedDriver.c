#include <stdlib.h>
#include "LedDriver.h"

#define ALL_LEDS_OFF    0
#define ALL_LEDS_ON     ~(ALL_LEDS_OFF) 

//-- static variable -------------------------------
static UINT16   *led_address;
static UINT16   led_image;


//-- prototype --------------------------------------
static UINT16 convertLedNumberToBit(int led_numer);


//-- PUBLIC ---------------------------------------
// Create, and initialize LEDs
void LedDriver_Create(UINT16 * address)
{
    led_address = address;
    led_image = 0;
    *led_address = led_image;
}

// TurnOn LED
void LedDriver_TurnOn(int led_number)
{
    led_image |= convertLedNumberToBit(led_number); 
    *led_address = led_image;
}

// Turn off LED
void LedDriver_TurnOff(int led_number)
{
    led_image &= ~(convertLedNumberToBit(led_number));
    *led_address = led_image;
}

// TurnOn All LEDs
void LedDriver_TurnAllOn(void)
{
    led_image = ALL_LEDS_ON;
    *led_address = led_image;
}

// TurnOff All LEDs
void LedDriver_TurnAllOff(void)
{
    led_image = ALL_LEDS_OFF;
    *led_address = led_image;
}


//--- PRIVATE ------------------------------------------
// convert LED number to bit
UINT16 convertLedNumberToBit(int led_number)
{
    return (1 << (led_number - 1));
}
