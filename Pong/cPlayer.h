/////////////////////////////////
// cPlayer.h
/////////////////////////////////
#ifndef __CPLAYER_HEADER__
#define __CPLAYER_HEADER__

#define MAX_PLAYER_SLOTS     8

#include <stdio.h>
#include <stdlib.h>

#define IM_WINNER			187
#define WINNER_FOUND		188


#include "Enumerations.h"

extern int		g_iScoreOut;		// score to lose
extern HWND    g_hDlg;

/////////////////////////////////
/////////////////////////////////
/////////////////////////////////

class CPlayer
{
public:
	int i_temp;
	
	int i_my_slot;	//0xFFFFFFFF = empty

	int i_PlayerType[MAX_PLAYER_SLOTS];	

	int SlotDPID[MAX_PLAYER_SLOTS];

	bool b_Player_Quit;

	int i_score[MAX_PLAYER_SLOTS+1];

	bool b_Loser[MAX_PLAYER_SLOTS+1];
	bool b_LoserRemove[MAX_PLAYER_SLOTS+1];
	bool b_Loser_Disp[MAX_PLAYER_SLOTS+1];
	bool b_Winner_Disp[MAX_PLAYER_SLOTS+1];
	bool b_Winner_Found;

	double	i_x_pos[MAX_PLAYER_SLOTS],
			i_y_pos[MAX_PLAYER_SLOTS];

	bool b_player_ready[MAX_PLAYER_SLOTS];

	bool b_all_players_ready;

	int i_numb_active_players;

	int i_mps;
	int i_want_mps;
	int i_have_mps;
	int i_adj_mps;

	double time_elapsed;
	double time_last;

	bool b_first_time;
	bool b_focus_on_ball;

	double  time_wait;
	double  time_exec;
	double  time_sleep;
	double  time_wait_display;
	double  time_exec_display;
	double  time_actual;
	double	time_game_start;
	double	time_game_play;

	LONGLONG	time_game_start_2;	
    LONGLONG	time_game_last_2;
	LONGLONG	time_game_elap_2;
	LONGLONG	time_game_elap_22;
	LONGLONG	time_game_acum_2;
	LONGLONG	time_game_freq_2;
	LONGLONG	time_game_count_2;
	LONGLONG	time_game_count_22;

	DWORD		dwHigh;
	DWORD		dwLow;

	bool	time_tested;
	bool	b_Game_Pause;

	double	Game_Seed;
	int		Game_Rand_Last;

	int		Rand_X;
	int		Rand_Y;

	bool	b_Help_Disp;

	double	scored_on;

	int		i_circle_deg;

	int		i_mouse;
	int		i_key;
	bool	b_sound;

//===============================================================
// construct player
//===============================================================
	CPlayer(int plr)
	{
	char      stg[256];
	i_temp = plr;

	sprintf(stg, "CPlayer Construct %i \n" + '\0',i_temp);
	OutputDebugString (stg);

	i_my_slot = -1;

	i_score	[plr]	=	0;

	i_x_pos	[plr]=	0;
	i_y_pos	[plr]=	0;

	b_player_ready[plr] = false;

	b_all_players_ready = false;

	time_tested = false;

	scored_on = 9;
	
	time_game_start_2 = 0;	
    time_game_last_2 = 0;
	//time_game_elap_2 = 0;
	time_game_acum_2 = 0;

	for ( int bL = 0 ; bL < MAX_PLAYER_SLOTS ; bL++)
		{
		b_Loser[bL] = false;
		b_LoserRemove[bL] = false;
		b_Loser_Disp[bL] =false;
		b_Winner_Disp[bL] = false;
		i_score[bL] = 0;
		}
	b_Winner_Found = false;
	time_elapsed = 0; 
	time_actual = 0;		//dq003
	time_game_play = 0;		//dq003


	time_game_start_2 = 0;	
    time_game_last_2 = 0;
	time_game_elap_2 = 0;
	time_game_elap_22 = 0;
	time_game_acum_2 = 0;
	time_game_freq_2 = 0;
	time_game_count_2 = 0;
	time_game_count_22 = 0;

	//b_mouse = true;
	//b_key = false;
	//b_sound = false;

	 }

//===============================================================
// destruct player
//===============================================================
	~CPlayer()
	{
	char      stg[256];

	sprintf(stg, "CPlayer ~Construct %i\n",i_temp);
	OutputDebugString (stg);
	}


public:
 //====================================
 void accum_elap ()	// this is based upon ddinput
 {

	/////////////////////////
	// don't allow moves or accum
	if (b_Game_Pause)
	{
		time_elapsed = 0;
	}// end !Paused

//	char      stg[256];
//	sprintf(stg, "ACCUM_ELAP %fp play %fp \n" ,time_elapsed,time_game_play);
//	OutputDebugString (stg);

	/////////////////////////
	// don't allow something to big
	if ( time_elapsed > 0 && time_elapsed < 2)
		time_game_play += time_elapsed;

 }
 //====================================
 void set_x_pos (int x, int plr)	// this is based upon ddinput
 {
	OutputDebugString ("CPlayer set_x_pos\n");
	 i_x_pos[plr] = x;
 }
//====================================
 void set_score (int x,int plr)	// this is based upon ddinput
{
char      stg[256];

//	OutputDebugString ("CPlayer set_score\n");
	i_score[plr] += x;
	scored_on = plr;

// don't allow score to be negative
	if (i_score[plr] >= g_iScoreOut)
		{
		i_score[plr] = g_iScoreOut;
		}

// remove player if score is too high
	if (i_score[plr] >= g_iScoreOut)
		{
			b_Loser[plr] = true;	// used for defending walls

// if the type = Closed then the score is not displayed
//			i_PlayerType[plr] = Closed;	
//			i_PlayerType[plr+4] = Closed;

			b_LoserRemove[plr]		=	true;	// hide paddle
			b_LoserRemove[plr+4]	=	true;	// hide paddle
			//prior two lines are for ----->a_list.remove_Owning_Player(lpQuitData->I_QUIT_PLAYER);
			b_Loser_Disp[plr]		=	true;	// display Loser
			OutputDebugString ("Loser\n");
		}
// TEST FOR # of losers, do we have a winner yet?

		int i_losers = 0;


		for ( int bL = 0 ; bL < MAX_PLAYER_SLOTS/2; bL++)
		{
			int ttt = 0;
			if (b_Loser_Disp[bL] == true) 
				ttt = 1;

			sprintf(stg, "Player %i loser %i '1=true' \n" + '\0',bL,ttt);
			OutputDebugString (stg);

			//sprintf(stg, "Winner Test Team %i \n", bL);
			//OutputDebugString (stg);
//
		if (i_PlayerType[bL]   == Computer || i_PlayerType[bL]   == Human ||
			i_PlayerType[bL+4] == Computer || i_PlayerType[bL+4] == Human)
					if (b_Loser_Disp[bL])
						{
						i_losers++;
						sprintf(stg, "    In game %i loser %i \n" + '\0', bL,i_losers);
						OutputDebugString (stg);
						}
					else
						{ //in game but not a loser
						sprintf(stg, "In !!loser %i loser %i \n" + '\0', bL,i_losers);
						OutputDebugString (stg);
						}
		else
						{
						i_losers++;
						sprintf(stg, "Not in game %i losers %i \n" + '\0',bL,i_losers);
						OutputDebugString (stg);
						}
			}

		// find the winner
		sprintf(stg, "Find Winner # of losers = %i \n" + '\0', i_losers);
		OutputDebugString (stg);


		if (i_losers >= 3)
			for ( int bW = 0 ; bW <= MAX_PLAYER_SLOTS/2 ; bW++)
			{
			int ttt = 0;
			if (b_Loser_Disp[bW]) 
				ttt = 1;
			sprintf(stg, "Find Winner Test Team %i lose t/f %i type[+0] %i type[+4] %i \n", bW, ttt,i_PlayerType[bW],i_PlayerType[bW+4]);
			OutputDebugString (stg);

			if (i_PlayerType[bW]   == Computer || i_PlayerType[bW]   == Human ||
				i_PlayerType[bW+4] == Computer || i_PlayerType[bW+4] == Human)
					{
					if (!b_Loser_Disp[bW])
						{
						b_Winner_Disp[bW] = true;
						sprintf(stg, "found winner In game %i loser %i %i \n" + '\0', bW,b_Loser_Disp[bW],b_Loser_Disp[bW+4]);
						OutputDebugString (stg);
						b_Winner_Found = true;
						b_focus_on_ball = false;
						PostMessage(g_hDlg, WM_COMMAND, WINNER_FOUND, 0);


						// POST THIS
						if (i_my_slot == bW || i_my_slot == (bW+4))
							PostMessage(g_hDlg, WM_COMMAND, IM_WINNER, 0);
							//SoundPlayEffect (MENCHEER_WIN);
						}
					else
						{
						sprintf(stg, "In game loser %i loser %i%i  \n" + '\0', bL,b_Loser_Disp[bW],b_Loser_Disp[bW+4]);
						OutputDebugString (stg);
						}							
					}
			else
					{
					// do nothing
					sprintf(stg, "Player Not in game %i losers %i %i \n" + '\0',b_Loser_Disp[bW],b_Loser_Disp[bW+4]);
					OutputDebugString (stg);
					}
			}
 }
 //====================================
 void check_all_players_ready ()	// this is based upon ddinput
 {
	OutputDebugString ("CPlayer Check_all_players_ready\n");

	for ( int x = 0 ; x < MAX_PLAYER_SLOTS ; x++)
		if ( i_PlayerType[x] != Open)
			if (b_player_ready[x] == false)
				return;

	b_all_players_ready = true;
 }
//==============================================================
// seed rand
//==============================================================
void Seed_Rand()

{
srand( (unsigned)Game_Seed );

// next line comes out when all computers stay in sync
//srand( 1681654358 );

//TRACE ( TEXT ("Seed Rand ---------------------- \n"));

Set_Game_Rand();

}

//==============================================================
// rand
//==============================================================

void Set_Game_Rand ()
 {
	Rand_X =rand()%15;
	Rand_Y =rand()%15;
	/*
	char      stg[256];
	sprintf(stg, "set rand x %i y %i\n" + '\0', Rand_X , Rand_Y);
	OutputDebugString (stg);
*/
	Game_Rand_Last = Rand_X;

//	TRACE ( TEXT ("Rand_X = %i \n"),Rand_X);
//	TRACE ( TEXT ("Rand_Y = %i \n"),Rand_Y);
 }
//==============================================================
// Return_Rand_X
//==============================================================

int Return_Rand_X ()
 {
	 /*
	 char      stg[256];
	sprintf(stg, "return rand x %i \n" + '\0', Rand_X);
	OutputDebugString (stg);
	*/
//	TRACE ( TEXT (" Return Rand_X = %i \n"),Rand_X);
	return Rand_X;
 }
//==============================================================
// Return_Rand_Y
//==============================================================

int Return_Rand_Y ()
 {
//	TRACE ( TEXT (" Return Rand_Y = %i \n"),Rand_Y)
	 /*
	char      stg[256];
	sprintf(stg, "return rand y %i \n" + '\0', Rand_Y);
	OutputDebugString (stg);
	*/
	return Rand_Y;
 }
//==============================================================
};
#endif
	// end class Play
	// end class Play
	// end class Play
	// end class Play

