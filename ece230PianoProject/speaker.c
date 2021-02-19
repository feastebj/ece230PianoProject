/*
 * speaker.c
 *
 *  Created on: Feb 11, 2021
 *      Author: rutantj
 */

/* DriverLib Includes */
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

/* Standard Includes */
#include <stdint.h>
#include <stdbool.h>

#include "speaker.h"

int CurrentNote = 0;

const uint16_t noteHalfPeriod[NOTECNT] = { NOTEC3, NOTEC3_, NOTED3, NOTED3_,
NOTEE3,
                                           NOTEF3,
                                           NOTEF3_,
                                           NOTEG3, NOTEG3_, NOTEA3,
                                           NOTEA3_,
                                           NOTEB3 };
bool edges[10] = { true, true, true, true, true, true, true, true, true, true };

//static int noteIndex = 0;

void SpeakerConfig(void)
{
//![Simple PMAP Config]
    /* Port mapper configuration register */
    const uint8_t port_mapping[] = {
//Port P2:
            PMAP_NONE,
            PMAP_NONE,
            PMAP_NONE, PMAP_NONE, PMAP_TA0CCR0A,
            PMAP_NONE,
            PMAP_NONE,
            PMAP_NONE };
//![Simple PMAP Config]

    /* Timer_A UpDown Configuration Parameter */
    const Timer_A_UpModeConfig upConfig = {
    TIMER_A_CLOCKSOURCE_SMCLK,              // SMCLK Clock SOurce
            TIMER_A_CLOCKSOURCE_DIVIDER_3,          // SMCLK/1 = 3MHz
            NOTEA4,                                    // 127 tick period
            TIMER_A_TAIE_INTERRUPT_DISABLE,         // Disable Timer interrupt
            TIMER_A_CCIE_CCR0_INTERRUPT_DISABLE,    // Disable CCR0 interrupt
            TIMER_A_DO_CLEAR                        // Clear value
            };

    /* Timer_A Compare Configuration Parameter  (PWM1) */
    const Timer_A_CompareModeConfig compareConfig_PWM1 = {
    TIMER_A_CAPTURECOMPARE_REGISTER_0,          // Use CCR1
            TIMER_A_CAPTURECOMPARE_INTERRUPT_DISABLE,   // Disable CCR interrupt
            TIMER_A_OUTPUTMODE_TOGGLE,              // Toggle output but
            REST                                          // 32 Duty Cycle
            };

    //![Simple PMAP Example]
    /* Remapping  TACCR0 to P2.4 */
    MAP_PMAP_configurePorts((const uint8_t*) port_mapping, PMAP_P2MAP, 1,
    PMAP_DISABLE_RECONFIGURATION);
    //![Simple PMAP Example]

    MAP_GPIO_setAsPeripheralModuleFunctionOutputPin(
            GPIO_PORT_P2,
            GPIO_PIN4,
            GPIO_PRIMARY_MODULE_FUNCTION);

    MAP_GPIO_setAsPeripheralModuleFunctionOutputPin(
            GPIO_PORT_PJ,
            GPIO_PIN3 | GPIO_PIN2,
            GPIO_PRIMARY_MODULE_FUNCTION);

    CS_setExternalClockSourceFrequency(32000, 48000000);

    /* Starting HFXT in non-bypass mode without a timeout. Before we start
     * we have to change VCORE to 1 to support the 48MHz frequency */
    MAP_PCM_setCoreVoltageLevel(PCM_VCORE1);
    MAP_FlashCtl_setWaitState(FLASH_BANK0, 2);
    MAP_FlashCtl_setWaitState(FLASH_BANK1, 2);
    MAP_CS_startHFXT(false);

    /* Initializing MCLK to HFXT (effectively 48MHz) */
    MAP_CS_initClockSignal(CS_MCLK, CS_HFXTCLK_SELECT, CS_CLOCK_DIVIDER_4);

    /* Initializing SMCLK to HFXT (effectively 48MHz) with prescaler of 4*/

    MAP_CS_initClockSignal(CS_SMCLK, CS_HFXTCLK_SELECT, CS_CLOCK_DIVIDER_4);

    /* Configuring Timer_A1 for Up Mode and starting */
    MAP_Timer_A_configureUpMode(TIMER_A0_BASE, &upConfig);
    MAP_Timer_A_startCounter(TIMER_A0_BASE, TIMER_A_UP_MODE);

    /* Initialize compare registers to generate PWM1 */
    MAP_Timer_A_initCompare(TIMER_A0_BASE, &compareConfig_PWM1);
}

void SpeakerBasicFunction(void)
{
    while (1)
    {
        volatile uint32_t delay = 0;
        for (delay = 1000000; delay > 0; delay--)
        {

        }
        //ChangeNote();
    }
}

void ChangeNote(uint8_t port, uint16_t pin, int buttonNum, double note)
{
    //Basic note cycling, NOTE: DO NOT DELETE
//    noteIndex = (noteIndex + 1) % NOTECNT;
//    MAP_Timer_A_setCompareValue(TIMER_A0_BASE,
//    TIMER_A_CAPTURECOMPARE_REGISTER_0,
//                                noteHalfPeriod[noteIndex]);

    if (edges[buttonNum])
    {
        MAP_Timer_A_setCompareValue(TIMER_A0_BASE,
        TIMER_A_CAPTURECOMPARE_REGISTER_0,
                                    note);
        MAP_GPIO_interruptEdgeSelect(port, pin,
        GPIO_LOW_TO_HIGH_TRANSITION);
        edges[buttonNum] = false;

        SetNote(note);
    }
    else
    {
        MAP_Timer_A_setCompareValue(TIMER_A0_BASE,
        TIMER_A_CAPTURECOMPARE_REGISTER_0,
                                    REST);
        MAP_GPIO_interruptEdgeSelect(port, pin,
        GPIO_HIGH_TO_LOW_TRANSITION);
        edges[buttonNum] = true;

        SetNote(REST);
    }
}

int GetNote(void)
{
    return CurrentNote;
}

void SetNote(double newNote)
{
    int freq = (int) (TimerAClock / newNote / 2);
    CurrentNote = freq;
}
