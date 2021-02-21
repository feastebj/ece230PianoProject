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

/*******************************************************************************
 *                                CONSTANTS
 ******************************************************************************/

#define NumberOfLEDs 50
#define DelayTime 5000000
#define NeoPixelDataOutSet P1->OUT=P1->OUT | 0b01000000;
#define NeoPixelDataOutClear P1->OUT=P1->OUT & 0b10111111;
//const char Position[8]={0b00000001,0b00000010,0b00000100,0b00001000,0b00010000,0b00100000,0b01000000,0b10000000};

char LEDS[NumberOfLEDs][3];


char BitPosition;

#ifdef __cplusplus
}
#endif

#endif /* NEOPIXEL_H_ */
