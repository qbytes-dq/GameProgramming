//-----------------------------------------------------------------------------
// Name: DoGreetingGame()
// Desc: Creates the main game window, and process Windows and DirectPlay 
//       messages
//-----------------------------------------------------------------------------
int DoGreetingGame( HINSTANCE hInst ,CPlayer &Player1)							//dq001
{
BOOL    bDone = FALSE;
int     nExitCode;
HRESULT hr; 
DWORD   dwResult;
MSG     msg;


char      stg[256];																//dq001
sprintf(stg, "DoGameLoop --- Player class = %i \n" + '\0', Player1.i_temp);	//dq001
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

	Player1.i_my_slot = g_dwLocalSlotNumber;

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

	//////////////////////////////////////////////////////////// 
	// init game
	//////////////////////////////////////////////////////////// 
	if( g_pDP == NULL )
		return E_FAIL;  // Sanity check

// figure out what timer to use prior to InitApp
// InitApp will set the default start point
// as part of WindowProc WM::timer when all players are ready.


EndDialog( g_hDlg_connect1, EXITCODE_QUIT );//dq005


//  if (InitApp(hInst, nCmdShow) != DD_OK)
	if (InitApp(hInst, 1) != DD_OK)
		return FALSE;

// sizes are 1280, 1024, 800, NOT-640
//	if (initDDraw(hInst,nCmdShow) != DD_OK)
	if (initDDraw(hInst,1,Player1) != DD_OK)
		return DD_FALSE;
		//return FALSE;


	////////////////////////////////////////////
	// LOAD MAP
	////////////////////////////////////////////
	int i_map;
	i_map = g_iNum_Balls % 4;

   switch ( i_map )
      {
      case 0:
		{
		#include "qmap0.h"
		}
        break;
      case 1:
		{
		#include "qmap1.h"
		}
        break;
      case 2:
		{
		#include "qmap2.h"
		}
        break;
      case 3:
		{
		#include "qmap3.h"
		}
        break;
	  }


	Player1.b_player_ready[Player1.i_my_slot] = true;

	///////////////////////////////////////////////////////////
	DWORD   dwHereNext;

	Player1.b_focus_on_ball = false;

	Player1.b_Game_Pause = false;

	Player1.b_Help_Disp = false; 

	Player1.b_Player_Quit = true;  // plug the defending wall off the bat.

	NumberOfPlayers( g_hDlg ,Player1);

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


	//////////////////////////////////////////////////////////// 
	// main game loop
	//////////////////////////////////////////////////////////// 

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
				//OutputDebugString ("sleep \n");
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
				if (Player1.b_all_players_ready)
				{
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
					// send my paddle data every other time
					static int xyz = 0;
					if (xyz++ > 0)  
						{
							if( FAILED( hr = PaddleToAllPlayers(Player1,*a_listwall) ) )
								PostQuitMessage( EXITCODE_ERROR );
							xyz = 0;
						}
				}// end if (Player1.b_all_players_ready)
				else
				{
				/////////////////////////
				// don't let other players know i'm ready until my frame rate is correct
				OutputDebugString ("FPS wait \n");
				if ( Player1.i_want_mps = Player1.i_have_mps)
					{// waiting for all players ready, continue doing this until they all check in

					
					// this step here to notify other players i'm ready, FPS OK
					if( FAILED( hr = ReadyToAllPlayers(Player1) ) )
							PostQuitMessage( EXITCODE_ERROR );

					if (Player1.time_game_freq_2 == 0)
						{// use Time Ticker
						Player1.time_game_count_22 = 0;
						}
					else
						{// use Performance Counter
						QueryPerformanceCounter((LARGE_INTEGER *)&Player2->time_game_start_2);
						QueryPerformanceCounter((LARGE_INTEGER *)&Player2->time_game_last_2);
						}
					}// end if
				}// end if else (Player1.b_all_players_ready)

			/////////////////////////
			// Display/Update screen only when active or if in a window
			if ( g_bActive || !g_Full_Screen )  
				UpdateFrame(*a_listwall,Player1);	// pass address of a_list to loop

			}// end if dwHereNext


			//////////////////////////
			// deal with system and game messages
			dwResult = MsgWaitForMultipleObjects( 1, &g_hDPMessageEvent, 
													  FALSE, 0, QS_ALLEVENTS );
			switch( dwResult )
				{
					case WAIT_OBJECT_0 + 0:
						// g_hDPMessageEvent is signaled, so there are
						// DirectPlay messages available
						if( FAILED( hr = ProcessDirectPlayMessages( g_hDlg , Player1, *a_listwall ) ) ) 
							return EXITCODE_ERROR;
						break;

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

		}// end while -> game still on

//////////////////
// all done clean up and get out //dq004
//////////////////

ReleaseAllObjects();			//dq004
DestroyWindow(g_hDlg);			//dq004

delete a_listwall;				//dq002

return nExitCode;
}// end function