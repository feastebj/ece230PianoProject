/* DriverLib Includes */
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

/* Standard Includes */
#include <stdint.h>
#include <stdbool.h>
#include "buttons.h"
#include "speaker.h"
#include "neopixel.h"

// Useful typedefs
typedef unsigned char u_char;   // 8 bit
typedef unsigned int u_int;     // 16 bit

//void NeoPixelDataTransfer(char Green, char Red, char Blue);

char LEDS_addressed[] = { 0, 1, 2, 3, 4, 6, 12, 18, 24, 25, 29, 31, 32, 33 };

//Use External 48MHz oscillator
//Set MCLK at 48 MHz for CPU
//Set SMCLK at 48 MHz
//Set ACLK at 128kHz
void NeopixelSetup(void)
{
//    static int smclock;

    /* Configuring pins for peripheral/crystal usage and LED for output */
    MAP_GPIO_setAsPeripheralModuleFunctionOutputPin(
            GPIO_PORT_PJ,
            GPIO_PIN3 | GPIO_PIN2,
            GPIO_PRIMARY_MODULE_FUNCTION);

    MAP_GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN6); //pin 15 on boosterpad
//    MAP_CS_setExternalClockSourceFrequency(32000, 48000000);
//
//    /* Starting HFXT in non-bypass mode without a timeout. Before we start
//     * we have to change VCORE to 1 to support the 48MHz frequency */
//    MAP_PCM_setCoreVoltageLevel(PCM_VCORE1);
//    MAP_FlashCtl_setWaitState(FLASH_BANK0, 2);
//    MAP_FlashCtl_setWaitState(FLASH_BANK1, 2);
//    MAP_CS_startHFXT(false);
//
    /* Initializing MCLK to HFXT (effectively 48MHz) */
    MAP_CS_initClockSignal(CS_MCLK, CS_HFXTCLK_SELECT, CS_CLOCK_DIVIDER_1);

    /*Timer A0 uses SMCLK */
    MAP_CS_initClockSignal(CS_SMCLK, CS_HFXTCLK_SELECT, CS_CLOCK_DIVIDER_1);

    /* Timer A1 clock source set up at 128kHz. Timer overflow occurs at 0.5 Second*/
    MAP_CS_setReferenceOscillatorFrequency(CS_REFO_128KHZ);
    MAP_CS_initClockSignal(CS_ACLK, CS_REFOCLK_SELECT, CS_CLOCK_DIVIDER_1);

//    smclock = CS_getSMCLK();
}

void NeoPixelDataTransfer(char Green, char Red, char Blue)
{

    const char Position[8] = { 0b00000001, 0b00000010, 0b00000100, 0b00001000,
                               0b00010000, 0b00100000, 0b01000000, 0b10000000 };

//send Green
    for (BitPosition = 8; BitPosition > 0; BitPosition--)
    {
        if ((Green & Position[BitPosition - 1]) == 0)
        {
            NeoPixelDataOutSet
            //Logic "0"
            NeoPixelDataOutClear
        }
        else
        {
            NeoPixelDataOutSet
            //Logic "1"
            NeoPixelDataOutSet
            NeoPixelDataOutClear
        }   //end if
    }   //end for
//send Red
    for (BitPosition = 8; BitPosition > 0; BitPosition--)
    {
        if ((Red & Position[BitPosition - 1]) == 0)
        {
            NeoPixelDataOutSet
            NeoPixelDataOutClear
        }
        else
        {
            NeoPixelDataOutSet
            NeoPixelDataOutSet
            NeoPixelDataOutClear
        }   //end if
    }   //end for
//send Blue
    for (BitPosition = 8; BitPosition > 0; BitPosition--)
    {
        if ((Blue & Position[BitPosition - 1]) == 0)
        {
            NeoPixelDataOutSet
            NeoPixelDataOutClear
        }
        else
        {
            NeoPixelDataOutSet
            NeoPixelDataOutSet
            NeoPixelDataOutClear
        }   //end if
    }   //end for
} //end NeoPixelDataTransfer()

void WriteNeopixelsToDisplay(void)
{
    long unsigned int i;

    int j;
    for (i = 0; i < NumberOfLEDs; i++)
    {

        // Iterate through each of the buttons to be illuminated
        for (j = 0; j < 14; j++)
        {
            // If the current led (i) is equal to the led we want illuminated (j), illuminate led i
            if (i == LEDS_addressed[j])
            {
                LEDS[i][0] = 0;
                LEDS[i][1] = 0;
                LEDS[i][2] = 20; // all blue
            }
        }
    }

    for (i = 0; i < NumberOfLEDs; i++)
    {
        NeoPixelDataTransfer(LEDS[i][0], LEDS[i][1], LEDS[i][2]);
    }

    // delay
    for (i = 0; i < 50; i++)
        ;
}

