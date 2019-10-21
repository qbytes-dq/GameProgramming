//-----------------------------------------------------------------------------
// File: MouseNon.cpp
//
// Desc: Demonstrates an application which receives relative mouse data
//       in non-exclusive mode via a dialog timer.
//
// Copyright (c) 1998-1999 Microsoft Corporation. All rights reserved.
//-----------------------------------------------------------------------------
#ifndef MOUSE_NON_H_CPP
#define MOUSE_NON_H_CPP

//#define INITGUID //don't know what this is, don't uncomment, linkage errors occur
#include "MouseNon.h"

static BYTE Mouse_State;
//-----------------------------------------------------------------------------
// Global variables for the DirectMusic sample 
//-----------------------------------------------------------------------------
IDirectInput*           g_pMouseDI  = NULL;
IDirectInputDevice*     g_pMouse    = NULL;
extern HINSTANCE        g_hInst;
extern BOOL SoundPlayEffect( EFFECT sfx );

//-----------------------------------------------------------------------------
// Function: InitMouseInput
//
// Description: 
//      Initialize the DirectInput variables.
//
//-----------------------------------------------------------------------------
HRESULT InitMouseInput( HWND hDlg )
{
    HRESULT hr;

    // Register with the DirectInput subsystem and get a pointer
    // to a IDirectInput interface we can use.
    hr = DirectInputCreate( g_hInst, DIRECTINPUT_VERSION, &g_pMouseDI, NULL );
    if ( FAILED(hr) ) 
        return hr;

    // Obtain an interface to the system mouse device.
    hr = g_pMouseDI->CreateDevice( GUID_SysMouse, &g_pMouse, NULL );
    if ( FAILED(hr) ) 
        return hr;

    // Set the data format to "mouse format" - a predefined data format 
    //
    // A data format specifies which controls on a device we
    // are interested in, and how they should be reported.
    //
    // This tells DirectInput that we will be passing a
    // DIMOUSESTATE structure to IDirectInputDevice::GetDeviceState.
    hr = g_pMouse->SetDataFormat( &c_dfDIMouse );
    if ( FAILED(hr) ) 
        return hr;

    // Set the cooperativity level to let DirectInput know how
    // this device should interact with the system and with other
    // DirectInput applications.
    hr = g_pMouse->SetCooperativeLevel( hDlg, 
                                        DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
    if ( FAILED(hr) ) 
        return hr;

	OutputDebugString ("MouseNon - Init \n");
    return S_OK;
}

//-----------------------------------------------------------------------------
// Function: SetMouseAcquire
//
// Description: 
//      Acquire or unacquire the mouse, depending on if the app is active
//       Input device must be acquired before the GetDeviceState is called
//
//-----------------------------------------------------------------------------
HRESULT SetMouseAcquire( HWND hDlg )
{
    char szText[128];
    HWND hDlgText;

    // nothing to do if g_pMouse is NULL
    if (NULL == g_pMouse)
        return S_FALSE;

    if (g_bActive) 
    {
        // acquire the input device 
        g_pMouse->Acquire();
    } 
    else 
    {
        // update the dialog text 
        strcpy( szText, "Unacquired" );
        hDlgText = GetDlgItem( hDlg, IDC_MOUSE_STATE );
        SetWindowText( hDlgText, szText );

        // unacquire the input device 
        g_pMouse->Unacquire();
    }

    return S_OK;
}

//-----------------------------------------------------------------------------
// Function: UpdateMouseState
//
// Description: 
//      Get the input device's state and display it.
//
//-----------------------------------------------------------------------------
HRESULT UpdateMouseState( HWND hDlg , CPlayer &Player1)
{

    if (NULL != g_pMouse) 
    {
        DIMOUSESTATE dims;      // DirectInput mouse state structure
        HRESULT hr;

        hr = DIERR_INPUTLOST;

		//------------------------------------------
        // if input is lost then acquire and keep trying 
        while ( DIERR_INPUTLOST == hr ) 
        {
            // get the input's device state, and put the state in dims
            hr = g_pMouse->GetDeviceState( sizeof(DIMOUSESTATE), &dims );

            if ( hr == DIERR_INPUTLOST )
            {
                // DirectInput is telling us that the input stream has
                // been interrupted.  We aren't tracking any state
                // between polls, so we don't have any special reset
                // that needs to be done.  We just re-acquire and
                // try again.
                hr = g_pMouse->Acquire();
                if ( FAILED(hr) )  
                    return hr;
            }// end if
        }// end while

        if ( FAILED(hr) )  
            return hr;

		//------------------------------------------
		// set player x or y poss.  
		Player1.i_x_pos[Player1.i_my_slot] = dims.lX * 3;
		Player1.i_y_pos[Player1.i_my_slot] = dims.lY * 3;
				
		//------------------------------------------
		// set ball focus status
		if (dims.rgbButtons[1] & 0x80  || Mouse_State & BallFocus)
		{
			Mouse_State |= BallFocus;
			if ( ! (dims.rgbButtons[1] & 0x80 ))
				{
				if (!Player1.b_Winner_Found)
					{
					SoundPlayEffect( SOUND_STUNNED );
					Player1.b_focus_on_ball = !Player1.b_focus_on_ball;
					Mouse_State &=~BallFocus;
					}
				}  // end if 
		} // end if

		//------------------------------------------
		//

	}// end if (NULL != g_pMouse)


    return S_OK;
}// end function


//-----------------------------------------------------------------------------
// Function: FreeMouseInput
//
// Description: 
//      Initialize the DirectInput variables.
//
//-----------------------------------------------------------------------------
HRESULT FreeMouseInput()
{
    // Unacquire and release any DirectInputDevice objects.
    if (NULL != g_pMouse) 
    {
        // Unacquire the device one last time just in case 
        // the app tried to exit while the device is still acquired.
        g_pMouse->Unacquire();

        g_pMouse->Release();
        g_pMouse = NULL;
    }

    // Release any DirectInput objects.
    if (NULL != g_pMouseDI) 
    {
        g_pMouseDI->Release();
        g_pMouseDI = NULL;
    }

    return S_OK;
}

#endif