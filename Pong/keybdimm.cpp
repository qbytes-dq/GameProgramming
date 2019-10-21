//-----------------------------------------------------------------------------
// File: KeybdImm.cpp
//
// Desc: Demonstrates an application which receives immediate 
//       keyboard data in non-exclusive mode via a dialog timer.
//
// Copyright (c) 1998-1999 Microsoft Corporation. All rights reserved.
//-----------------------------------------------------------------------------
#ifndef KEYBOARD_NON_H_CPP
#define KEYBOARD_NON_H_CPP

#include "KeybdImm.h"

//-----------------------------------------------------------------------------
// Global variables
//-----------------------------------------------------------------------------
LPDIRECTINPUT       g_pKeyboardDI       = NULL;         
LPDIRECTINPUTDEVICE g_pKeyboard = NULL;     
bool                g_bActive   = true;     

extern int  draw_item_num;
extern bool b_intro;
//-----------------------------------------------------------------------------
// Name: InitKeyBoardInput()
// Desc: Initialize the DirectInput variables.
//-----------------------------------------------------------------------------
HRESULT InitKeyBoardInput( HWND hWnd )
{
    HRESULT hr;

    // Register with the DirectInput subsystem and get a pointer
    // to a IDirectInput interface we can use.
    hr = DirectInputCreate( (HINSTANCE)GetWindowLong( hWnd, GWL_HINSTANCE ),
		                    DIRECTINPUT_VERSION, &g_pKeyboardDI, NULL );
    if( FAILED(hr) ) 
        return hr;

    // Obtain an interface to the system keyboard device.
    hr = g_pKeyboardDI->CreateDevice( GUID_SysKeyboard, &g_pKeyboard, NULL );
    if( FAILED(hr) ) 
        return hr;

    // Set the data format to "keyboard format" - a predefined data format 
    //
    // A data format specifies which controls on a device we
    // are interested in, and how they should be reported.
    //
    // This tells DirectInput that we will be passing an array
    // of 256 bytes to IDirectInputDevice::GetDeviceState.
    hr = g_pKeyboard->SetDataFormat( &c_dfDIKeyboard );
    if( FAILED(hr) ) 
        return hr;

    // Set the cooperativity level to let DirectInput know how
    // this device should interact with the system and with other
    // DirectInput applications.

//  hr = g_pKeyboard->SetCooperativeLevel( hWnd, 
//  RINGS BELL IN NON-EX             DISCL_NONEXCLUSIVE | DISCL_FOREGROUND );

    hr = g_pKeyboard->SetCooperativeLevel( hWnd, 
                                     DISCL_EXCLUSIVE | DISCL_FOREGROUND );
    if( FAILED(hr) ) 
        return hr;
OutputDebugString ("KeyBoard - Init \n");
    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: SetKeyBoardAcquire()
// Desc: Acquire or unacquire the keyboard, depending on if the app is active
//       Input device must be acquired before the GetDeviceState is called
//-----------------------------------------------------------------------------
HRESULT SetKeyBoardAcquire( HWND hDlg )
{
    // Nothing to do if g_pKeyboard is NULL
    if( NULL == g_pKeyboard )
        return S_FALSE;

    if( g_bActive ) 
    {
        // Acquire the input device 
        g_pKeyboard->Acquire();
    } 
    else 
    {
        // Update the dialog text 
		// SetWindowText( GetDlgItem( hDlg, IDC_KEYBD_STATE ), "Unacquired" );

        // Unacquire the input device 
        g_pKeyboard->Unacquire();
    }

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: UpdateKeyBoardState()
// Desc: Get the input device's state and display it.
//-----------------------------------------------------------------------------
HRESULT UpdateKeyBoardState( HWND hDlg , CPlayer &Player1)

{
    if( g_pKeyboard ) 
    {
		static BYTE Key_State;
        BYTE    diks[256];   // DirectInput keyboard state buffer 
        HRESULT hr;

        hr = DIERR_INPUTLOST;

        // If input is lost then acquire and keep trying 
        while( DIERR_INPUTLOST == hr ) 
        {
            // Get the input's device state, and put the state in dims
            hr = g_pKeyboard->GetDeviceState( sizeof(diks), &diks );

            if( hr == DIERR_INPUTLOST )
            {
                // DirectInput is telling us that the input stream has been
				// interrupted.  We aren't tracking any state between polls, so
				// we don't have any special reset that needs to be done.
				// We just re-acquire and try again.
                hr = g_pKeyboard->Acquire();
            }
        }

        if( FAILED(hr) )  
            return hr;

		// Quit (ESCAPE)
		// Quit (ESCAPE)
		// Quit (ESCAPE)
		 if (diks[DIK_ESCAPE] & 0x80)
			{
				//PostMessage(hDlg, WM_CLOSE, 0, 0);
	 			 PostMessage(hDlg, WM_COMMAND, IDC_GAMEQUIT, 0);
			}

		 if (diks[DIK_0] & 0x80)
		 { // hide the display
			draw_item_num = 0;
  		    PostMessage(hDlg, WM_COMMAND, IDC_EXTEND_KEY, 0);
		 }
		 if (diks[DIK_1] & 0x80)
		 {
			//SoundPlayEffect( SOUND_BEARMISS );
			draw_item_num = 1;
			//Player1.i_my_slot = 0;
			 PostMessage(hDlg, WM_COMMAND, IDC_EXTEND_KEY, 0);
		 }
		 if (diks[DIK_2] & 0x80)
		 {
			//SoundPlayEffect( SOUND_BEARSTRIKE );
			draw_item_num = 2;
			//Player1.i_my_slot = 1;
			 PostMessage(hDlg, WM_COMMAND, IDC_EXTEND_KEY, 0);
		 }
		 if (diks[DIK_3] & 0x80)
		 {
			//SoundPlayEffect( SOUND_BITE );
			draw_item_num = 3;
			//Player1.i_my_slot = 2;
			 PostMessage(hDlg, WM_COMMAND, IDC_EXTEND_KEY, 0);
		 }
		 if (diks[DIK_4] & 0x80)
		 {
			//SoundPlayEffect( SOUND_JUMP );
			draw_item_num = 4;
			//Player1.i_my_slot = 3;
			 PostMessage(hDlg, WM_COMMAND, IDC_EXTEND_KEY, 0);
		 }
		 if (diks[DIK_5] & 0x80)
		 {
			//SoundPlayEffect( SOUND_STOP );
			draw_item_num = 5;
			//Player1.i_my_slot = 4;
			 PostMessage(hDlg, WM_COMMAND, IDC_EXTEND_KEY, 0);
		 }
		 if (diks[DIK_6] & 0x80)
		 {
			//SoundPlayEffect( SOUND_STRIKE );
			draw_item_num = 6;
			//Player1.i_my_slot = 5;
			 PostMessage(hDlg, WM_COMMAND, IDC_EXTEND_KEY, 0);
		 }
		 if (diks[DIK_7] & 0x80)
		 {
			//SoundPlayEffect( SOUND_STUNNED );
			draw_item_num = 7;
			//Player1.i_my_slot = 6;
			 PostMessage(hDlg, WM_COMMAND, IDC_EXTEND_KEY, 0);
		 }
		 if (diks[DIK_8] & 0x80)
		 {
			//SoundPlayEffect( SOUND_THROW );
			draw_item_num = 8;
			//Player1.i_my_slot = 7;
			 PostMessage(hDlg, WM_COMMAND, IDC_EXTEND_KEY, 0);
		 }

//* PAUSE DOES NOT WORK PROPERLY, NEXT FUNCTION IS 'P' FOR PAUSE

		 // Pause the game
		if (b_intro != true)		 
			if (diks[DIK_P] & 0x80 || Key_State & GamePause)
			{
				Key_State |= GamePause;
				if ( !(diks[DIK_P] & 0x80))
				{
				PostMessage(hDlg, WM_COMMAND, IDC_GAMEPAUSE, 0);
				Key_State &= ~GamePause;
				SoundPlayEffect( SOUND_Pause );
				}
			}


		 // Display help for the game
		 if (diks[DIK_F1] & 0x80 || Key_State & GameHelp)
		 {
			Key_State |= GameHelp;
			if ( !(diks[DIK_F1] & 0x80))
			 {
			 Key_State &= ~GameHelp;
			 Player1.b_Help_Disp = !Player1.b_Help_Disp;
			 PostMessage(hDlg, WM_COMMAND, IDC_EXTEND_KEY, 0);
			 }
		 }//Player1.b_Help_Disp	GameHelp

// up / down
		 if (diks[DIK_DOWN] & 0x80)
			Player1.i_y_pos[Player1.i_my_slot] += 10;
		 if (diks[DIK_UP] & 0x80)
			Player1.i_y_pos[Player1.i_my_slot] -= 10;


// left / right
		 if (diks[DIK_LEFT] & 0x80)
			Player1.i_x_pos[Player1.i_my_slot] -= 10;
		 if (diks[DIK_RIGHT] & 0x80)
			Player1.i_x_pos[Player1.i_my_slot] += 10;
		 
  }

   return S_OK;
}




//-----------------------------------------------------------------------------
// Name: FreeKeyBoardInput()
// Desc: Initialize the DirectInput variables.
//-----------------------------------------------------------------------------
HRESULT FreeKeyBoardInput()
{
    // Unacquire and release any DirectInputDevice objects.
    if( g_pKeyboard ) 
    {
        // Unacquire the device one last time just in case 
        // the app tried to exit while the device is still acquired.
        g_pKeyboard->Unacquire();
        g_pKeyboard->Release();
        g_pKeyboard = NULL;
    }

    // Release any DirectInput objects.
    if( g_pKeyboardDI ) 
    {
        g_pKeyboardDI->Release();
        g_pKeyboardDI = NULL;
    }

    return S_OK;
}

#endif