/* DriverLib Includes */
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

/* Standard Includes */
#include <stdint.h>
#include <stdbool.h>

#include "speaker.h"

int main(void)
{
    /* Halting WDT  */
    MAP_WDT_A_holdTimer();

    SpeakerConfig();

    //Button 2.7 Configuration
    MAP_GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P2, GPIO_PIN7);
    MAP_GPIO_clearInterruptFlag(GPIO_PORT_P2, GPIO_PIN7);
    MAP_GPIO_enableInterrupt(GPIO_PORT_P2, GPIO_PIN7);
    MAP_Interrupt_enableInterrupt(INT_PORT2);

    MAP_Interrupt_enableSleepOnIsrExit();
    MAP_Interrupt_enableMaster();

    while (1)
    {
        //SpeakerBasicFunction();
        MAP_PCM_gotoLPM0();
    }
}

void PORT2_IRQHandler(void)
{
    uint32_t status = MAP_GPIO_getEnabledInterruptStatus(GPIO_PORT_P2);
    MAP_GPIO_clearInterruptFlag(GPIO_PORT_P2, status);

    if (status & GPIO_PIN7)
    {
        ChangeNote();
    }
}
