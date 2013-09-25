#include <stdlib.h>
#include "LedDriver.h"
#include "RuntimeError.h"

#define ALL_LEDS_OFF    0
#define ALL_LEDS_ON     ~(ALL_LEDS_OFF) 

//-- static variable -------------------------------
static UINT16   *led_address;
static UINT16   leds_image;

//-- data ------------------------------------------
enum { FIRST_LED=1, LAST_LED=16};

//-- prototype --------------------------------------
static UINT16 convertLedNumberToBit(int led_numer);
static void   updateLedHardware(void);
static BOOL   isLedOutOfBounds(int led_number);
static void   setImageBit(int led_number);
static void   clearImageBit(int led_number);


//-- PUBLIC ---------------------------------------
// Create, and initialize LEDs
void LedDriver_Create(UINT16 * address)
{
    led_address = address;

    leds_image = 0;
    updateLedHardware();
}

// TurnOn LED
void LedDriver_TurnOn(int led_number)
{
    if (TRUE == isLedOutOfBounds(led_number))
    {
        RUNTIME_ERROR("LED Driver : out-of-bounds LED", -1);
        return;
    }

    setImageBit(led_number);
    updateLedHardware();
}

// Turn off LED
void LedDriver_TurnOff(int led_number)
{
    if (TRUE == isLedOutOfBounds(led_number))
    {
        RUNTIME_ERROR("LED Driver : out-of-bounds LED", -1);
        return;
    }

    clearImageBit(led_number);
    updateLedHardware();
}

// TurnOn All LEDs
void LedDriver_TurnAllOn(void)
{
    leds_image = ALL_LEDS_ON;
    updateLedHardware();
}

// TurnOff All LEDs
void LedDriver_TurnAllOff(void)
{
    leds_image = ALL_LEDS_OFF;
    updateLedHardware();
}


//--- PRIVATE ------------------------------------------
// convert LED number to bit
UINT16 convertLedNumberToBit(int led_number)
{
    return (1 << (led_number - 1));
}

// update LED Hardware
void updateLedHardware(void)
{
    *led_address = leds_image;
}

// check out of bounds
BOOL isLedOutOfBounds(int led_number)
{
    if ((led_number < FIRST_LED) || (LAST_LED < led_number))
    {
        // out of range
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

// set led image bit
void setImageBit(int led_number)
{
    leds_image |= convertLedNumberToBit(led_number); 
}

// clear led image bit
void clearImageBit(int led_number)
{
    leds_image &= ~(convertLedNumberToBit(led_number));
}
