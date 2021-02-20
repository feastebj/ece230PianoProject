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
#include "speaker.h"

#define PORT2_PIN_NUM 4
#define PORT5_PIN_NUM 6

uint16_t portTwoButtonsArray[PORT2_PIN_NUM] = { GPIO_PIN3, GPIO_PIN5, GPIO_PIN6,
GPIO_PIN7 };

uint16_t portFiveButtonsArray[PORT5_PIN_NUM] = { GPIO_PIN0, GPIO_PIN1,
GPIO_PIN2,
                                                 GPIO_PIN4,
                                                 GPIO_PIN6,
                                                 GPIO_PIN7 };

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

void Port5Handler(uint32_t pin)
{
    if (pin & GPIO_PIN7)
    {
        //Button 6
        //Plays F#
        ChangeNote(GPIO_PORT_P5, GPIO_PIN7, 6, NOTEF3_);
    }
    else if (pin & GPIO_PIN6)
    {
        //Button 2
        //Plays D
        ChangeNote(GPIO_PORT_P5, GPIO_PIN6, 2, NOTED3);
    }
    else if (pin & GPIO_PIN4)
    {
        //Button 9
        //Plays A
        ChangeNote(GPIO_PORT_P5, GPIO_PIN4, 9, NOTEA3);
    }
    else if (pin & GPIO_PIN2)
    {
        //Button 8
        //Plays G#
        ChangeNote(GPIO_PORT_P5, GPIO_PIN2, 8, NOTEG3_);
    }
    else if (pin & GPIO_PIN1)
    {
        //Button 4
        //Plays E
        ChangeNote(GPIO_PORT_P5, GPIO_PIN1, 4, NOTEE3);
    }
    else if (pin & GPIO_PIN0)
    {
        //Button 7
        //Plays G
        ChangeNote(GPIO_PORT_P5, GPIO_PIN0, 7, NOTEG3);
    }
}

void Port2Handler(uint32_t pin)
{
    if (pin & GPIO_PIN7)
    {
        //Button 0
        //Plays C
        ChangeNote(GPIO_PORT_P2, GPIO_PIN7, 0, NOTEC3);
    }
    else if (pin & GPIO_PIN6)
    {
        //Button 1
        // Plays C#
        ChangeNote(GPIO_PORT_P2, GPIO_PIN6, 1, NOTEC3_);
    }
    else if (pin & GPIO_PIN5)
    {
        //Button 5
        //Plays F
        ChangeNote(GPIO_PORT_P2, GPIO_PIN5, 5, NOTEF3);
    }
    else if (pin & GPIO_PIN3)
    {
        //Button 3
        //Plays D#
        ChangeNote(GPIO_PORT_P2, GPIO_PIN3, 3, NOTED3_);
    }
}
