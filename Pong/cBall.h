//cBall.h


#include <stdio.h>
#include <stdlib.h>

#include "Enumerations.h"

char      stg[256];
#define SYNC_BALL		177
#define SCORE_AGAINST	199

//#define TestOut
//-----------------------------------------------------------------------------
// DAQ Temp Global variables
//-----------------------------------------------------------------------------


extern int		draw_cnt_start;
extern int		draw_item_num;
extern double	draw_x;
extern double	draw_x_dir;
extern double	draw_y;
extern double	draw_y_dir;
extern int		draw_obj_ID;
extern int		draw_wait_cnt;

extern int		g_iDifficult;		// how fast the balls are
extern int		g_iScoreOut;		// score to lose

static cnt1;

double d_xpos,d_ypos;
/////////////////////////////////
class ball_list_element : wall_list_element
{

public:
//===============================================================
 ball_list_element(const int i_xpos, const int i_ypos, LPDIRECTDRAWSURFACE7 &p_dds,int cnt,double i_deg,int i_radius) :
			 wall_list_element (i_xpos, i_ypos, p_dds)
{
	i_wait		= 0;	// override default wait 

	i_xpos_wall = i_xpos;
	i_ypos_wall = i_ypos;

	while (i_x_dir == 0 && i_y_dir == 0)
		{
		i_x_dir = ((rand()%50)-25)/10; 
		i_y_dir = ((rand()%50)-25)/10; 
		}
	Last_Hit = 0;

	i_object_ID = cnt;

	 d_xpos = (i_radius * sin ((i_deg*0.017453292) + 1.570796) ) + i_xpos;
	 d_ypos = (i_radius * sin ((i_deg*0.017453292) + 3.141592) ) + i_ypos;

	 i_xpos_wall = int (d_xpos);
	 i_ypos_wall = int (d_ypos);

	char      stg[256];
	sprintf(stg, "ball ID = %i x = %fp y = %fp  deg = %fp \n", i_object_ID, i_xpos_wall,i_ypos_wall,i_deg);
	OutputDebugString (stg);
}
 //==============================================================
public:
int Return_Last_Hit()
{
	return Last_Hit;
} //==============================================================
public:
int Return_X()
{
	return (int)i_xpos_wall;
}
  //==============================================================
public:
int Return_Y()
{
	return (int)i_ypos_wall;
}
 //==============================================================
public:
int Return_XV()
{
	return (int)i_x_dir;
}
  //==============================================================
public:
int Return_YV()
{
	return (int)i_y_dir;
}
 //==============================================================
 //  move the list
 //==============================================================
private:
 void move(wall_list_element *first_ptr, wall_list_element *cur_element, CPlayer &Player1) 
 {
	// if game is over or game is paused, don't do anything
	if (!Player1.b_Winner_Found && !Player1.b_Game_Pause)
	{
		//TRACE( TEXT("1) i_x_dir = %i i_y_dir %i  elapsed %d\n"),i_xpos_wall,i_ypos_wall,2.2 );
		cur_element->i_xpos_wall += cur_element->i_x_dir * Player1.time_elapsed;
		cur_element->i_ypos_wall += cur_element->i_y_dir * Player1.time_elapsed;
		//TRACE( TEXT("2) i_x_dir = %i i_y_dir %i \n"),i_xpos_wall,i_ypos_wall );

		// just in case the ball is off the playing field
		// sanity check, move to middle and don't score
		if (i_xpos_wall < 0 || i_xpos_wall > 608 ||
			i_ypos_wall < 0 || i_ypos_wall > 608)
			{
				//daq to test here for allow score
				i_xpos_wall = (592/2)-8;
				i_ypos_wall = i_xpos_wall;
				tell_others_data(Player1,99);
			}
//OutputDebugString ("pre-check");
		// sanity check to see if balls are on the same page
		++Last_Hit;
		 if( g_bHostPlayer )
			{
			if (Last_Hit == 3)
				{
				PostMessage(g_hDlg, WM_COMMAND, SYNC_BALL, i_object_ID);
				//tell_others_data(Player1,99);
				//char      stg[256];
				//sprintf(stg, "Telling others last hit %i hit %i \n" + '\0', i_object_ID,Last_Hit);
				//OutputDebugString (stg);
				}
			}
	}

// DAQ Temp Global variables
//if (++draw_cnt_start == draw_item_num)	// daq 1/08/02
if (cur_element->i_object_ID == draw_item_num)
	{
	//draw_item_num;
	draw_x = cur_element->i_xpos_wall;
	draw_x_dir = cur_element->i_x_dir;
	draw_y = cur_element->i_ypos_wall;
	draw_y_dir = cur_element->i_y_dir;
	draw_obj_ID;
	draw_wait_cnt;
	}
 }	// end move


 //==============================================================
 //  Adjust the score
 //==============================================================
public:
 void adj_score(int score_on,double x, double y,CPlayer &Player1)
 {
	SoundPlayEffect( SOUND_STUNNED );
	Player1.set_score(1,score_on);
	//ChangeBallPos to center of screen
	i_xpos_wall = (592/2)-8;
	i_ypos_wall = i_xpos_wall;

	char  buffer[100], 
	j = sprintf( buffer,"score0 %i score1 %i on %i g_out %i lose 0 %b lose 1 %b \n",Player1.i_score[0],Player1.i_score[1], score_on, g_iScoreOut ,Player1.b_Loser[1],Player1.b_Loser[1]);
	buffer[80] = '\0';
	OutputDebugString (buffer);

	//TRACE( TEXT("score at x = %i \t y = %i \n"), int(x),int(y) );
	//Player1.b_Game_Pause = true;

//TRACE( TEXT("score at x = %i \t y = %i \t slot = %i \t type = %i \t host = %i \n"), int(x), int(y),Player1.i_my_slot ,Player1.i_PlayerType[Player1.i_my_slot],g_bHostPlayer);
 }
//==============================================================
//  speedup the ball on a bounce
//==============================================================
public:
 void speed_up(CPlayer &Player1)

// void speed_up(double x, double y,CPlayer &Player1)
 {
/*
sprintf(stg, "Max Speed test xd %fp yd %fp \n" + '\0', i_x_dir , i_y_dir);
OutputDebugString (stg);
*/
int RX;
int RY;
double CRX;
double CRY;
RX = Player1.Rand_X;
RY = Player1.Rand_Y;
CRX = double (RX*10)/100;
//CRX = double (RX/10);
CRY = double (Player1.Rand_Y*10)/100;
//CRY = double (Player1.Rand_Y/10);
	if (i_x_dir == g_iDifficult)
		{
		i_x_dir = i_x_dir - (CRX * 4);
		//OutputDebugString ("Adj. CRX \n");
		}
	else
		{
		if (i_x_dir > 0)
			i_x_dir = i_x_dir + CRX;
		else
			i_x_dir = i_x_dir - CRX;

		if (i_x_dir > g_iDifficult)
			i_x_dir = g_iDifficult;
		if (i_x_dir < -g_iDifficult)
			i_x_dir = -g_iDifficult;
		}
	//=====
	if (i_y_dir == g_iDifficult)
		{
		i_y_dir = i_y_dir - (CRY * 4);
		//OutputDebugString ("Adj. CRY \n");
		}
	else
		{
		if (i_y_dir > 0)
			i_y_dir = i_y_dir + CRY;
		else
			i_y_dir = i_y_dir - CRY;


		if (i_y_dir > g_iDifficult)
			i_y_dir = g_iDifficult;
		if (i_y_dir < -g_iDifficult)
			i_y_dir = -g_iDifficult;
		}
	//=====
	//TRACE( TEXT("HIT SOMETHING vx = %i vy = %i \n"),i_x_dir,i_y_dir );
//#define TestOut

#if defined ( TestOut )    
	sprintf(stg, "speed_up rx %i ry %i RX %i RY %i cRX %fp cRY %fp \n" + '\0', Player1.Return_Rand_X() , Player1.Return_Rand_Y() ,RX ,RY,CRX ,CRY );
	OutputDebugString (stg);

	sprintf(stg, "speed_up rand x %i y %i \n" + '\0', Player1.Rand_X , Player1.Rand_Y);
	OutputDebugString (stg);

	sprintf(stg, "speed_up   x %fp y %fp \n" + '\0',  i_x_dir , i_y_dir);
	OutputDebugString (stg);

#endif

	SoundPlayEffect( SOUND_JUMP );
 }
 //==============================================================
 //  tell others my DATA
 //==============================================================
 private:
void tell_others_data(CPlayer &Player1,int against)
{

	if (against < 99)
	{
		PostMessage(g_hDlg, WM_COMMAND, SCORE_AGAINST, against);
	}

	speed_up( Player1);

	PostMessage(g_hDlg, WM_COMMAND, SYNC_BALL, i_object_ID);
//Player1.b_Game_Pause=true;
}
private:
void direction_change(wall_list_element *first_ptr, wall_list_element *cur_element, CPlayer &Player1)
{
	//double tx, ty;
	//tx   = i_xpos_wall;				
	//ty   = i_ypos_wall;

	RECT RectTest;		// item to be tested
	RectTest.top	= long(i_ypos_wall);
	RectTest.left	= long(i_xpos_wall);
	RectTest.bottom	= long(i_ypos_wall + i_h_wall);
	RectTest.right	= long(i_xpos_wall + i_w_wall);

	if (intersect(RectTest ,cur_element, first_ptr))	// test if occupied
	{
	//	i_x_dir = - i_x_dir;
	//	i_y_dir = - i_y_dir;
		direction_change_(first_ptr , cur_element, Player1);
	}
}
 //==============================================================
 //  direction_change the list
 //==============================================================
private:
void direction_change_(wall_list_element *first_ptr, wall_list_element *cur_element, CPlayer &Player1)
{
	//================
	// load start location of balls
	//================
int hit_test = 0;

RECT RectTest;		// item to be tested

bool TL= false, TR= false, BL= false, BR = false;

//=========================================================================================
// test where hit and adj from there.  If hit in the back (based on dir), don't allow change.
//=========================================================================================

// up to left
	if ( (i_x_dir <= 0) && (i_y_dir <= 0) )
	{
		BL = true;
		TL = true;
		TR = true;
	}
// up to right
	if ( (i_x_dir >= 0) && (i_y_dir <= 0) )
	{
		BR = true;
		TL = true;
		TR = true;
	}
// down left
	if ( (i_x_dir <= 0) && (i_y_dir >= 0) )
		{
		BL = true;
		TL = true;
		BR = true;
	}
// down to right
	if ( (i_x_dir >= 0)  && (i_y_dir >= 0) )
	{
		BL = true;
		TR = true;
		BR = true;
	}

//=========================================================================================
// test top/left corner
//=========================================================================================
	if ( TL )
	{
		//corner test (Top Left)
		RectTest.top	= long(i_ypos_wall);
		RectTest.left	= long(i_xpos_wall);
		RectTest.bottom	= RectTest.top;
		RectTest.right	= RectTest.left;

		if (intersect(RectTest ,cur_element, first_ptr))	// test if occupied
			hit_test +=1;
	}

//=========================================================================================
// test top/right corner
//=========================================================================================
	if (TR)
	{
		//corner test (Top Right)
		RectTest.top	= long(i_ypos_wall);
		RectTest.left	= long(i_xpos_wall + i_w_wall);
		RectTest.bottom	= RectTest.top;
		RectTest.right	= RectTest.left;

		if (intersect(RectTest ,cur_element, first_ptr))	// test if occupied
			hit_test +=2;
	}
//=========================================================================================
// test botton/left corner
//=========================================================================================

	if ( BL )
	{
		//corner test (bottom left)
		RectTest.top	= long(i_ypos_wall + i_h_wall);
		RectTest.left	= long(i_xpos_wall);
		RectTest.bottom	= RectTest.top;
		RectTest.right	= RectTest.left;

		if (intersect(RectTest ,cur_element, first_ptr))	// test if occupied
			hit_test +=4;
	}
//=========================================================================================
// test bottom/right corner
//=========================================================================================
	if ( BR )
	{
		//corner test (bottom right)
		RectTest.top	= long(i_ypos_wall + i_h_wall);
		RectTest.left	= long(i_xpos_wall + i_w_wall);
		RectTest.bottom	= RectTest.top;
		RectTest.right	= RectTest.left;

		if (intersect(RectTest ,cur_element, first_ptr))	// test if occupied
			hit_test +=8;
	}

	//char      stg[256];
	//sprintf(stg, "hit_test %i  CORNER TEST TL %i,TR %i ,BL %i, BR %i \n" + '\0',hit_test,TL,TR,BL,BR);
	//OutputDebugString (stg);





/*
sprintf(stg, "Max Speed test xd %fp yd %fp \n" + '\0', i_x_dir , i_y_dir);
OutputDebugString (stg);
*/

//=========================================================================================
// accept new pos
//=========================================================================================
//cur_element->i_x_dir = i_new_x_dir;
//cur_element->i_y_dir = i_new_y_dir;

// first check if it is a hit
// then check to see if inside goal area
// then check to see if it is mine to hit, host has computers
// if not mine and in goal area, clear hit flag
// if mine and goal let every one know i've been scored on
// if none of the above.  Must be a regular hit

double t_x, t_y;
//
t_x = i_xpos_wall + i_x_dir;
t_y = i_ypos_wall + i_y_dir;

if (hit_test >= 1)
	{
		// Red 	paddle 592-(16*5)=512
		if (t_x >= 528+16)
			{

			//TRACE( TEXT("t_x > 536 %i \n"),int(t_x));
			if (Player1.i_my_slot == 0 || Player1.i_my_slot == 4 ||
				g_bHostPlayer && Player1.i_PlayerType[0] == Computer ||
				g_bHostPlayer && Player1.i_PlayerType[4] == Computer)
				{
					cur_element->d_bounce_x=t_x;
					cur_element->d_bounce_y=t_y;

					//cur_element->i_x_dir = - cur_element->i_x_dir;
					//cur_element->i_y_dir = - cur_element->i_y_dir;

					tell_others_data(Player1,0);

					adj_score(0, i_xpos_wall, i_ypos_wall, Player1);
				}
			else
				hit_test = 0;	// not mine to hit
			}
		else
		//Yellow		PADDLE (16*4)-24=80
		if (t_x <= 40-16)
			{
			if (Player1.i_my_slot == 1 || Player1.i_my_slot == 5 ||
				g_bHostPlayer && Player1.i_PlayerType[1] == Computer ||
				g_bHostPlayer && Player1.i_PlayerType[5] == Computer)
				{
					cur_element->d_bounce_x = t_x;
					cur_element->d_bounce_y = t_y;

					//cur_element->i_x_dir = - cur_element->i_x_dir;
					//cur_element->i_y_dir = - cur_element->i_y_dir;

					tell_others_data(Player1,1);

					adj_score(1, i_xpos_wall, i_ypos_wall, Player1);
				}
			else
				hit_test = 0;	// not mine to hit
			}
		 else
		// Green	PADDLE (16*4)=64+16=80
		if (t_y <= 40-16)
		{
			if (Player1.i_my_slot == 2 || Player1.i_my_slot == 6 ||
				g_bHostPlayer && Player1.i_PlayerType[2] == Computer ||
				g_bHostPlayer && Player1.i_PlayerType[6] == Computer)
				{
					cur_element->d_bounce_x=t_x;
					cur_element->d_bounce_y=t_y;

					//cur_element->i_x_dir = - cur_element->i_x_dir;
					//cur_element->i_y_dir = - cur_element->i_y_dir;

					tell_others_data(Player1,2);

					adj_score(2, i_xpos_wall, i_ypos_wall, Player1);
				}
			else
				hit_test = 0;	// not mine to hit
			}
		 else
		// Blue	paddle 592-(16*5)=512
		//if (t_y  > 536)
		if (t_y  >= 528+16)
		{
			//TRACE( TEXT("t_y > 536 %i \n"),int(t_y));
			if (Player1.i_my_slot == 3 || Player1.i_my_slot == 7 ||
				g_bHostPlayer && Player1.i_PlayerType[3] == Computer ||
				g_bHostPlayer && Player1.i_PlayerType[7] == Computer)
				{
					cur_element->d_bounce_x=t_x;
					cur_element->d_bounce_y=t_y;

					//cur_element->i_x_dir = - cur_element->i_x_dir;
					//cur_element->i_y_dir = - cur_element->i_y_dir;

					tell_others_data(Player1,3);

					adj_score(3, i_xpos_wall, i_ypos_wall, Player1);
					//TRACE( TEXT("x = %i \t y = %i \t host = %i slot = %i \n"),t_x,t_y,g_bHostPlayer,Player1.i_my_slot);
				}
			else
				hit_test = 0;	// not mine to hit
		}
		else
		// Try to prevent ball from hanging on paddle.  
		// don't let a hit occur within x moves of a prior hit
		if (cur_element->Last_Hit >2)				
			if (hit_test >= 1)
			//	if  (t_x  > 32 && t_x  < 536 && t_y  > 32 && t_y  < 536 )
			{
					switch ( hit_test )
					{
						//case 0:	do what ?? hit from a dir not tested. ?? speedup based on TL BR etc..
						case 1:	//Top Left
									i_y_dir = - i_y_dir;
									i_x_dir = - i_x_dir;
									//sprintf(stg, "1 CASE %i \n" + '\0', hit_test);
									//OutputDebugString (stg);
									break;
						case 2:	// Top Right
									i_y_dir = - i_y_dir;
									i_x_dir = - i_x_dir;
									//sprintf(stg, "2 CASE %i \n" + '\0', hit_test);
									//OutputDebugString (stg);
									break;
						case 3:	//Top left&right
									i_y_dir = - i_y_dir;
									//sprintf(stg, "3 CASE %i \n" + '\0', hit_test);
									//OutputDebugString (stg);
									break;
						case 4:	//Bottom Left
									i_y_dir = - i_y_dir;
									i_x_dir = - i_x_dir;
									//sprintf(stg, "4 CASE %i \n" + '\0', hit_test);
									//OutputDebugString (stg);
									break;
						case 5:	// Left top&bottom
									i_x_dir = - i_x_dir;
									//sprintf(stg, "5 CASE %i \n" + '\0', hit_test);
									//OutputDebugString (stg);
									break;
						//case 6:	do what ??
						case 7:	//Bottom Right
									i_y_dir = - i_y_dir;
									i_x_dir = - i_x_dir;
									//sprintf(stg, "7 CASE %i \n" + '\0', hit_test);
									//OutputDebugString (stg);
									break;
						case 8:	//Bottom Right
									i_y_dir = - i_y_dir;
									i_x_dir = - i_x_dir;
									//sprintf(stg, "8 CASE %i \n" + '\0', hit_test);
									//OutputDebugString (stg);
									break;
						//case 9:	do what ??
						case 10:	// Right top&bottom
									i_x_dir = - i_x_dir;
									//sprintf(stg, "10 CASE %i \n" + '\0', hit_test);
									//OutputDebugString (stg);
									break;
						case 11:	//Bottom Right
									i_y_dir = - i_y_dir;
									i_x_dir = - i_x_dir;
									//sprintf(stg, "8 CASE %i \n" + '\0', hit_test);
									//OutputDebugString (stg);
									break;
						case 12:	//Bottom left&right
									i_y_dir = - i_y_dir;
									//sprintf(stg, "12 CASE %i \n" + '\0', hit_test);
									//OutputDebugString (stg);
									break;
						case 13:	//Bottom Right
									i_y_dir = - i_y_dir;
									i_x_dir = - i_x_dir;
									//sprintf(stg, "13 CASE %i \n" + '\0', hit_test);
									//OutputDebugString (stg);
									break;
						case 14:	//Bottom Right
									i_y_dir = - i_y_dir;
									i_x_dir = - i_x_dir;
									//sprintf(stg, "14 CASE %i \n" + '\0', hit_test);
									//OutputDebugString (stg);
									break;
						//case 15:	do what ??
						default:
									//sprintf(stg, "???????????def CASE %i \n" + '\0', hit_test);
									//OutputDebugString (stg);
									break;
						}

				cur_element->d_bounce_x=t_x;
				cur_element->d_bounce_y=t_y;
				
				tell_others_data(Player1,99);

				cur_element->Last_Hit = 0;
			}	// end switch
	} // if hit
 }	// end move

//==============================================================
//==============================================================
//==============================================================
//==============================================================
//==============================================================
//==============================================================
//==============================================================
//  direction_change the list
//==============================================================
private:
void direction_change_orig(wall_list_element *first_ptr, wall_list_element *cur_element, CPlayer &Player1)
{
	//================
	// load start location of balls
	//================
double i_new_x_dir, i_new_y_dir;
double tx, ty, ax, ay;
int hit_test = 0;

// tx ty are test x, y
// ax ay are actuall x , y
// daq set ball data removed
//if (Player1.b_new_ball_data)
//	set_ball_data(Player1);

	//  x = left/right
	//  y = up/down

// is it safe to move or change dir

//default of the ball
i_new_x_dir = i_x_dir;
i_new_y_dir = i_y_dir;


bool TL= false, TR= false, BL= false, BR = false;

//=========================================================================================
// test what corner
//=========================================================================================

// up to left
	if ( (i_x_dir <= 0) && (i_y_dir <= 0) )
	{
		BL = true;
		TL = true;
		TR = true;
	}
// up to right
	if ( (i_x_dir >= 0) && (i_y_dir <= 0) )
	{
		BR = true;
		TL = true;
		TR = true;
	}
// down left
	if ( (i_x_dir <= 0) && (i_y_dir >= 0) )
		{
		BL = true;
		TL = true;
		BR = true;
	}
// down to right
	if ( (i_x_dir >= 0)  && (i_y_dir >= 0) )
	{
		BL = true;
		TR = true;
		BR = true;
	}
double t_x, t_y;
t_x = i_xpos_wall + i_x_dir;
t_y = i_ypos_wall + i_y_dir;
//=========================================================================================
// test upper/left corner
//=========================================================================================
	if ( TL )
	{
				tx   = i_xpos_wall + i_x_dir;				
				ty   = i_ypos_wall + i_y_dir;
				ax   = i_xpos_wall;				
				ay   = i_ypos_wall;

				if (occupied (tx,ty, cur_element, first_ptr))
					{
					if (occupied( ax, ty, cur_element, first_ptr))
						{
						//hit_y(	cout, x, y);
						if ( i_y_dir == i_new_y_dir)
							{

								i_new_y_dir = - i_y_dir;
								if ( hit_test == 0 )
								{
									hit_test = 1;
								}
							}
						}
					if (occupied( tx, ay, cur_element, first_ptr))
						{
						//hit_y( cout , x, y);
						if ( i_x_dir == i_new_x_dir)
							{

								i_new_x_dir = - i_x_dir;
								if ( hit_test == 0 )
								{
									hit_test = 1;
								}
							}

						}
					}
	}

//=========================================================================================
// test upper/right corner
//=========================================================================================
	if (TR)
	{
				tx   = i_xpos_wall + i_x_dir + i_w_wall;				
				ty   = i_ypos_wall + i_y_dir;
				ax   = i_xpos_wall + i_w_wall;				
				ay   = i_ypos_wall;

				if (occupied (tx,ty, cur_element, first_ptr))
					{
					if (occupied( ax, ty, cur_element, first_ptr))
						{
						//hit_y(	cout, x, y);
						if ( i_y_dir == i_new_y_dir)
							{
								i_new_y_dir = - i_y_dir;
								if ( hit_test == 0 )
								{
									hit_test = 1;
								}
							}
						}
					if (occupied( tx, ay, cur_element, first_ptr))
						{
						//hit_y( cout , x, y);
						if ( i_x_dir == i_new_x_dir)
							{
								i_new_x_dir = - i_x_dir;
								if ( hit_test == 0 )
								{
									hit_test = 1;
								}
							}
						}
					}
	}
//=========================================================================================
// test down/left corner
//=========================================================================================

	if ( BL )
	{
				tx   = i_xpos_wall + i_x_dir;				
				ty   = i_ypos_wall + i_y_dir + i_h_wall;
				ax   = i_xpos_wall;				
				ay   = i_ypos_wall + i_h_wall;

				if (occupied (tx,ty, cur_element, first_ptr))
					{
					if (occupied( ax, ty, cur_element, first_ptr))
						{
						//hit_y(	cout, x, y);
						if ( i_y_dir == i_new_y_dir)
							{
							i_new_y_dir = - i_y_dir;
								if ( hit_test == 0 )
								{
									hit_test = 1;
								}
							}
						}
					if (occupied( tx, ay, cur_element, first_ptr))
						{
						//hit_y( cout , x, y);
						if ( i_x_dir == i_new_x_dir)
							{	
								i_new_x_dir = - i_x_dir;
								if ( hit_test == 0 )
								{
									hit_test = 1;
								}
							}
						}
					}
	}
//=========================================================================================
// test down/left corner
//=========================================================================================
	if ( BR )
	{
				tx   = i_xpos_wall + i_x_dir + i_w_wall;				
				ty   = i_ypos_wall + i_y_dir + i_h_wall;
				ax   = i_xpos_wall + i_w_wall;				
				ay   = i_ypos_wall + i_h_wall;

				if (occupied (tx,ty, cur_element, first_ptr))
					{
					if (occupied( ax, ty, cur_element, first_ptr))
						{
						//hit_y(	cout, x, y);
						if ( i_y_dir == i_new_y_dir)
							{
								i_new_y_dir = - i_y_dir;
								if ( hit_test == 0 )
								{
									hit_test = 1;
								}
							}
						}
					if (occupied( tx, ay, cur_element,  first_ptr))
						{
						//hit_y( cout , x, y);
						if ( i_x_dir == i_new_x_dir)
							{
								i_new_x_dir = - i_x_dir;
								if ( hit_test == 0 )
								{
									hit_test = 1;
								}
							}
						}
					}
	}


//=========================================================================================
// accept new pos
//=========================================================================================
	
cur_element->i_x_dir = i_new_x_dir;
cur_element->i_y_dir = i_new_y_dir;

// first check if it is a hit
// then check to see if inside goal area
// then check to see if it is mine to hit, host has computers
// if not mine and in goal area, clear hit flag
// if mine and goal let every one know i've been scored on
// if none of the above.  Must be a regular hit



if (hit_test == 1)
	{
		// Red 	paddle 592-(16*5)=512
		if (t_x >= 528)
			{

			//TRACE( TEXT("t_x > 536 %i \n"),int(t_x));
			if (Player1.i_my_slot == 0 || Player1.i_my_slot == 4 ||
				g_bHostPlayer && Player1.i_PlayerType[0] == Computer ||
				g_bHostPlayer && Player1.i_PlayerType[4] == Computer)
				{
					cur_element->d_bounce_x=t_x;
					cur_element->d_bounce_y=t_y;

					cur_element->i_x_dir = - cur_element->i_x_dir;
					cur_element->i_y_dir = - cur_element->i_y_dir;

					tell_others_data(Player1,0);

					adj_score(0, i_xpos_wall, i_ypos_wall, Player1);
				}
			else
				hit_test = 0;	// not mine to hit
			}
		else
		//Yellow		PADDLE (16*4)-24=80
		if (t_x <= 40)
			{
			if (Player1.i_my_slot == 1 || Player1.i_my_slot == 5 ||
				g_bHostPlayer && Player1.i_PlayerType[1] == Computer ||
				g_bHostPlayer && Player1.i_PlayerType[5] == Computer)
				{
					cur_element->d_bounce_x=t_x;
					cur_element->d_bounce_y=t_y;

					cur_element->i_x_dir = - cur_element->i_x_dir;
					cur_element->i_y_dir = - cur_element->i_y_dir;

					tell_others_data(Player1,1);

					adj_score(1, i_xpos_wall, i_ypos_wall, Player1);
				}
			else
				hit_test = 0;	// not mine to hit
			}
		 else
		// Green	PADDLE (16*4)=64+16=80
		if (t_y <= 40)
		{
			if (Player1.i_my_slot == 2 || Player1.i_my_slot == 6 ||
				g_bHostPlayer && Player1.i_PlayerType[2] == Computer ||
				g_bHostPlayer && Player1.i_PlayerType[6] == Computer)
				{
					cur_element->d_bounce_x=t_x;
					cur_element->d_bounce_y=t_y;

					cur_element->i_x_dir = - cur_element->i_x_dir;
					cur_element->i_y_dir = - cur_element->i_y_dir;

					tell_others_data(Player1,2);

					adj_score(2, i_xpos_wall, i_ypos_wall, Player1);
				}
			else
				hit_test = 0;	// not mine to hit
			}
		 else
		// Blue	paddle 592-(16*5)=512
		//if (t_y  > 536)
		if (t_y  >= 528)
		{
			//TRACE( TEXT("t_y > 536 %i \n"),int(t_y));
			if (Player1.i_my_slot == 3 || Player1.i_my_slot == 7 ||
				g_bHostPlayer && Player1.i_PlayerType[3] == Computer ||
				g_bHostPlayer && Player1.i_PlayerType[7] == Computer)
				{
					cur_element->d_bounce_x=t_x;
					cur_element->d_bounce_y=t_y;

					cur_element->i_x_dir = - cur_element->i_x_dir;
					cur_element->i_y_dir = - cur_element->i_y_dir;

					tell_others_data(Player1,3);

					adj_score(3, i_xpos_wall, i_ypos_wall, Player1);
					//TRACE( TEXT("x = %i \t y = %i \t host = %i slot = %i \n"),t_x,t_y,g_bHostPlayer,Player1.i_my_slot);
				}
			else
				hit_test = 0;	// not mine to hit
		}
		else
		// plan old bounce only, no paddles hit
		if (hit_test == 1)
		//	if  (t_x  > 32 && t_x  < 536 && t_y  > 32 && t_y  < 536 )
			{
			cur_element->d_bounce_x=t_x;
			cur_element->d_bounce_y=t_y;
			
			tell_others_data(Player1,99);

			cur_element->Last_Hit = 0;
			}
	
	} // if hit

 }	// end move

 //========

 //========
// Destructor defaults
//    private:
// No copy constructor
   //     ball_list_element(const ball_list_element &); 
// No assignment operator
   //     ball_list_element operator =(const ball_list_element &);
};

	// end class ball_list_element

