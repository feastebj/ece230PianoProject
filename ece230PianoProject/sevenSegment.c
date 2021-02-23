/*
 * sevenSegment.c
 *
 *  Created on: Feb 17, 2021
 *      Author: rutantj
 */

/* DriverLib Includes */
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

/* Standard Includes */
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

#include "sevenSegment.h"

int digitIndex = 0;

void SevenSegmentConfig(void)
{
    /* Timer_A UpMode Configuration Parameter */
    const Timer_A_UpDownModeConfig upDownConfig = {
    TIMER_A_CLOCKSOURCE_SMCLK,                      // SMCLK Clock Source
            TIMER_A_CLOCKSOURCE_DIVIDER_3,          // SMCLK/1 = 3MHz
            TIMER_PERIOD_7SEG,                      // 5000 tick period
            TIMER_A_TAIE_INTERRUPT_ENABLE,          // Enable Timer interrupt
            TIMER_A_CCIE_CCR0_INTERRUPT_ENABLE,     // Enable CCR0 interrupt
            TIMER_A_DO_CLEAR                        // Clear value
            };

    const uint16_t sevenSegPinArray[7] = { GPIO_PIN6, GPIO_PIN4, GPIO_PIN2,
    GPIO_PIN1,
                                           GPIO_PIN0,
                                           GPIO_PIN5,
                                           GPIO_PIN3 };

    int p;
    for (p = 0; p < 7; p++)
    {
        GPIO_setAsOutputPin(GPIO_PORT_P4, sevenSegPinArray[p]);
    }

    GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN7);
    GPIO_setAsOutputPin(GPIO_PORT_P3, GPIO_PIN6);
    GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN5);

    /* Configuring Timer_A1 for Up Down Mode */
    MAP_Timer_A_configureUpDownMode(TIMER_A1_BASE, &upDownConfig);

    /* Enabling interrupts and starting the timer */
    MAP_Interrupt_enableSleepOnIsrExit();
    MAP_Interrupt_enableInterrupt(INT_TA1_0);
    MAP_Timer_A_startCounter(TIMER_A1_BASE, TIMER_A_UPDOWN_MODE);
}

/*
 * This function cycles to the next digit and then lights and dims
 * each segment of the display digit depending on the integer value
 * passed. If a 0 is passed, the display will show a 0 and so on.
 */
void WriteToDigit(int num)
{
    const uint16_t sevenSegPinArray[7] = { GPIO_PIN6, GPIO_PIN4, GPIO_PIN2,
    GPIO_PIN1,
                                           GPIO_PIN0,
                                           GPIO_PIN5,
                                           GPIO_PIN3 };

//    Each digit gets its own array of 1's and 0's. A 1 lights the
//    given segment of the digit, a 0 leaves it dim.

//    0 = { 1, 1, 1, 1, 1, 1, 0 };
//    1 = { 0, 1, 1, 0, 0, 0, 0 };
//    2 = { 1, 1, 0, 1, 1, 0, 1 };
//    3 = { 1, 1, 1, 1, 0, 0, 1 };
//    4 = { 0, 1, 1, 0, 0, 1, 1 };
//    5 = { 1, 0, 1, 1, 0, 1, 1 };
//    6 = { 1, 0, 1, 1, 1, 1, 1 };
//    7 = { 1, 1, 1, 0, 0, 0, 0 };
//    8 = { 1, 1, 1, 1, 1, 1, 1 };
//    9 = { 1, 1, 1, 1, 0, 1, 1 };

    const int sevenSegArray[10][7] = { { 1, 1, 1, 1, 1, 1, 0 }, { 0, 1, 1, 0, 0,
                                                                  0, 0 },
                                       { 1, 1, 0, 1, 1, 0, 1 }, { 1, 1, 1, 1, 0,
                                                                  0, 1 },
                                       { 0, 1, 1, 0, 0, 1, 1 }, { 1, 0, 1, 1, 0,
                                                                  1, 1 },
                                       { 1, 0, 1, 1, 1, 1, 1 }, { 1, 1, 1, 0, 0,
                                                                  0, 0 },
                                       { 1, 1, 1, 1, 1, 1, 1 }, { 1, 1, 1, 1, 0,
                                                                  1, 1 } };

    //Cycle to the next digit to start writing
    CycleDisplayDigits();

    int s;
    for (s = 0; s < 7; s++)
    {
        if (sevenSegArray[num][s] == 1)
        {
            //Light the segment if given a 1
            GPIO_setOutputHighOnPin(GPIO_PORT_P4, sevenSegPinArray[s]);
        }
        else
        {
            //Dim the segment if given a 0
            GPIO_setOutputLowOnPin(GPIO_PORT_P4, sevenSegPinArray[s]);
        }
    }
}

/*
 * This function cycles to the next digit on the seven segment display.
 *
 * This is called each time a digit is rewritten.
 */
void CycleDisplayDigits(void)
{
    volatile uint32_t delay = 0;
    for (delay = 2000; delay > 0; delay--)
    {

    }

    DisplayDigit(digitIndex);

    digitIndex = (digitIndex + 1) % 3;
}

void DisplayDigit(int num)
{
    if (num == 0)
    {
        GPIO_setOutputHighOnPin(GPIO_PORT_P1, GPIO_PIN7);
        GPIO_setOutputHighOnPin(GPIO_PORT_P3, GPIO_PIN6);
        GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN5);
    }
    else if (num == 1)
    {
        GPIO_setOutputHighOnPin(GPIO_PORT_P1, GPIO_PIN7);
        GPIO_setOutputLowOnPin(GPIO_PORT_P3, GPIO_PIN6);
        GPIO_setOutputHighOnPin(GPIO_PORT_P1, GPIO_PIN5);
    }
    else if (num == 2)
    {
        GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN7);
        GPIO_setOutputHighOnPin(GPIO_PORT_P3, GPIO_PIN6);
        GPIO_setOutputHighOnPin(GPIO_PORT_P1, GPIO_PIN5);
    }
}

/*
 * This function takes an incoming frequency of a note
 * and uses the modulus operation to separate each digit
 * from the variable. Those individual digits are then
 * written to their own digit on the display.
 *
 * This is called by the TA1_0_IRQHandler()
 */
void WriteToDisplay(int num)
{
    int a = num % 10;
    num /= 10;
    int b = num % 10;
    num /= 10;
    int c = num % 10;

    WriteToDigit(a);
    WriteToDigit(b);
    WriteToDigit(c);

}
