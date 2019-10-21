////////////////////////////////////////////////////
//Objects with a (0) zero field of view are not allowed to move
//Objects with a (0) zero field of view are not allowed to move
//Objects with a (0) zero field of view are not allowed to move
////////////////////////////////////////////////////


//#define DEBUG

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <Windows.h>

#include <time.h>
#include <mmsystem.h> // timeGetTime
#include <math.h>
//////////
#include <stdio.h>
//----------------------------------------------------------------------------

#include <winuser.h> //  Header: Declared in winuser.h.
////////////////////////////////////////////////////
//
//proto type
//proto type
//proto type

void find_path();
void displayPath();
void displayMap();
void displayMark();
void display_map();



////////////////////////////////////////////////////
#define odd(a)  (  (a)&1  )
#define even(a) (!((a)&1) )

////////////////////////////////////////////////////
enum 
{
	un_explored,
	explored,
	visable
};
////////////////////////////////////////////////////
enum
{
	unknown = -1,
	land0,
	land1,
	land2,
	land3,
	beach,
	water,
	rock,
	gold,
	stone,
	end,
	wall=9995

};
/////////////////////////////////////////////////
enum
{
	neg = -1,
	empty,
	start_path,
	end_path,
	path,
	block=9996
};

////////////////////////////////////////////////////
const int width  = 200;
const int height = 200;

int x,y;

POINT ptStart;
POINT ptEnd;
POINT ptNext;

POINT ptPath[10000];
int	  PathPtNext;

int cx;
int cy;
int nx;
int ny;

bool found;
int lowvalue;

int the_game_map			[width][height];	// the overall map (Master Map)
int currently_visable_map	[width][height];	// what i can currently see
int my_view_map				[width][height];	// what i can and have seen

int  map					[width][height];				// contains map layout
int  mappath				[width][height];				// contains path info
bool mapmark				[width][height];				// contains marked tiles path

////////////////////////////////////////////////////

#include "old_dopathable.h";

////////////////////////////////////////////////////
char wait()
{
	printf("\n\nPress 'q' to quit... any other for next");
	Beep(100,100);
	return getch();
}
/////////////////////////////////////////////////
void build_path()
{

	for ( cy = 0; cy < width; cy++)
		for ( cx = 0; cx < height ; cx++)		
			if (my_view_map[cx][cy] == wall)
				map[cx][cy] = block;
			else
				map[cx][cy] = empty;
}
/////////////////////////////////////////////////
void findstart()
{
	for ( cy = 0 ; cy < height ; cy++)
		for ( cx = 0 ; cx < width ; cx++)		
			if (map[cx][cy] == start_path)
			{
				ptStart.x = cx ;
				ptStart.y = cy ;
				break;
			}
}
/////////////////////////////////////////////////
void findend()
{
	for ( cy = 0 ; cy < height ; cy++)
		for ( cx = 0 ; cx < width ; cx++)		
			if (map[cx][cy] == end_path)
			{
				ptEnd.x = cx;
				ptEnd.y = cy;
			}
}
/////////////////////////////////////////////////
void displayMap()
{
printf("Map\n");

for (x = 0; x < width/10;x++)
	printf("....+....X");

	for ( cy = 0 ; cy < height ; cy++)
	{
		printf("\n");
		for ( cx = 0 ; cx < width ; cx++)		
			printf("%i\t",map[cx][cy]);
	}
}
/////////////////////////////////////////////////
void displayPath()
{
	printf("\n\nPath\n");

	for (x = 0; x < width/10;x++)
		printf("....+....X");

	for ( cy = 0 ; cy < height ; cy++)
	{
		printf("\n");
		for ( cx = 0 ; cx < width ; cx++)		
			printf("%i\t",mappath[cx][cy]);
	}
}
/////////////////////////////////////////////////
void displayMark()
{
	printf("\n\nMark\n");

	for (x = 0; x < width/10;x++)
		printf("....+....X");


	for ( cy = 0 ; cy < height ; cy++)
	{
		printf("\n");
		for ( cx = 0 ; cx < width ; cx++)		
			printf("%i",mapmark[cx][cy]);
	}
}

/////////////////////////////////////////////////
void dopathsetup()
{
    for ( cy = 0 ; cy < height; cy++)
		for ( cx = 0 ; cx < width; cx++)
			switch(map[cx][cy])
				{
				case start_path:
					{
						mappath[cx][cy]=0;
					}break;
				case block:
					{
						mappath[cx][cy]=9999;
					}break;
				case empty:
					{
						mappath[cx][cy]=neg;
					}break;
				default:
					{
						mappath[cx][cy]=neg;
					}break;
				}			
}
///////////////////////////////////////////
///////////////////////////////////////////
///////////////////////////////////////////
	POINT	LoopArray [10000];
	POINT	LoopNext  [10000];
	int		LookUp;
	int		LookNext;
	int		Loop;
	bool	DestFound;
	int		Depth;
	bool	Done;
///////////////////////////////////////////
void dopathable_cell_check(int TestX, int TestY)
{

	int MapX = TestX + LoopArray[Loop].x;
	int MapY = TestY + LoopArray[Loop].y;

#ifdef DEBUG
	POINT tmp1 = LoopArray[Loop];
	int   tmp2 = mappath[TestX][TestY];
	int   tmp3 = mappath[MapX][MapY];
#endif

//  Next 2 lines not needed if outside is 9998 to block off board test
//	if (MapX >= 0 && MapY >= 00 &&
//		MapX < width && MapY < height)
			if (mappath[MapX][MapY] == -1)
				{
				//Add block to the Next set of tile tests
				LookNext++;	
				LoopNext[LookNext] = LoopArray[Loop];
				LoopNext[LookNext].x += TestX; 
				LoopNext[LookNext].y += TestY;

				//Set current tile to current + 1
				mappath[MapX][MapY] = mappath[LoopArray[Loop].x][LoopArray[Loop].y] + 1;

				// did we find the last tile yet?
				if (mappath[ptEnd.x][ptEnd.y] != -1)
					DestFound = true;
				}
}
/////////////////////////////////////////////////
void dopathable2()
{
	DWORD time_start = timeGetTime();

	Depth		= 0;
	Done		= false;
	DestFound	= false;	

	// set map up as all hidden
	for( cx = 0 ; cx < width; cx++)
		for( cy = 0 ; cy < height; cy++)
			mapmark[cx][cy]=false;

	// set map edges as unreachable
	for( cx = 0 ; cx < width-1; cx++)
		{
		mappath[cx][0]			=9998;
		mappath[0][cx]			=9998;
		mappath[cx][width-1]	=9998;
		mappath[height-1][cx]	=9998;
		}
	mappath[height-1][height-1]	=9998;

	// Setup for Map review
	LoopArray[0] = ptStart;
	LookUp = 0;
	Depth = 0;
	while (!Done)
		{
		Depth++;
		LookNext = -1;
		// find all cells ready for pathing
		for (Loop = LookUp; Loop >= 0; Loop--)
			{
			dopathable_cell_check(-1, -1);	// up left
			dopathable_cell_check(-1,  0);	// up center
			dopathable_cell_check(-1, +1);	// up right

			dopathable_cell_check(+1, -1);	// down left
			dopathable_cell_check(+1,  0);	// down center
			dopathable_cell_check(+1, +1);	// down right

			dopathable_cell_check( 0, -1);	// Left
			dopathable_cell_check( 0, +1);	// Right
		  //dopathable_cell_check( 0, 0);	// Don't do myself
			}
		// Setup for next lookup
		LookUp = LookNext;
		for (Loop = 0; LookUp >= Loop; Loop ++)
			LoopArray[Loop] = LoopNext[Loop];

		if (LookUp < 0 || DestFound)
			Done = true;
		}

	//if (mappath[ptEnd.x][ptEnd.y] != -1)
	for (x = 0; x < width-1;x++)
		for (y = 0 ; y < height-1; y++)
			if (mappath[x][y] == -1)
				mappath[x][y] = 9997;

	DWORD time_end = timeGetTime();
	printf("\n dopathable %d",time_end - time_start);
//displayPath();
//wait();
}

/////////////////////////////////////////////////
void dopathback()
{
//	if(mappath[ptEnd.x][ptEnd.y]!=-1)
	if(mappath[ptEnd.x][ptEnd.y] < 9000)
		{		
		ptNext=ptEnd;
		lowvalue=mappath[ptEnd.x][ptEnd.y];

		ptPath[PathPtNext++] = ptEnd;
		
		while(lowvalue > 0)
			{
			found=false;			
			do
				{
				do
					{
					nx=rand()%3-1;
					ny=rand()%3-1;
					}				
					while(  ( nx==0 && ny==0)			||
							( ptNext.x + nx) <	0		|| 
							( ptNext.x + nx) >= width	||
							( ptNext.y + ny) <	0		|| 
							( ptNext.y + ny) >= height );

							if(mappath[ptNext.x + nx][ptNext.y + ny] < lowvalue)
								{
								found=true;
								map[ptNext.x][ptNext.y] = path;
								ptNext.x += nx;
								ptNext.y += ny;
								lowvalue = mappath[ptNext.x][ptNext.y];

								mapmark[ptNext.x][ptNext.y]=true;
								ptPath[PathPtNext++] = ptNext;
								}

				//displayPath();
				//displayMap();
				//displayMark();
				//display_map();		// print map

				}while(!found);
			}

		map[ptEnd.x][ptEnd.y]=end;

		ptPath[PathPtNext].x = -1;  // show end of list
		ptPath[PathPtNext].y = -1;	// show end of list

		PathPtNext--;	// move prior to end of list
		}
	else
		{
		// Dest not reached
		printf("\nDestination unreachable....");
		Beep(500,200);
		printf("\nDestination unreachable....");
		Beep(800,200);
		printf("\nDestination unreachable....");
		Beep(1000,600);
		}
}
/////////////////////////////////////////////////
void find_path()
{
	//DWORD time_start;
	//DWORD time_end;

	PathPtNext = 0;
	ptPath[PathPtNext].x = -1;	// show end of list
	ptPath[PathPtNext].y = -1;	// show end of list

	build_path();

	map[ptStart.x][ptStart.y] = start_path;	
	map[ptEnd.x][ptEnd.y] = end_path;

	findstart();
	findend();

	// do we have a start and a end point
	if (ptStart.x != -1 || ptEnd.x != -1)
	{
		dopathsetup();
		dopathable2();
		dopathback();

		//displayPath();
	}
}
////////////////////////////////////////////////////
void build_map()
{

	// place objects on map
	for (y = 0; y <height; y++)
		for (x = 0; x < width; x++)
			{
			the_game_map[x][y] = rand()%end;
			my_view_map[x][y] = unknown;
			}
/*
	// install a big wall
	for ( x = 0 ; x < width ; x++)
		{
		the_game_map[x][10]=wall;
		}

	// install a big wall
	for ( x = 3 ; x < 20 ; x++)
		for (y = 3 ; y < 7 ; y++)
		{
		the_game_map[y][x]=wall;
		the_game_map[x][y]=wall;
		}

	
	// install walls
	for (x = 0;x < width -10;x++)
		{
		the_game_map[x][10]  =wall;
		the_game_map[x][30]  =wall;
		the_game_map[x][50]  =wall;
		the_game_map[x][70]  =wall;
		the_game_map[x][90]  =wall;
		}

	for (x = width;x > 10;x--)
		{
		the_game_map[x][20]  =wall;
		the_game_map[x][40]  =wall;
		the_game_map[x][60]  =wall;
		the_game_map[x][80]  =wall;
		the_game_map[x][100] =wall;
		}
*/

	// install walls
	for (y = 0;y < height-10;y++)
		{
		the_game_map[10][y]  =wall;
		the_game_map[30][y]  =wall;
		the_game_map[50][y]  =wall;
		the_game_map[70][y]  =wall;
		the_game_map[90][y]  =wall;
		}

	for (y = height;y > 10;y--)
		{
		the_game_map[20][y]  =wall;
		the_game_map[40][y]  =wall;
		the_game_map[60][y]  =wall;
		the_game_map[80][y]  =wall;
		the_game_map[100][y] =wall;
		}

/*
	// split bottom
	for ( x = 30 ; x < width +1 ; x++)
		for (y = 24 ; y < 28 ; y++)
		{
		the_game_map[y][x]=wall;
		the_game_map[x][y]=wall;
		}

	// install a big block
	for (x = 22; x < 29; x++)
		for (y = 22; y < 29 ; y++)
			the_game_map[x][y] = wall;
*/
	for (x = 0; x < 11; x++)
			the_game_map[x][22] = wall;

}
////////////////////////////////////////////////////
void init_view()
{
	for (y = 0; y <height; y++)
		for (x = 0; x < width; x++)
			currently_visable_map[x][y] = false;
}
////////////////////////////////////////////////////
void init_view_all()
{
	for (y = 0; y <height; y++)
		for (x = 0; x < width; x++)
			{
			currently_visable_map[x][y] = true;
			my_view_map[x][y] = the_game_map[x][y];
			}
}
////////////////////////////////////////////////////
void print_map_org(int x, int y, char c[2])
{
	// 46 = '.' 32 = ' '
	int asc = *c;

	if (!currently_visable_map[x][y])
		asc = 176;	

	printf("%c", asc);
}
////////////////////////////////////////////////////
void print_map(int x, int y, char c[2])
{
	int asc = *c;

	if (currently_visable_map[x][y])
		{}// ok the way it is
	else
		// force lower case
		asc+= 32;

	// show as fog
	if (asc == 64)
		asc = 176;

	printf("%c", asc);
}
////////////////////////////////////////////////////
void display_map()
{
	printf("\nDisplay Map:\n  ");

	for (x = 0; x < width/10;x++)
		printf("....+....X");

	for (y = 0; y < height; y++)
		{
		printf("\n");

		if ((y+1)%10 == 0)
			printf(" X");
		else
			if ((y+1)%5 == 0)
				printf(" +");
			else
				printf(" .");


		for (x = 0; x < width; x++)
			{
			//switch(the_game_map[x][y])
			switch(my_view_map[x][y])
				{
				case unknown:
					print_map(x,y," ");
					break;
				case land0:
				case land1:
				case land2:
				case land3:
					print_map(x,y,"L");
					break;
				case beach:
					print_map(x,y,"B");
					break;
				case water:
					print_map(x,y,"A");
					break;
				case rock:
					print_map(x,y,"R");
					break;
				case gold:
					print_map(x,y,"G");
					break;
				case stone:
					print_map(x,y,"S");
					break;
				case wall:
					print_map(x,y,"W");
					break;
				}
		}
	}
}
////////////////////////////////////////////////////
void fov_set(int fx, int fy)
{
	// make sure it is on the map
	if (fx >= 0 && fx < width && fy>=0 && fy < height)
		{
		// set visable
		currently_visable_map[fx][fy] = true;
		my_view_map[fx][fy] = the_game_map[fx][fy];
		}
}

////////////////////////////////////////////////////
void fov_rec(int fx,int fy, int v, int w, int h)
{	// recursion till fov complete when v = 1
	// set tiles visable

	for (x = fx - w; x <= fx + w; x++)
		{
		fov_set(x,fy+v);
		fov_set(x,fy-v);
		}

	// are we done
	if (v==1)
		return;  // yes, quit
	else
		{		// not, do it again
		if (v > h)
			w++;

		fov_rec(fx,fy,--v,w,h);	// do it again
		}
}
////////////////////////////////////////////////////
void fov(int fx,int fy, int v)
{
	if (v > 1) // sight range > 1
		{
		// set tiles visable
		for (x = fx - v; x <= fx + v; x++)
			{
			fov_set(x,fy);
			}	

		int w = (int)((v/2)+0.5);
		int h = (int)((v/2)+0.5);
		fov_rec(fx,fy, v, w, h );
		}
	else
		if (v == 1) // sight range = 1 --- set tiles visable
			{
			for (x = fx - 1; x <= fx + 1; x++)
				{
				fov_set(x,fy-1);
				fov_set(x,fy);
				fov_set(x,fy+1);
				}	
			}
		else
			if (v == 0) // sight range = 0
				{
				fov_set(fx,fy);
				return;
				}
			else // sight range < 0 -- don't do a thing
				return;
}

////////////////////////////////////////////////////
void main()
{

srand( (unsigned)time( NULL ) );
int unitFOV = 3;
int atempts = 0;

printf("Fog Of War Map:");
build_map();		// map


DWORD time_start;
DWORD time_end; 
DWORD time_used;

do
	{
	time_start = timeGetTime();
	/////////////////////////////////////////////////////////////
	//start at dead zone
	//ptStart.x	= 5;
	//ptStart.y	= 5;

	//start ok top
	//ptStart.x	= 2;
	//ptStart.y	= 2;

	//start ok bottom
	ptStart.x	= width  - 3;
	ptStart.y	= height - 3;

	// End Point bottom
	//ptEnd.x		= width  -2;
	//ptEnd.y		= height -2;

	// End Point 1/2 waybottom
	//ptEnd.x		= width  /2;
	//ptEnd.y		= height / 2;

	// End Point top
	ptEnd.x		= 3;
	ptEnd.y		= 3;

	int x_blocked = 0;

	find_path();

	// move on the map
	while (PathPtNext != 0)
		{
		init_view();	// all fogged

		fov(ptPath[PathPtNext].x , ptPath[PathPtNext].y ,unitFOV);

		if ( my_view_map[ ptPath[PathPtNext - 1].x][ ptPath[PathPtNext - 1].y ] == wall)
			{
			// set new start point
			ptStart = ptPath[PathPtNext];
/*
			printf("\n \t\t Block at x %i y %i current tile %i block %i new start x %i y %i PathPtNext %i",
						ptPath[PathPtNext - 1].x , 
						ptPath[PathPtNext - 1].y , 
						my_view_map[ ptPath[PathPtNext].x][ ptPath[PathPtNext].y ],
						block,
						ptStart.x,
						ptStart.y,
						PathPtNext);
*/
			// find new path to way point
			PathPtNext++;
			find_path();
			x_blocked++;
			}
		if (PathPtNext !=0)
			PathPtNext--;	
		}

	time_end = timeGetTime();
	time_used = time_end - time_start;

	/////////////////////////////////////////////////////////////q
	display_map();						// print map
	printf("\n Number of Blocked paths %i elap %d time/frame %i",
									   x_blocked, 
											   time_used, 
															 1000/30);

	printf("\n pre block %d",time_used/++x_blocked,PathPtNext);

	printf ("\n Atempts %i",++atempts); // number of times displaying map.
	} while (wait() != 'q');			// wait for quit

init_view_all();	// no fog
display_map();		// print map
wait();				// wait for quit
}
