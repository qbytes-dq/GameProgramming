// cCircle.h

#include <math.h>
//extern int g_i_deg;
float		sin_table[360];
float		cos_table[360];

/////////////////////////////////
class boom_list_element : wall_list_element
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
boom_list_element(const int i_xpos, const int i_ypos, const int i_rad,int i_deg, LPDIRECTDRAWSURFACE7 &p_dds) :
		   wall_list_element (i_xpos, i_ypos, p_dds)
 {
	 i_radius     = i_rad;
	 i_center_x   = i_xpos;
	 i_center_y   = i_ypos;
	 i_degree	  = i_deg;
	 i_wait       = 0;

	 i_delay = 0;

	 preBuild();		// Pre Build Lookup Table for Sin/Cos
 }

private:

//===============================================================
//TODO 10/31/03 added
void preBuild() 
 {
	int		index;     
	double	pi = 3.14159;
	// here is the speed of the pre build
	for (index = 0; index < 360; index++)
		{
		sin_table[index] = (float)sin(index*pi/180);
		cos_table[index] = (float)cos(index*pi/180);
		}
 }
 //===============================================================
	private:
void move(wall_list_element *first_ptr, wall_list_element *cur_element, CPlayer &Player1) 
 {
	 i_radius+=3;

	 i_xpos_wall = int (i_radius * sin_table[i_degree] ) + i_center_x;
	 i_ypos_wall = int (i_radius * cos_table[i_degree] ) + i_center_y;

	 //if (++i_delay > 2)
	//	{
 			if (++i_frame > i_frames)
				i_frame = 0;

	//		i_delay = 0;
	//	}
 }
 //===============================================================
};
