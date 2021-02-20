/*
 * octaveDial.c
 *
 *  Created on: Feb 19, 2021
 *      Author: rutantj
 */

/* DriverLib Includes */
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

/* Standard Includes */
#include <stdint.h>
#include <stdbool.h>

/* Statics */
static volatile uint16_t curADCResult;
static volatile float normalizedADCRes;

void OctaveDialConfig(void)
{
    /* Initializing Variables */
    curADCResult = 0;

    /* Setting DCO to 48MHz  */
    MAP_PCM_setPowerState(PCM_AM_LDO_VCORE1);
    MAP_CS_setDCOCenteredFrequency(CS_DCO_FREQUENCY_48);

    /* Enabling the FPU for floating point operation */
    MAP_FPU_enableModule();
    MAP_FPU_enableLazyStacking();

    //![Single Sample Mode Configure]
    /* Initializing ADC (MCLK/1/4) */
    MAP_ADC14_enableModule();
    MAP_ADC14_initModule(ADC_CLOCKSOURCE_MCLK, ADC_PREDIVIDER_1, ADC_DIVIDER_4,
                         0);

    /* Configuring GPIOs (5.5 A0) */
    MAP_GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P5, GPIO_PIN5,
    GPIO_TERTIARY_MODULE_FUNCTION);

    /* Configuring ADC Memory */
    MAP_ADC14_configureSingleSampleMode(ADC_MEM0, true);
    MAP_ADC14_configureConversionMemory(ADC_MEM0, ADC_VREFPOS_AVCC_VREFNEG_VSS,
    ADC_INPUT_A0,
                                        false);

    /* Configuring Sample Timer */
    MAP_ADC14_enableSampleTimer(ADC_MANUAL_ITERATION);

    /* Enabling/Toggling Conversion */
    MAP_ADC14_enableConversion();
    MAP_ADC14_toggleConversionTrigger();
    //![Single Sample Mode Configure]

    /* Enabling interrupts */
    MAP_ADC14_enableInterrupt(ADC_INT0);
    MAP_Interrupt_enableInterrupt(INT_ADC14);
}

double GetVoltage(void)
{
    curADCResult = MAP_ADC14_getResult(ADC_MEM0);
    normalizedADCRes = (curADCResult * 3.3) / 16384;
    return (double) normalizedADCRes;
}
