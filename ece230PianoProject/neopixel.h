/*
 * neopixel.h
 *
 *  Created on: Feb 20, 2021
 *      Author: Benjamin
 */

#ifndef NEOPIXEL_H_
#define NEOPIXEL_H_

#ifdef __cplusplus
extern "C"
{
#endif

/*******************************************************************************
 *                                FUNCTIONS
 ******************************************************************************/
extern void NeopixelSetup(void);
extern void NeoPixelDataTransfer(char Green, char Red, char Blue);
extern void WriteNeopixelsToDisplay(int num);

/*******************************************************************************
 *                                CONSTANTS
 ******************************************************************************/

#define NumberOfLEDs 50
#define DelayTime 5000
#define NeoPixelDataOutSet P1->OUT = P1->OUT | 0b01000000;
#define NeoPixelDataOutClear P1->OUT = P1->OUT & 0b10111111;

char LEDS[NumberOfLEDs][3];


char BitPosition;

#ifdef __cplusplus
}
#endif

#endif /* NEOPIXEL_H_ */
