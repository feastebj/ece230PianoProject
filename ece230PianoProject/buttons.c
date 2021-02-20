/*
 * buttons.c
 *
 *  Created on: Feb 14, 2021
 *      Author: rutantj
 */

/* DriverLib Includes */
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

/* Standard Includes */
#include <stdint.h>
#include <stdbool.h>

#include "buttons.h"

#define PORT2_PIN_NUM 4
#define PORT5_PIN_NUM 6

uint16_t portTwoButtonsArray[PORT2_PIN_NUM] = { GPIO_PIN3, GPIO_PIN5, GPIO_PIN6,
GPIO_PIN7 };

uint16_t portFiveButtonsArray[PORT5_PIN_NUM] = { GPIO_PIN0, GPIO_PIN1,
                                                 GPIO_PIN2,
                                                 GPIO_PIN4,
                                                 GPIO_PIN6, GPIO_PIN7 };

//Button 0  -> C    -> 2.7  -> 40
//Button 1  -> C#   -> 2.6  -> 39
//Button 2  -> D    -> 5.6  -> 37
//Button 3  -> D#   -> 2.3  -> 34
//Button 4  -> E    -> 5.1  -> 33
//Button 5  -> F    -> 2.5  -> 19
//Button 6  -> F#   -> 5.7  -> 17
//Button 7  -> G    -> 5.0  -> 13
//Button 8  -> G#   -> 5.2  -> 12
//Button 9  -> A    -> 5.4  -> 29
//Button 10 -> A#
//Button 11 -> B

void ButtonsConfig(void)
{
    // Port 2 Button Configuration
    int i;
    for (i = 0; i < PORT2_PIN_NUM; i++)
    {
        MAP_GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P2,
                                                 portTwoButtonsArray[i]);
        MAP_GPIO_clearInterruptFlag(GPIO_PORT_P2, portTwoButtonsArray[i]);
        MAP_GPIO_enableInterrupt(GPIO_PORT_P2, portTwoButtonsArray[i]);
    }

    // Port 5 Button Configuration
    int j;
    for (j = 0; j < PORT5_PIN_NUM; j++)
    {
        MAP_GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P5,
                                                 portFiveButtonsArray[j]);
        MAP_GPIO_clearInterruptFlag(GPIO_PORT_P5, portFiveButtonsArray[j]);
        MAP_GPIO_enableInterrupt(GPIO_PORT_P5, portFiveButtonsArray[j]);
    }

    MAP_Interrupt_enableInterrupt(INT_PORT2);
    MAP_Interrupt_enableInterrupt(INT_PORT5);

}
