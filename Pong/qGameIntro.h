//DQ006 all below
//-----------------------------------------------------------------------------
// Name: DoGameIntro()
// Desc: Creates the main game window, and process Windows and DirectPlay 
//       messages
//-----------------------------------------------------------------------------
int DoGameIntro( HINSTANCE hInst ,CPlayer &Player1)							//dq001
{
BOOL    bDone = FALSE;
int     nExitCode;
//HRESULT hr; 
DWORD   dwResult;
MSG     msg;

b_intro = true;
g_bHostPlayer = true;
Player1.i_numb_active_players = 0;
g_Full_Screen = true;

g_iPlayerType[0] = Open;
g_iPlayerType[1] = Open;
g_iPlayerType[2] = Open; 
g_iPlayerType[3] = Open;
g_iPlayerType[4] = Computer;
g_iPlayerType[5] = Computer;
g_iPlayerType[6] = Computer;
g_iPlayerType[7] = Computer;


char      stg[256];																//dq001
sprintf(stg, "DoGreetingGame --- Player class = %i \n" + '\0', Player1.i_temp);	//dq001
OutputDebugString (stg);														//dq001

wall_list* a_listwall;			//dq002
a_listwall = new wall_list();	//dq002

g_wall_list = a_listwall;		//dq002

//////////////////////////////////////////////////////////// 
// loop thru all the players for init
//////////////////////////////////////////////////////////// 
#define MAX_PLAYER_SLOTS     8
extern DWORD g_dwSlotDPID[MAX_PLAYER_SLOTS]; 
extern DWORD g_dwLocalSlotNumber;

Player1.i_my_slot = 9;


	TRACE( TEXT("Player slot = %i \n"), Player1.i_my_slot );

	for ( int x = 0 ; x < MAX_PLAYER_SLOTS ; x++)
		{
		Player1.i_PlayerType[x] = g_iPlayerType[x];	// player type
		Player1.SlotDPID[x]		= g_dwSlotDPID[x];	// actual DPID


		if ( g_iPlayerType[x] == Open)
			{// host player
				Player1.b_player_ready[x] = true;
			}
			else
			if ( g_iPlayerType[x] == Computer)
			{ // computer player
				Player1.b_player_ready[x] = true;
			}
			else
			if ( g_iPlayerType[x] == Closed)
			{ // closed player
				Player1.b_player_ready[x] = true;
			}
			else
			{// other network player
				Player1.b_player_ready[x] = false;
			}

		TRACE( TEXT("Players type = %i =======================\n"), Player1.i_PlayerType[x]);
		TRACE( TEXT("Players dpid = %i =======================\n"), Player1.SlotDPID[x]);
		}// end for next loop

	//////////////////////////////////////////////////////////// 
	// end loop thru all the players
	//////////////////////////////////////////////////////////// 




//  if (InitApp(hInst, nCmdShow) != DD_OK)
	if (InitApp(hInst, 1) != DD_OK)
		return FALSE;



// sizes are 1280, 1024, 800, NOT-640
	if (initDDraw(hInst,1,Player1) != DD_OK)
	{
		return DD_FALSE;		
	}
//return EXITCODE_ERROR;
	////////////////////////////////////////////
	// LOAD MAP
	////////////////////////////////////////////

	#include "qmap1.h"

//	for (int x99=0 ; x99 < 360 ; x99++)
//		a_listwall->add_boom( 592/2 , 592/2, 0 ,x99 ,g_pDDSwall);

	Player1.b_player_ready[Player1.i_my_slot] = true;

	///////////////////////////////////////////////////////////
	DWORD   dwHereNext;

	Player1.b_focus_on_ball = false;

	Player1.b_Game_Pause = false;

	Player1.b_Help_Disp = false; 

	Player1.b_Player_Quit = true;  // plug the defending wall off the bat.

	//NumberOfPlayers( g_hDlg ,Player1);

	Player1.i_want_mps	= 35;
	Player1.i_adj_mps	= 0;
	Player1.i_mps		= Player1.i_want_mps;
	Player1.i_have_mps	= Player1.i_want_mps;

	g_iDifficult = g_iDifficult +6;		// adjust game speed

	//DQ003 timer freq
	//Note that the value returned by the timeGetTime function is a DWORD value. 
	//The return value wraps around to 0 every 2^32 milliseconds, which is about 49.71 days.
	DWORD dwtimeGetTime;
	dwHereNext = timeGetTime();

	LONGLONG time_freq;
	LONGLONG time_next;
	LONGLONG time_this;

	double temp_freq;
	double temp_elap;
	double time_start;

	QueryPerformanceFrequency((LARGE_INTEGER *)&Player1.time_game_freq_2);

	//DQ003 timing testing, next two lines come out
	if (g_bHostPlayer == true)
		Player1.time_game_freq_2 = 0;

	if (Player1.time_game_freq_2 == 0)
		{// use Time Ticker
		//Player1.time_game_freq_2 = 0;
		timeBeginPeriod(1);			//dq003		time counter set to 1 ms or 0.001 seconds
		time_start = timeGetTime();	//dq003
		Player1.time_actual  = time_start;
		Player1.time_last = time_start;
		Player1.time_tested  = false;
		}
	else
		{// use Performance Counter
		time_freq = Player1.time_game_freq_2;	//dq003
		time_freq /= Player1.i_want_mps;
		QueryPerformanceCounter((LARGE_INTEGER *)&time_this);	//dq003
		QueryPerformanceCounter((LARGE_INTEGER *)&time_next);	//dq003	
		Player1.time_tested  = false;
		}

//		SoundPlayEffect (SOUND_ENERGIZE);

	//////////////////////////////////////////////////////////// 
	// main game loop
	//////////////////////////////////////////////////////////// 

SoundPlayEffect (SOUND_QBYTESPONG);
g_iScoreOut = 5;

	while( !bDone ) 
	{ 
		/////////////////////////
		// setup for exec vs wait timer using Time Ticker
		if (!Player1.time_tested)
			{
				dwtimeGetTime = timeGetTime();
				Player1.time_exec   +=  dwtimeGetTime-Player1.time_actual;
				Player1.time_actual  = dwtimeGetTime;
				Player1.time_tested  = true;
				draw_cnt_start = 0;

                int i_sleep; // 15 and 20 work good hard coded
				i_sleep = (int)((Player1.time_wait_display/1.25) / (double)Player1.i_want_mps);
				Player1.time_sleep = (double)(i_sleep * Player1.i_want_mps)/10;
				Sleep(i_sleep);
				//OutputDebugString ("sleep over\n");
			}// end if time.tested
		
		if (Player1.time_game_freq_2 == 0)
				{// use Time Ticker
				dwtimeGetTime = timeGetTime();
				}
			else
				{// use Performance Counter
				QueryPerformanceCounter((LARGE_INTEGER *)&time_this);
				}

		if ( Player1.time_game_freq_2 == 0 && dwtimeGetTime > dwHereNext || 
				Player1.time_game_freq_2 != 0 && time_this > time_next  )
			{
				//OutputDebugString ("sleep~not \n");
				/////////////////////////
				// exec time vs wait time
				dwtimeGetTime = timeGetTime();
				Player1.time_wait   += dwtimeGetTime - Player1.time_actual;
				Player1.time_actual  = dwtimeGetTime;
				Player1.time_tested  = false;	


					//draw_cnt_start = 0;
				
					if (Player1.time_game_freq_2 == 0)

						{// use Time Ticker
						Player1.time_game_count_22  += (LONGLONG)(dwtimeGetTime - Player1.time_last);
						Player1.time_game_count_2 = Player1.time_game_count_22/1000;

						Player1.time_elapsed = (double)((dwtimeGetTime - Player1.time_last) * (double)Player1.i_want_mps/2000);
						Player1.time_last = dwtimeGetTime;
						//dwHereNext = dwtimeGetTime + 1000 /(Player1.i_want_mps+Player1.i_adj_mps);
						dwHereNext = dwtimeGetTime + ((1000+Player1.i_adj_mps) / Player1.i_want_mps);
						}
					else
						{// use Performance Counter
						QueryPerformanceCounter((LARGE_INTEGER *)&Player1.time_game_last_2);

						Player1.time_game_elap_2 = (Player1.time_game_last_2 - Player1.time_game_start_2) - Player1.time_game_acum_2;

						temp_freq = (double)Player1.time_game_elap_2;
						temp_elap = (double) time_freq;
						Player1.time_elapsed = (temp_freq/2) / temp_elap ;

						Player1.time_game_acum_2 = (Player1.time_game_last_2 - Player1.time_game_start_2);

						Player1.time_game_count_2 = Player1.time_game_acum_2 / (Player1.time_game_freq_2);
						Player1.time_game_count_22 = Player1.time_game_acum_2 / (Player1.time_game_freq_2/60);
						time_next += time_freq;
						}

				/////////////////////////
				// do move, paint screen, plays sound if everyone is ready
				//if (Player1.b_all_players_ready)
				//	{
					/////////////////////////
					//
					Player1.accum_elap();

					//OutputDebugString ("a_list.do_move \n");
					a_listwall->do_move(Player1);

					/////////////////////////
					//any losers out there
					//if so remove their paddle
					for ( int bL = 0 ; bL < MAX_PLAYER_SLOTS ; bL++)
						if (Player1.b_LoserRemove[bL] == true)
							{
							a_listwall->remove_Owning_Player(bL);
							Player1.b_LoserRemove[bL] = false;
							}

			/////////////////////////
			// Display/Update screen only when active or if in a window
			if ( g_bActive || !g_Full_Screen )  
				UpdateFrame(*a_listwall,Player1);	// pass address of a_list to loop

			//if (Player1.b_Winner_Found == true)
			//	{
				static int i_exit_soon = 0;
				if (i_exit_soon++ > Player1.i_want_mps * 50)	//hang out for 5 seconds
					bDone = true;
			//	}
			}// end if dwHereNext


			//////////////////////////
			// deal with system and game messages
			dwResult = MsgWaitForMultipleObjects( 1, &g_hDPMessageEvent, 
													  FALSE, 0, QS_ALLEVENTS );
			switch( dwResult )
				{
					/*
					case WAIT_OBJECT_0 + 0:
						// g_hDPMessageEvent is signaled, so there are
						// DirectPlay messages available
						if( FAILED( hr = ProcessDirectPlayMessages( g_hDlg , Player1, *a_listwall ) ) ) 
							return EXITCODE_ERROR;
						break;
					*/
					case WAIT_OBJECT_0 + 1:
						// Windows messages are available
						while( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) ) 
						{ 
							if( !IsDialogMessage( g_hDlg, &msg ) )  
							{
								TranslateMessage( &msg ); 
								DispatchMessage( &msg ); 
							}// end if

							if( msg.message == WM_QUIT )
							{
								// See the above EXITCODE #defines for 
								// what nExitCode could be 
								nExitCode = msg.wParam;

								EndDialog( g_hDlg, nExitCode );
								bDone = TRUE;
							}// end if
						}// end while
						break;
				}// end switch


		}// end while -> intro still on

//////////////////
// all done clean up and get out //dq004
//////////////////
/*
b_intro = false;
g_bHostPlayer = false;
g_iNum_Balls = 1;
g_iDifficult = 1;
g_iScoreOut = 1;
*/
ReleaseAllObjects();			//dq004
DestroyWindow(g_hDlg);			//dq004

delete a_listwall;				//dq002

return nExitCode;
}// end function