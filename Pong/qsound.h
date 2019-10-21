/*==========================================================================
 *
 *  Copyright (C) 1995-1997 Microsoft Corporation. All Rights Reserved.
 *
 *  File:       sound.h
 *  Content:	Includes for Sound DirectSound support
 *
 ***************************************************************************/
#ifndef __FBSOUND_INCLUDED__
#define __FBSOUND_INCLUDED__

/*
 * types of sound effects
 */

/* ORDER IN enum_EFFECTs NEEDS TO MATCH szSoundEffects, also change NUM_SOUND_EFFECTS */
/* ORDER IN enum_EFFECTs NEEDS TO MATCH szSoundEffects, also change NUM_SOUND_EFFECTS */
/* ORDER IN enum_EFFECTs NEEDS TO MATCH szSoundEffects, also change NUM_SOUND_EFFECTS */
/* ORDER IN enum_EFFECTs NEEDS TO MATCH szSoundEffects, also change NUM_SOUND_EFFECTS */
/* ORDER IN enum_EFFECTs NEEDS TO MATCH szSoundEffects, also change NUM_SOUND_EFFECTS */


// don't forget to change the NUM_SOUND_EFFECTS at bottom
// don't forget to change the NUM_SOUND_EFFECTS at bottom
typedef enum enum_EFFECT
{
	SOUND_JUMP = 0,		//jump
// don't forget to change the NUM_SOUND_EFFECTS at bottom
//	SOUND_BEARMISS,		//miss01
    SOUND_BEARSTRIKE,	//miss02
    SOUND_STOP,			//stop
	SOUND_STRIKE,		//strike01
	SOUND_BITE,			//strike02
	SOUND_STUNNED,		//stunned
    SOUND_THROW,		//throw
	SOUND_ENERGIZE,
	SOUND_LOSE,
	SOUND_XPLOSION,
	SOUND_MENCHEER_WIN,
	SOUND_VICTORY,
	SOUND_Pause,
	SOUND_playerdies,
	SOUND_QBYTESPONG,
} EFFECT;

#define NUM_SOUND_EFFECTS      15


/*
 * fn prototypes
 */
BOOL InitSound( HWND );
extern BOOL DestroySound( void );
BOOL DSDisable( void );
BOOL DSEnable( HWND );
BOOL SoundLoadEffect( EFFECT );
extern BOOL SoundPlayEffect( EFFECT );
BOOL SoundStopEffect( EFFECT );
BOOL SoundDestroyEffect( EFFECT );

#endif
