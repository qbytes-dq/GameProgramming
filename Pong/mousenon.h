//-----------------------------------------------------------------------------
// File: MouseNon.h
//
// Desc: Header file for for DirectInput sample
//
// Copyright (c) 1997-1999 Microsoft Corporation. All rights reserved.
//-----------------------------------------------------------------------------
#ifndef MOUSE_NON_H
#define MOUSE_NON_H

#define STRICT
#include <windows.h>
#include <dinput.h>
#include "resource.h"
#include "CPlayer.h"
#include "sound.h"

#define BallFocus 0x80
//-----------------------------------------------------------------------------
// External function-prototypes
//-----------------------------------------------------------------------------
extern HRESULT InitMouseInput( HWND hDlg );
extern HRESULT SetMouseAcquire( HWND hDlg );
extern HRESULT FreeMouseInput();
extern HRESULT UpdateMouseState( HWND hDlg , CPlayer &Player1);

extern bool g_bActive;		
extern HINSTANCE g_hInst;		


#endif // !defined(MOUSE_NON_H)
