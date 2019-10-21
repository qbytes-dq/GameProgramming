// cWall.h

//#include <stdlib.h>
//#include <time.h>
#include <math.h>


/********************************************************
 * wall element class.     *
 *       *
 * From the "cWallList.h" file in the programs from  *
 * Practical C++.     *
 ********************************************************/

// Define an element of a wall list
class wall_list_element 
{
	public:
//1/8/02 	static int i_ball_cnt1;

public:
//static int rtncnt() { return wall_list_element::i_ball_cnt; }

double	i_xpos_wall,	i_ypos_wall;  // Data for the element
int		i_w_wall,		i_h_wall;
double	i_x_dir,		i_y_dir;								//12/09/02
int		i_frame,		i_frames;
int		i_wait_count,	i_wait;
double	d_bounce_x,		d_bounce_y;
int		i_object_ID;


LPDIRECTDRAWSURFACE7	p_DDS;  // Offscreen Direct Draw Surface

int OwningPlayerID;


int AI_X;
int AI_Y;

int Last_Hit;	// count number of moves since last hit;  host will make sure everyone is on the same page

 // Pointer to the prev/next element
public:
 class wall_list_element *prev_ptr;
 class wall_list_element *next_ptr;

 //private:
 // share data with wall_list    
 friend class wall_list; // The list itself
 
 //===============================================================
 //===============================================================
 //===============================================================
     wall_list_element(const int i_xpos, const int i_ypos, LPDIRECTDRAWSURFACE7 &p_dds) 
	 {
	//===================
		p_DDS		= p_dds;	// image to display
	//===================
		i_xpos_wall	= i_xpos;	 // need a routine to validate the x, y are good values (Max,Min?)
		i_ypos_wall	= i_ypos;
							
		i_w_wall	=      16;		
		i_h_wall	=      16;        
	//=====
		i_x_dir		=		0; 
		i_y_dir		=		0; 
	//=====
		i_wait_count=       0;	// always 0
		i_frame		=       0;	// always 0
		i_frames	=     10-1; // zero relative
		//===================
		i_wait		=     0;	// number of loops before exec // 0 because color is based on time
		i_frame     =       0;	// fix color to red
	//================
	//  set next value, always NULL
		next_ptr    =   NULL;

		i_object_ID = 0;  // default to zero if not needed
			
 		AI_X = 0;
		AI_Y = 0;

		d_bounce_x = 0;
		d_bounce_y = 0;
		
		OwningPlayerID = 99;
	 }

// Destructor defaults
//    private:
// No copy constructor
      //  wall_list_element(const wall_list_element &);

 
// No assignment operator
      //  wall_list_element operator =(const wall_list_element &);
 //==============================================================
 //==============================================================
 //==============================================================
//1/8/02 public:
 //1/8/02 int rtn_cnt99()
//1/8/02 	{
//1/8/02 			int x;
//1/8/02 			x = ++wall_list_element::i_ball_cnt1;
//1/8/02 			return x;
//1/8/02 	}
//1/8/02 public:
//1/8/02 void set_cnt99()
//1/8/02 	{
//1/8/02 			wall_list_element::i_ball_cnt1 = 0;
//1/8/02 	}
//==============================================================
 //==============================================================
 //==============================================================
public:
 int rtn_obj_id()
	{
		return i_object_ID;
	}
public:
 int rtn_OwningPlayer()
	{
		return OwningPlayerID;
	}
	
 //==============================================================
 //==============================================================
 //==============================================================
 //  free to move to space check 
 //==============================================================
public:
 BOOL occupied_ (double x, double y, wall_list_element *this_element,wall_list_element *first_ptr)
	{
	 // test movement up and to the left
     // Element we are testing
	 wall_list_element *test_element;

	 double xt ,yt ,wt ,ht;    // test element

	 double th;
	 double xtx, yty;
	 double xtx2, yty2;

//		don't wait time finding the sqrt, it is 32
//		xt = sqrt(256); = 32p
//		xt = sqrt((x2-x1)^2+(y2-y1)^2)
		OutputDebugString ("================ \n");

	char      stg[256];

				x = x + 8;
				y = y + 8;

//==== test for x first //=====
     for (	test_element = first_ptr; 
			test_element != NULL; 
			test_element = test_element->next_ptr)
			
			if ( this_element->i_object_ID != test_element->i_object_ID )
				{
				xt = test_element->i_xpos_wall + 8;
				yt = test_element->i_ypos_wall + 8;
				wt = test_element->i_w_wall;
				ht = test_element->i_h_wall;

				xtx = x - xt;
				yty = y - yt;
				xtx2 = xtx*xtx;
				yty2 = yty*yty;

				th =(xtx2 + yty2);

				if (th <= 300)
					{
					sprintf(stg, "IDs ? #1 %i #2 %i \n" + '\0',this_element->i_object_ID,test_element->i_object_ID);
					OutputDebugString (stg);

					sprintf(stg, "did it hit ? xt %fp x %fp yt %fp y %fp\n" + '\0',xt ,x,yt,y);
					OutputDebugString (stg);

					sprintf(stg, "did it hit ? xtx %fp xtx2 %fp yty %fp yty2 %fp dist %fp\n" + '\0',xtx ,xtx2,yty,yty2,th);
					OutputDebugString (stg);

					return true;
					}
				}
	return FALSE; // free to move
	} // end occupied

//////////////////////////////////////////////////////////////////////////////
//Intersect test
//////////////////////////////////////////////////////////////////////////////
//---- this is a good test
bool intersect(RECT recta , wall_list_element *this_element,wall_list_element *first_ptr)
{
     // Element we are testing
	 wall_list_element *test_element;

	 RECT rectb;
	 bool b_hit = false;

     for (	test_element = first_ptr; 
			test_element != NULL; 
			test_element = test_element->next_ptr)
			
			{
			if ( this_element != test_element )
				{
				rectb.top	 = long(test_element->i_ypos_wall);
				rectb.left	 = long(test_element->i_xpos_wall);
				rectb.bottom = long(test_element->i_ypos_wall + test_element->i_h_wall);
				rectb.right	 = long(test_element->i_xpos_wall + test_element->i_w_wall);

				if  (recta.left > rectb.right || rectb.left > recta.right ||
 					 recta.top > rectb.bottom || rectb.top > recta.bottom )
						{
						//return false;
						}
					else
						{
						b_hit = true;

/*						char      stg[256];
						sprintf(stg, "this %d test %d  hit %i \n" + '\0',this_element,test_element,b_hit);
						OutputDebugString (stg);				
						sprintf(stg, "rect a top %i left %i bottom %i right %i \n" + '\0',recta.top,recta.left,recta.bottom,recta.right);
						OutputDebugString (stg);
						sprintf(stg, "rect b top %i left %i bottom %i right %i \n" + '\0',rectb.top,rectb.left,rectb.bottom,rectb.right);
						OutputDebugString (stg);
						sprintf(stg, "high %i wide %i  \n" + '\0',test_element->i_h_wall,test_element->i_w_wall);
						OutputDebugString (stg);
*/
						}
				} // next-loop
			} // end pass_element
	
	return b_hit;
	//return false;// hit no thing (miss)
	//return true; // hit something
} // end occupied
 //==============================================================
 //==============================================================
 //==============================================================
 //  free to move to space check 
 //==============================================================
	// origingal copy below
public:
 BOOL occupied (double x, double y, wall_list_element *this_element,wall_list_element *first_ptr)
	{
	 // test movement up and to the left
     // Element we are testing
	 wall_list_element *test_element;

	 double xt ,yt ,wt ,ht;    // test element

//==== test for x first //=====
     for (	test_element = first_ptr; 
			test_element != NULL; 
			test_element = test_element->next_ptr)
			
			{
			if ( this_element != test_element )
				{
				xt = test_element->i_xpos_wall;
				yt = test_element->i_ypos_wall;
				wt = test_element->i_w_wall;
				ht = test_element->i_h_wall;

				if ( (xt <= x)  &&  (x <= (xt + wt)) )
						{
						//==== y test to //=====
						//=== we have a hit on x if y is good change something
						if ( (yt <= y)  &&  (y <= (yt + ht)) )
									{
									// we have a hit on x and y, something in the way
									return TRUE;  // occupied									
								 	}  	// if
 //==== end y test ========================================================
					 	}  	// if
				} // next-loop
			} // end pass_element
	return FALSE; // free to move
	} // end occupied


//==============================================================
//  adjust_score
//==============================================================
// virtual is needed for multi defines of move
public:
virtual void adj_score(double x,double y, CPlayer &Player1) 
{
}	// end move
//==============================================================
//  move the list
//==============================================================
// virtual is needed for multi defines of move
 private:
virtual void move(wall_list_element *first_ptr, wall_list_element *cur_element, CPlayer &Player1) 
{
	 //i_frame = ((int)(Player1.time_actual - Player1.time_game_start )/1000) % (i_frames+1);
}

//==============================================================
//  return x pos of ball
//==============================================================
 public:
virtual int Return_X()
{
	return -1; // return -1 because your not a ball
}
//==============================================================
//  return y pos of ball
//==============================================================
public:
virtual int Return_Y()
{
	return -1;  // return -1 because your not a ball
}
//==============================================================
//  return x pos of ball
//==============================================================
public:
virtual int Return_XV()
{
	return -1; // return -1 because your not a ball
}
//==============================================================
//  return y pos of ball
//==============================================================
 public:
virtual int Return_YV()
{
	return -1;  // return -1 because your not a ball
}
//==============================================================
//  direction_change the list
//==============================================================
// virtual is needed for multi defines of move
 private:
 virtual void direction_change(wall_list_element *first_ptr, wall_list_element *cur_element, CPlayer &Player1) 

 {
 }	// direction_change
//==============================================================

};	// end class wall_list_element
	// end class wall_list_element
	// end class wall_list_element

//1/8/02 // next line is for static var i_ball_cnt1.	
//1/8/02 	int wall_list_element::i_ball_cnt1 = 0;
