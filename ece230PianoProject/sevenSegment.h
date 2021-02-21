/*
 * sevenSegment.h
 *
 *  Created on: Feb 17, 2021
 *      Author: rutantj
 */

#ifndef SEVENSEGMENT_H_
#define SEVENSEGMENT_H_

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 *                                FUNCTIONS
 ******************************************************************************/

extern void WriteToDisplay(int num);
extern void WriteToDigit(int num);
extern void CycleDisplayDigits(void);
extern void DisplayDigit(int num);
extern void SevenSegmentConfig(void);

/*******************************************************************************
 *                                CONSTANTS
 ******************************************************************************/

#define TIMER_PERIOD_7SEG    5000000 //5000

const uint16_t sevenSegPinArray[];
const int sevenSegDisplayArray[];

#ifdef __cplusplus
}
#endif

#endif /* SEVENSEGMENT_H_ */
