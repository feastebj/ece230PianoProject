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

uint16_t portTwoButtonsArray[] = { GPIO_PIN3, GPIO_PIN5, GPIO_PIN6,
GPIO_PIN7 };

uint16_t portFiveButtonsArray[] = { GPIO_PIN0, GPIO_PIN1, GPIO_PIN2,
GPIO_PIN4,
                                    GPIO_PIN5, GPIO_PIN6, GPIO_PIN7 };

void ButtonsConfig(void)
{
//    // Port 2 Button Configuration
//    int i;
//    for (i = 0; i <= sizeof(portTwoButtonsArray); i++)
//    {
//        MAP_GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P2,
//                                                 portTwoButtonsArray[i]);
//        MAP_GPIO_clearInterruptFlag(GPIO_PORT_P2, portTwoButtonsArray[i]);
//        MAP_GPIO_enableInterrupt(GPIO_PORT_P2, portTwoButtonsArray[i]);
//    }
//
//    // Port 5 Button Configuration
//    int j;
//    for (j = 0; j <= sizeof(portFiveButtonsArray); j++)
//    {
//        MAP_GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P5,
//                                                 portFiveButtonsArray[i]);
//        MAP_GPIO_clearInterruptFlag(GPIO_PORT_P5, portFiveButtonsArray[i]);
//        MAP_GPIO_enableInterrupt(GPIO_PORT_P5, portFiveButtonsArray[i]);
//    }

//Button 2.3 Configuration
    MAP_GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P2, GPIO_PIN3);
    MAP_GPIO_clearInterruptFlag(GPIO_PORT_P2, GPIO_PIN3);
    MAP_GPIO_enableInterrupt(GPIO_PORT_P2, GPIO_PIN3);
    //Button 2.5 Configuration
    MAP_GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P2, GPIO_PIN5);
    MAP_GPIO_clearInterruptFlag(GPIO_PORT_P2, GPIO_PIN5);
    MAP_GPIO_enableInterrupt(GPIO_PORT_P2, GPIO_PIN5);
    //Button 2.6 Configuration
    MAP_GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P2, GPIO_PIN6);
    MAP_GPIO_clearInterruptFlag(GPIO_PORT_P2, GPIO_PIN6);
    MAP_GPIO_enableInterrupt(GPIO_PORT_P2, GPIO_PIN6);
    //Button 2.7 Configuration
    MAP_GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P2, GPIO_PIN7);
    MAP_GPIO_clearInterruptFlag(GPIO_PORT_P2, GPIO_PIN7);
    MAP_GPIO_enableInterrupt(GPIO_PORT_P2, GPIO_PIN7);

    //Button 5.0 Configuration
    MAP_GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P5, GPIO_PIN0);
    MAP_GPIO_clearInterruptFlag(GPIO_PORT_P5, GPIO_PIN0);
    MAP_GPIO_enableInterrupt(GPIO_PORT_P5, GPIO_PIN0);
    //Button 5.1 Configuration
    MAP_GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P5, GPIO_PIN1);
    MAP_GPIO_clearInterruptFlag(GPIO_PORT_P5, GPIO_PIN1);
    MAP_GPIO_enableInterrupt(GPIO_PORT_P5, GPIO_PIN1);
    //Button 5.2 Configuration
    MAP_GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P5, GPIO_PIN2);
    MAP_GPIO_clearInterruptFlag(GPIO_PORT_P5, GPIO_PIN2);
    MAP_GPIO_enableInterrupt(GPIO_PORT_P5, GPIO_PIN2);
    //Button 5.5 Configuration
    MAP_GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P5, GPIO_PIN5);
    MAP_GPIO_clearInterruptFlag(GPIO_PORT_P5, GPIO_PIN5);
    MAP_GPIO_enableInterrupt(GPIO_PORT_P5, GPIO_PIN5);
    //Button 5.6 Configuration
    MAP_GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P5, GPIO_PIN6);
    MAP_GPIO_clearInterruptFlag(GPIO_PORT_P5, GPIO_PIN6);
    MAP_GPIO_enableInterrupt(GPIO_PORT_P5, GPIO_PIN6);
    //Button 5.7 Configuration
    MAP_GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P5, GPIO_PIN7);
    MAP_GPIO_clearInterruptFlag(GPIO_PORT_P5, GPIO_PIN7);
    MAP_GPIO_enableInterrupt(GPIO_PORT_P5, GPIO_PIN7);

    MAP_Interrupt_enableInterrupt(INT_PORT2);
    MAP_Interrupt_enableInterrupt(INT_PORT5);

}
