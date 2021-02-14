
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

    SpeakerBasicFunction();

    MAP_Interrupt_enableSleepOnIsrExit();
    MAP_Interrupt_enableMaster();   

    while(1)
    {
        MAP_PCM_gotoLPM0();
    }
}
