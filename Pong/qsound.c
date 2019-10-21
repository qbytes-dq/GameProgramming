/*==========================================================================
 *
 *  Copyright (C) 1995-1997 Microsoft Corporation. All Rights Reserved.
 *
 *  File:       fbsound.c
 *  Content:	Game sound effect routines
 *
 ***************************************************************************/
/*
#ifndef DEBUG
void _cdecl Mesg( LPSTR fmt, ... ) { }
#endif
*/
#include <stdio.h>
#include "sound.h"
   
// the next commented out sections is what the WAV should look like in the RC file
/////////////////////////////////////////////////////////////////////////////
//
// WAV
//

//MISS01                  WAV     MOVEABLE PURE   "MISS01.WAV" 
// end comment


/*
 * Array of pointers to our sound effects
 */
LPDIRECTSOUND			lpDS;
LPDIRECTSOUNDBUFFER     lpSoundEffects[NUM_SOUND_EFFECTS];

/* ORDER IN enum_EFFECTs NEEDS TO MATCH szSoundEffects, also change NUM_SOUND_EFFECTS */
/* ORDER IN enum_EFFECTs NEEDS TO MATCH szSoundEffects, also change NUM_SOUND_EFFECTS */
/* ORDER IN enum_EFFECTs NEEDS TO MATCH szSoundEffects, also change NUM_SOUND_EFFECTS */
/* ORDER IN enum_EFFECTs NEEDS TO MATCH szSoundEffects, also change NUM_SOUND_EFFECTS */
/* ORDER IN enum_EFFECTs NEEDS TO MATCH szSoundEffects, also change NUM_SOUND_EFFECTS */

char szSoundEffects[NUM_SOUND_EFFECTS][MAX_PATH] =
{
    "JUMP",
//	"MISS01",
	"MISS02",
	"STOP",
	"STRIKE01",
	"STRIKE02",
	"STUNNED",
	"THROW",
	"ENERGIZE",
	"LOSE",
	"XPLOSION",
	"MENCHEER_WIN",
	"VICTORY",
	"Pause",
	"playerdies",
	"QBYTESPONG",
};


/*
 * DSEnable
 *
 * Figures out whether or not to use DirectSound, based on an entry
 * in WIN.INI.  Sets a module-level flag and goes about creating the
 * DirectSound object if necessary.  Returns TRUE if successful.
 */
BOOL DSEnable( HWND hwnd )
{
    HRESULT		dsrval;
    BOOL                bUseDSound;
	BOOL				bWantSound = TRUE;

    bUseDSound = GetProfileInt("Pong", "use_dsound", bWantSound);

    if (!bUseDSound)
    {
        lpDS = NULL;
        return TRUE;
    }

    if (lpDS != NULL)
    {
		OutputDebugString ("DSEnable, already enabled \n");
        //Mesg( "DSEnable, already enabled" );
        return TRUE;
    }

    dsrval = DirectSoundCreate(NULL, &lpDS, NULL);

    if (dsrval != DS_OK)
    {
		OutputDebugString ("DirectSoundCreate FAILED \n");
        //Mesg("DirectSoundCreate FAILED");
        return FALSE;
    }


    dsrval = IDirectSound_SetCooperativeLevel(lpDS, hwnd, DSSCL_NORMAL);

    if (dsrval != DS_OK)
    {
        DSDisable();
		OutputDebugString ("Sound SetCooperativeLevel FAILED \n");
        return FALSE;
    }

    return TRUE;

} /* DSEnable */


/*
 * DSDisable
 *
 * Turn off DirectSound
 */
BOOL DSDisable( void )
{
    if (lpDS == NULL)
    {
	return TRUE;
    }

    IDirectSound_Release(lpDS);
    lpDS = NULL;

    return TRUE;

} /* DSDisable */

/*
 * InitSound
 *
 * Sets up the DirectSound object and loads all sounds into secondary
 * DirectSound buffers.  Returns FALSE on error, or TRUE if successful
 */
BOOL InitSound( HWND hwndOwner )
{
    int idx;
    DSBUFFERDESC dsBD;
    IDirectSoundBuffer *lpPrimary;

	char      stg[256];

    DSEnable(hwndOwner);

    if (lpDS == NULL)
        //return TRUE;
		return FALSE;

    /*
     * Load all sounds -- any that can't load for some reason will have NULL
     * pointers instead of valid SOUNDEFFECT data, and we will know not to
     * play them later on.
     */


    for( idx = 0; idx < NUM_SOUND_EFFECTS; idx++ )
    {
        if (SoundLoadEffect((EFFECT)idx))
        {
            DSBCAPS  caps;

            caps.dwSize = sizeof(caps);
			//LPCTSTR lpName
            IDirectSoundBuffer_GetCaps(lpSoundEffects[idx], &caps);

            if (caps.dwFlags & DSBCAPS_LOCHARDWARE)
			{
				sprintf(stg, "Sound effect %s in hardware\n", szSoundEffects[idx]);
				OutputDebugString (stg);
				//OutputDebugString ("Sound effect %s in hardware \n","asdf");
                //Mesg( "Sound effect %s in hardware", szSoundEffects[idx]);
			}
            else
			{
				sprintf(stg, "Sound effect %s in software\n", szSoundEffects[idx]);
				OutputDebugString (stg);
				//OutputDebugString ("Sound effect %s in software \n");
                //Mesg( "Sound effect %s in software", szSoundEffects[idx]);
			}
        }
        else
        {
			sprintf(stg, "cant load sound effect %s\n", szSoundEffects[idx]);
			OutputDebugString (stg);
			//OutputDebugString ("cant load sound effect \n");
            //Mesg( "cant load sound effect %s", szSoundEffects[idx]);
        }
    }

    /*
     * get the primary buffer and start it playing
     *
     * by playing the primary buffer, DirectSound knows to keep the
     * mixer active, even though we are not making any noise.
     */

    ZeroMemory( &dsBD, sizeof(DSBUFFERDESC) );
    dsBD.dwSize = sizeof(dsBD);
    dsBD.dwFlags = DSBCAPS_PRIMARYBUFFER;

    if (SUCCEEDED(IDirectSound_CreateSoundBuffer(lpDS, &dsBD, &lpPrimary, NULL)))
    {
        if (!SUCCEEDED(IDirectSoundBuffer_Play(lpPrimary, 0, 0, DSBPLAY_LOOPING)))
        {
			OutputDebugString ("Unable to play Primary sound buffer \n");
			return FALSE;
            //Mesg("Unable to play Primary sound buffer");
        }

        IDirectSoundBuffer_Release(lpPrimary);
    }
    else
    {
		OutputDebugString ("Unable to create Primary sound buffer \n");
		return FALSE;
        //Mesg("Unable to create Primary sound buffer");
    }

    return TRUE;

} /* InitSound */

/*
 * DestroySound
 *
 * Undoes everything that was done in a InitSound call
 */
BOOL DestroySound( void )
{
    DWORD	idxKill;
    
    for( idxKill = 0; idxKill < NUM_SOUND_EFFECTS; idxKill++ )
    {
	SoundDestroyEffect( (EFFECT)idxKill );
    }

    DSDisable();
    return TRUE;

} /* DestroySound */

/*
 * SoundDestroyEffect
 *
 * Frees up resources associated with a sound effect
 */
BOOL SoundDestroyEffect( EFFECT sfx )
{
    if(lpSoundEffects[sfx])
    {
        IDirectSoundBuffer_Release(lpSoundEffects[sfx]);
        lpSoundEffects[sfx] = NULL;
    }
    return TRUE;

} /* SoundDestryEffect */

/*
 * SoundLoadEffect
 *
 * Initializes a sound effect by loading the WAV file from a resource
 */
BOOL SoundLoadEffect( EFFECT sfx )
{
    if (lpDS && lpSoundEffects[sfx] == NULL && *szSoundEffects[sfx])
    {
        //
        //  use DSLoadSoundBuffer (in ..\misc\dsutil.c) to load
        //  a sound from a resource.
        //
        lpSoundEffects[sfx] = DSLoadSoundBuffer(lpDS, szSoundEffects[sfx]);
    }

    return lpSoundEffects[sfx] != NULL;

} /* SoundLoadEffect */

/*
 * SoundPlayEffect
 *
 * Plays the sound effect specified.  
 * Returns TRUE if succeeded.
 */
BOOL SoundPlayEffect( EFFECT sfx )
{
    HRESULT     dsrval;

    IDirectSoundBuffer *pdsb = lpSoundEffects[sfx];
    

    if( !lpDS || !pdsb )
    {
	return FALSE;
    }
    
    /*
     * Rewind the play cursor to the start of the effect, and play
     */
    IDirectSoundBuffer_SetCurrentPosition(pdsb, 0);
    dsrval = IDirectSoundBuffer_Play(pdsb, 0, 0, 0);
	
    if (dsrval == DSERR_BUFFERLOST)
    {
		OutputDebugString ("** %s needs restored \n");
        //Mesg("** %s needs restored", szSoundEffects[sfx]);

        dsrval = IDirectSoundBuffer_Restore(pdsb);
        if (dsrval == DS_OK)
        {
            if (DSReloadSoundBuffer(pdsb, szSoundEffects[sfx]))
            {
				OutputDebugString ("** %s has been restored \n");
                //Mesg("** %s has been restored", szSoundEffects[sfx]);
                IDirectSoundBuffer_SetCurrentPosition(pdsb, 0);
                dsrval = IDirectSoundBuffer_Play(pdsb, 0, 0, 0);
            }
            else
            {
                dsrval = E_FAIL;
            }
        }
    }

    return (dsrval == DS_OK);

} /* SoundPlayEffect */

/*
 * SoundStopEffect
 *
 * Stops the sound effect specified.
 * Returns TRUE if succeeded.
 */
BOOL SoundStopEffect( EFFECT sfx )
{
    HRESULT	dsrval;

    if( !lpDS || !lpSoundEffects[sfx] )
    {
	return FALSE;
    }

    dsrval = IDirectSoundBuffer_Stop(lpSoundEffects[sfx]);

    return SUCCEEDED(dsrval);

} /* SoundStopEffect */
