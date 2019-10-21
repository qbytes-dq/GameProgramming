// Virtical cPaddle.h

//#include "trace.h"

#include "Enumerations.h"

//#define  TRACE   stagetrace 
/////////////////////////////////
class paddle_v_list_element : wall_list_element
{
public:


//===============================================================
paddle_v_list_element(  const int i_xpos, 
						const int i_ypos, 
						LPDIRECTDRAWSURFACE7 &p_dds,
						double OwningPlayerID) : wall_list_element (i_xpos, i_ypos, p_dds)
{


	i_w_wall	= 16; //30; //24;	// won't show if bigger then image 		  
	i_h_wall	= 60; //60; //128;  // won't show if bigger then image        
	i_wait      =  0;

	i_x_dir		=	0;
	i_y_dir		=	0;

	i_frame = (int)OwningPlayerID; 
	if (i_frame > 3)
		i_frame -=4;

	if (i_frame > 1)
		i_frame -=2;
}

 //===============================================================
private:
 void move(wall_list_element *first_ptr, wall_list_element *cur_element, CPlayer &Player1) 
 {
	 if (Player1.i_my_slot == cur_element->OwningPlayerID)
		{// my paddle move  (up/down)
			 cur_element->i_ypos_wall += Player1.i_y_pos[Player1.i_my_slot];

			if ( cur_element->i_ypos_wall < 80 )
				cur_element->i_ypos_wall = 80;

			if ( cur_element->i_ypos_wall + cur_element->i_h_wall >592 -80 )
				cur_element->i_ypos_wall = 592 -80- cur_element->i_h_wall;

			// prep for send
//			Player1.i_x_1_pos[cur_element->OwningPlayerID] = cur_element->i_xpos_wall;
//			Player1.i_y_1_pos[cur_element->OwningPlayerID] = cur_element->i_ypos_wall;

			//TRACE( TEXT("My Move    x= %i, y= %i , p= %i\n"), Player1.i_y_pos[Player1.i_my_slot], Player1.i_x_pos[Player1.i_my_slot], Player1.i_my_slot );
			//TRACE( TEXT("My Paddle  x= %i, y= %i , p= %i\n"), cur_element->i_xpos_wall, cur_element->i_ypos_wall,cur_element->OwningPlayerID );
	 } // end my move
	else
		{	// next question is computer (AI) or someone else doing the move
			// next question is computer (AI) or someone else doing the move
			// next question is computer (AI) or someone else doing the move
		if (Player1.i_PlayerType[cur_element->OwningPlayerID] == Computer)
			{	// this is the computer moving (AI)
				// this is the computer moving (AI)
				// this is the computer moving (AI)
				double temp_move;
				int move_rate = 15;
//				int xxx;
//				xxx = (int)cur_element->i_ypos_wall;
		//	TRACE( TEXT("Paddle  AI1= %i,AI2= %i, objID= %i , Player= %i, X = %i, xwal = %i\n"), cur_element->AI_X1,cur_element->AI_X2, cur_element->i_object_ID,cur_element->OwningPlayerID,cur_element->Return_X(), xxx);
				if (cur_element->i_xpos_wall < 296)  // 592/2
						// left paddle (up/down)
							temp_move=((double)(592-cur_element->AI_X)/592)*move_rate;
					else
						// right paddle (up/down)
							temp_move=((double)(cur_element->AI_X)/592)*move_rate;
					// calculate move left or right based on ball pos
					if (cur_element->AI_Y > cur_element->i_ypos_wall + (cur_element->i_w_wall/2) +(move_rate))
							cur_element->i_ypos_wall +=temp_move;
						else
							if (cur_element->AI_Y < cur_element->i_ypos_wall + (cur_element->i_w_wall/2)-(move_rate))
								cur_element->i_ypos_wall -=temp_move;

//cur_element->i_ypos_wall=cur_element->AI_Y-22;  /// EXACTLY WHERE BALL IS, NOW

					// must still play by the rules, stay in bounds
					if ( cur_element->i_ypos_wall < 80 )
							cur_element->i_ypos_wall = 80;

					if ( cur_element->i_ypos_wall + cur_element->i_h_wall >592 -80 )
							cur_element->i_ypos_wall = 592 -80- cur_element->i_h_wall;
			} // end computer (AI) doing move
		else
			{	// this is someone elses paddle
				// rules don't apply for us being told what to do,  
				// the rules were applied on the other computer.

				//		TRACE( TEXT("Not My Pad x= %i, y= %i , p= %i\n"), cur_element->i_xpos_wall, cur_element->i_ypos_wall,cur_element->OwningPlayerID );
			} // end some else paddle move
		} // end if
 }  // end move


// Destructor defaults
//    private:
// No copy constructor
   //     circle_list_element(const circle_list_element &); 
// No assignment operator
   //     circle_list_element operator =(const circle_list_element &);
};

	// end class paddle_list_element
