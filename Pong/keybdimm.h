//-----------------------------------------------------------------------------
// File: KeybdImm.h
//
// Desc: Header file for for DirectInput sample
//
// Copyright (c) 1997-1999 Microsoft Corporation. All rights reserved.
//-----------------------------------------------------------------------------
#ifndef KEYBDIMM_H
#define KEYBDIMM_H

#define STRICT
#include <windows.h>
#include <dinput.h>
#include "resource.h"
#include "CPlayer.h"
#include "sound.h"

//#include "cWall.h"
//#include "cWallList.h"

#define GameHelp	0x40
#define GamePause	0x80

//-----------------------------------------------------------------------------
// External function-prototypes
//-----------------------------------------------------------------------------
extern HRESULT InitKeyBoardInput( HWND hDlg );
extern HRESULT SetKeyBoardAcquire( HWND hDlg );
extern HRESULT FreeKeyBoardInput();
extern HRESULT UpdateKeyBoardState( HWND hDlg , CPlayer &Player1);

extern bool    g_bActive;		


#endif // KEYBDIMM_H
