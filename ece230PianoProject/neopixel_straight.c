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

//char LEDS_addressed[] = { 0, 1, 2, 3, 4, 6, 12, 18, 24, 25, 29, 31, 32, 33 };
//char LEDS_addressed[] = { 6,7,8,10,14,15,19,20,24 };
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

void WriteNeopixelsToDisplay(int num)
{
    long unsigned int i;

//    char neoPixelC[] =  {01,02,03,05,09,10,14,15,19,50,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00};
//    char neoPixelC_[] = {01,02,03,05,09,10,14,15,19,26,28,30,31,32,33,34,36,38,40,41,42,43,44,46,48,50,00,00,00,00};
//    char neoPixelD[] =  {00,01,02,03,04,05,09,10,14,16,17,18,50,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00};
//    char neoPixelD_[] = {00,01,02,03,04,05,09,10,14,16,17,18,26,28,30,31,32,33,34,36,38,40,41,42,43,44,46,48,50,00};
//    char neoPixelE[] =  {00,01,02,03,04,05,07,09,10,12,14,15,19,50,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00};
//    char neoPixelF[] =  {00,01,02,03,04,07,09,12,14,19,50,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00};
//    char neoPixelF_[] = {00,01,02,03,04,07,09,12,14,19,26,28,30,31,32,33,34,36,38,40,41,42,43,44,46,48,50,00,00,00};
//    char neoPixelG[] =  {00,01,02,03,04,05,09,10,12,14,15,16,17,19,50,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00};
//    char neoPixelG_[] = {00,01,02,03,04,05,09,10,12,14,15,16,17,19,26,28,30,31,32,33,34,36,38,40,41,42,43,44,46,48};
//    char neoPixelA[] =  {00,01,02,03,07,09,12,14,15,16,17,18,50,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00};
//    char neoPixelA_[] = {00,01,02,03,04,05,07,09,10,12,14,16,18,25,26,27,28,29,30,32,35,36,50,00,00,00,00,00,00,00};
//    char neoPixelB[] =  {00,01,02,03,04,05,07,09,10,12,14,16,18,50,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00};

//    int neoPixelNote[12][30] = {{01,02,03,05,09,10,14,15,19,50,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00},
//                                 {01,02,03,05,09,10,14,15,19,26,28,30,31,32,33,34,36,38,40,41,42,43,44,46,48,50,00,00,00,00},
//                                 {00,01,02,03,04,05,09,10,14,16,17,18,50,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00},
//                                 {00,01,02,03,04,05,09,10,14,16,17,18,26,28,30,31,32,33,34,36,38,40,41,42,43,44,46,48,50,00},
//                                 {00,01,02,03,04,05,07,09,10,12,14,15,19,50,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00},
//                                 {00,01,02,03,04,07,09,12,14,19,50,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00},
//                                 {00,01,02,03,04,07,09,12,14,19,26,28,30,31,32,33,34,36,38,40,41,42,43,44,46,48,50,00,00,00},
//                                 {00,01,02,03,04,05,09,10,12,14,15,16,17,19,50,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00},
//                                 {00,01,02,03,04,05,09,10,12,14,15,16,17,19,26,28,30,31,32,33,34,36,38,40,41,42,43,44,46,48},
//                                 {00,01,02,03,07,09,12,14,15,16,17,18,50,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00},
//                                 {00,01,02,03,04,05,07,09,10,12,14,16,18,25,26,27,28,29,30,32,35,36,50,00,00,00,00,00,00,00},
//                                 {00,01,02,03,04,05,07,09,10,12,14,16,18,50,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00}};
    int neoPixelNote[24][30] = { {1}, { 1, 2, 3, 4, 5, 9, 10, 14, 15, 19},
                                 {1}, { 1, 2, 3, 4, 5, 9, 10, 14, 15, 19, 26, 28, 30,
                                   31, 32, 33, 34, 36, 38, 40, 41, 42, 43, 44,
                                   46, 48},
                                 {1}, { 0, 1, 2, 3, 4, 5, 9, 10, 14, 16, 17, 18},
                                 {1}, { 0, 1, 2, 3, 4, 5, 9, 10, 14, 16, 17, 18, 26,
                                   28, 30, 31, 32, 33, 34, 36, 38, 40, 41, 42,
                                   43, 44, 46, 48},
                                 {1}, { 0, 1, 2, 3, 4, 5, 7, 9, 10, 12, 14, 15, 19
                                   },
                                 {1}, { 0, 1, 2, 3, 4, 7, 9, 12, 14, 19},
                                 {1}, { 0, 1, 2, 3, 4, 7, 9, 12, 14, 19, 26, 28, 30,
                                   31, 32, 33, 34, 36, 38, 40, 41, 42, 43, 44,
                                   46, 48 },
                                 {1}, { 0, 1, 2, 3, 4, 5, 9, 10, 12, 14, 15, 16, 17,
                                   19},
                                 {1}, { 0, 1, 2, 3, 4, 5, 9, 10, 12, 14, 15, 16, 17,
                                   19, 26, 28, 30, 31, 32, 33, 34, 36, 38, 40,
                                   41, 42, 43, 44, 46, 48 },
                                 {1}, { 0, 1, 2, 3, 7, 9, 12, 14, 15, 16, 17, 18},
                                 {1}, { 0, 1, 2, 3, 4, 5, 7, 9, 10, 12, 14, 16, 18,
                                   25, 26, 27, 28, 29, 30, 32, 35, 36},
                                 {1}, { 0, 1, 2, 3, 4, 5, 7, 9, 10, 12, 14, 16, 18} };

    int j;
    for (i = 0; i < NumberOfLEDs; i++)
    {

        // Iterate through each of the buttons to be illuminated
        for (j = 0; j < NumberOfLEDs; j++)
        {
            // If the current led (i) is equal to the led we want illuminated (j), illuminate led i
            if (i == neoPixelNote[num][j])
            {
                LEDS[i][0] = 0;
                LEDS[i][1] = 0;
                LEDS[i][2] = 10; // all blue
            }

//            if (neoPixelNote[num][j] == 50)
//            {
//                i = 50;
//            }
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

