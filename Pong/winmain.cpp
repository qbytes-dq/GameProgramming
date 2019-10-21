/*
  if a versions error occurs:
	fatal error C1071: unexpected end of file found in comment Error executing cl.exe.

  delete in *.rc
	#include "verinfo.h"
	#include "verinfo.ver"


  when inserting new BMP make sure the name is formated "ABC"  also
	make sure the type is Neutral
*/
#include <stdio.h>
//----------------------------------------------------------------------------

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#define STRICT
#define IDIRECTPLAY2_OR_GREATER
#include <windows.h>
#include <dplobby.h>
#include <dplay.h>
#include <stdio.h>
#include <stdlib.h>
#include "resource.h"
#include <time.h>

#include <mmsystem.h>
//-----------------------------------------------------------------------------

#include "MouseNon.h"
#include "KeybdImm.h"
#include "qsound.c"
#include "qDraw.h"

#include "Enumerations.h"


#include "trace.h"
#define TRACE   stagetrace 

//-----------------------------------------------------------------------------
// Defines, and constants
//-----------------------------------------------------------------------------
#define SAFE_DELETE(p)       { if(p) { delete (p);     (p)=NULL; } }
#define SAFE_DELETE_ARRAY(p) { if(p) { delete[] (p);   (p)=NULL; } }
#define SAFE_RELEASE(p)      { if(p) { (p)->Release(); (p)=NULL; } }

#define DPLAY_QBYTES_KEY     TEXT("Software\\QBYTES\\FIRSTGAME")

#define MAX_PLAYER_NAME     14
#define MAX_SESSION_NAME    256

#define EXITCODE_FORWARD     1  // Dialog success, so go forward
#define EXITCODE_BACKUP      2  // Dialog canceled, show previous dialog
#define EXITCODE_QUIT        3  // Dialog quit, close app
#define EXITCODE_ERROR       4  // Dialog error, terminate app

// This GUID allows DirectPlay to find other instances of the same game on
// the network.  So it must be unique for every game, and the same for 
// every instance of that game.  // {1EBAF240-7496-47c4-B94E-DFA358DE3871}
GUID g_AppGUID = { 0x1ebaf240, 0x7496, 0x47c4, { 0xb9, 0x4e, 0xdf, 0xa3, 0x58, 0xde, 0x38, 0x71 } };

HINSTANCE	g_hInst	= NULL;
HWND    g_hDlg = NULL;
HWND	g_hwnd = NULL;
int g_iPlayerType[7];
int	g_iNum_Balls = 8;
int	g_iDifficult = 5;
int	g_iScoreOut = 1;

bool g_bLostFocus = false;

bool g_Full_Screen = true;
int	g_Resolution = 800;

//int g_i_deg;

extern HWND g_hDlg_connect1;		//DQ005
extern HWND g_hDlg_connect2;		//DQ005
extern HWND g_hDlg_connect3;		//DQ005
extern HWND g_hDlg_connect4;		//DQ005
extern HWND g_hDlg_connect5;		//DQ005

//-----------------------------------------------------------------------------
// Global variables
//-----------------------------------------------------------------------------
LPDIRECTPLAY4A     g_pDP                                     = NULL;
LPDPLCONNECTION    g_pDPLConnection                          = NULL;  
LPDIRECTPLAYLOBBY3 g_pDPLobby                                = NULL;  
HANDLE             g_hDPMessageEvent                         = NULL;
BOOL               g_bUseProtocol;
HKEY               g_hQBytesRegKey                      = NULL;
TCHAR              g_strLocalPlayerName[MAX_PLAYER_NAME];
TCHAR              g_strSessionName[MAX_SESSION_NAME];
TCHAR              g_strPreferredProvider[MAX_SESSION_NAME];
VOID*              g_pvDPMsgBuffer                           = NULL;
DWORD              g_dwDPMsgBufferSize                       = 0;
bool               g_bHostPlayer;
DPID               g_LocalPlayerDPID; 
TCHAR              g_strAppName[256] = "Q Bytes : StagedConnect";

extern DWORD g_dwSlotDPID[MAX_PLAYER_SLOTS];

bool b_intro;	//DQ006

//-----------------------------------------------------------------------------
// DAQ Temp Global variables
//-----------------------------------------------------------------------------
int		draw_cnt_start;
int		draw_item_num = 1;
double	draw_x;
double	draw_x_dir;
double	draw_y;
double	draw_y_dir;
int		draw_obj_ID;
int		draw_wait_cnt;

//-----------------------------------------------------------------------------
// App specific DirectPlay messages and structures 
//-----------------------------------------------------------------------------
#define GAMEMSG_START		1
#define GAMEMSG_GAME_SEED	2
#define GAMEMSG_GAME_PAUSE	3
#define GAMEMSG_GAME_QUIT	4
#define GAMEMSG_PADDLE		5
#define GAMEMSG_GAME_READY	6
#define GAMEMSG_SYNC_BALL	7

#define GAMEMSG_EXTEND_KEY	8


#define SYNC_BALL			177

#define IM_WINNER			187
#define WINNER_FOUND		188
#define SCORE_AGAINST		199
//-----------------------------------------------------------------------------
typedef struct _GAMEMSG_GENERIC
{
    BYTE dwType;
} GAMEMSG_GENERIC, *LPGAMEMSG_GENERIC;
//-----------------------------------------------------------------------------
typedef struct _GAMEMSG_PADDLEDATA
{
    BYTE dwType;
    double Paddle_Pos_X;
    double Paddle_Pos_Y;
	DWORD d_Slot;
	int		i_cir_deg;
} GAMEMSG_PADDLEDATA, *LPGAMEMSG_PADDLEDATA;
//-----------------------------------------------------------------------------
typedef struct _GAMEMSG_GAMEREADY
{
    BYTE dwType;
	DWORD d_Slot;
} GAMEMSG_GAMEREADY, *LPGAMEMSG_GAMEREADY;
//-----------------------------------------------------------------------------
typedef struct _GAMEMSG_SEED_DATA
{
    BYTE dwType;
	double d_Seed;
} GAMEMSG_SEEDDATA, *LPGAMEMSG_SEEDDATA;
//-----------------------------------------------------------------------------
typedef struct _GAMEMSG_PAUSE_DATA
{
    BYTE dwType;
	bool b_PAUSE;
} GAMEMSG_PAUSEDATA, *LPGAMEMSG_PAUSEDATA;
//-----------------------------------------------------------------------------
typedef struct _GAMEMSG_QUIT_DATA
{
    BYTE dwType;
	int I_QUIT_PLAYER;
} GAMEMSG_QUITDATA, *LPGAMEMSG_QUITDATA;
//-----------------------------------------------------------------------------
typedef struct _GAMEMSG_BALLDATA
{
    BYTE dwType;
    double	Ball_Pos_X;
    double	Ball_Pos_Y;
    double	Ball_Vol_X;
    double	Ball_Vol_Y;
	int		Ball_OwnerID;
	DWORD d_Slot;
	double Ball_bounce_x;
	double Ball_bounce_y;
} GAMEMSG_BALLDATA, *LPGAMEMSG_BALLDATA;
//-----------------------------------------------------------------------------
typedef struct _GAMEMSG_KEY_DATA
{
    BYTE dwType;
	bool State;
	int	Ball;
} GAMEMSG_KEYDATA, *LPGAMEMSG_KEYDATA;
//-----------------------------------------------------------------------------
typedef struct _SCORE_AGAINST_DATA
{
    BYTE dwType;
	int SCORE_ON_PLAYER;
} SCORE_AGAINSTDATA, *LPSCORE_AGAINSTDATA;
//-----------------------------------------------------------------------------
// Function-prototypes
//-----------------------------------------------------------------------------
extern int     DPConnect_StartDirectPlayConnect( HINSTANCE hInst, BOOL bBackTrack = FALSE );
extern int     DPStage_StartDirectPlayStage( HINSTANCE hInst );
extern HRESULT DPConnect_CheckForLobbyLaunch( BOOL* pbLaunchedByLobby );

HRESULT        DoConnectAndGame( HINSTANCE hInst , CPlayer &Player8);	//dq001
int            DoGreetingGame( HINSTANCE hInst , CPlayer &Player8);		//dq001
int            DoGameIntro( HINSTANCE hInst , CPlayer &Player8);			//DQ006


BOOL CALLBACK  GreetingDlgProc( HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam );
HRESULT        NumberOfPlayers( HWND hDlg ,CPlayer &Player1);

HRESULT        ProcessDirectPlayMessages( HWND hDlg,CPlayer &Player1,wall_list &a_list );
HRESULT        HandleAppMessages( HWND, GAMEMSG_GENERIC*, DWORD, DPID, DPID,CPlayer &Player1,wall_list &a_list );
HRESULT        HandleSystemMessages( HWND, DPMSG_GENERIC*, DWORD, DPID, DPID );

HRESULT        ReadyToAllPlayers(CPlayer &Player1);
HRESULT		   SeedToAllPlayers(CPlayer &Player1);
HRESULT		   PauseToAllPlayers(CPlayer &Player1);
HRESULT		   QuitToAllPlayers(CPlayer &Player1);
HRESULT        StartToAllPlayers(CPlayer &Player1);
HRESULT        PaddleToAllPlayers(CPlayer &Player1,wall_list &a_list);
HRESULT        BallToAllPlayers(int x);
HRESULT        ScoreToAllPlayers(int Against);
HRESULT        ExtendKeyToPlayers(CPlayer &Player1);

//CPlayer        CPlayerAddress(CPlayer &Player1,bool set);
//void		   DefaultBallData();

HRESULT        DisplayPlayerStart( HWND hDlg, DPID idFrom ,CPlayer &Player1);
HRESULT        DisplayPlayerPaddle( HWND hDlg, DPID idFrom, double numb_x, double numb_y, DWORD d_Slot);
HRESULT        DisplayPlayerBall( HWND hDlg, DPID idFrom, double numb_x, double numb_y,double numb_vx, double numb_vy, DWORD d_Slot);

HRESULT        ReadRegKey( HKEY hKey, TCHAR* strName, TCHAR* strValue, DWORD dwLength, TCHAR* strDefault );
HRESULT        WriteRegKey( HKEY hKey, TCHAR* strName, TCHAR* strValue );

HRESULT			InitApp(HINSTANCE hInstance, int nCmdShow);
HRESULT			initDDraw (HINSTANCE hInstance, int nCmdShow);

//-----------------------------------------------------------------------------

#include "cPlayer.h"


//CPlayer Player1(0);	//(0) = player #, will overlay when slots filled	//dq001
CPlayer		*Player2;			//daq001 needed for WinProc
wall_list	*g_wall_list;		//dq002

//-----------------------------------------------------------------------------
//wall_list *a_list_wall;		//dq002
//wall_list		a_list;			//dq002

//#include "trace.h"
//
//#define extern TRACE   stagetrace 
//-----------------------------------------------------------------------------
// Name: WindowProc()
// Desc: The Main Window Procedure
//-----------------------------------------------------------------------------
long FAR PASCAL
WindowProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{

	g_hwnd = hDlg;
    HRESULT hr;



    switch (message)
    {
		//==============================================================================================
        case WM_TIMER:
			{
            // update the input device every timer message
		    if ( g_bActive )  // update only when active
			{//active
					//======================================
					hr = UpdateMouseState( hDlg, *Player2 );	//dq001
	                if ( FAILED(hr) )
		            {
			            KillTimer( hDlg, 0 );    
				      //  MessageBox( NULL, "Error Reading Mouse State", "DirectInput Sample", MB_ICONERROR | MB_OK );
	                  //  EndDialog( hDlg, TRUE ); 
						g_bLostFocus = true;
						OutputDebugString ("WM-Timer Mouse Error\n");
						if (Player2->i_mouse == 1)//DQ007 thru else
							Player2->i_mouse = 0;
		            }
					else
					{
						if (Player2->i_mouse == 0)
							Player2->i_mouse = 1;
					}

					//======================================
					hr = UpdateKeyBoardState( hDlg, *Player2);	//dq001
		            if( FAILED(hr) )
			        {
				        KillTimer( hDlg, 0 );    
					//    MessageBox( NULL, "Error Reading Keyboard State", "DirectInput Sample", MB_ICONERROR | MB_OK );
	                //    EndDialog( hDlg, TRUE ); 
						g_bLostFocus = true;
						OutputDebugString ("WM-Timer KeyBoard Error\n");
						if (Player2->i_key == 1)//DQ007 thru else
							Player2->i_key = 0;
		            }
					else
					{
						if (Player2->i_key == 0)
							Player2->i_key = 1;
					}
				}	
			else
			{// not active
				if (Player2->i_mouse == 1)
					Player2->i_mouse = 0;

				if (Player2->i_key == 1)
					Player2->i_key = 0;

				Player2->b_sound = false;
			}
//1/11/03
				// no game play if intro, skip ready test
				if (b_intro != true)	//DQ006
					{
					// game play on
					///////////////////////////////////////////////////////////
					// Don't start any movement till all players check in
					///////////////////////////////////////////////////////////
					if (Player2->b_all_players_ready)	//dq001
					///////////////////////////////////////////////////////////
					// all players ready & playing game
					///////////////////////////////////////////////////////////
							{
							// waiting for everyone to say go
							}//end if
					else
					///////////////////////////////////////////////////////////
					// wait for all players ready
					///////////////////////////////////////////////////////////
							{
								Player2->check_all_players_ready();	//dq001

								if (Player2->b_all_players_ready)	//dq001
								{
									SoundPlayEffect (SOUND_ENERGIZE);

									if( FAILED( hr = StartToAllPlayers(*Player2) ) )	//dq001
										PostQuitMessage( EXITCODE_ERROR );

									if (g_bHostPlayer)
										{
										// this step here to notify other players of the rand seed
										if( FAILED( hr = SeedToAllPlayers(*Player2) ) )	//dq001
											PostQuitMessage( EXITCODE_ERROR );
										}  // end if


									//Get the time at beginning of frame
	// 1/10/03								QueryPerformanceCounter((LARGE_INTEGER *)&Player2->time_game_start_2);
	// 1/10/03		 						QueryPerformanceCounter((LARGE_INTEGER *)&Player2->time_game_last_2);

									}  // end if
							} // end if else
					}	//end (b_intro != true)
			///////////////////////////////////////////////////////////
			}
            break;
		//==============================================================================================
        case WM_COMMAND:
			{
            switch( LOWORD(wParam) )
	            {
				case WINNER_FOUND:
					{
					// Play this when the game is over.....
					SoundPlayEffect (SOUND_MENCHEER_WIN);
					}
		            break;
				//=========================
				case IM_WINNER:
					{
					// Play this when the game is over, AND I AM THE WINNER.....
					SoundPlayEffect (SOUND_VICTORY);
					}
		            break;
				//=========================
				case SYNC_BALL:
					{
					if( FAILED( hr = BallToAllPlayers(LOWORD(lParam)) ) )
						    PostQuitMessage( EXITCODE_ERROR );
					Player2->Set_Game_Rand();  // use 2 more rand	//dq001
					/*
					char      stg[256];
					sprintf(stg, "command set game rand x %i y %i \n" + '\0', Player1.Return_Rand_X() , Player1.Return_Rand_Y());
					OutputDebugString (stg);
					sprintf(stg, "command set game rand x %i y %i \n" + '\0', Player1.Rand_X , Player1.Rand_Y);
					OutputDebugString (stg);
					*/
					}
					break;
				//=========================
				case SCORE_AGAINST:
					{
					ScoreToAllPlayers(LOWORD(lParam));					
					}
					break;
				//=========================
				case IDC_INITTIMER:
					{
					// set a timer to go off 30 times a second
		            // at every timer message the input device will be read
					OutputDebugString ("WindowProc - InitTimer \n");
				    SetTimer( hDlg, 0, 1000/30, NULL );
					}
					break;

				//==========================
				case IDC_GAMEPAUSE:
					{
						 Player2->b_Game_Pause = !Player2->b_Game_Pause;	//dq001
						 PauseToAllPlayers(*Player2);	//dq001
					}
					break;

				//==========================
				case IDC_EXTEND_KEY:
					{
					OutputDebugString ("IDC_EXTEND_KEY \n");
					ExtendKeyToPlayers(*Player2);	//dq001
					}
					break;

				//==========================
				case IDC_GAMEQUIT:
					{
						// FIRST, LET EVERYONE KNOW I QUIT
						QuitToAllPlayers(*Player2);	//dq001
						// SECOND, CLOSE ME DOWN
						PostMessage(hDlg, WM_CLOSE, 0, 0);
					}
					break;
				}
				break;
			}
		//==============================================================================================
	    case WM_ACTIVATE:

			OutputDebugString ("WindowProc - Activate \n");
            if ( WA_INACTIVE == wParam )
            {
				// Lost focus
                g_bActive = false;
				g_bLostFocus = true;
				OutputDebugString ("WM-LostFocus\n");
            }
            else
            {
				// has focus
                g_bActive = true;
				//g_bLostFocus = false;
				// Set exclusive mode access to the mouse based on active state
				SetMouseAcquire( hDlg );
				SetKeyBoardAcquire( hDlg );
			
				PostMessage(hDlg, WM_COMMAND, IDC_INITTIMER, 0);

				BOOL	b_temp;
				b_temp = InitSound(hDlg);		//DQ007
				if (b_temp == TRUE)
					Player2->b_sound = true;
				else
					Player2->b_sound = false;

				OutputDebugString ("WM-HasFocus\n");
            }

			break;
/*		//==============================================================================================
        case WM_INITDIALOG:
			OutputDebugString ("WinMain_GreetingDlgProc WM_INITDIALOG \n");
                if( FAILED( hr = NumberOfPlayers( hDlg ) ) )
                    PostQuitMessage( EXITCODE_ERROR );
            //return TRUE;
            break;
*/
		//==============================================================================================
        case WM_CREATE:
            // Clean up and close the app
			OutputDebugString ("WindowProc - CREATE \n");
			//==========================
            hr = InitMouseInput( hDlg );

            if ( FAILED(hr) )
            {//DQ007 thru else
                /*MessageBox( NULL, 
                    "Error Initializing Mouse", 
                    "DirectInput Sample", 
                    MB_ICONERROR | MB_OK );

                EndDialog( hDlg, 0 );
				*/
				Player2->i_mouse = -1;
            }
			else 
				Player2->i_mouse = 0;
			//=============================
	        hr = InitKeyBoardInput( hDlg );
            if( FAILED(hr) )
            {//DQ007 thru else
             /*   MessageBox( NULL, 
							"Error Initializing Keyboard", 
                            "DirectInput Sample", 
							MB_ICONERROR | MB_OK );
                EndDialog( hDlg, 0 );
				*/
				Player2->i_key = -1;
            }
			else
				Player2->i_key = 0;
  
			// Set exclusive mode access to the mouse based on active state
            SetMouseAcquire( hDlg );
			//daq 12/15/02 uncomment next line
			SetKeyBoardAcquire( hDlg );

			BOOL	b_temp;
			b_temp = InitSound(hDlg);		//DQ007
			if (b_temp == TRUE)
                Player2->b_sound = true;
			else
				Player2->b_sound = false;

			PostMessage(hDlg, WM_COMMAND, IDC_INITTIMER, 0);
			break;
		//==============================================================================================
        case WM_SETCURSOR:
			{
			// Turn off the cursor since this is a full-screen app
            SetCursor(NULL);
			}
			break;
		//==============================================================================================
        case WM_CLOSE:
			{
			OutputDebugString ("WindowProc - WM_CLOSE \n");
            KillTimer( hDlg, 0 );
			DestroySound();			
			FreeMouseInput();
			FreeKeyBoardInput();
 
			EndDialog( hDlg, TRUE ); 
			PostQuitMessage(0);

            return TRUE;
			}
            break;
		//==============================================================================================
    }

    return DefWindowProc(hDlg, message, wParam, lParam);
}


//==============================================================================================
//CPlayer     CPlayerAddress(CPlayer &Player1,bool set)
//{
//	static CPlayer *Player2;
//	if (set == true)
//		Player2 = &Player1;
//
//	// always return the address
//	return *Player2;
//}

//-----------------------------------------------------------------------------
// Name: WinMain()
// Desc: Entry point for the application.  Since we use a simple dialog for 
//       user interaction we don't need to pump messages.
//-----------------------------------------------------------------------------
int PASCAL
WinMain(HINSTANCE hInst,
        HINSTANCE hPrevInst,
        LPSTR pCmdLine,
        int nCmdShow)

{

HRESULT hr = true;		//jh001 moved from below
CPlayer* Player8;		//daq001

//DQ006
// call intro to game
g_hInst = hInst;						//DQ006
Player8 = new CPlayer(8);				//DQ006
Player2 = Player8;						//DQ006 is a global for where we do not have control
hr = DoGameIntro( hInst , *Player8);	//DQ006

delete Player8;							//DQ006

//??? do I need to test hr from intro???  Yes,  if DirectDraw fails, bail
if (hr == DD_OK)
	{
	hr = S_OK;	//dq006 prevent exit from while loop
	///////////////////////////////////////////////
	// loop 
		while(hr !=  E_ABORT)	//jh001
		{						//jh001

			Player8 = new CPlayer(8);	//daq001

			b_intro = false;
			g_bHostPlayer = false;
			g_iNum_Balls = 1;
			g_iDifficult = 1;	// stage will reassign 1-5, for a range from 7 to 11 after adding 6
			g_iScoreOut = 1;

			Player2 = Player8;	//dq001 is a global for where we do not have control

	//		g_hInst = hInst;  1/11/03

			OutputDebugString ("WinMain \n");

			// Read information from registry
			RegCreateKeyEx( HKEY_CURRENT_USER, DPLAY_QBYTES_KEY, 0, NULL,
							REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, 
							&g_hQBytesRegKey, NULL );
			ReadRegKey( g_hQBytesRegKey, "Player Name", 
						g_strLocalPlayerName, MAX_PLAYER_NAME, "" );
			ReadRegKey( g_hQBytesRegKey, "Session Name", 
						g_strSessionName, MAX_SESSION_NAME, "" );
			ReadRegKey( g_hQBytesRegKey, "Preferred Provider", 
						g_strPreferredProvider, MAX_SESSION_NAME, "" );

			// open first window
			g_hDPMessageEvent = CreateEvent( NULL, FALSE, FALSE, NULL );

			if( FAILED( hr = CoInitialize( NULL ) ) )
				return FALSE;

			hr = DoConnectAndGame( hInst , *Player8);	//dq001
			if( SUCCEEDED( hr ) )
				{
				// Write information to the registry
				WriteRegKey( g_hQBytesRegKey, "Player Name", g_strLocalPlayerName );
				WriteRegKey( g_hQBytesRegKey, "Session Name", g_strSessionName );
				WriteRegKey( g_hQBytesRegKey, "Preferred Provider", g_strPreferredProvider );
			}

			// Cleanup DirectPlay
			if( g_pDP )
				{
				g_pDP->DestroyPlayer( g_LocalPlayerDPID );
				g_pDP->Close();

				SAFE_DELETE_ARRAY( g_pDPLConnection );
				SAFE_RELEASE( g_pDPLobby );
				SAFE_RELEASE( g_pDP )
				}
			
			CoUninitialize();

			CloseHandle( g_hQBytesRegKey );
			CloseHandle( g_hDPMessageEvent );

			delete Player8;		//daq001

			//return TRUE;			//jh001
			DestroyWindow(g_hwnd);  //jh001

			// dq005 g_hdlg_connext*
			if (g_hDlg_connect1 != NULL)
				{
				EndDialog( g_hDlg_connect1, EXITCODE_QUIT );
				g_hDlg_connect1 = NULL;
				}
			if (g_hDlg_connect2 != NULL)
				{
				EndDialog(g_hDlg_connect2, EXITCODE_QUIT );
				g_hDlg_connect2 = NULL;
				}
			if (g_hDlg_connect3 != NULL)
				{
				EndDialog( g_hDlg_connect3, EXITCODE_QUIT );
				g_hDlg_connect3 = NULL;
				}
			if (g_hDlg_connect4 != NULL)
				{
				EndDialog( g_hDlg_connect4, EXITCODE_QUIT );
				g_hDlg_connect4 = NULL;
				}
			if (g_hDlg_connect5 != NULL)
				{
				EndDialog( g_hDlg_connect5, EXITCODE_QUIT );
				g_hDlg_connect5 = NULL;
				}
		}	// end while loop
	}// if intro worked, do next
	return true;			//jh001
}	// end winmain




//-----------------------------------------------------------------------------
// Name: DoConnectAndGame()
// Desc: Connect to other players using DirectPlay and begin the the game.
//-----------------------------------------------------------------------------
HRESULT DoConnectAndGame( HINSTANCE hInst,CPlayer &Player8 )	//dq001
{
    int     nExitCode;
    HRESULT hr;
    int     nStep;
    BOOL    bBacktrack;
    BOOL    bLaunchedByLobby;

char      stg[256];																			//dq001
sprintf(stg, "WinMain_DoConnectAndGame --- Player class = %i \n" + '\0', Player8.i_temp);	//dq001
OutputDebugString (stg);																	//dq001

    // See if we were launched from a lobby server
    hr = DPConnect_CheckForLobbyLaunch( &bLaunchedByLobby );
    if( FAILED(hr) )
		{
        if( hr == DPERR_USERCANCEL )
            return S_OK;

        return hr;
		}

    if( !bLaunchedByLobby )
    {
        nStep      = 0;
        bBacktrack = FALSE;

        // If not, show the dialog boxes to start a DirectPlay connect, and loop
        // until the user completes them all successfully or quits.
        while( TRUE )
        {
            switch( nStep )
            {
                case 0:
                    // The first step is to prompt the user about the network 
                    // connection and which session they would like to join or 
                    // if they want to create a new one.
                    nExitCode = DPConnect_StartDirectPlayConnect( hInst, bBacktrack );
                    bBacktrack = TRUE;
                    break;

                case 1:
                    // The second step is to start a multiplayer stage 
                    nExitCode = DPStage_StartDirectPlayStage( hInst );
//					EndDialog( g_hDlg_connect4, EXITCODE_QUIT );//dq005 added
                    break;
            }

            // See the above EXITCODE #defines for what nExitCode could be 
            if( nExitCode == EXITCODE_QUIT )
            {
                // The user canceled the mutliplayer connect.
                // The sample will now quit.
                return E_ABORT;
            }

            if( nExitCode == EXITCODE_ERROR || g_pDP == NULL )
            {
                MessageBox( NULL, TEXT("Mutliplayer connect failed. "
                            "The Q Bytes game will now quit."),
                            TEXT("Q Bytes DirectPlay"), MB_OK | MB_ICONERROR );
                return E_FAIL;
            }

            if( nExitCode == EXITCODE_BACKUP )
                nStep--;
            else
                nStep++;

            if( nStep == 2 )
                break;
        }
    }

    // The next step is to start the game
    nExitCode = DoGreetingGame( hInst , Player8);		//dq001

    if( nExitCode == EXITCODE_ERROR )
    {
        MessageBox( NULL, "An error occured during the game. "
                    "The Q Bytes game will now quit.",
                    TEXT("Q Bytes DirectPlay"), MB_OK | MB_ICONERROR );

        return E_FAIL;
    }

    return S_OK;
}


//#include "trace.h"
//#define TRACE   stagetrace 
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
#include "qGameIntro.h"	//DQ006
#include "qGameLoop.h"

//-----------------------------------------------------------------------------
// Name: NumberOfPlayers()
// Desc: Inits the dialog for the greeting game.
//-----------------------------------------------------------------------------
HRESULT NumberOfPlayers( HWND hDlg ,CPlayer &Player1)
{
    DWORD           dwBufferSize;
    BYTE*           pData = NULL;
    DPSESSIONDESC2* pdpsd;
    HRESULT         hr;

    // Get the size of the dpsd
    g_pDP->GetSessionDesc( NULL, &dwBufferSize );

    // Allocate space for it now that we know the size 
    pData = new BYTE[ dwBufferSize ];
    if( pData == NULL )
        return E_OUTOFMEMORY;

    // Now, get the dpsd in the buffer
    if( FAILED( hr = g_pDP->GetSessionDesc( pData, &dwBufferSize ) ) )
        return hr;

    // Typecast the data to a DPSESSIONDESC2* 
    pdpsd = (DPSESSIONDESC2*) pData;
	Player1.i_numb_active_players = pdpsd->dwCurrentPlayers;

TRACE( TEXT("Numb Players = %i\n"), Player1.i_numb_active_players);
    // Update the dialog box

    return S_OK;
}


//-----------------------------------------------------------------------------
// Name: ProcessDirectPlayMessages()
// Desc: Processes for DirectPlay messages
//-----------------------------------------------------------------------------
HRESULT ProcessDirectPlayMessages( HWND hDlg,CPlayer &Player1,wall_list &a_list )
{
    DPID    idFrom;
    DPID    idTo;
    LPVOID  pvMsgBuffer;
    DWORD   dwMsgBufferSize;
    HRESULT hr;

    // Read all messages in queue
    dwMsgBufferSize = g_dwDPMsgBufferSize;
    pvMsgBuffer     = g_pvDPMsgBuffer;
//OutputDebugString ("WinMain_ProcessDirectPlayMessages \n");    
    while( TRUE )
    {
        // See what's out there
        idFrom = 0;
        idTo   = 0;

        hr = g_pDP->Receive( &idFrom, &idTo, DPRECEIVE_ALL, 
                             pvMsgBuffer, &dwMsgBufferSize );

        if( hr == DPERR_BUFFERTOOSMALL )
        {
            // The current buffer was too small, 
            // so reallocate it and try again
            SAFE_DELETE_ARRAY( pvMsgBuffer );

            pvMsgBuffer = new BYTE[ dwMsgBufferSize ];
            if( pvMsgBuffer == NULL )
                return E_OUTOFMEMORY;

            // Save new buffer in globals
            g_pvDPMsgBuffer     = pvMsgBuffer;
            g_dwDPMsgBufferSize = dwMsgBufferSize;

            continue; // Now that the buffer is bigger, try again
        }

        if( DPERR_NOMESSAGES == hr )
            return S_OK;

        if( FAILED(hr) )
            return hr;

        // Handle the messages. If its from DPID_SYSMSG, its a system message, 
        // otherwise its an application message. 
        if( idFrom == DPID_SYSMSG )
        {
            hr = HandleSystemMessages( hDlg, (DPMSG_GENERIC*)pvMsgBuffer, 
                                       dwMsgBufferSize, idFrom, idTo );
            if( FAILED(hr) )
                return hr;
        }
        else
        {
            hr = HandleAppMessages( hDlg, (GAMEMSG_GENERIC*)pvMsgBuffer, 
                                    dwMsgBufferSize, idFrom, idTo ,Player1,a_list);
            if( FAILED(hr) )
                return hr;
        }
    }

    return S_OK;
}


//-----------------------------------------------------------------------------
// Name: HandleAppMessages()
// Desc: Evaluates application messages and performs appropriate actions
//-----------------------------------------------------------------------------

HRESULT HandleAppMessages( HWND hDlg, LPGAMEMSG_GENERIC pMsg, DWORD dwMsgSize, 
                           DPID idFrom, DPID idTo ,CPlayer &Player1,wall_list &a_list)
						   
{
    HRESULT hr;
	
//OutputDebugString ("WinMain_HandleAppMessages \n");
    switch( pMsg->dwType )
    {

		case GAMEMSG_PADDLE:
            {

				LPGAMEMSG_PADDLEDATA lpPaddleData;
				lpPaddleData = (LPGAMEMSG_PADDLEDATA) pMsg;

				// the host tell us where the spinner should be
				if (g_bHostPlayer == false)
					{
					Player1.i_circle_deg = lpPaddleData->i_cir_deg;
					//g_i_deg = lpPaddleData->i_cir_deg;
				
					//char      stg[256];
					//sprintf(stg, "rcv circle data %i %i %i\n", Player1.i_circle_deg , lpPaddleData->i_cir_deg);
					//sprintf(stg, "rcv circle data %i %i %i\n", Player1.i_circle_deg , lpPaddleData->i_cir_deg , g_i_deg);
					//OutputDebugString (stg);
					}

				// Place the paddle data on the paddle
                if( FAILED( hr = DisplayPlayerPaddle( hDlg, idFrom , 
													lpPaddleData->Paddle_Pos_X,
													lpPaddleData->Paddle_Pos_Y,
													lpPaddleData->d_Slot) ) ) 
                    return hr;

				//		TRACE( TEXT("RCVD Player1 x= %i, y= %i , slot= %i\n"), lpPaddleData->Paddle_Pos_, lpPaddleData->Paddle_Pos_1 ,lpPaddleData->d_Slot);
            }
            break;

		case GAMEMSG_SYNC_BALL:
            {

				LPGAMEMSG_BALLDATA lpBallData;
				lpBallData = (LPGAMEMSG_BALLDATA) pMsg;

				a_list.Rcv_Sync_OwningID(	Player1,
											lpBallData->Ball_OwnerID,
											lpBallData->Ball_Pos_X,
											lpBallData->Ball_Pos_Y,
											lpBallData->Ball_Vol_X,
											lpBallData->Ball_Vol_Y,
											lpBallData->Ball_bounce_x,
											lpBallData->Ball_bounce_y);
				
				Player1.Set_Game_Rand();
				
            }
            break;


		case GAMEMSG_EXTEND_KEY:
            {// rcv msg	
				OutputDebugString ("IDC_EXTEND_KEY \n");
				LPGAMEMSG_KEYDATA lpKeyData;
				lpKeyData = (LPGAMEMSG_KEYDATA) pMsg;
				
				Player1.b_Help_Disp = lpKeyData->State;
				draw_item_num		= lpKeyData->Ball;
            }
            break;

		case GAMEMSG_GAME_READY:
            {

				LPGAMEMSG_GAMEREADY lpGameReady;
				lpGameReady = (LPGAMEMSG_GAMEREADY) pMsg;


				TRACE( TEXT("RCVD Player1 Ready slot= %i\n") ,lpGameReady->d_Slot);
				Player1.b_player_ready[lpGameReady->d_Slot] = true;  // flag player as ready

				TRACE( TEXT("Player1 ready t/f %i , slot= 0\n"), Player1.b_player_ready[0] );
				TRACE( TEXT("Player1 ready t/f %i , slot= 1\n"), Player1.b_player_ready[1] );
				TRACE( TEXT("Player1 ready t/f %i , slot= 2\n"), Player1.b_player_ready[2] );
				TRACE( TEXT("Player1 ready t/f %i , slot= 3\n"), Player1.b_player_ready[3] );
				TRACE( TEXT("Player1 ready t/f %i , slot= 4\n"), Player1.b_player_ready[4] );
				TRACE( TEXT("Player1 ready t/f %i , slot= 5\n"), Player1.b_player_ready[5] );
				TRACE( TEXT("Player1 ready t/f %i , slot= 6\n"), Player1.b_player_ready[6] );
				TRACE( TEXT("Player1 ready t/f %i , slot= 7\n"), Player1.b_player_ready[7] );

// reiderat host ready
//			if( FAILED( hr = ReadyToAllPlayers() ) )
//					    PostQuitMessage( EXITCODE_ERROR );
//
            }
            break;


		case GAMEMSG_START:
            {
                // This message is sent when all players to Start us.
                if( FAILED( hr = DisplayPlayerStart( hDlg, idFrom ,Player1) ) ) 
                    return hr;
				Player1.time_game_start = timeGetTime();
            }
            break;

		case GAMEMSG_GAME_SEED:
            {
				LPGAMEMSG_SEEDDATA lpSeedData;
				lpSeedData = (LPGAMEMSG_SEEDDATA) pMsg;

                // This message is sent when game is ready to start to seed rand().
				Player1.Game_Seed = lpSeedData->d_Seed;
								Player1.Seed_Rand();
				// do sync in here to set ball original direction. 
				//(non - host,  host in the post of this message)
				//			DefaultBallData();
				// daqsync
            }
            break;

		case GAMEMSG_GAME_PAUSE:
            {
				LPGAMEMSG_PAUSEDATA lpPauseData;
				lpPauseData = (LPGAMEMSG_PAUSEDATA) pMsg;

                // This message is sent when game is ready to start to PAUSE rand().
				Player1.b_Game_Pause = lpPauseData->b_PAUSE;
				SoundPlayEffect( SOUND_Pause );
//////////////				 void remove(const int OwningPlayer) 
            }
            break;


		case GAMEMSG_GAME_QUIT:
            {
				LPGAMEMSG_QUITDATA lpQuitData;
				lpQuitData = (LPGAMEMSG_QUITDATA) pMsg;

				Player1.b_Player_Quit = true; 
				Player1.i_PlayerType[lpQuitData->I_QUIT_PLAYER]=Closed;

				// remove the player paddle from the list and the screen
				a_list.remove_Owning_Player(lpQuitData->I_QUIT_PLAYER);

				// do we now have a winner

				// this is where the error is when a player quites the game
				// and someone on hit team is still in

				int PLR;
				PLR = lpQuitData->I_QUIT_PLAYER;

				if (PLR >= 4)
					PLR -= 4;
	
				// IS THERE A PLAYER STILL ON THE TEAM
				if (!(Player1.i_PlayerType[PLR] == Computer ||
					  Player1.i_PlayerType[PLR] == Human ||
					  Player1.i_PlayerType[PLR+4] == Computer ||
					  Player1.i_PlayerType[PLR+4] == Human ))
							{
							Player1.set_score(g_iScoreOut - Player1.i_score[lpQuitData->I_QUIT_PLAYER] , lpQuitData->I_QUIT_PLAYER);
							}
            }
            break;
//=====================================
		case SCORE_AGAINST:
            {
				LPSCORE_AGAINSTDATA lpScoreAgainst;
				lpScoreAgainst = (LPSCORE_AGAINSTDATA) pMsg;

				//if lpScoreAgainst->SCORE_ON_PLAYER < 99					
				SoundPlayEffect( SOUND_STUNNED );
				Player1.set_score(1,lpScoreAgainst->SCORE_ON_PLAYER);				
            }
            break;
//=====================================
    }

    return S_OK;
}


//-----------------------------------------------------------------------------
// Name: HandleSystemMessages()
// Desc: Evaluates system messages and performs appropriate actions
//-----------------------------------------------------------------------------
HRESULT HandleSystemMessages( HWND hDlg, DPMSG_GENERIC* pMsg, DWORD dwMsgSize, 
                              DPID idFrom, DPID idTo )
{  
HRESULT       hr;
if( FAILED( hr = NumberOfPlayers( hDlg ,*Player2 ) ) )	//dq001
           PostQuitMessage( EXITCODE_ERROR );


//OutputDebugString ("WinMain_HandleSystemMessages \n");
    switch( pMsg->dwType )
    {
        case DPSYS_SESSIONLOST:
            // Non-host message.  This message is sent to all players 
            // when the host exits the game.
            if( g_bHostPlayer )
                return E_FAIL; // Sanity check

            PostQuitMessage( DPERR_SESSIONLOST );
            break;

        case DPSYS_CREATEPLAYERORGROUP:
            DPMSG_CREATEPLAYERORGROUP* pCreateMsg;
            pCreateMsg = (DPMSG_CREATEPLAYERORGROUP*) pMsg;

            if( pCreateMsg->dwPlayerType == DPPLAYERTYPE_PLAYER )
            {
                // This message should typically not happen in a staged game
                // since joining after the stage is not allowed
                return E_FAIL;
            }
            break;

        case DPSYS_DESTROYPLAYERORGROUP:
            DPMSG_DESTROYPLAYERORGROUP* pDeleteMsg;
            pDeleteMsg = (DPMSG_DESTROYPLAYERORGROUP*) pMsg;

            break;
        case DPSYS_HOST:
        {
            g_bHostPlayer = TRUE;
          //  UpdateTitle();
            break;
        }
    }

    return S_OK;
}

//-----------------------------------------------------------------------------
// Name: StartToAllPlayers()
// Desc: Send a app-defined "wave" DirectPlay message to all connected players
//-----------------------------------------------------------------------------
HRESULT StartToAllPlayers(CPlayer &Player1)
{
    HRESULT hr;

    GAMEMSG_GENERIC msgGenr;
    msgGenr.dwType = GAMEMSG_START;

OutputDebugString ("WinMain_StartToAllPlayers \n");

    // Send it to all of the players
    if( FAILED( hr = g_pDP->Send( g_LocalPlayerDPID, DPID_ALLPLAYERS, 
                                  DPSEND_GUARANTEED, &msgGenr, sizeof(GAMEMSG_START) ) ) ) 
        return hr;
	Player1.time_game_start = timeGetTime();
    return S_OK;
}

//-----------------------------------------------------------------------------
// Name: PaddleToAllPlayers()
// Desc: Send a app-defined "time" DirectPlay message to all connected players
//-----------------------------------------------------------------------------
HRESULT PaddleToAllPlayers(CPlayer &Player1,wall_list &a_listwall)
{
// no game play if intro, just return	//DQ006
if (b_intro == true)
	return S_OK;


// game play on
    HRESULT hr;

//OutputDebugString ("WinMain_PaddleToAllPlayers \n");

	GAMEMSG_PADDLEDATA msgGenr;
	msgGenr.dwType = GAMEMSG_PADDLE;

	msgGenr.Paddle_Pos_X	=	a_listwall.get_paddle_data_x(Player1.i_my_slot);
	msgGenr.Paddle_Pos_Y	=	a_listwall.get_paddle_data_y(Player1.i_my_slot);

	msgGenr.d_Slot			= Player1.i_my_slot;
// the host tell everyone where the spinner should be
	msgGenr.i_cir_deg		= Player1.i_circle_deg;

//	char      stg[256];																//dq001
//	sprintf(stg, "snd circle data %i %i \n", Player1.i_circle_deg , msgGenr.i_cir_deg);
//	OutputDebugString (stg);

//	TRACE( TEXT("temp turned off PaddleToAllPlayers x= %i, y= %i slot= %i \n"), Player1.i_x_1_pos[Player1.i_my_slot], Player1.i_y_1_pos[Player1.i_my_slot], Player1.i_my_slot);

	// Send it to all of the players
    if( FAILED( hr = g_pDP->Send( g_LocalPlayerDPID, DPID_ALLPLAYERS, 
                      DPSEND_GUARANTEED, &msgGenr, sizeof(GAMEMSG_PADDLEDATA) ) ) ) 
				      return hr;

    return S_OK;
}

//-----------------------------------------------------------------------------
// Name: BallToAllPlayers()
// Desc: Send a app-defined "ball" DirectPlay message to all connected players
//-----------------------------------------------------------------------------
HRESULT BallToAllPlayers(int ID)
{

// no game play if intro, just return	//DQ006
if (b_intro == true)
	return S_OK;


// game play on
 HRESULT hr;

 wall_list_element *cur_ptr; // Current item

     for (	cur_ptr = g_wall_list->return_first(); //dq002
			cur_ptr != NULL; 
			cur_ptr = cur_ptr->next_ptr) 
		{
			if (cur_ptr->i_object_ID == ID) 
				{
					 //cur_ptr->i_xpos_wall	= x_pos;
					 //cur_ptr->i_ypos_wall	= y_pos;
					 //cur_ptr->i_x_dir		= x_vol;
					 //cur_ptr->i_y_dir		= y_vol;
					GAMEMSG_BALLDATA msgGenr;
					msgGenr.dwType = GAMEMSG_SYNC_BALL;

					msgGenr.Ball_OwnerID	=	ID;
					msgGenr.Ball_Pos_X		=	cur_ptr->i_xpos_wall;
					msgGenr.Ball_Pos_Y		=	cur_ptr->i_ypos_wall;
					msgGenr.Ball_Vol_X		=	cur_ptr->i_x_dir;
					msgGenr.Ball_Vol_Y		=	cur_ptr->i_y_dir;
					msgGenr.d_Slot			=	0;   //Player1.i_my_slot;

					msgGenr.Ball_bounce_x	=	cur_ptr->d_bounce_x;
					msgGenr.Ball_bounce_y	=	cur_ptr->d_bounce_y;
				//TRACE( TEXT("BALL TO ALL PLAYERS x= %i, y= %i Vx= %i, Vy= %i slot= %i \n"),Player1.ball_x,Player1.ball_y,Player1.ball_vx,Player1.ball_vy );

					// Send it to all of the players
					if( FAILED( hr = g_pDP->Send( g_LocalPlayerDPID, DPID_ALLPLAYERS, 
												  DPSEND_GUARANTEED, &msgGenr, sizeof(GAMEMSG_BALLDATA) ) ) ) 
				//                                  0, &msgGenr, sizeof(GAMEMSG_BALLDATA) ) ) ) 
													return hr;

					
				}
		}	//next
return S_OK;
} // end sync
//-----------------------------------------------------------------------------
// Name: ExtendKeyToPlayers
// Desc: Send a app-defined "ball" DirectPlay message to all connected players
//-----------------------------------------------------------------------------
HRESULT ExtendKeyToPlayers(CPlayer &Player1)
{
// no game play if intro, just return	//DQ006
if (b_intro == true)
	return S_OK;


// game play on
OutputDebugString ("ExtendKeyToPlayers \n");
 HRESULT hr;

					GAMEMSG_KEYDATA msgGenr;
					msgGenr.dwType = GAMEMSG_EXTEND_KEY;

					msgGenr.State	=	Player1.b_Help_Disp;
					msgGenr.Ball	=	draw_item_num;

					// Send it to all of the players
					if( FAILED( hr = g_pDP->Send( g_LocalPlayerDPID, DPID_ALLPLAYERS, 
												  DPSEND_GUARANTEED, &msgGenr, sizeof(GAMEMSG_KEYDATA) ) ) ) 
													return hr;
return S_OK;
} // end Key Send
//-----------------------------------------------------------------------------
// Name: ReadyToAllPlayers()
// Desc: Send a app-defined "ready" DirectPlay message to all connected players
//-----------------------------------------------------------------------------
HRESULT ReadyToAllPlayers(CPlayer &Player1)
{
    HRESULT hr;

//OutputDebugString ("WinMain_ReadyToAllPlayers \n");

	GAMEMSG_GAMEREADY msgGenr;
	// set the msgGenr data
	msgGenr.dwType = GAMEMSG_GAME_READY;
	msgGenr.d_Slot	  = Player1.i_my_slot;

	// Send it to all of the players
    if( FAILED( hr = g_pDP->Send( g_LocalPlayerDPID, DPID_ALLPLAYERS, 
                                  DPSEND_GUARANTEED, &msgGenr, sizeof(GAMEMSG_GAMEREADY) ) ) ) 
				      return hr;

    return S_OK;
}
//-----------------------------------------------------------------------------
// Name: PAUSEToAllPlayers()
// Desc: Send a app-defined "PAUSE" DirectPlay message to all connected players
//-----------------------------------------------------------------------------
HRESULT PauseToAllPlayers(CPlayer &Player1)
{
    HRESULT hr;

//OutputDebugString ("WinMain_PauseToAllPlayers \n");

	GAMEMSG_PAUSEDATA msgGenr;
	// set the msgGenr data

	msgGenr.dwType = GAMEMSG_GAME_PAUSE;
	msgGenr.b_PAUSE = Player1.b_Game_Pause;


	// Send it to all of the players
    if( FAILED( hr = g_pDP->Send( g_LocalPlayerDPID, DPID_ALLPLAYERS, 
                                  DPSEND_GUARANTEED, &msgGenr, sizeof(GAMEMSG_PAUSEDATA) ) ) ) 
				      return hr;
    return S_OK;
}
//-----------------------------------------------------------------------------
// Name: QUITToAllPlayers()
// Desc: Send a app-defined "QUIT" DirectPlay message to all connected players
//-----------------------------------------------------------------------------
HRESULT QuitToAllPlayers(CPlayer &Player1)
{
// no game play if intro, just return	//DQ006
if (b_intro == true)
	return S_OK;


// game play on
    HRESULT hr;

//OutputDebugString ("WinMain_QUITToAllPlayers \n");

	GAMEMSG_QUITDATA msgGenr;
	// set the msgGenr data

	msgGenr.dwType = GAMEMSG_GAME_QUIT;
	msgGenr.I_QUIT_PLAYER = Player1.i_my_slot;

	// Send it to all of the players
    if( FAILED( hr = g_pDP->Send( g_LocalPlayerDPID, DPID_ALLPLAYERS, 
                                  DPSEND_GUARANTEED, &msgGenr, sizeof(GAMEMSG_QUITDATA) ) ) ) 
				      return hr;
    return S_OK;
}
//-----------------------------------------------------------------------------
// Name: ScoreToAllPlayers()
// Desc: 
//-----------------------------------------------------------------------------
HRESULT ScoreToAllPlayers(int Against)
{
// no game play if intro, just return	//DQ006
if (b_intro == true)
	return S_OK;


// game play on
    HRESULT hr;

//OutputDebugString ("WinMain_ScoreToAllPlayers \n");

	SCORE_AGAINSTDATA msgGenr;
	// set the msgGenr data

	msgGenr.dwType = SCORE_AGAINST;
	msgGenr.SCORE_ON_PLAYER = Against;

	// Send it to all of the players
    if( FAILED( hr = g_pDP->Send( g_LocalPlayerDPID, DPID_ALLPLAYERS, 
                                  DPSEND_GUARANTEED, &msgGenr, sizeof(SCORE_AGAINSTDATA) ) ) ) 
				      return hr;
    return S_OK;
}

//-----------------------------------------------------------------------------
// Name: SeedToAllPlayers()
// Desc: Send a app-defined "Seed" DirectPlay message to all connected players
//-----------------------------------------------------------------------------
HRESULT SeedToAllPlayers(CPlayer &Player1)
{
    HRESULT hr;

//OutputDebugString ("WinMain_SeedToAllPlayers \n");

	GAMEMSG_SEEDDATA msgGenr;
	// set the msgGenr data
	Player1.Game_Seed = timeGetTime();

	msgGenr.dwType = GAMEMSG_GAME_SEED;
	msgGenr.d_Seed = Player1.Game_Seed;


	// Send it to all of the players
    if( FAILED( hr = g_pDP->Send( g_LocalPlayerDPID, DPID_ALLPLAYERS, 
                                  DPSEND_GUARANTEED, &msgGenr, sizeof(GAMEMSG_SEEDDATA) ) ) ) 
				      return hr;

	Player1.Seed_Rand();

	// do sync in here to set ball original direction. 
	//(non - host,  host in the post of this message)
//	DefaultBallData();
	// daqsync
    return S_OK;
}
//-----------------------------------------------------------------------------
// Name: DisplayPlayerStart()
//-----------------------------------------------------------------------------
HRESULT DisplayPlayerStart( HWND hDlg, DPID idFrom ,CPlayer &Player1)
{
OutputDebugString ("WinMain_DisplayPlayerStart \n");

for ( int x = 0 ; x < MAX_PLAYER_SLOTS ; x++)
	{
				Player1.b_player_ready[x] = true;
	}
return S_OK;
}


//-----------------------------------------------------------------------------
// Name: DisplayPlayerPaddle()
// Desc: A player has Paddle to us, so find out the player's name and 
//       tell the local player about it.
//-----------------------------------------------------------------------------
HRESULT DisplayPlayerPaddle( HWND hDlg, DPID idFrom ,double numb_x, double numb_y, DWORD d_Slot )
{
//	BYTE*   pData = NULL;
//    HRESULT hr;
//    DWORD   dwBufferSize;

/*******************  gets a players name
    // Get the size of the buffer needed
    hr = g_pDP->GetPlayerName( idFrom, NULL, &dwBufferSize );
    if( hr != DPERR_BUFFERTOOSMALL && FAILED(hr) )
        return hr;

    // Allocate the buffer now that we know the size
    pData = new BYTE[ dwBufferSize ];
    if( NULL == pData )
        return E_OUTOFMEMORY;

    // Get the data from DirectPlay
    if( FAILED( hr = g_pDP->GetPlayerName( idFrom, pData, &dwBufferSize ) ) )
        return hr;

    // Typecast the buffer into a DPNAME structure
    DPNAME* pdpname = (DPNAME*) pData;
*********************/
//Player1.i_x_1_pos[d_Slot] = numb_x;
//Player1.i_y_1_pos[d_Slot] = numb_y;
//g_wall_list
g_wall_list->set_paddle_data(d_Slot, numb_x, numb_y);	//dq002

//TRACE( TEXT(" RCV DisplayPlayerPaddle x= %i, y= %i slot= %i\n"), numb_x, numb_y, d_Slot );

	return S_OK;
}

//-----------------------------------------------------------------------------
// Name: ReadRegKey()
// Desc: Read a registry key 
//-----------------------------------------------------------------------------
HRESULT ReadRegKey( HKEY hKey, TCHAR* strName, TCHAR* strValue, 
                    DWORD dwLength, TCHAR* strDefault )
{
	DWORD dwType;
	LONG bResult;
OutputDebugString ("WinMain_ReadRegKey \n");
	bResult = RegQueryValueEx( hKey, strName, 0, &dwType, 
							   (LPBYTE) strValue, &dwLength );
	if ( bResult != ERROR_SUCCESS )
		strcpy( strValue, strDefault );

    return S_OK;
}

//-----------------------------------------------------------------------------
// Name: WriteRegKey()
// Desc: Writes a registry key 
//-----------------------------------------------------------------------------
HRESULT WriteRegKey( HKEY hKey, TCHAR* strName, TCHAR* strValue )
{
	LONG bResult;
OutputDebugString ("WinMain_WriteRegKey \n");
	bResult = RegSetValueEx( hKey, strName, 0, REG_SZ, 
							 (LPBYTE) strValue, strlen(strValue) + 1 );
	if ( bResult != ERROR_SUCCESS )
		return E_FAIL;

    return S_OK;
}

//-----------------------------------------------------------------------------
// Name: InitApp()
// Desc: Do work required for every instance of the application:
//          Create the window, initialize data
//-----------------------------------------------------------------------------
static HRESULT InitApp(HINSTANCE hInstance, int nCmdShow)
{
    WNDCLASS                    wc;
    // Set up and register window class
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WindowProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MAIN));
    wc.hCursor = LoadCursor(NULL, NULL);
    wc.hbrBackground = (HBRUSH )GetStockObject(BLACK_BRUSH);
    wc.lpszMenuName = NAME;
    wc.lpszClassName = NAME;
    RegisterClass(&wc);

return DD_OK;
}




