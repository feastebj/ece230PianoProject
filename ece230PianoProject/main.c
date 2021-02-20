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

int main(void)
{
    /* Halting WDT  */
    MAP_WDT_A_holdTimer();

    SpeakerConfig();
    ButtonsConfig();
    SevenSegmentConfig();
    OctaveDialConfig();

    MAP_Interrupt_enableSleepOnIsrExit();
    MAP_Interrupt_enableMaster();

    while (1)
    {
        MAP_PCM_gotoLPM0();
    }
}

/*************************************************************************
 *                          INTERRUPT HANDLERS
 *************************************************************************/

void PORT2_IRQHandler(void)
{
    uint32_t status = MAP_GPIO_getEnabledInterruptStatus(GPIO_PORT_P2);
    MAP_GPIO_clearInterruptFlag(GPIO_PORT_P2, status);
    Port2Handler(status);
}

void PORT5_IRQHandler(void)
{
    uint32_t status = MAP_GPIO_getEnabledInterruptStatus(GPIO_PORT_P5);
    MAP_GPIO_clearInterruptFlag(GPIO_PORT_P5, status);
    Port5Handler(status);
}

void TA1_0_IRQHandler(void)
{
    WriteToDisplay(GetNote());
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

