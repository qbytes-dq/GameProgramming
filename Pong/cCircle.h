// cCircle.h

#include <math.h>
//extern int g_i_deg;
/////////////////////////////////
class circle_list_element : wall_list_element
{

private:
	int		i_radius,
			i_degree;
	int		i_center_x,
			i_center_y;
	int		i_delay;
	double	d_xpos,
			d_ypos;
 //===============================================================
public:
circle_list_element(const int i_xpos, const int i_ypos, const int i_rad,int i_deg, LPDIRECTDRAWSURFACE7 &p_dds) :
		   wall_list_element (i_xpos, i_ypos, p_dds)
 {
	 i_radius     = i_rad;
	 i_center_x   = i_xpos;
	 i_center_y   = i_ypos;
	 i_degree	  = i_deg;
	 i_wait       = 0;

	 i_delay = 0;
 }

 //===============================================================
	private:
void move(wall_list_element *first_ptr, wall_list_element *cur_element, CPlayer &Player1) 
 {
	 int temp_deg;

	 //////////////////////////////////
	 if (g_bHostPlayer == true)
			temp_deg = int((int)Player1.time_game_play ) + i_degree;

	 //////////////////////////////////
/*	 if (g_bHostPlayer == true)
		if (Player1.time_game_freq_2 == 0)
			temp_deg = int((int)Player1.time_game_count_22 / 333.3) + i_degree;
		else
			temp_deg = int((int)Player1.time_game_count_22 / 20) + i_degree;
*/
	 //////////////////////////
	 if (g_bHostPlayer == true)
		Player1.i_circle_deg = temp_deg;
	 else
		temp_deg = Player1.i_circle_deg + i_degree;
	  //temp_deg = g_i_deg + i_degree;

//char      stg[256];																//dq001
//sprintf(stg, "cal circle data %i %i %i \n", Player1.i_circle_deg , temp_deg , g_i_deg );
//sprintf(stg, "cal circle data %i %i %i \n", Player1.i_circle_deg , temp_deg);

//OutputDebugString (stg);


	 d_xpos = (i_radius * sin ((temp_deg * 0.017453292) + 1.570796) ) + i_center_x;
	 d_ypos = (i_radius * sin ((temp_deg * 0.017453292) + 3.141592) ) + i_center_y;

	 i_xpos_wall = int (d_xpos);
	 i_ypos_wall = int (d_ypos);

	 if (++i_delay > 4)
		{
 			if (++i_frame > i_frames)
				i_frame = 0;

			i_delay = 0;
		}
 }
/*
  void change_direction(wall_list_element *first_ptr, wall_list_element *cur_element, CPlayer &Player1) 

 {
  }
  */
// Destructor defaults
//    private:
// No copy constructor
   //     circle_list_element(const circle_list_element &); 
// No assignment operator
   //     circle_list_element operator =(const circle_list_element &);
};

	// end class circle_list_element
	// end class circle_list_element
	// end class circle_list_element
	// end class circle_list_element

