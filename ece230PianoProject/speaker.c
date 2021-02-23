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
#include "neopixel.h"

int CurrentNote = 0;

double CurrentOctave = 2.0;

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

//    /* Initializing MCLK to HFXT (effectively 48MHz) */
//    MAP_CS_initClockSignal(CS_MCLK, CS_HFXTCLK_SELECT, CS_CLOCK_DIVIDER_4);
//
//    /* Initializing SMCLK to HFXT (effectively 48MHz) with prescaler of 4*/
//
//    MAP_CS_initClockSignal(CS_SMCLK, CS_HFXTCLK_SELECT, CS_CLOCK_DIVIDER_4);

    /* Configuring Timer_A1 for Up Mode and starting */
    MAP_Timer_A_configureUpMode(TIMER_A0_BASE, &upConfig);
    MAP_Timer_A_startCounter(TIMER_A0_BASE, TIMER_A_UP_MODE);

    /* Initialize compare registers to generate PWM1 */
    MAP_Timer_A_initCompare(TIMER_A0_BASE, &compareConfig_PWM1);
}

/*
 * This function changes the note (or rest) played by the speaker.
 *
 * Within the function, the edge select of the passed button number
 * will be checked. If the edge select is true (high-to-low), the
 * current note value will be played. If not, a rest will be loaded
 * to the speaker's capture-compare register and stay silent.
 *
 * In either case, the edge select is toggled each time a button is pushed.
 * This allows the interrupt to occur after each button press and release,
 * so a note is only played while a key is held down.
 *
 * This is called by the Port2Handler() and
 * Port5Handler() functions.
 */
void ChangeNote(uint8_t port, uint16_t pin, int buttonNum, double note)
{
    //This operation will double, halve, or maintain the
    //note frequency to give the note in the current
    //octave register.
    note /= GetOctave();

    if (edges[buttonNum])
    {
        //If the button is pushed, load the note value.

        //The note value is multiplied by 4 to
        //make up for the neopixel clock configuration
        //increasing the clock speed by 4
        MAP_Timer_A_setCompareValue(TIMER_A0_BASE,
        TIMER_A_CAPTURECOMPARE_REGISTER_0,
                                    4*note);
        MAP_GPIO_interruptEdgeSelect(port, pin,
        GPIO_LOW_TO_HIGH_TRANSITION);
        edges[buttonNum] = false;

        SetNote(note);
        SetLetter(buttonNum);
    }
    else
    {
        //If the button is released, load the rest value.
        MAP_Timer_A_setCompareValue(TIMER_A0_BASE,
        TIMER_A_CAPTURECOMPARE_REGISTER_0,
                                    REST);
        MAP_GPIO_interruptEdgeSelect(port, pin,
        GPIO_HIGH_TO_LOW_TRANSITION);
        edges[buttonNum] = true;

        SetNote(REST);
        SetLetter(12);
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

double GetOctave(void)
{
    return CurrentOctave;
}

/*
 * This function sets the octave divider on the current
 * note frequency which regulates the octave in which a
 * note is.
 *
 */
void SetOctave(double voltage)
{
    double newOctave;

    if (voltage > HIGH_OCTAVE_THRESH)
    {
        newOctave = 4.0;
    }
    else if (voltage < LOW_OCTAVE_THRESH)
    {
        newOctave = 1.0;
    }
    else
    {
        newOctave = 2.0;
    }

    CurrentOctave = newOctave;
}
