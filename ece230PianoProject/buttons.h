/*
 * buttons.h
 *
 *  Created on: Feb 14, 2021
 *      Author: rutantj
 */

#ifndef BUTTONS_H_
#define BUTTONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

/*******************************************************************************
 *                                FUNCTIONS
 ******************************************************************************/
//extern void interruptHandler(int port, uint_t gpioArray);
extern void ButtonsConfig(void);
extern void Port5Handler(uint32_t pin);
extern void Port2Handler(uint32_t pin);

/*******************************************************************************
 *                                CONSTANTS
 ******************************************************************************/


// All pins on port 2


#ifdef __cplusplus
}
#endif

#endif /* BUTTONS_H_ */
