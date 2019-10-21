// cWallList.h

//==============================================================
// The list
//==============================================================
#include "trace.h"
#define TRACE   stagetrace 

//================
class wall_list 
{
	private:
	wall_list_element *first_ptr;	// First element of the list
	wall_list_element *last_ptr;		// Last element of the list

	public:
	static int i_ball_cnt;

	wall_list_element *paddles[8];	// this array is for the moves of a paddle from other players

//==============================================================
 public:
 // Create the list
 wall_list(void) 
		{ 
			//1/8/02 int x;
			//1/8/02 x = wall_list::i_ball_cnt++;

			i_ball_cnt = 0;


		//wall_list_element::count = 0;
	    first_ptr = NULL; 
	    last_ptr  = NULL;	  

		for (int loop = 0 ; loop < 8 ; loop++)
			paddles[loop] = NULL;		// set paddle to NULL so it's not used.

		//i_ball_cnt = 0;

		sprintf(stg, "wall_list Construct %i\n",i_ball_cnt);//1/8/02 
		OutputDebugString (stg);

		}	// end create\construct

//==============================================================
 ~wall_list(void) // Destroy the list
 {
int cnttt = 0;

     while (first_ptr != NULL) 
	 {
		// Pointer to the next item in the list
        wall_list_element *next_ptr = first_ptr->next_ptr;
		first_ptr->prev_ptr = NULL;
		first_ptr->next_ptr = NULL;

		sprintf(stg, "wall_list ~Construct %i addr %i obj-ID %i player %i \n",cnttt++,first_ptr,first_ptr->rtn_obj_id(),first_ptr->rtn_OwningPlayer());
		OutputDebugString (stg);

		delete first_ptr;
		first_ptr = next_ptr;

     }
first_ptr = NULL;
last_ptr = NULL;
 }	  // end destroy\destruct
//==============================================================
 //   private:
 // Don't allow use of the copy constructor
 //wall_list(const wall_list &); 

//==============================================================
// return first
//==============================================================
	public:
wall_list_element* return_first()
{
	return first_ptr;
}	 // end return first
	public:
//==============================================================
// Add a wall item to the list
//==============================================================
//	private:
//void assign_object_ID(wall_list_element *new_wall)
//{
//	static int id = 0;
//	new_wall->i_object_ID = ++id;
//}


//==============================================================
// Add a wall item to the list
//==============================================================
//	private:
	public:
void add_wall(int i_xpos, int i_ypos, LPDIRECTDRAWSURFACE7 &p_dds) 
{
	wall_list_element *new_wall;
// The wall we are adding
	new_wall = new wall_list_element(i_xpos, i_ypos,p_dds);


     if (first_ptr == NULL) 
	 {
        first_ptr = new_wall;
		last_ptr = new_wall;
		new_wall->next_ptr = NULL;
		new_wall->prev_ptr = NULL;

		new_wall->i_frame=0;
		//new_wall->set_cnt99();
     } 
	 else 
	 {
		last_ptr->next_ptr = new_wall;
		new_wall->prev_ptr = last_ptr;
		last_ptr = new_wall;
     }
 //assign_object_ID(new_wall); daq 1/8/02DQ006
 }	 // end add_wall


//==============================================================
// Add a ball item to the list
//==============================================================
//	private:
	public:
void add_ball(int i_xpos, int i_ypos, LPDIRECTDRAWSURFACE7 &p_dds, double i_deg,int i_radius) 
{
	wall_list_element *new_ball;
	wall_list_element *old_ball;
// The wall we are adding
	new_ball = new ball_list_element(i_xpos, i_ypos,p_dds, ++i_ball_cnt , i_deg, i_radius);


     if (first_ptr == NULL) 
	 {
        first_ptr = new_ball;
		last_ptr = new_ball;
		new_ball->next_ptr = NULL;
		new_ball->prev_ptr = NULL;
		new_ball->i_frame=0;
		//new_ball->set_cnt99();
     } 
	 else 
	 {
		last_ptr->next_ptr = new_ball;
		new_ball->prev_ptr = last_ptr;
		//last_ptr = new_ball;

		old_ball = last_ptr;
		last_ptr = new_ball;

		new_ball->i_frame=old_ball->i_frame;

		if (new_ball->i_frame++ > 8)
			new_ball->i_frame = 0;
     }
  //assign_object_ID(new_ball);	daq 1/8/02DQ006
}	 // end add_wall


//==============================================================
// Add a circle item to the list
//==============================================================
//	private:
	public:
void add_circle(int i_xpos, int i_ypos, int i_rad, int i_degree, LPDIRECTDRAWSURFACE7 &p_dds) 
{
	wall_list_element *new_circle;
	wall_list_element *old_circle;
// The wall we are adding
	new_circle = new circle_list_element(i_xpos, i_ypos, i_rad, i_degree, p_dds);


     if (first_ptr == NULL) 
	 {
        first_ptr = new_circle;
		last_ptr = new_circle;
		new_circle->next_ptr = NULL;
		new_circle->prev_ptr = NULL;
		new_circle->i_frame=0;
		//new_circle->set_cnt99();
     } 
	 else 
	 {
		last_ptr->next_ptr = new_circle;
		new_circle->prev_ptr = last_ptr;
		//last_ptr = new_circle;

		old_circle = last_ptr;
		last_ptr = new_circle;

		new_circle->i_frame=old_circle->i_frame;

		if (new_circle->i_frame++ > 8)
			new_circle->i_frame = 0;
     }
//assign_object_ID(new_circle);	daq 1/8/02DQ006
 }	 // end add_wall

//==============================================================
// Add a boom item to the list
//==============================================================
//	private:
	public:
void add_boom(int i_xpos, int i_ypos, int i_rad, int i_degree, LPDIRECTDRAWSURFACE7 &p_dds) 
{
	wall_list_element *new_boom;
	wall_list_element *old_boom;
// The wall we are adding
	new_boom = new boom_list_element(i_xpos, i_ypos, i_rad, i_degree, p_dds);


     if (first_ptr == NULL) 
	 {
        first_ptr = new_boom;
		last_ptr = new_boom;
		new_boom->next_ptr = NULL;
		new_boom->prev_ptr = NULL;
		new_boom->i_frame=0;
		//new_boom->set_cnt99();
     } 
	 else 
	 {
		last_ptr->next_ptr = new_boom;
		new_boom->prev_ptr = last_ptr;
		//last_ptr = new_boom;

		old_boom = last_ptr;
		last_ptr = new_boom;

		new_boom->i_frame=old_boom->i_frame;

		if (new_boom->i_frame++ > 8)
			new_boom->i_frame = 0;
     }
//assign_object_ID(new_boom);	daq 1/8/02DQ006
 }	 // end add_wall

//==============================================================
// Add a Virtical paddle item to the list
//==============================================================
//	private:
	public:
void add_v_paddle(int i_xpos, int i_ypos, LPDIRECTDRAWSURFACE7 &p_dds, DWORD OwningPlayerID, CPlayer &Player1) 
{
wall_list_element *new_paddle;
wall_list_element *old_paddle;
// The wall we are adding
	new_paddle = new paddle_v_list_element(i_xpos, i_ypos,p_dds,OwningPlayerID);

     if (first_ptr == NULL) 
		 {
			first_ptr = new_paddle;
			last_ptr = new_paddle;
			new_paddle->next_ptr = NULL;
			new_paddle->prev_ptr = NULL;
			new_paddle->i_frame=0;
			//new_paddle->set_cnt99();
		 } 
	 else 
		 {
			last_ptr->next_ptr = new_paddle;
			new_paddle->prev_ptr = last_ptr;
			//last_ptr = new_boom;

			old_paddle = last_ptr;
			last_ptr = new_paddle;
		 }

//assign_object_ID(new_paddle);  daq 1/8/02DQ006
new_paddle->OwningPlayerID = OwningPlayerID;

paddles[OwningPlayerID] = new_paddle;
 }	 // end add_v_paddle

//==============================================================
// Add a Horizonal paddle item to the list
//==============================================================
//	private:
	public:
void add_h_paddle(int i_xpos, int i_ypos, LPDIRECTDRAWSURFACE7 &p_dds, DWORD OwningPlayerID, CPlayer &Player1) 
{
wall_list_element *new_paddle;
wall_list_element *old_paddle;
// The wall we are adding
	new_paddle = new paddle_h_list_element(i_xpos, i_ypos,p_dds,OwningPlayerID);

     if (first_ptr == NULL) 
		 {
			first_ptr = new_paddle;
			last_ptr = new_paddle;
			new_paddle->next_ptr = NULL;
			new_paddle->prev_ptr = NULL;
			new_paddle->i_frame=0;
			//new_paddle->set_cnt99();
		 } 
	 else 
		 {
			last_ptr->next_ptr = new_paddle;
			new_paddle->prev_ptr = last_ptr;
			//last_ptr = new_boom;

			old_paddle = last_ptr;
			last_ptr = new_paddle;
		 }

//assign_object_ID(new_paddle);		daq 1/8/02DQ006
new_paddle->OwningPlayerID = OwningPlayerID;

paddles[OwningPlayerID] = new_paddle;
 }	 // end add_h_paddle


//==============================================================
// set paddle data , sync paddles
//==============================================================
public:
void
set_paddle_data(int OwningPlayer, double x, double y)
{
//TRACE( TEXT(" RCV SetPlayerPaddle x= %i, y= %i slot= %i\n"), x, y, OwningPlayer );

	paddles[OwningPlayer]->i_xpos_wall = x;
	paddles[OwningPlayer]->i_ypos_wall = y;
}	 // end sync paddles
//==============================================================
// get paddle data, rtn paddles
//==============================================================
public:
double
get_paddle_data_x(int OwningPlayer)
{
	return paddles[OwningPlayer]->i_xpos_wall;
}
//==============================================================
// get paddle data, rtn paddles
//==============================================================
public:
double
get_paddle_data_y(int OwningPlayer)
{
	return paddles[OwningPlayer]->i_ypos_wall;
}
//==============================================================
//   line of walls
//==============================================================
	public:
void line_wall (int x1, int y1, int x2, int y2, LPDIRECTDRAWSURFACE7 &p_dds)
{
	int dy, dx;
	int tempx, tempy;

	// lock to grid
	x1 = x1 / 16;
	y1 = y1 / 16;
	
	x2 = x2 / 16;
	y2 = y2 / 16;


	if (x1 > x2)	// map iii, iv, v , vi 
	{				// on to vii, viii, i ,ii
		tempx = x1;
		x1 = x2;
		x2 = tempx;

		tempy = y1;
		y1 = y2;
		y2 = tempy;
	}


dx = abs(x2 - x1);
dy = abs(y2 - y1);


if ( dy > dx ) 
	highslope(x1, y1, x2, y2,p_dds);
	else 
	lowslope (x1, y1, x2, y2,p_dds);
}
//==============================================================
//  routine to handle quadrants i and viii
//==============================================================
	private:
void lowslope ( int x1, int y1, int x2, int y2, LPDIRECTDRAWSURFACE7 &p_dds)
{
	int dy, dx;

	int error_hor;
	int error_45;
	int decision_var;
	int xpos, ypos;

	int xdir, ydir, i;

	dy = abs(y2 - y1);
	dx = abs(x2 - x1);

	error_hor = 2 * dy;
					  
	error_45 = 2 * (dy - dx) ;
	decision_var = 2 * dy - dx;

	xpos = x1;
	ypos = y1;

	ydir = 1;
	if (y2 < y1) 
		ydir = -ydir;

	xdir =1;
	if (x2 < x1) 
		xdir = -xdir;


	for (i=dx; i>=0; i-- )
	{
		// add wall

		add_wall( xpos  * 16 , ypos * 16,p_dds);
		xpos += xdir;
		if (decision_var > 0)
		{
			ypos += ydir;
			decision_var += error_45;
		}
		else
			decision_var += error_hor;
	}
}

//==============================================================
// routine to handal quadrants ii and viii
//==============================================================
	private:
void highslope ( int x1, int y1, int x2, int y2, LPDIRECTDRAWSURFACE7 &p_dds)
{
	int dy, dx;

	int error_ver;
	int error_45;
	int decision_var;
	int xpos, ypos;

	int xdir,ydir, i;

	dy = abs(y2 - y1);

	dx = abs(x2 - x1);

	error_ver = 2 * dx;


	error_45 = 2 * (dx - dy);
	decision_var = 2 * dx - dy;

	xpos = x1;
	ypos = y1;

	xdir = 1;
	if (x2 < x1) 
		xdir = -xdir;
	ydir = 1;
	if (y2 < y1) 
		ydir = -ydir;


	for ( i = dy; i >=0; i--)
	{
		// set_pis (xpos, ypos++);

		add_wall( xpos * 16 , ypos * 16,p_dds);
		ypos += ydir;
		if (decision_var > 0 )
		{
			xpos += xdir;
			decision_var +=error_45;
		}
		else
			decision_var += error_ver;
	}
}



 //==============================================================
 // Delete an item from the list based on OwningPlayer
 //==============================================================
	public:
 void remove_Owning_Player(const int OwningPlayer) 
 {
     wall_list_element *cur_ptr; // Current item
     wall_list_element *prev_ptr; // Previous item

     prev_ptr = NULL;
     for (	cur_ptr = first_ptr; 
			cur_ptr != NULL; 
			cur_ptr = cur_ptr->next_ptr) 
		{
         if (cur_ptr->OwningPlayerID == OwningPlayer) 
			{
			// Are we deleting the first element
			if (cur_ptr == first_ptr) 
				{
				first_ptr = cur_ptr->next_ptr;
				cur_ptr->prev_ptr = NULL;	 
				} 
				else 
				// Are we deleting the last element
				if (cur_ptr == last_ptr) 
					{
					last_ptr = prev_ptr;
					last_ptr->next_ptr = NULL;
					} 
      
			if (cur_ptr->next_ptr != NULL)
				  cur_ptr->next_ptr->prev_ptr = cur_ptr->prev_ptr;

			if (cur_ptr->prev_ptr != NULL)
				  cur_ptr->prev_ptr->next_ptr = cur_ptr->next_ptr;

			delete cur_ptr;
			cur_ptr = NULL;
			return;
			}
		prev_ptr = cur_ptr;
		}	//next

     // At this point we didn't find the item.
     // So don't worry about deleting what's not there

 }	 // end remove
 //==============================================================
 // Delete an item from the list, based on ID
 //==============================================================
 void remove_Owning_ID(const int OwningID) 
 {
     wall_list_element *cur_ptr; // Current item
     wall_list_element *prev_ptr; // Previous item

     prev_ptr = NULL;
     for (	cur_ptr = first_ptr; 
			cur_ptr != NULL; 
			cur_ptr = cur_ptr->next_ptr) 
		{
         if (cur_ptr->i_object_ID == OwningID) 
			{
			// Are we deleting the first element
			if (cur_ptr == first_ptr) 
				{
				first_ptr = cur_ptr->next_ptr;
				cur_ptr->prev_ptr = NULL;	 
				} 
				else 
				// Are we deleting the last element
				if (cur_ptr == last_ptr) 
					{
					last_ptr = prev_ptr;
					last_ptr->next_ptr = NULL;
					} 
      
			if (cur_ptr->next_ptr != NULL)
				  cur_ptr->next_ptr->prev_ptr = cur_ptr->prev_ptr;

			if (cur_ptr->prev_ptr != NULL)
				  cur_ptr->prev_ptr->next_ptr = cur_ptr->next_ptr;

			delete cur_ptr;
			cur_ptr = NULL;
			return;
			}
		prev_ptr = cur_ptr;
		}	//next

 }	 // end remove ID
      
 //==============================================================
 // sync an item from the list, based on ID
 //==============================================================
 void Rcv_Sync_OwningID( CPlayer &Player1,
							int		OwningID,
							double	x_pos,
							double	y_pos,
							double	x_vol,
							double	y_vol,
							double	b_x_pos,
							double	b_y_pos) 
 {
     wall_list_element *cur_ptr; // Current item

     for (	cur_ptr = first_ptr; 
			cur_ptr != NULL; 
			cur_ptr = cur_ptr->next_ptr) 
		{
			if (cur_ptr->i_object_ID == OwningID) 
				{
				// only adjust if were not in sync with DIRECTION
				//if (x_vol != cur_ptr->i_x_dir && cur_ptr->i_y_dir != y_vol)
						{
						cur_ptr->i_xpos_wall	=	x_pos;
						cur_ptr->i_ypos_wall	=	y_pos;
						cur_ptr->i_x_dir		=	x_vol;
						cur_ptr->i_y_dir		=	y_vol;
						cur_ptr->d_bounce_x		=	b_x_pos;
						cur_ptr->d_bounce_y		=	b_y_pos;

						cur_ptr->Last_Hit = 0;
						
						char      stg[256];
						sprintf(stg, "RCV SYNC %i \n" + '\0', OwningID);
						OutputDebugString (stg);
						}


				//	} // end last hit
				} // end if Owning ID
		}	//next
 }	 // end sync owning ID
 //============================

 //==============================================================
 // Move an item
 //==============================================================
public:
 void do_move(CPlayer &Player1) 
 {
     wall_list_element *cur_ptr; // Current item
     //wall_list_element *prev_ptr; // Previous item




// do the move
	 //prev_ptr = NULL;
     for (cur_ptr  = first_ptr; 
		  cur_ptr != NULL; 
		  cur_ptr  = cur_ptr->next_ptr) 

		{
			if (++cur_ptr->i_wait_count > cur_ptr->i_wait)
				{
					cur_ptr->i_wait_count = 0;

					cur_ptr->move(first_ptr , cur_ptr, Player1);
				}
		}	  // end for


// adjust the direction

		  	 //prev_ptr = NULL;
     for (cur_ptr  = first_ptr; 
		  cur_ptr != NULL; 
		  cur_ptr  = cur_ptr->next_ptr) 

			{
				cur_ptr->direction_change(first_ptr , cur_ptr, Player1);
			}

	check_close_to_me(Player1);  // part of AI
 }// end do_move

 //==============================================================
 // Check balls Close to me, AI for computer play
 //==============================================================
 private:

 void check_close_to_me(CPlayer &Player1) 
 {
  wall_list_element *cur_ptr; // Current items
//  x = left/right
//  y = up/down

// TOP NUMBER NEEDS TO BE OPPOSITE OF THE BOTTOM NUMBER TO MAINTAIN CENTER WHILE WAITING
///////////////////////////////////////////////////////////////////////////////////
// testing for Top Green Paddle 1
  int TP1  = 592;	
  int TPX1 = 592/2; // default to middle cur_ptr->AI_X;	// 
  int TPY1 = 0;
  double TPW1 = 1000; // how soon till impact
// testing for Top Green Paddle 2
  int TP2  = 592;	
  int TPX2 = 592/2; // default to middle cur_ptr->AI_X;	// 
  int TPY2 = 0;
  double TPW2 = 1000; // how soon till impact

// one or two GREEN in game?
  int TPT = 0;
  int TPB = 592;

  if (Player1.i_PlayerType[2]   == Computer || Player1.i_PlayerType[2]   == Human)
	if (Player1.i_PlayerType[6] == Computer || Player1.i_PlayerType[6] == Human)
		{
			TPT = 592/2;
			TPB = 592/2;

			TPX1 = (592/5)*3;	// assign new center point
			TPX2 = (592/5)*2;		// assign new center point
		}
///////////////////////////////////////////////////////////////////////////////////
// testing for Bottom Paddle
  int BP1  = 0; 
  int BPX1 = 592/2; // default to middle cur_ptr->AI_X;	// 
  int BPY1 = 592;
  double BPW1 = 1000; // how soon till impact

// testing for Bottom Paddle
  int BP2  = 0; 
  int BPX2 = 592/2; // default to middle cur_ptr->AI_X;	// 
  int BPY2 = 592;
  double BPW2 = 1000; // how soon till impact

// one or two BLUE in game?
  int BPT = 0;
  int BPB = 592;

  if (Player1.i_PlayerType[3]   == Computer || Player1.i_PlayerType[3]   == Human)
		if (Player1.i_PlayerType[7] == Computer || Player1.i_PlayerType[7] == Human)
		{
			BPT = 592/2;
			BPB = 592/2;

			BPX1 = (592/5)*3;	// assign new center point
			BPX2 = (592/5)*2;	// assign new center point

		}

///////////////////////////////////////////////////////////////////////////////////
// testing for Right Red Paddle front
//  int RP1  = 0;	
//  int RPX1 = 592;
//  int RPY1 = 592/2; // default to middle cur_ptr->AI_Y;	//
//  double RPW1 = 1000; // how soon till impact

// testing for Right Red Paddle back
  int RP2  = 0;	
  int RPX2 = 592;
  int RPY2 = 592/2; // default to middle cur_ptr->AI_Y;	//
  double RPW2 = 1000; // how soon till impact
// one or two RED in game?
  int RPL = 0;
  int RPR = 592;

  if (Player1.i_PlayerType[0]   == Computer || Player1.i_PlayerType[0]   == Human)
		if (Player1.i_PlayerType[4] == Computer || Player1.i_PlayerType[4] == Human)
		{
			RPL = 592/2;
			RPR = 592/2;

//			RPX1 = (592/5)*3;	// assign new center point
			RPY2 = (592/5)*2;		// assign new center point

		}

///////////////////////////////////////////////////////////////////////////////////
// testing for Left Paddle
  int LP1  = 592; 
  int LPX1 = 0;
  int LPY1 = 592/2; // default to middle cur_ptr->AI_Y;	//
  double LPW1 = 1000; // how soon till impact

  int LP2  = 592; 
  int LPX2 = 0;
  int LPY2 = 592/2; // default to middle cur_ptr->AI_Y;	//
  double LPW2 = 1000; // how soon till impact

// one or two YELLOW in game?
  int LPL = 0;
  int LPR = 592;

  if (Player1.i_PlayerType[1]   == Computer || Player1.i_PlayerType[1]   == Human)
		if (Player1.i_PlayerType[5] == Computer || Player1.i_PlayerType[5] == Human)
		{
			LPL = 592/2;
			LPR = 592/2;
            
			LPY1 = (592/5)*3;	// assign new center point
			LPY2 = (592/5)*2;		// assign new center point
		}
///////////////////////////////////////////////////////////////////////////////////
//TRACE( TEXT("=DAQ========================================= \n"));
     for (cur_ptr  = first_ptr; 
		  cur_ptr != NULL; 
		  cur_ptr  = cur_ptr->next_ptr) 
			{

			//TRACE( TEXT("Paddle  return x = %i\n"), cur_ptr->Return_X(cur_ptr) );

			  // need to verify its a moveable ball
			  if (cur_ptr->Return_X() != -1) // -1 not a ball
			  {
				//TRACE( TEXT("Paddle  return x = %i, y = %i, xv = %i  yv = %i  \n"), cur_ptr->Return_X(), cur_ptr->Return_Y(),cur_ptr->Return_XV(), cur_ptr->Return_YV() );

				//sprintf(stg, "  TPW %fp test_TPW %fp YV %fp ,,, %i \n", TPW,test_TPW, cur_ptr->i_y_dir,cur_ptr->i_object_ID );
				//OutputDebugString (stg);

				  ////////////////////////////////////////////////////////////////////////////////////////////
					// top GREEN paddle
							// only if it's coming at me
							if (cur_ptr->Return_YV() < 0) // moving up
							{
									double test_TPW;
									double test_TPx;

									test_TPW = (cur_ptr->Return_Y()- 80) / abs(cur_ptr->Return_YV());
									test_TPx = (test_TPW * cur_ptr->Return_XV())+cur_ptr->Return_X();

									// Green paddle 2
									//if (test_TPx > 592/2)
									if (test_TPx > TPT)
									{
										if (test_TPW < TPW1)
											{
											TPW1 = test_TPW;
											//
											TP1 = cur_ptr->Return_Y();  // set left paddle y
											TPX1 = cur_ptr->Return_X(); //
											TPY1 = cur_ptr->Return_Y();
											}
									}
									//else
									if (test_TPx <= TPB)
									{
										// Green paddle 6
										if (test_TPW < TPW2)
											{
											TPW2 = test_TPW;
											//
											TP2 = cur_ptr->Return_Y();  // set left paddle y
											TPX2 = cur_ptr->Return_X(); //
											TPY2 = cur_ptr->Return_Y();
											}
									}
							}
				  ////////////////////////////////////////////////////////////////////////////////////////////
					// bottom BLUE paddle
							// only if it's coming at me
							if (cur_ptr->Return_YV() > 0) // moving down
							{
								double test_BPW;
								double test_BPx;

								test_BPW = ( (592 - 80) - cur_ptr->Return_Y() ) / abs(cur_ptr->Return_YV());
								test_BPx = (test_BPW * cur_ptr->Return_XV()) + cur_ptr->Return_X();

								// paddle 3
								//if (test_BPx > 592/2)
								if (test_BPx > BPT)
									{
									if (test_BPW < BPW1)
										{
										BPW1 = test_BPW;
										//
										BP1 = cur_ptr->Return_Y();  // set left paddle y
										BPX1 = cur_ptr->Return_X(); //
										BPY1 = cur_ptr->Return_Y();
										}
									}
								//else
								if (test_BPx <= BPB)
									{
									// paddle 7
									if (test_BPW < BPW2)
										{
										BPW2 = test_BPW;
										//
										BP2 = cur_ptr->Return_Y();  // set left paddle y
										BPX2 = cur_ptr->Return_X(); //
										BPY2 = cur_ptr->Return_Y();
										}
									}
							}
				  ////////////////////////////////////////////////////////////////////////////////////////////
					// left Yellow Paddle 
					if (cur_ptr->Return_XV() < 0) // Moving to right
						{
						double test_LPW;
						double test_LPx;

						test_LPW = (cur_ptr->Return_X() - 80 ) / abs(cur_ptr->Return_XV() );
						test_LPx = (test_LPW * cur_ptr->Return_YV() ) + cur_ptr->Return_Y();
						// only if it's coming at me
						if (test_LPx > LPL)
							{
							if (test_LPW < LPW1)
									{
									LPW1 = test_LPW;
									//
									LP1 = cur_ptr->Return_X();  // set left paddle y
									LPX1 = cur_ptr->Return_X();
									LPY1 = cur_ptr->Return_Y(); //
									}
							}
						if (test_LPx <= LPR)
							{
							if (test_LPW < LPW2)
								{
								LPW2 = test_LPW;
								//
								LP2 = cur_ptr->Return_X();  // set left paddle y
								LPX2 = cur_ptr->Return_X();
								LPY2 = cur_ptr->Return_Y(); //
								}
							}
						}
				  ////////////////////////////////////////////////////////////////////////////////////////////
  				  // right Red Paddle back paddle
					  //if (cur_ptr->Return_X() > RP2) // find ball closest to me
					  if (cur_ptr->Return_XV() > 0) // Moving to right
						{
						double test_RPW;
						double test_RPx;

						test_RPW = ((592-80)-cur_ptr->Return_X() ) / abs(cur_ptr->Return_XV() );
						test_RPx = (test_RPW * cur_ptr->Return_YV() ) + cur_ptr->Return_Y();

						if (test_RPx <= RPR)
							{
								// only if it's coming at me
								//if (cur_ptr->Return_XV() >= 0) // moving right
								if (test_RPW < RPW2)
									{
									RPW2 = test_RPW;
									//
									RP2  = cur_ptr->Return_X();  // set left paddle y
									RPX2 = cur_ptr->Return_X();
									RPY2 = cur_ptr->Return_Y(); //
									}
							}
						}
				  } // end not ball->// -1 not a ball
			} // get next ball

  ////////////////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////////////////
  // Assign what we have learned.

     for (cur_ptr  = first_ptr; 
		  cur_ptr != NULL; 
		  cur_ptr  = cur_ptr->next_ptr) 
			{
			  // Right paddle 0 always human

			  // left
			  if (cur_ptr->OwningPlayerID == 1) 
					{
					cur_ptr->AI_Y = LPY1;//
					cur_ptr->AI_X = LPX1;
					}

			  // top
			  if (cur_ptr->OwningPlayerID == 2)
					{
					cur_ptr->AI_X = TPX1;//
					cur_ptr->AI_Y = TPY1;
					}
			  
			  // bottom		
			  if (cur_ptr->OwningPlayerID == 3)   
					{
					cur_ptr->AI_X = BPX1;//
					cur_ptr->AI_Y = BPY1;
					}

			  // right
			  if (cur_ptr->OwningPlayerID == 4)  
					{
					cur_ptr->AI_Y = RPY2;//
					cur_ptr->AI_X = RPX2;
					}
			  // left
			  if (cur_ptr->OwningPlayerID == 5) 
					{
					cur_ptr->AI_Y = LPY2;//
					cur_ptr->AI_X = LPX2;
					}

			  // top
			  if (cur_ptr->OwningPlayerID == 6)
					{
					cur_ptr->AI_X = TPX2;//
					cur_ptr->AI_Y = TPY2;
					}
			  
			  // bottom		
			  if (cur_ptr->OwningPlayerID == 7)   
					{
					cur_ptr->AI_X = BPX2;//
					cur_ptr->AI_Y = BPY2;
					}
			}

 }// end check_close_to_me




 //==============================================================
 //==============================================================
 //==============================================================

};// end class
 int wall_list::i_ball_cnt = 0;