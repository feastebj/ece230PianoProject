/*
 * speaker.h
 *
 *  Created on: Feb 13, 2021
 *      Author: rutantj
 */

#ifndef SPEAKER_H_
#define SPEAKER_H_

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 *                                FUNCTIONS
 ******************************************************************************/

extern void SpeakerConfig(void);
extern void ChangeNote(double note);
extern void SpeakerBasicFunction(void);

/*******************************************************************************
 *                                CONSTANTS
 ******************************************************************************/

#define SystemClock 12000000 //Hz
#define Prescaler 3 //Timer A prescaler
#define TimerAClock  SystemClock/Prescaler
#define TIMER_PERIOD    1000000 // (3*10^6) / (3)

#define FrequencyC3      130.81 //Hz
#define FrequencyC3_     138.59 //Hz
#define FrequencyD3      146.83 //Hz
#define FrequencyD3_     155.56 //Hz
#define FrequencyE3      164.81 //Hz
#define FrequencyF3      174.61 //Hz
#define FrequencyF3_     185.00 //Hz
#define FrequencyG3      196.00 //Hz
#define FrequencyG3_     207.65 //Hz
#define FrequencyA3      220.00 //Hz
#define FrequencyA3_     233.08 //Hz
#define FrequencyB3      246.94 //Hz

// A 440 is used as the tuning note
#define FrequencyA4      440.0  //Hz

#define NOTECNT 12

#define NOTEC3   TimerAClock/FrequencyC3/2
#define NOTEC3_  TimerAClock/FrequencyC3_/2
#define NOTED3   TimerAClock/FrequencyD3/2
#define NOTED3_  TimerAClock/FrequencyD3_/2
#define NOTEE3   TimerAClock/FrequencyE3/2
#define NOTEF3   TimerAClock/FrequencyF3/2
#define NOTEF3_  TimerAClock/FrequencyF3_/2
#define NOTEG3   TimerAClock/FrequencyG3/2
#define NOTEG3_  TimerAClock/FrequencyG3_/2
#define NOTEA3   TimerAClock/FrequencyA3/2
#define NOTEA3_  TimerAClock/FrequencyA3_/2
#define NOTEB3   TimerAClock/FrequencyB3/2

#define NOTEA4   TimerAClock/FrequencyA4/2

#ifdef __cplusplus
}
#endif

#endif /* SPEAKER_H_ */
