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

//Button 0  -> C    -> 2.7
//Button 1  -> C#   -> 2.6
//Button 2  -> D    -> 5.6
//Button 3  -> D#   -> 2.3
//Button 4  -> E    -> 5.1
//Button 5  -> F    -> 2.5
//Button 6  -> F#   -> 5.7
//Button 7  -> G    -> 5.0
//Button 8  -> G#   -> 5.2
//Button 9  -> A    -> 5.5
//Button 10 -> A#
//Button 11 -> B

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
        //Button 7
        //ChangeNote();
    }
    else if (status & GPIO_PIN3)
    {
        //Button 5
        //ChangeNote();
    }
}

void PORT5_IRQHandler(void)
{
    uint32_t status = MAP_GPIO_getEnabledInterruptStatus(GPIO_PORT_P5);
    MAP_GPIO_clearInterruptFlag(GPIO_PORT_P5, status);

    if (status & GPIO_PIN7)
    {
        //Button 8
        //ChangeNote();
    }
    else if (status & GPIO_PIN6)
    {
        //Button 2
        //Plays D
        ChangeNote(NOTED3);
    }
    else if (status & GPIO_PIN1)
    {
        //Button 6
        //ChangeNote();
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

