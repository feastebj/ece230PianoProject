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

void ButtonsConfig(void)
{
    //Button 2.6 Configuration
    MAP_GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P2, GPIO_PIN6);
    MAP_GPIO_clearInterruptFlag(GPIO_PORT_P2, GPIO_PIN6);
    MAP_GPIO_enableInterrupt(GPIO_PORT_P2, GPIO_PIN6);
    //Button 2.7 Configuration
    MAP_GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P2, GPIO_PIN7);
    MAP_GPIO_clearInterruptFlag(GPIO_PORT_P2, GPIO_PIN7);
    MAP_GPIO_enableInterrupt(GPIO_PORT_P2, GPIO_PIN7);

    //Button 5.6 Configuration
    MAP_GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P5, GPIO_PIN6);
    MAP_GPIO_clearInterruptFlag(GPIO_PORT_P5, GPIO_PIN6);
    MAP_GPIO_enableInterrupt(GPIO_PORT_P5, GPIO_PIN6);

    MAP_Interrupt_enableInterrupt(INT_PORT2);
    MAP_Interrupt_enableInterrupt(INT_PORT5);

}
