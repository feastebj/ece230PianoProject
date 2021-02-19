/* DriverLib Includes */
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

/* Standard Includes */
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include "speaker.h"
#include "buttons.h"
#include "sevenSegment.h"

int main(void)
{
    /* Halting WDT  */
    MAP_WDT_A_holdTimer();

    SpeakerConfig();
    ButtonsConfig();
    SevenSegmentConfig();

    MAP_Interrupt_enableSleepOnIsrExit();
    MAP_Interrupt_enableMaster();

    while (1)
    {
        //int ii;
//        int jj;

        //for (ii = 0; ii < 100; ii++)
        //{
//            WriteToDisplay(GetNote());
        //}

//        for (jj = 0; jj < 100; jj++)
//        {
//            WriteToDisplay(842);
//        }
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

    if (status & GPIO_PIN7)
    {
        //Button 0
        //Plays C
        ChangeNote(GPIO_PORT_P2, GPIO_PIN7, 0, NOTEC3);
    }
    else if (status & GPIO_PIN6)
    {
        //Button 1
        // Plays C#
        ChangeNote(GPIO_PORT_P2, GPIO_PIN6, 1, NOTEC3_);
    }
    else if (status & GPIO_PIN5)
    {
        //Button 5
        //Plays F
        ChangeNote(GPIO_PORT_P2, GPIO_PIN5, 5, NOTEF3);
    }
    else if (status & GPIO_PIN3)
    {
        //Button 3
        //Plays D#
        ChangeNote(GPIO_PORT_P2, GPIO_PIN3, 3, NOTED3_);
    }
}

void PORT5_IRQHandler(void)
{
    uint32_t status = MAP_GPIO_getEnabledInterruptStatus(GPIO_PORT_P5);
    MAP_GPIO_clearInterruptFlag(GPIO_PORT_P5, status);

    if (status & GPIO_PIN7)
    {
        //Button 6
        //Plays F#
        ChangeNote(GPIO_PORT_P5, GPIO_PIN7, 6, NOTEF3_);
    }
    else if (status & GPIO_PIN6)
    {
        //Button 2
        //Plays D
        ChangeNote(GPIO_PORT_P5, GPIO_PIN6, 2, NOTED3);
    }
    else if (status & GPIO_PIN5)
    {
        //Button 9
        //Plays A
        ChangeNote(GPIO_PORT_P5, GPIO_PIN5, 9, NOTEA3);
    }
    else if (status & GPIO_PIN2)
    {
        //Button 8
        //Plays G#
        ChangeNote(GPIO_PORT_P5, GPIO_PIN2, 8, NOTEG3_);
    }
    else if (status & GPIO_PIN1)
    {
        //Button 4
        //Plays E
        ChangeNote(GPIO_PORT_P5, GPIO_PIN1, 4, NOTEE3);
    }
    else if (status & GPIO_PIN0)
    {
        //Button 7
        //Plays G
        ChangeNote(GPIO_PORT_P5, GPIO_PIN0, 7, NOTEG3);
    }
}

void TA1_0_IRQHandler(void)
{
    WriteToDisplay(GetNote());
    MAP_Timer_A_clearCaptureCompareInterrupt(TIMER_A1_BASE,
    TIMER_A_CAPTURECOMPARE_REGISTER_0);
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

