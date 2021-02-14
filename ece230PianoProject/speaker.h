/*
 * speaker.h
 *
 *  Created on: Feb 13, 2021
 *      Author: rutantj
 */

#ifndef SPEAKER_H_
#define SPEAKER_H_

#ifdef __cplusplus
extern "C"
{
#endif

/*******************************************************************************
 *                                FUNCTIONS
 ******************************************************************************/

extern void SpeakerConfig(void);
extern void SpeakerBasicFunction(void);

/*******************************************************************************
 *                            CONSTANTS
 ******************************************************************************/

#define NOTECNT 3
// Note A4 - 440 Hz, B4 - 493.88 Hz, C5 - 523.26 Hz
#define NOTEA4  4545
#define NOTEB4  4050
#define NOTEC5  3822

#ifdef __cplusplus
}
#endif

#endif /* SPEAKER_H_ */
