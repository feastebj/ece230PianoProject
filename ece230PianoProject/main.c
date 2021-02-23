/*
 * Author:  Ben Feaster, T.J. Rutan
 * Design:  Capstone Project, ECE230-02
 * Date:    2 February 2021
 *
 * Description: This program is written to run an electric piano
 *              with supporting peripherals to display the frequency
 *              and the letter of the note being played and a dial
 *              to switch octave registers.
 *
 *              There are 12 push buttons to function the keys of
 *              a keyboard. The frequency is displayed on a four
 *              digit seven segment display. The letter of the note
 *              is displayed on a neo-pixel array. The hardware also
 *              supports a volume dial but does not require a driver
 *              for it to function.
 *
 *              All the peripherals are run via interrupts (see
 *              handlers at the bottom of this file) so the main
 *              only includes the configuration modules and then
 *              goes into low power mode from then on.
 */

/* DriverLib Includes */
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

/* Standard Includes */
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include "speaker.h"
#include "buttons.h"
#include "sevenSegment.h"
#include "octaveDial.h"
#include "neopixel.h"

int main(void)
{
    /* Halting WDT  */
    MAP_WDT_A_holdTimer();

    SpeakerConfig();
    ButtonsConfig();
    SevenSegmentConfig();
    NeopixelSetup();
    OctaveDialConfig();

    MAP_Interrupt_enableSleepOnIsrExit();
    MAP_Interrupt_enableMaster();

    // Do this forever
    while (1)
    {
        MAP_PCM_gotoLPM0();
    }
}
/*************************************************************************
 *                          INTERRUPT HANDLERS
 *************************************************************************/

/*
 * This handler manages the buttons on
 * Port 2.
 *
 * See Port2Handler() in buttons.c
 */
void PORT2_IRQHandler(void)
{
    uint32_t status = MAP_GPIO_getEnabledInterruptStatus(GPIO_PORT_P2);
    MAP_GPIO_clearInterruptFlag(GPIO_PORT_P2, status);
    Port2Handler(status);
}

/*
 * This handler manages the buttons on
 * Port 5.
 *
 * See Port5Handler() in buttons.c
 */
void PORT5_IRQHandler(void)
{
    uint32_t status = MAP_GPIO_getEnabledInterruptStatus(GPIO_PORT_P5);
    MAP_GPIO_clearInterruptFlag(GPIO_PORT_P5, status);
    Port5Handler(status);
}

/*
 * This handler manages the buttons on
 * Port 3.
 *
 * See Port3Handler() in buttons.c
 */
void PORT3_IRQHandler(void)
{
    uint32_t status = MAP_GPIO_getEnabledInterruptStatus(GPIO_PORT_P3);
    MAP_GPIO_clearInterruptFlag(GPIO_PORT_P3, status);
    Port3Handler(status);
}

/*
 * This handler updates the seven segment
 * display.
 *
 * See WriteToDisplay() in sevenSegment.c
 * and GetNote() in speaker.c
 */
void TA1_0_IRQHandler(void)
{
    WriteToDisplay(GetNote());
    WriteNeopixelsToDisplay(GetLetter()); // range from 0 to 11

    MAP_Timer_A_clearCaptureCompareInterrupt(TIMER_A1_BASE,
    TIMER_A_CAPTURECOMPARE_REGISTER_0);
}

/* ADC Interrupt Handler. This handler is called whenever there is a conversion
 * that is finished for ADC_MEM0.
 */
void ADC14_IRQHandler(void)
{
    uint64_t status = MAP_ADC14_getEnabledInterruptStatus();
    MAP_ADC14_clearInterruptFlag(status);

    if (ADC_INT0 & status)
    {
        SetOctave(GetVoltage());

        MAP_ADC14_toggleConversionTrigger();
    }
}
//void interruptHandler(port, gpioArray) {
//
//       uint32_t status = MAP_GPIO_getEnabledInterruptStatus(port);
//       MAP_GPIO_clearInterruptFlag(port, status);
//
//       for (i = 0; i <= sizeof(sizeof(gpioArray)); i++)
//       //    {
//       if (status & gpioArray[i])
//       {
//           ChangeNote();
//       }
//}

