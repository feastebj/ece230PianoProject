/* DriverLib Includes */
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

/* Standard Includes */
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include "speaker.h"
#include "buttons.h"

int main(void)
{
    /* Halting WDT  */
    MAP_WDT_A_holdTimer();

    SpeakerConfig();
    ButtonsConfig();

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

    if (status & GPIO_PIN7)
    {
        //Button 0
        //Plays C
        ChangeNote(NOTEC3);
    }
    else if (status & GPIO_PIN6)
    {
        //Button 1
        // Plays C#
        ChangeNote(NOTEC3_);
    }
    else if (status & GPIO_PIN5)
    {
        //Button 5
        //Plays F
        ChangeNote(NOTEF3);
    }
    else if (status & GPIO_PIN3)
    {
        //Button 3
        //Plays D#
        ChangeNote(NOTED3_);
    }
}

void PORT5_IRQHandler(void)
{
    uint32_t status = MAP_GPIO_getEnabledInterruptStatus(GPIO_PORT_P5);
    MAP_GPIO_clearInterruptFlag(GPIO_PORT_P5, status);

    if (status & GPIO_PIN7)
    {
        //Button 6
        //Plays G#
        ChangeNote(NOTEF3_);
    }
    else if (status & GPIO_PIN6)
    {
        //Button 2
        //Plays D
        ChangeNote(NOTED3);
    }
    else if (status & GPIO_PIN2)
    {
        //Button 8
        //Plays A
        ChangeNote(NOTEG3_);
    }
    else if (status & GPIO_PIN1)
    {
        //Button 4
        //Plays E
        ChangeNote(NOTEE3);
    }
    else if (status & GPIO_PIN0)
    {
        //Button 7
        //Plays G
        ChangeNote(NOTEG3);
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

