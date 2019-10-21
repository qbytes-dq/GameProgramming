//-----------------------------------------------------------------------------			 
// Direct Draw
//-----------------------------------------------------------------------------			 
LPDIRECTDRAW7               g_pDD		  = NULL;  // DirectDraw object
LPDIRECTDRAWSURFACE7        g_pDDSPrimary = NULL;  // DirectDraw primary surface
LPDIRECTDRAWSURFACE7        g_pDDSBack	  = NULL;  // DirectDraw back surface
LPDIRECTDRAWSURFACE7        g_pDDSminimap  = NULL;  // Offscreen surface 2
LPDIRECTDRAWSURFACE7        g_pDDSwall    = NULL;  // Offscreen surface 4
LPDIRECTDRAWSURFACE7        g_pDDSpaddle_V  = NULL;  // Offscreen surface 5
LPDIRECTDRAWSURFACE7        g_pDDSpaddle_H  = NULL;  // Offscreen surface 5
LPDIRECTDRAWSURFACE7        g_pDDScell1    = NULL;  // Offscreen surface
LPDIRECTDRAWSURFACE7        g_pDDSabc	   = NULL;  // Offscreen surface
LPDIRECTDRAWSURFACE7        g_pDDSexe_line = NULL;  // Offscreen surface
LPDIRECTDRAWSURFACE7        g_pDDSinterface = NULL;  // Offscreen surface

LPDIRECTDRAWPALETTE         g_pDDPal	  = NULL;  // The primary surface palette

#include <string.h>
#include <wchar.h>
#include <math.h>

#include "ddutil.h"

#include "Enumerations.h"

extern bool b_intro;	//DQ006


//-----------------------
// Local definitions
//-----------------------
#define NAME                "Pong"
#define TITLE               "Pong - By QBytesWorld"
#define x_wide		37
#define y_high		37
#define mini_div	5/16   ///it's faster to mult than div //////sync with mini_size
#define mini_size   5
#define mini_x		600	
#define mini_y		414


#define screen_wide 592
#define screen_high 592

#define	black			0
#define	red				249
#define	orange			295
#define	yellow			251 
#define green			250 
#define	green_mustard	3
#define	blue			252
#define	purple			253
//#define	teal		 6
#define	gray			7 
#define	brown			293
#define	lt_blue			10
#define white			255
#define teal			191
//-----------------------------------------------------------------------------
// Local data
//-----------------------------------------------------------------------------
// Name of our bitmap resource.
static char					szMINIMAP[]  = "MINIMAP";
static char					szWALL[]	 = "WALL";
static char					szPADDLE_V[] = "PADDLE_V";
static char					szPADDLE_H[] = "PADDLE_H";
static char					szCELL1[]    = "CELL1";
static char					szABC[]      = "ABC";
static char					szEXELINE[]  = "EXE_LINE";
static char					szINTERFACE[] = "INTERFACE";

static DWORD  dwFrameCount, dwFrameTime, dwFrames, dwFramesLast , bltScore;
int cells [x_wide][y_high];

//-----------------------------------------------------------------------------
// external data
//-----------------------------------------------------------------------------

//bool g_bBackGround;
extern HWND    g_hDlg;
extern bool g_bHostPlayer;
extern bool g_bLostFocus;
extern int	g_iScoreOut;
DDSURFACEDESC2              g_ddsd;

extern bool g_Full_Screen;
extern int	g_Resolution;

//bool FullScreenFlag = false;
int Height, Width;


//-----------------------------------------------------------------------------
// DAQ Temp Global variables
//-----------------------------------------------------------------------------

extern int		draw_item_num;
extern double	draw_x;
extern double	draw_x_dir;
extern double	draw_y;
extern double	draw_y_dir;
extern int		draw_obj_ID;
extern int		draw_wait_cnt;

enum eAcrossDown
   {
      Across,
      Down
   };

enum COLOR_TYPE 
	{
		_5x5x5_,
		_5x6x5_
	};

class CTest
{
public:
    CTest(){};
    ~CTest(){};
    const char *ShowReason() const { return "Exception in CTest class."; }

};

//-----------------------------------------------------------------------------
// Name: ReleaseAllObjects()
// Desc: Finished with all objects we use; release them
//-----------------------------------------------------------------------------
static void
ReleaseAllObjects(void)
{
    if (g_pDD != NULL)
    {
        if (g_pDDSPrimary != NULL)
			{
            g_pDDSPrimary->Release();
            g_pDDSPrimary = NULL;
			}

		//daq next 7 lines

        if (g_pDDSminimap != NULL)
			{
            g_pDDSminimap->Release();
            g_pDDSminimap = NULL;
			}

        if (g_pDDSwall != NULL)
			{
            g_pDDSwall->Release();
            g_pDDSwall = NULL;
			}

        if (g_pDDSpaddle_V != NULL)
			{
            g_pDDSpaddle_V->Release();
            g_pDDSpaddle_V = NULL;
			}

        if (g_pDDSpaddle_H != NULL)
			{
            g_pDDSpaddle_H->Release();
            g_pDDSpaddle_H = NULL;
			}

        if (g_pDDScell1 != NULL)
			{
            g_pDDScell1->Release();
            g_pDDScell1 = NULL;
			}

        if (g_pDDSabc != NULL)
			{
            g_pDDSabc->Release();
            g_pDDSabc = NULL;
			}

        if (g_pDDSexe_line != NULL)
			{
            g_pDDSexe_line->Release();
            g_pDDSexe_line = NULL;
			}

		if (g_pDDSinterface != NULL)
			{
            g_pDDSinterface->Release();
            g_pDDSinterface = NULL;
			}

        if (g_pDDPal != NULL)
			{
            g_pDDPal->Release();
            g_pDDPal = NULL;
			}

        g_pDD->Release();
        g_pDD = NULL;
    }
}

//-----------------------------------------------------------------------------
// Name: InitFail()
// Desc: This function is called if an initialization function fails
//-----------------------------------------------------------------------------
HRESULT
InitFail(HWND hWnd, HRESULT hRet, LPCTSTR szError,...)
{
    char                        szBuff[128];
    va_list                     vl;

    va_start(vl, szError);
    vsprintf(szBuff, szError, vl);
    ReleaseAllObjects();
    MessageBox(hWnd, szBuff, TITLE, MB_OK);
    DestroyWindow(hWnd);
    va_end(vl);
    return hRet;
}  // end function


//-----------------------------------------------------------------------------
// Name: RestoreAll()
// Desc: Restore all lost objects
//-----------------------------------------------------------------------------
HRESULT 
RestoreAll(void)
{
    HRESULT                     hRet;

    hRet = g_pDDSPrimary->Restore();
    if (hRet == DD_OK)
    {

// MINIMAP
        hRet = g_pDDSminimap->Restore();
        if (hRet == DD_OK)
        {
            DDReLoadBitmap(g_pDDSminimap, szMINIMAP);
        }
// WALL
        hRet = g_pDDSwall->Restore();
        if (hRet == DD_OK)
        {
            DDReLoadBitmap(g_pDDSwall, szWALL);
        }
// PADDLE_V
        hRet = g_pDDSpaddle_V->Restore();
        if (hRet == DD_OK)
        {
            DDReLoadBitmap(g_pDDSpaddle_V, szPADDLE_V);
        }
// PADDLE_H
        hRet = g_pDDSpaddle_H->Restore();
        if (hRet == DD_OK)
        {
            DDReLoadBitmap(g_pDDSpaddle_H, szPADDLE_H);
        }
// CELL 1
        hRet = g_pDDScell1->Restore();
        if (hRet == DD_OK)
        {
            DDReLoadBitmap(g_pDDScell1, szCELL1);
        }
// ABC
        hRet = g_pDDSabc->Restore();
        if (hRet == DD_OK)
        {
            DDReLoadBitmap(g_pDDSabc, szABC);
        }
// EXELINE
        hRet = g_pDDSexe_line->Restore();
        if (hRet == DD_OK)
        {
            DDReLoadBitmap(g_pDDSexe_line, szEXELINE);
        }
// INTERFACES
        hRet = g_pDDSinterface->Restore();
        if (hRet == DD_OK)
        {
            DDReLoadBitmap(g_pDDSinterface, szINTERFACE);
        }

    }
    return hRet;
}  // end function

//======================================
// x y display char
//======================================
void
xyDisplayChar ( int i_asc, int x_pos, int y_pos, bool b_clear)
{
	RECT                        rcRect;
	HRESULT                     hRet;

	if (i_asc < 0 )
		return;
	if (i_asc >37 )
		return;

	// Blit the stuff for the next frame
	rcRect.left   = i_asc % 10 * 16;
	rcRect.top    = i_asc / 10 * 16;
	rcRect.right  = rcRect.left + 15;
	rcRect.bottom = rcRect.top  + 15; 

	if (b_clear)
		hRet = g_pDDSBack->BltFast(x_pos,
								   y_pos,
								   g_pDDSabc,	
								   &rcRect,
								   DDBLTFAST_SRCCOLORKEY);
	else
		hRet = g_pDDSBack->BltFast(x_pos,
								   y_pos,
								   g_pDDSabc,	
								   &rcRect,
								   DDBLTFAST_NOCOLORKEY);	   // no hide of bit map color x
}  // end function
//===================================================
//  display text Across screen
//===================================================
void 
xyDisplayAcross( char *buff, int x, int y ,bool b_clear,int across_down)
{	
char *chr;
int  i_asc;
	for ( chr = buff;
		 *chr != '\0';
		  chr++)
		  {
				i_asc = *chr - '0';	

				if (i_asc <= 10 )
						{
						if (i_asc == -2)		// it's a period
							{
							xyDisplayChar( 37 , x, y,b_clear);
							//x -=13;
							}
						else					
						if (i_asc == -3)		// it's a minus sign
							{
							xyDisplayChar( 36 , x, y,b_clear);
							//x -=13;
							}
						else					// it's a number
							xyDisplayChar(i_asc, x, y,b_clear);
						}
					else
						{						// it's a letter
						i_asc = *chr - 'A' + 10;
						xyDisplayChar( i_asc , x, y,b_clear);
						}
			if (across_down == Across)
				x += 15;
				else
				y+=15;
		  }  // end for loop

}  // end function

//=============================================================================
// Display String
//=============================================================================
void 
xyDisplayString(char *buff,
			  double dwNumber,
			  int show_whole, 
			  int show_decimal,
			  int across_down,
			  int across,
			  int down,
			  bool b_clear)
{
//passed in

//char buf[50] = "";

//int show_whole	= 15;	// max is 20 before errors
//int show_decimal = 9;		// max is 8 before errors (mostly rounding)
//double dwNumber = 123456.987654321;
double dwRemainder;
double iNumber;

// calc and used in function
char *pbuf ;
double	rem;
pbuf = buff;

int z;
double div;

// make sure we weren't passed nothing
//	z = int(strlen( buff ));
//	if (int(strlen( buff ) == 0))
//		strcpy(buff, "EMPTY ");

// skip to end of string past to us
for (z=0 ; z < int(strlen( buff )) ; z++)
	pbuf++;

if (dwNumber < 0)
	{
	dwNumber *= -1;
	pbuf[0] = '-';
	pbuf++;
	}
	else
	{
	pbuf[0] = ' ';
	pbuf++;
	}

iNumber = (double)((__int64) dwNumber);
dwRemainder = (dwNumber - iNumber) + 0.00000000001;
dwNumber = (double)iNumber;		

div = pow( 10, (double)show_whole );; // the divider

// eztract whole numbers
	for (z=0;z<show_whole;z++)
		{
		rem = (DWORD)dwNumber % (DWORD)div;
		div /= 10;
		pbuf[0] = (char)(rem/div) + '0';
		pbuf++;
		}

// eztract decimal numbers, if requested
	if (show_decimal > 0)
		{
		pbuf[0] = '.';
		pbuf++;
		dwNumber = dwRemainder * (pow (10,9));			
		div = pow( 10, (double)9 );; // the divider

		for (z=0;z<show_decimal;z++)
			{
			rem = (DWORD)dwNumber % (DWORD)div;
			div /= 10;
			pbuf[0] = (char)(rem/div) + '0';
			pbuf++;
			}
		}
    pbuf[0] = '\0';

	xyDisplayAcross( buff, across, down , b_clear, across_down);
//	if (across_down == Across)
//		xyDisplayAcross( buff, across, down , b_clear);
//	else
//		xyDisplayDown( buff, across, down , b_clear, Across);

}
//=============================================================================
// Display String
//=============================================================================
void 
xyDisplayLONGLONG(char *buff,
			  LONGLONG dwNumber,
			  int across_down,
			  int across,
			  int down,
			  bool b_clear,
			  CPlayer &Player1)
{

// calc and used in function
char *pbuf ;
DWORD	rem;
pbuf = buff;

int z;
DWORD div;

// skip to end of string past to us
for (z=0 ; z < int(strlen( buff )) ; z++)
	pbuf++;

div = 100000000;
Player1.dwHigh = (DWORD)(dwNumber / div);
Player1.dwLow  = (DWORD)(dwNumber - (Player1.dwHigh * div)); 

	for (z=0;z<8;z++)
		{
		rem = (DWORD)(Player1.dwHigh % div);
		div /= 10;
		pbuf[0] = (char)(rem/div) + '0';
		pbuf++;
		}

	div = 100000000;

	for (z=0;z<8;z++)
		{
		rem = (DWORD)(Player1.dwLow % div);
		div /= 10;
		pbuf[0] = (char)(rem/div) + '0';
		pbuf++;
		}

    pbuf[0] = '\0';

	xyDisplayAcross( buff, across, down , b_clear, across_down);
}
//======================================
// Cell Set
//======================================
void
CellSet()
{int x,y;
	for (	x = 0; 	x < x_wide; x +=1) 
	{
		for ( y = 0;	y < y_high;	y +=1)
			{
				//cells [x][y] = 20; // open field
				cells [x][y] = 22; // open field
			}   // end y loop
	}	// end x loop
}  // end function
//======================================
// Cell Set
//======================================
void
CellSet1()
{
	enum ground{net = 0,
			angel_bl,
			angel_br,
			angel_tl,
			angel_tr,
			line_dw_left,
			line_ac_top,
			line_ac_bot,
			line_dw_right,
			diag_l_r,
			diag_r_l,
			tl_fld,
			bl_fld,
			tr_fld,
			br_fld,
			the_fld,
			left_the_fld,
			bottom_the_fld,
			top_the_fld,
			right_the_fld,
			the_goal_fld};

	int x,y;

	// display net
	for (	x = 5; 	x < 32; x++) 
		for ( y = 1 ; y < 5; y++)
		{
			cells [x][y] = net;
			cells [y][x] = net;
			cells [x][36-y] = net;
			cells [36-y][x] = net;
		}	// end x loop


	// display goal line left&right
	for (	x = 6; 	x < 31; x++) 
		{
			y = 5;
			cells [x][y] = line_ac_top;
			cells [y][x] = line_dw_left;
			cells [x][36-y] = line_ac_bot;
			cells [36-y][x] = line_dw_right;
		}	// end x loop


	// display net
	for (	x = 5; 	x < 32; x++) 
		for ( y = 1 ; y < 5; y++)
		{
			cells [x][y] = net;
			cells [y][x] = net;
			cells [x][36-y] = net;
			cells [36-y][x] = net;
		}	// end x loop


// corner of goals
	cells [31][31] = angel_br;
	cells [5][5]   = angel_tl;
    
	cells [5][31]  = angel_bl;
	cells [31][5]  = angel_tr;

// display field in front of net
	for (	x = 6; 	x < 31; x++) 
		for ( y = 6 ; y < 9; y++)
		{
			cells [x][y] = the_fld;
			cells [y][x] = the_fld;
			cells [x][36-y] = the_fld;
			cells [36-y][x] = the_fld;
		}	// end x loop

// diag in front of goal net
	cells [6][6]   = diag_r_l;
	cells [30][30] = diag_r_l;
	cells [7][7]   = diag_r_l;
	cells [29][29] = diag_r_l;
	cells [8][8]   = diag_r_l;
	cells [28][28] = diag_r_l;

	cells [6][30] = diag_l_r;
	cells [30][6] = diag_l_r;
	cells [7][29] = diag_l_r;
	cells [29][7] = diag_l_r;
	cells [8][28] = diag_l_r;
	cells [28][8] = diag_l_r;

// display field line in front of net
	for (	x = 9; 	x < 28; x++) 
		for ( y = 9 ; y < 10; y++)
		{
			cells [x][y] = top_the_fld;//top
			cells [y][x] = left_the_fld;//left
			cells [x][36-y] = bottom_the_fld;//bottom
			cells [36-y][x] = right_the_fld;//right
		}	// end x loop

// fill the field corners
	cells [9][9] = tl_fld;
	cells [9][27] = bl_fld;
	cells [27][9] = tr_fld;
	cells [27][27] = br_fld;

}  // end function
//==============================================================
// Draw an item
//==============================================================
void
DisplayCells(CPlayer &Player1)
{
//1024 = 64 x 48
// 800 = 50 x 37.5
// 640 = 40 x 30
// Blit the stuff for the next frame
//RECT                        rcRectPre;
//rcRectPre.left   = (int)((cells[1][1] % 10 * 16) );
//rcRectPre.top    = (int)((cells[1][1] / 10 * 16) );
//rcRectPre.right  = rcRectPre.left + 16;
//rcRectPre.bottom = rcRectPre.top  + 16; 
//bool Changed;

RECT                        rcRect;
HRESULT                     hRet;
int x, y;

for (	x = 0; x < x_wide; x++) 
	{for ( y = 0;  y < y_high;y++)
		{
		//Changed = true;
		int xt;
		int yt;
		int LL = 0;								// left
		int LR = 16;			// right
		int LT = 0;								// top
		int LB = 16;			// bottom

		if (Player1.b_focus_on_ball)
			{
				xt = (x*16) - (int)draw_x + (296);	//592/2
				yt = (y*16) - (int)draw_y + (296);	//592/2
			}
		else
			{
				xt = (x*16);
				yt = (y*16);
			}

		// only display if in pan
		if (xt > -16 && xt < (592) && yt > -16 && yt < (592))
			{
			//=====================
			// left
			if ( xt < 0)
			{
				LL -=xt;
				xt = 0;
				//Changed = true;
			}
			else
			// right
			if (xt + 16 > 592)
			{
				LR=592-xt;
				//Changed = true;
			}

			//=====================

			// top
			if (yt < 0)
			{
				LT -=yt;
				yt = 0;
				//Changed = true;
			}
			else
			//bottom
			if (yt + 16 > 592)
			{
				LB = 592 - yt;
				//Changed = true;
			}
			//==============================================================
				// Blit the stuff for the next frame ( FULL SCREEN)
//			if (Changed)	
//				{
				rcRect.left   = (int)((cells[x][y] % 10 * 16) + LL);
				rcRect.top    = (int)((cells[x][y] / 10 * 16) + LT);
				rcRect.right  = (int)((cells[x][y] % 10 * 16) + LR);
				rcRect.bottom = (int)((cells[x][y] / 10 * 16) + LB);
		
				hRet = g_pDDSBack->BltFast(xt,
											yt,
											g_pDDScell1,		//g_pDDSwall.  //
											&rcRect,
											DDBLTFAST_NOCOLORKEY);	   // no hide of bit map color x
//				}
//				else
//				{
//				hRet = g_pDDSBack->BltFast(xt,
//											yt,
//											g_pDDScell1,		//g_pDDSwall.  //
//											&rcRectPre,
//											DDBLTFAST_NOCOLORKEY);	   // no hide of bit map color x	
//				}
			}	// end 'in pan view'
		}  // end y loop
	}  // end x loop
}	// end function

//=============================================================================
// Display the Mini Map
//=============================================================================
void 
DisplayMiniMapTest(CPlayer &Player1)
{
///////////////////
HWND              hWnd = NULL;
RECT              rcRect;
HRESULT           hRet;
DDSURFACEDESC2    ddsd;
BYTE              *dest;
int               x, y;

ddsd = g_ddsd;

// First, clear the primary surface to white using Lock and Unlock
// to directly access surface memory

// Lock the primary surface
	if FAILED( g_pDDSminimap->Lock( NULL, &ddsd, DDLOCK_WAIT , NULL ) )
		{
			HDC hdc;
			int     offset = 0;
			TCHAR   strBuf[256];
			//uses	wprintf <stdio.h> or <wchar.h> 
			offset = wsprintf(strBuf, "Couldn't lock the surface." );

		   if (g_pDDSBack->GetDC(&hdc) == DD_OK) // must be locked
				{ 
				//SetBkMode (hdc,TRANSPARENT );
				SetBkColor(hdc, RGB(255, 0, 0)); 
				SetTextColor(hdc, RGB(255, 255, 0)); 
				TextOut(hdc, 0, 0,strBuf, offset); 
				g_pDDSBack->ReleaseDC(hdc); 
				}
		} // end lock

// Clear it to white
// We are assuming: 
// 1) we are palettized, so each pixel is represented by a "byte" 
// 2) since we are not setting a new palette, entry 255 should be white.


dest = (BYTE *)ddsd.lpSurface;
//    for ( y = 0; y < (int) ddsd.dwHeight ; y++ ) 
//		{
//			for ( x = 0; x < (int) ddsd.dwWidth ; x++ ) 
//				{
for ( y = 0; y < x_wide*2 ; y++ ) 
	{
		for ( x = 0; x < y_high*2 ; x++ ) 
				dest[x] = black;
		// lPitch contains the pitch in *bytes*
		dest += ddsd.lPitch;
	}

// Unlock the primary surface
if FAILED( g_pDDSminimap->Unlock( NULL ) )
	{
		HDC hdc;
		int     offset = 0;
		TCHAR   strBuf[256];
		//uses	wprintf <stdio.h> or <wchar.h> 
		offset = wsprintf(strBuf, "Couldn't un-lock the surface." );

		if (g_pDDSBack->GetDC(&hdc) == DD_OK) // must be locked
				{ 
				//SetBkMode (hdc,TRANSPARENT );
				SetBkColor(hdc, RGB(255, 0, 0)); 
				SetTextColor(hdc, RGB(255, 255, 0)); 
				TextOut(hdc, 0, 16,strBuf, offset); 
				g_pDDSBack->ReleaseDC(hdc); 
				}
	}// end unlock



rcRect.left   = 0;
rcRect.top    = 0;
rcRect.right  = x_wide*2;
rcRect.bottom = y_high*2; 

hRet = g_pDDSBack->BltFast(mini_x,
						   mini_y,
						   g_pDDSminimap,	
						   &rcRect,
						   DDBLTFAST_NOCOLORKEY);	   // no hide of bit map color x
//						   DDBLTFAST_SRCCOLORKEY);

} // end function
//=============================================================================
// Display the Mini Map
//=============================================================================
void 
DisplayMiniMapTest2(CPlayer &Player1)
{
HWND              hWnd = NULL;
RECT              rcRect;
HRESULT           hRet;
DDSURFACEDESC2    ddsd;
BYTE              *dest;
int               x;
static int		  y = 0;

ddsd = g_ddsd;

	// First, clear the primary surface to white using Lock and Unlock
	// to directly access surface memory

	// Lock the primary surface
	if FAILED( g_pDDSminimap->Lock( NULL, &ddsd, DDLOCK_WAIT , NULL ) )
		{
			HDC hdc;
			int     offset = 0;
			TCHAR   strBuf[256];
			//uses	wprintf <stdio.h> or <wchar.h> 
			offset = wsprintf(strBuf, "Couldn't lock the surface." );

		   if (g_pDDSBack->GetDC(&hdc) == DD_OK) // must be locked
				{ 
				//SetBkMode (hdc,TRANSPARENT );
				SetBkColor(hdc, RGB(255, 0, 0)); 
				SetTextColor(hdc, RGB(255, 255, 0)); 
				TextOut(hdc, 0, 0,strBuf, offset); 
				g_pDDSBack->ReleaseDC(hdc); 
				}
		} // end lock

// Clear it to white
// We are assuming: 
// 1) we are palettized, so each pixel is represented by a "byte" 
// 2) since we are not setting a new palette, entry 255 should be white.

	dest = (BYTE *)ddsd.lpSurface;
	dest += ddsd.lPitch * y;

	for ( int yy = y+2  ; y < yy; y++) 
		{
			for ( x = 0; x <x_wide * 2 ; x++ ) 
				{
					dest[x] = black;
				}
			dest += ddsd.lPitch;
		}

	for ( x = 0; x <x_wide * 2 ; x++ ) 
		{
			dest[x] = red;
		}

	if (y>y_high*2)
		y=0;

	// Unlock the primary surface
	if FAILED( g_pDDSminimap->Unlock( NULL ) )
		{
			HDC hdc;
			int     offset = 0;
			TCHAR   strBuf[256];
			//uses	wprintf <stdio.h> or <wchar.h> 
			offset = wsprintf(strBuf, "Couldn't un-lock the surface." );

			if (g_pDDSBack->GetDC(&hdc) == DD_OK) // must be locked
					{ 
					//SetBkMode (hdc,TRANSPARENT );
					SetBkColor(hdc, RGB(255, 0, 0)); 
					SetTextColor(hdc, RGB(255, 255, 0)); 
					TextOut(hdc, 0, 16,strBuf, offset); 
					g_pDDSBack->ReleaseDC(hdc); 
					}
		}// end unlock



	rcRect.left   = 0;
	rcRect.top    = 0;
	rcRect.right  = x_wide*2;
	rcRect.bottom = y_high*2; 

	hRet = g_pDDSBack->BltFast(mini_x,
							   mini_y,
							   g_pDDSminimap,	
							   &rcRect,
							   DDBLTFAST_NOCOLORKEY);	   // no hide of bit map color x
	//						   DDBLTFAST_SRCCOLORKEY);

} // end function
//=============================================================================
// Display the Mini Map
//=============================================================================
void 
DisplayMiniMapTest3(CPlayer &Player1)
{
HWND              hWnd = NULL;
RECT              rcRect;
HRESULT           hRet;
DDSURFACEDESC2    ddsd;
BYTE              *dest;
int               x;
static int		  y = 0;

ddsd = g_ddsd;

	// First, clear the primary surface to white using Lock and Unlock
	// to directly access surface memory

	// Lock the primary surface
	if FAILED( g_pDDSminimap->Lock( NULL, &ddsd, DDLOCK_WAIT , NULL ) )
		{
			HDC hdc;
			int     offset = 0;
			TCHAR   strBuf[256];
			//uses	wprintf <stdio.h> or <wchar.h> 
			offset = wsprintf(strBuf, "Couldn't lock the surface." );

		   if (g_pDDSBack->GetDC(&hdc) == DD_OK) // must be locked
				{ 
				//SetBkMode (hdc,TRANSPARENT );
				SetBkColor(hdc, RGB(255, 0, 0)); 
				SetTextColor(hdc, RGB(255, 255, 0)); 
				TextOut(hdc, 0, 0,strBuf, offset); 
				g_pDDSBack->ReleaseDC(hdc); 
				}
		} // end lock

	// Clear it to black
	// We are assuming: 
	// 1) we are palettized, so each pixel is represented by a "byte" 
	// 2) since we are not setting a new palette, entry 255 should be white.

	dest = (BYTE *)ddsd.lpSurface;
	dest += ddsd.lPitch * y;

	////////////////////////////////////////
//    char *buf;
//    try
    {
	// clear mini map
	for ( int yy = y+2  ; y < yy; y++) 
		{
			for ( x = 0; x <x_wide * mini_size ; x++ ) 
				{
				if ( g_bActive && !g_bLostFocus )  // update only when active
					dest[x] = black;
				}
			dest += ddsd.lPitch;
		}

	// drawl red line on mini map
	for ( x = 0; x <x_wide * mini_size ; x++ ) 
			{
			if ( g_bActive && !g_bLostFocus )  // update only when active
				dest[x] = red;
			}

	if (y>y_high*mini_size)
		y=0;

    }

/////////////// end of try

	// Unlock the primary surface
	if FAILED( g_pDDSminimap->Unlock( NULL ) )
		{
			HDC hdc;
			int     offset = 0;
			TCHAR   strBuf[256];
			//uses	wprintf <stdio.h> or <wchar.h> 
			offset = wsprintf(strBuf, "Couldn't un-lock the surface." );

			if (g_pDDSBack->GetDC(&hdc) == DD_OK) // must be locked
					{ 
					//SetBkMode (hdc,TRANSPARENT );
					SetBkColor(hdc, RGB(255, 0, 0)); 
					SetTextColor(hdc, RGB(255, 255, 0)); 
					TextOut(hdc, 0, 16,strBuf, offset); 
					g_pDDSBack->ReleaseDC(hdc); 
					}
		}// end unlock



	rcRect.left   = 0;
	rcRect.top    = 0;
	rcRect.right  = x_wide*mini_size;
	rcRect.bottom = y_high*mini_size; 

	hRet = g_pDDSBack->BltFast(mini_x,
							   mini_y,
							   g_pDDSminimap,	
							   &rcRect,
							   DDBLTFAST_NOCOLORKEY);	   // no hide of bit map color x
	//						   DDBLTFAST_SRCCOLORKEY);

} // end function

//=============================================================================
// Display the Mini Map
//=============================================================================
void 
DisplayMiniMap(CPlayer &Player1)
{

RECT                        rcRect;

/////////////mini map clear
DDBLTFX                     ddbltfx;
ZeroMemory(&ddbltfx, sizeof(ddbltfx));
ddbltfx.dwSize = sizeof(ddbltfx);

int x, y;
	for (	x = 0; x < x_wide; x +=1) 
		{for ( y = 0;  y < y_high;y +=1)
			{
	// mini map with no adj for color.....
			 rcRect.left   = mini_x + (x*2);
			 rcRect.top    = mini_y + (y*2);
			 rcRect.right  = rcRect.left + 2;
			 rcRect.bottom = rcRect.top  + 2;
			 ddbltfx.dwFillColor = gray;
			 g_pDDSBack->Blt(&rcRect, NULL, NULL, DDBLT_COLORFILL | DDBLT_WAIT, &ddbltfx);
			} // end for loop y
	} //end for loop x
} // end function
/*
//=============================================================================
// Display the Move Rate
//=============================================================================
void 
DisplayNumber( char buf[256],double number,int x_pos,int y_pos)
{
//DWORD				rem;
double				rem;
//char      stg[256];
int inum;

	//don't do next 3 lines.  loses the decimal data
	//next two lines make the compiler happy for the prior line,accomplesses the same thing without compile warning
//	inum =int(number);
//	number = double(abs(inum));


	//number = number + 0.12;

	//sprintf(stg, "display number %fp \n" + '\0', number);
	//OutputDebugString (stg);

	number = number * 1000;	// hide the decimal
	//next two lines make the compiler happy for the prior line,accomplesses the same thing without compile warning
	inum =int(number);
	number = double(abs(inum));
//	number = abs(number);	// make a positive number

	//sprintf(stg, "display number %fp \n" + '\0', number);
	//OutputDebugString (stg);

    rem = (DWORD)number % 100000000;
	buf[4] =  (char) ( rem/10000000 ) + '0';

    rem = (DWORD)number % 10000000;
	buf[5] =  (char) ( rem/1000000 ) + '0';

    rem = (DWORD)number % 1000000;
	buf[6] =  (char) ( rem/100000 ) + '0';

    rem = (DWORD)number % 100000;
	buf[7] =  (char) ( rem/10000 ) + '0';

    rem = (DWORD)number % 10000;
	buf[8] =  (char) ( rem/1000 ) + '0';

	buf[9] = '.';

    rem = (DWORD)number % 1000;
    buf[10] =  (char) ( rem/100 ) + '0';

    rem = (DWORD)number % 100;
	buf[11] =  (char) ( rem/10 ) + '0';

    rem = (DWORD)number % 10;
	buf[12] = (char) ( rem ) + '0';

	buf[13] = '\0';

    xyDisplayAcross( buf, x_pos, y_pos,true);   
}
*/
//=============================================================================
// Display the Move Rate
//=============================================================================
void 
DisplayDraw(CPlayer &Player1)
{	
	char                buf[256];

	int xt,yt;
			if (Player1.b_focus_on_ball)
				{
					xt =  296; //(int)cur_element->i_xpos_wall - (int)draw_x + (296);	// 592/2
					yt =  296; //(int)cur_element->i_ypos_wall - (int)draw_y + (296);	// 592/2
				}
			else
				{
					xt = (int)draw_x;
					yt = (int)draw_y;
				}

	if (draw_item_num != 0)
		{
			strcpy(buf, "ITM ");
			//xyDisplayString(buf,draw_item_num,3,0,Across,int(draw_x),int(draw_y),true);
			xyDisplayString(buf,draw_item_num,3,0,Across,xt,yt,true);

			strcpy(buf, "X   ");
			xyDisplayString(buf,draw_x,3,5,Across,xt,yt + 16,true);

			strcpy(buf, "XD  ");
			xyDisplayString(buf,draw_x_dir,3,5,Across,xt,yt + 32,true);

			strcpy(buf, "Y   ");
			xyDisplayString(buf,draw_y,3,5,Across,xt,yt + 48,true);

			strcpy(buf, "YD  ");
			xyDisplayString(buf,draw_y_dir,3,5,Across,xt,yt + 64,true);

			strcpy(buf, "OBJ ");
			xyDisplayString(buf,draw_obj_ID,3,5,Across,xt,yt + 80,true);

			strcpy(buf, "WAT ");
			xyDisplayString(buf,draw_wait_cnt,3,5,Across,xt,yt + 96,true);
		}
}
//=============================================================================
// Display the Move Rate
//=============================================================================
void 
DisplayMoveRate( CPlayer &Player1)
{
	char	buf[256]="MOV ";
	xyDisplayString(buf,Player1.i_have_mps,2,0,Across,650,280,true);

}
//=============================================================================
// Display the CaltTimeRate
//=============================================================================
void 
CalcTimeRate( CPlayer &Player1)
{
	DWORD               time2;
	DWORD               temptime;
    dwFrameCount++;
	temptime = timeGetTime();
    time2 = temptime - dwFrameTime;

    if( time2 > 1000 )
		{
		    dwFrames = (dwFrameCount*1000)/time2;

	        dwFrameTime = temptime;
			dwFrameCount = 0;

			Player1.i_have_mps = Player1.i_mps;
			Player1.i_mps = 0;			

			// adjust mps to be what we want
			if (Player1.time_game_freq_2 == 0)
				{
					if (Player1.i_want_mps == Player1.i_have_mps)
					{
						// do nothing (life is good)
					}
					else
					if (Player1.i_want_mps > Player1.i_have_mps)
					{
						Player1.i_adj_mps--;
					}
					else
					{
						Player1.i_adj_mps++;
					}
				}
			////////////////////////////////////
			//
			if (Player1.time_exec < 1000)
				Player1.time_wait_display = 1000 - Player1.time_exec;
			else
				Player1.time_wait_display = 1;

			Player1.time_exec_display = Player1.time_exec;
			Player1.time_wait=0;
			Player1.time_exec=0;
		}
    
    if (dwFrames != dwFramesLast)
		{
		dwFramesLast = dwFrames;
		}
}
//=============================================================================
// Display the Time Rate
//=============================================================================
void 
DisplayTimeRate( CPlayer &Player1)
{
char                buf[256];
LONGLONG pass_time;
/////////////////////////////////////////
	strcpy(buf, "WAIT ");
	xyDisplayString(buf,Player1.time_wait_display,4,0,Across,600, 360,true);

//=============================================================================
	strcpy(buf, "EXEC ");
	xyDisplayString(buf,Player1.time_exec_display,4,0,Across,600, 380,true);

//=============================================================================
//=============================================================================
	strcpy(buf, "ELAPSED ");
	xyDisplayString(buf, Player1.time_elapsed,3,5,Across,300-32, 90-64,true);

//=============================================================================
	strcpy(buf, "PLAY");
	xyDisplayString(buf, Player1.time_game_play,7,5,Across,300-32, 110-64,true);

//=============================================================================
//=============================================================================
	strcpy(buf, "STRT 2 ");
	pass_time = Player1.time_game_start_2;
	xyDisplayLONGLONG(buf, pass_time,Across,280-64, 170-64,true,Player1);
//=============================================================================
	strcpy(buf, "LAST 2 ");
	pass_time = Player1.time_game_last_2;
	xyDisplayLONGLONG(buf, pass_time,Across,280-64, 190-64,true,Player1);

//=============================================================================
	strcpy(buf, "ACUM 2 ");
	pass_time = Player1.time_game_acum_2;
	xyDisplayLONGLONG(buf, pass_time,Across,280-64, 210-64,true,Player1);
//=============================================================================
	strcpy(buf, "ELAP 2 ");
	pass_time = Player1.time_game_elap_2;
	xyDisplayLONGLONG(buf, pass_time,Across,280-64, 230-64,true,Player1);
//=============================================================================
	strcpy(buf, "FREQ 2 ");
	pass_time = Player1.time_game_freq_2;
	xyDisplayLONGLONG(buf, pass_time,Across,280-64, 250-64,true,Player1);
//=============================================================================
	strcpy(buf, "CNT  2 ");
	pass_time = Player1.time_game_count_2;
	xyDisplayLONGLONG(buf, pass_time,Across,280-64, 270-64,true,Player1);
//=============================================================================
	strcpy(buf, "CNT 22 ");
	pass_time = Player1.time_game_count_22;
	xyDisplayLONGLONG(buf, pass_time,Across,280-64, 290-64,true,Player1);

}
//=============================================================================
// Display the Frame Rate
//=============================================================================
void 
DisplayFrameRate( CPlayer &Player1)
{
char   buf[256] = "FPS ";

	xyDisplayString(buf,dwFrames,2,0,Across,650, 300,true);
}
//=============================================================================
// Display the Time Rate
//=============================================================================
void 
DisplayAdjRate( CPlayer &Player1)
{
char   buf[256] = "ADJ ";

	xyDisplayString(buf,Player1.i_adj_mps,3,0,Across,650, 320,true);
}

//=============================================================================
// Display the Score
//=============================================================================
void 
DisplayScore(CPlayer &Player1)
{
//__int64		rem ;
char		buf[30];
//int			level = 10;
int dwn = 0;

	for (int x =0 ; x <= 3 ; x++)
		{
			// only display score if a team is present
			if (!((Player1.i_PlayerType[x] == Open || Player1.i_PlayerType[x] == Closed) && ((Player1.i_PlayerType[x+4] == Open || Player1.i_PlayerType[x+4] == Closed))))
				{
					switch ( x )
						{
							case 0:
								{
								strcpy(buf,"RED    ");
								dwn++;
								break;
								}
							case 1:
								{
								strcpy(buf,"YELLOW ");
								dwn++;
								break;
								}
							case 2:
								{
								strcpy(buf,"GREEN  ");
								dwn++;
								break;
								}
							case 3:
								{
								strcpy(buf,"BLUE   ");
								dwn++;
								break;
								}

						}// end case switch

	xyDisplayString(buf,g_iScoreOut - Player1.i_score[x],2,0,Across,630, 5+ (25 * dwn),true);
				}// end if
	}// end for loop
}// end function
//=============================================================================
// Display the Data
//=============================================================================
void 
DisplayType( CPlayer &Player1)
{
char                buf[256];
int					rem2;
	strcpy(buf, "SLOT ");
	xyDisplayString(buf,Player1.i_my_slot,2,0,Across,50, 40,true);
//==============================================
		for ( rem2 = 0 ; rem2 < 8 ; rem2++ )
			{
				strcpy(buf, "TYPE ");
				xyDisplayString(buf,Player1.i_PlayerType[rem2],2,0,Across,50, 90+(rem2*20),true);
			}
}
//=============================================================================
// Display the Time Rate
//=============================================================================
void 
DisplayRandRate( CPlayer &Player1)
{
char                buf[256] = "RAND ";

	xyDisplayString(buf,Player1.Game_Rand_Last,2,0,Across,650, 340,true);

}
//=============================================================================
// Display the Pause Rate
//=============================================================================
void 
DisplayPauseRate( CPlayer &Player1)
{
char                buf[256] = "PAUSED";

int xt,yt;

			if (Player1.b_focus_on_ball)
				{
					xt =  screen_wide - (int)draw_x - (16*3)+3;
					yt =  screen_high - (int)draw_y - 8;
				}
			else
				{
					xt = screen_wide/2 - (16*3)+3;
					yt = screen_high/2 - 8;
				}

	if (Player1.b_Game_Pause)
		{
		xyDisplayString(buf,0,0,0,Across,xt,yt ,false);
		}
}
//=============================================================================
// Display the Host Rate
//=============================================================================
void 
DisplayHostRate( CPlayer &Player1)
{
char                buf[256];

	if (g_bHostPlayer)
		{
				strcpy(buf, "HOST");
				xyDisplayString(buf,0,0,0,Across,650, 260,true);
		}
		else
		{
				strcpy(buf, "JOIN");
				xyDisplayString(buf,0,0,0,Across,650, 260,true);
		}
}
//=============================================================================
// Display the Mini Rate
//=============================================================================
void 
DisplayMiniRate( CPlayer &Player1)
{
char                buf[256] = "MINI MAP";

	xyDisplayString(buf,0,0,0,Across,mini_x, mini_y-18,true);

}
//=============================================================================
// Display the Num Players
//=============================================================================
void 
DisplayNumPlayers( CPlayer &Player1)
{

char                buf[256] = "PLAYERS";

	xyDisplayString(buf,Player1.i_numb_active_players,1,0,Across,595, 230,true);

}
//=============================================================================
// Display the Loser
//=============================================================================
void 
DisplayLoser(int x,int y,int across_down)
{
char                buf[256] = "LOSER";

	xyDisplayString(buf,0,0,0,across_down,x, y,false);
}
//=============================================================================
// Display the Winner Down
//=============================================================================
void 
DisplayWinner(int x,int y,int across_down)
{
char                buf[256] = "WINNER";
static int xx=5*16;
static int yy=5*16;
static int d=1;

	if (across_down == Across)
		{
		xx+=(10*d);
		if (xx>26*16)
			d=-1;
		if (xx<6*16)
			d=1;
		x=xx;
		}
	else
		{
		yy+=(10*d);
		if (yy>26*16)
			d=-1;
		if (yy<6*16)
			d=1;
		y=yy;
		}

	xyDisplayString(buf,0,0,0,across_down,x, y,false);
}
//=============================================================================
// clear background
//=============================================================================
void
ClearBackground()
{
// Use the blter to do a color fill to clear the back buffer

DDBLTFX                     ddbltfx;
ZeroMemory(&ddbltfx, sizeof(ddbltfx));
ddbltfx.dwSize = sizeof(ddbltfx);

  ddbltfx.dwFillColor = red;
  ddbltfx.dwFillColor = 0;
  g_pDDSBack->Blt(NULL, NULL, NULL, DDBLT_COLORFILL | DDBLT_WAIT, &ddbltfx);
}

//=============================================================================
// setup classes for game play
//=============================================================================

//int it_x_dir, it_y_dir;
//Classes
//#include "cPlayer.h"
#include "cWall.h"
#include "cBall.h"
#include "cCircle.h"
#include "cPaddle_V.h"
#include "cPaddle_H.h"
#include "cboom.h"

// when inserting a new class that cWallList uses.  
// put it before here.............................
#include "cWallList.h"


//==============================================================
// Draw an item
//==============================================================
void
DisplayObjects(wall_list &b_list,CPlayer &Player1)
{
RECT                        rcRect;
HRESULT                     hRet;
wall_list_element *cur_element;
cur_element = b_list.return_first();
	
for (	cur_element = b_list.return_first(); //b_list.first_ptr; 
		cur_element != NULL; 
		cur_element = cur_element->next_ptr) 
		{
			int xt;
			int yt;
			int LL=0;								// left
			int LR = cur_element->i_w_wall;			// right
			int LT=0;								// top
			int LB = cur_element->i_h_wall;			// bottom

			if (Player1.b_focus_on_ball)
				{
					xt =  (int)cur_element->i_xpos_wall - (int)draw_x + (296);	// 592/2
					yt =  (int)cur_element->i_ypos_wall - (int)draw_y + (296);	// 592/2
				}
			else
				{
					xt = (int)cur_element->i_xpos_wall;
					yt = (int)cur_element->i_ypos_wall;
				}

			// only display if in pan
			if (xt > -cur_element->i_w_wall && xt < (592) && yt > -cur_element->i_h_wall && yt < (592))
				{
				//=====================
				// left
				if ( xt < 0)
				{
					LL -=xt;
					xt = 0;
				}
				else
				// right
				if (xt + cur_element->i_w_wall > 592)
				{
					LR=592-xt;
				}

				//=====================

				// top
				if (yt < 0)
				{
					LT -=yt;
					yt = 0;
				}
				else
				//bottom
				if (yt + cur_element->i_h_wall > 592)
				{
					LB = 592 - yt;
				}
				//==============================================================
				 // Blit the stuff for the next frame ( FULL SCREEN)
					rcRect.left   = (int)((cur_element->i_frame % 10 * cur_element->i_w_wall) + LL) ;
					rcRect.top    = (int)((cur_element->i_frame / 10 * cur_element->i_h_wall) + LT) ;
					rcRect.right  = (int)( cur_element->i_frame % 10 * cur_element->i_w_wall + LR);
					rcRect.bottom = (int)( cur_element->i_frame / 10 * cur_element->i_h_wall + LB);

					hRet = g_pDDSBack->BltFast(xt,
											 yt,
											 cur_element->p_DDS,		//g_pDDSwall.  //
											 &rcRect,
											 DDBLTFAST_SRCCOLORKEY);	// hide bitmap color x
										//	 DDBLTFAST_NOCOLORKEY);	   // no hide of bit map color x

				}	// end pan		  
		}  // end loop
}	// end function

//==============================================================
// display mini map objects
//==============================================================
void
DisplayMiniObjects1(wall_list &b_list,CPlayer &Player1)
{

RECT                        rcRect;
wall_list_element *cur_element;
cur_element = b_list.return_first();
	
/////////////mini map clear
DDBLTFX                     ddbltfx;
ZeroMemory(&ddbltfx, sizeof(ddbltfx));
ddbltfx.dwSize = sizeof(ddbltfx);

	for (	cur_element = b_list.return_first(); //b_list.first_ptr; 
		cur_element != NULL; 
		cur_element = cur_element->next_ptr) 
		{
			//==============================================================
			// Blit the stuff for the next frame (MINI MAP)
			// mini map with no adj for color.....

			// directly apply to BackGround based on 
			rcRect.left   = mini_x + (int)(cur_element->i_xpos_wall*mini_div); //+(cur_element->i_w_wall/2);
			rcRect.top    = mini_y + (int)(cur_element->i_ypos_wall*mini_div); //+(cur_element->i_h_wall/2);
			rcRect.right  = rcRect.left + mini_size;
			rcRect.bottom = rcRect.top  + mini_size;
			ddbltfx.dwFillColor = yellow;
			g_pDDSBack->Blt(&rcRect, NULL, NULL, DDBLT_COLORFILL | DDBLT_WAIT, &ddbltfx);


		} // end loop
} // end function
//==============================================================
// display mini map objects 2
//==============================================================
void
DisplayMiniObjects2(wall_list &b_list,CPlayer &Player1)
{
RECT                        rcRect;
wall_list_element *cur_element;
cur_element = b_list.return_first();
/////////////mini map clear
DDBLTFX                     ddbltfx;
ZeroMemory(&ddbltfx, sizeof(ddbltfx));
ddbltfx.dwSize = sizeof(ddbltfx);
HRESULT                     hRet;


int tmp_c = 2;
	for (	cur_element = b_list.return_first(); //b_list.first_ptr; 
		cur_element != NULL; 
		cur_element = cur_element->next_ptr) 
		{
			rcRect.left   = (int)((cur_element->i_frame % 10 * cur_element->i_w_wall) + tmp_c);
			rcRect.top    = (int)((cur_element->i_frame / 10 * cur_element->i_h_wall) + tmp_c);
			rcRect.right  = rcRect.left + mini_size;
			rcRect.bottom = rcRect.top  + mini_size; 

			hRet = g_pDDSBack->BltFast((int)((cur_element->i_xpos_wall+(cur_element->i_w_wall/2))*mini_div)+mini_x-2,
									   (int)((cur_element->i_ypos_wall+(cur_element->i_h_wall/2))*mini_div)+mini_y-2,
									   cur_element->p_DDS,		//g_pDDSwall.  //
									   &rcRect,
									   DDBLTFAST_SRCCOLORKEY);	// hide bitmap color x
									// DDBLTFAST_NOCOLORKEY);	   // no hide of bit map color x
		} // end loop
} // end function

//==============================================================
// Flip the surfaces
//==============================================================
void
FlipSurface()
{

	POINT pt = {0, 0};
	ClientToScreen (g_hDlg, &pt);

	int xx = 0,yy = 0;
/*	if (pt.x < 0)	
	{
		xx = abs(pt.x);
		pt.x =0;
	}
	if (pt.y < 0)	
	{
		yy = abs(pt.y);
		pt.y =0;
	}
*/
//DDSURFACEDESC2    ddsd;
//ddsd = g_ddsd;
//ddsd.dwSize = sizeof(ddsd);
//ddsd.dwFlags = DDSD_HEIGHT | DDSD_WIDTH;
//g_pDDSPrimary->GetSurfaceDesc(&ddsd);
//int Width  = (DWORD)ddsd.dwWidth;
//int Height = (DWORD)ddsd.dwHeight;

//==========================================

    HRESULT                     hRet;
	if (g_Full_Screen)
	{
		while (TRUE)
		{
			hRet = g_pDDSPrimary->Flip(NULL, 0);
			if (hRet == DD_OK)
				break;
			if (hRet == DDERR_SURFACELOST)
			{
				hRet = RestoreAll();
				if (hRet != DD_OK)
					break;
			}
			if (hRet != DDERR_WASSTILLDRAWING)
				break;
		}  // end while
	}
		else
		{
		double aspect;
		aspect = (double)Height / (double)600.0;

		// scale it here.  
		//the BLT will auto scale to the correct size of the dest RECT
		RECT BuffRect = {pt.x, pt.y, (long)(pt.x+(Width/2.2)), (long)(pt.y+(Height/2.2))};
		RECT DRect = {xx, yy, (long)(Width/aspect), (long)(Height/aspect)};
			int pass = 0;//DDFLIP_WAIT;

			hRet = g_pDDSPrimary->Blt (&BuffRect, g_pDDSBack, &DRect, pass, NULL);
			if (hRet == DDERR_SURFACELOST)
			{
				hRet = RestoreAll();
			}
//			if (hRet != DDERR_WASSTILLDRAWING)
//				break;
		}
}  // end function

//==============================================================
// Defending Walls
//==============================================================
void
DefendingWalls_red(wall_list &a_list,CPlayer &Player1)
{
a_list.line_wall (600-16-64,16+64,600-16-64,564-64,g_pDDSwall);
}
//==============================================================
void
DefendingWalls_yellow(wall_list &a_list,CPlayer &Player1)
{
a_list.line_wall (0+64,16+64,0+64,600-32-64,g_pDDSwall);
}
//==============================================================
void
DefendingWalls_blue(wall_list &a_list,CPlayer &Player1)
{
a_list.line_wall (0+64+16,0+64,600-16-64-16,0+64,g_pDDSwall);	
}
//==============================================================
void
DefendingWalls_green(wall_list &a_list,CPlayer &Player1)
{
a_list.line_wall (0+80,600-80,600-16-80,600-80,g_pDDSwall);
}

void
DefendingWalls(wall_list &a_list,CPlayer &Player1)
{
	//inside walls if no player to defend

		// red team (this will never happen, someone needs to host the game
		if (Player1.i_PlayerType[0] == Open || Player1.i_PlayerType[0] == Closed)
			if (Player1.i_PlayerType[4] == Open || Player1.i_PlayerType[4] == Closed)
				DefendingWalls_red(a_list,Player1);
						
		// yellow team
		if (Player1.i_PlayerType[1] == Open || Player1.i_PlayerType[1] == Closed)
			if (Player1.i_PlayerType[5] == Open || Player1.i_PlayerType[5] == Closed)
				DefendingWalls_yellow(a_list,Player1);

			// blue team
		if (Player1.i_PlayerType[2] == Open || Player1.i_PlayerType[2] == Closed)
			if (Player1.i_PlayerType[6] == Open || Player1.i_PlayerType[6] == Closed)
				DefendingWalls_blue(a_list,Player1);
				
			// green team
		if (Player1.i_PlayerType[3] == Open || Player1.i_PlayerType[3] == Closed)
			if (Player1.i_PlayerType[7] == Open || Player1.i_PlayerType[7] == Closed)
				DefendingWalls_green(a_list,Player1);


		Player1.b_Player_Quit = false;

/////// loser code below
		if (Player1.b_Loser[0] == true)
				{
				DefendingWalls_red(a_list,Player1);
                Player1.b_Loser[0] = false;
				if (Player1.i_my_slot == 0 || Player1.i_my_slot == 4)
					{
					SoundPlayEffect (SOUND_LOSE);
					SoundPlayEffect (SOUND_playerdies);
					}
				}

		if (Player1.b_Loser[1] == true)
				{
				DefendingWalls_yellow(a_list,Player1);
                Player1.b_Loser[1] = false;
				if (Player1.i_my_slot == 1 || Player1.i_my_slot == 5)
					{
					SoundPlayEffect (SOUND_LOSE);
					SoundPlayEffect (SOUND_playerdies);
					}
				}

		if (Player1.b_Loser[2] == true)
				{
				DefendingWalls_blue(a_list,Player1);
                Player1.b_Loser[2] = false;
				if (Player1.i_my_slot == 2 || Player1.i_my_slot == 6)
					{
					SoundPlayEffect (SOUND_LOSE);
					SoundPlayEffect (SOUND_playerdies);
					}
				}

		if (Player1.b_Loser[3] == true)
				{
				DefendingWalls_green(a_list,Player1);
				Player1.b_Loser[3] = false;
				if (Player1.i_my_slot == 3 || Player1.i_my_slot == 7)
					{
					SoundPlayEffect (SOUND_LOSE);
					SoundPlayEffect (SOUND_playerdies);
					}
				}
}

void UsageCPU(CPlayer &Player1)
{
	RECT                        rcRect;
	HRESULT                     hRet;
	// Blit the stuff for the exe
	rcRect.left   = 1;
	rcRect.top    = 1;
	rcRect.right  = 100;
	rcRect.bottom = 2; 

	hRet = g_pDDSBack->BltFast(mini_x,
								mini_y-2,
								g_pDDSexe_line,	
								&rcRect,
								DDBLTFAST_SRCCOLORKEY);

	// Blit the stuff for the wait
	rcRect.left   = 1;
	rcRect.top    = 0;
	rcRect.right  = LONG(100 - (Player1.time_wait_display/10));
	rcRect.bottom = 1; 

	hRet = g_pDDSBack->BltFast(mini_x,
								mini_y-2,
								g_pDDSexe_line,	
								&rcRect,
								DDBLTFAST_SRCCOLORKEY);

	// Blit the stuff for the sleep
	rcRect.left   = 1;
	rcRect.top    = 2;
	rcRect.right  = (LONG)Player1.time_sleep;
	rcRect.bottom = 3; 

	hRet = g_pDDSBack->BltFast(mini_x + (DWORD)(100-Player1.time_sleep),
								mini_y-2,
								g_pDDSexe_line,	
								&rcRect,
								DDBLTFAST_SRCCOLORKEY);
}

void DisplayInterface(CPlayer &Player1)
{
	RECT                        rcRect;
	HRESULT                     hRet;

	int y = 180;
	// Blit the stuff mouse, key, speak
	rcRect.left   = 0;
	rcRect.top    = 0;
	rcRect.right  = 32*3;
	rcRect.bottom = 32; 

	hRet = g_pDDSBack->BltFast(650,
								y,
								g_pDDSinterface,	
								&rcRect,
								DDBLTFAST_SRCCOLORKEY);

	// Blit the stuff mouse
	if (Player1.i_mouse > 0)
		{
		// ok
		rcRect.left   = 32*4;
		rcRect.top    = 0;
		rcRect.right  = 32*5;
		rcRect.bottom = 32; 
		}
	else
		{
		// off-line
		rcRect.left   = 32*3;
		rcRect.top    = 0;
		rcRect.right  = 32*4;
		rcRect.bottom = 32; 
		}

	hRet = g_pDDSBack->BltFast(650,
								y,
								g_pDDSinterface,	
								&rcRect,
								DDBLTFAST_SRCCOLORKEY);

	// Blit the stuff key
	if (Player1.i_key > 0)
		{
		// ok
		rcRect.left   = 32*4;
		rcRect.top    = 0;
		rcRect.right  = 32*5;
		rcRect.bottom = 32; 
		}
	else
		{
		// off-line
		rcRect.left   = 32*3;
		rcRect.top    = 0;
		rcRect.right  = 32*4;
		rcRect.bottom = 32; 
		}

	hRet = g_pDDSBack->BltFast(650+32,
								y,
								g_pDDSinterface,	
								&rcRect,
								DDBLTFAST_SRCCOLORKEY);

	// Blit the stuff speak
	if (Player1.b_sound == true)
		{
		// ok
		rcRect.left   = 32*4;
		rcRect.top    = 0;
		rcRect.right  = 32*5;
		rcRect.bottom = 32; 
		}
	else
		{
		// off-line
		rcRect.left   = 32*3;
		rcRect.top    = 0;
		rcRect.right  = 32*4;
		rcRect.bottom = 32; 
		}

	hRet = g_pDDSBack->BltFast(650+64,
								y,
								g_pDDSinterface,	
								&rcRect,
								DDBLTFAST_SRCCOLORKEY);
}
//-----------------------------------------------------------------------------

void 	displayQBytesIntro()
{
	int x;
	char   buf[256];

	strcpy(buf, "WELCOME TO QBYTES PONG");
	x = ((592+16)/2) - (16 * ((strlen(buf)+1)/2));
	xyDisplayString(buf,0,0,0,Across,x, 100,true);

	strcpy(buf, "VISIT US ONLINE");
	x = ((592+16)/2) - (16 * ((strlen(buf)+1)/2));
	xyDisplayString(buf,0,0,0,Across,x, 460,true);

	strcpy(buf, "WWW.QBYTESWORLD.COM");
	x = ((592+16)/2) - (16 * ((strlen(buf)+1)/2));
	xyDisplayString(buf,0,0,0,Across,x, 468+16,true);
}

//-----------------------------------------------------------------------------
// Name: UpdateFrame()
// Desc: Decide what needs to be blitted next, wait for flip to complete,
//       then flip the buffers.
//-----------------------------------------------------------------------------

void UpdateFrame(wall_list &b_list,CPlayer &Player1) 
{
static int si_flash = 0;
// same as FPS
Player1.i_mps++;

ClearBackground();

CalcTimeRate( Player1);

DisplayCells(Player1);

DisplayObjects(b_list, Player1);

//DisplayMiniMap(Player1);
//if ( g_bActive && !g_bLostFocus )  // update only when active
//	DisplayMiniMapTest3(Player1);	

//DisplayMiniObjects1(b_list, Player1);	// OLD
DisplayMiniObjects2(b_list, Player1); // GOOD ONE IS HERE? 99% Sure

if (b_intro == false)
	DisplayNumPlayers(Player1);

DisplayMiniRate(Player1);

DisplayPauseRate(Player1);

if (b_intro == false)
	DisplayHostRate(Player1);

DisplayScore(Player1);

if(Player1.b_Help_Disp)
	{
		DisplayFrameRate(Player1);
		DisplayTimeRate(Player1);
		DisplayMoveRate(Player1);
		DisplayAdjRate(Player1);
		DisplayRandRate(Player1);
		DisplayType(Player1);
		DisplayDraw(Player1);
	}

if (Player1.b_Player_Quit)
	DefendingWalls(b_list,Player1);

if (Player1.b_Loser[0] || Player1.b_Loser[1] || Player1.b_Loser[2] || Player1.b_Loser[3])
	DefendingWalls(b_list,Player1);

// flash display Losers and winner
if (si_flash++ > 5)
	{
	// loser code
	if (Player1.b_Loser_Disp[0])
		DisplayLoser(33*16,16*16,Down);
	if (Player1.b_Loser_Disp[1])
		DisplayLoser(3*16,16*16,Down);
	if (Player1.b_Loser_Disp[2])
		DisplayLoser(16*16,3*16,Across);
	if (Player1.b_Loser_Disp[3])
		DisplayLoser(16*16,33*16,Across);

	if (si_flash > 10)
		si_flash = 0;
	}

// winner code
if (Player1.b_Winner_Disp[0])
	DisplayWinner(33*16, 5*16 ,Down);
if (Player1.b_Winner_Disp[1])
	DisplayWinner(3*16 , 5*16 ,Down);
if (Player1.b_Winner_Disp[2])
	DisplayWinner(5*16 ,3*16  ,Across);
if (Player1.b_Winner_Disp[3])
	DisplayWinner(5*16 ,33*16 ,Across);

DisplayInterface(Player1);

UsageCPU(Player1);

if (b_intro == true)
	displayQBytesIntro();

// display the version on the screen
xyDisplayAcross( "V 1.34", 654, 160 , true, false);


// nothing after this point but flip surface
// nothing after this point but flip surface
// nothing after this point but flip surface
FlipSurface();
}


//==============================================================
// init Direct Draw
//==============================================================
static HRESULT initDDraw (HINSTANCE hInstance, int nCmdShow,CPlayer &Player1)
{    // Create a window
	HWND                        hWnd = NULL;
    DDSURFACEDESC2              ddsd;
    DDSCAPS2                    ddscaps;
    HRESULT                     hRet;



	//size = 640x480 does not work

      switch ( g_Resolution )
      {
         case 1280:
					{
						Width  = 1280;
						Height = 960;
						break;
					}
		case 1024:
					{
						Width  = 1024;
						Height = 768;
						break;
					}
		case 800:
					{
						Width  = 800;
						Height = 600;
						break;
					}
/*		case 640:
					{
						Width  = 640;
						Height = 480;
						break;
					}
*/
	  }

   if (g_Full_Screen)
	{
	hWnd = CreateWindowEx(WS_EX_APPWINDOW,
                          NAME,
                          TITLE,
                          WS_POPUP,
                          0,
                          0,
                          GetSystemMetrics(SM_CXSCREEN),
                          GetSystemMetrics(SM_CYSCREEN),
                          NULL,
                          NULL,
                          hInstance,
                          NULL);
	}
	else
		{int WindowX,WindowY;
		WindowX	= 0;
		WindowY = 0;

		// this is for testing multi windows on 1 screen (debugging)
			//WindowX = GetSystemMetrics (SM_CXSCREEN)/2-Width/2, // center the window
			//WindowY = GetSystemMetrics (SM_CYSCREEN)/2-Height/2;

		if (Player1.i_my_slot == 1)
            WindowX = 800/2;
		if (Player1.i_my_slot == 2)
            WindowY = 800/2;
		if (Player1.i_my_slot == 3)
			{
            WindowX = 800/2;
			WindowY = 800/2;
			}

		hWnd = CreateWindowEx( 
			0, 
            NAME,
            TITLE, 
			//WS_POPUP, 
			WS_BORDER | WS_SYSMENU | WS_VISIBLE  ,
			WindowX, //WindowX, 
			WindowY, //WindowY, 
			Width/2,
			Height/2,
			NULL, 
			NULL, 
			hInstance, 
			NULL);	
	}

	if (!hWnd)
		return InitFail(hWnd, S_FALSE , "MS Create Window Error");
        //return FALSE;
	
	g_hDlg=hWnd;

	CellSet();  // fill all cells with 20
	CellSet1(); // build field
    
	ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);
    SetFocus(hWnd);

    ///////////////////////////////////////////////////////////////////////////
    // Create the main DirectDraw object
    ///////////////////////////////////////////////////////////////////////////


    hRet = DirectDrawCreateEx(NULL, (VOID**)&g_pDD, IID_IDirectDraw7, NULL);
    if (hRet != DD_OK)
        return InitFail(hWnd, hRet, "DirectDrawCreateEx FAILED");

    hRet = g_pDD->SetCooperativeLevel (hWnd,  
		(g_Full_Screen) ? (DDSCL_FULLSCREEN | DDSCL_EXCLUSIVE | DDSCL_ALLOWREBOOT) : (DDSCL_NORMAL));	
	
    if (hRet != DD_OK)
        return InitFail(hWnd, hRet, "Video SetCooperativeLevel FAILED");

	hRet = NULL;

	if (g_Full_Screen)
		{
		// Set the video mode to 640x480x8, 1024x768x8, 800x600x8
		// Set the video mode
			hRet = g_pDD->SetDisplayMode(Width, Height, 16, 0, 0);
			if (hRet != DD_OK)
				return InitFail(hWnd, hRet, "SetDisplayMode FAILED");
		}

    // Create the primary surface with 1 back buffer
    ZeroMemory(&ddsd, sizeof(ddsd));
	ZeroMemory (&ddsd.ddpfPixelFormat, sizeof(DDPIXELFORMAT));

    ddsd.dwSize = sizeof(ddsd);
	ddsd.dwFlags = DDSD_CAPS;
	ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE;

	g_ddsd = ddsd;

	if (g_Full_Screen) 
	{
		ddsd.ddsCaps.dwCaps |= DDSCAPS_FLIP | DDSCAPS_COMPLEX;
		ddsd.dwFlags |= DDSD_BACKBUFFERCOUNT;
	}

    ddsd.dwBackBufferCount = 1;

    hRet = g_pDD->CreateSurface(&ddsd, &g_pDDSPrimary, NULL);
    if (hRet != DD_OK)
        return InitFail(hWnd, hRet, "CreateSurface Primary  - FAILED");

		//***************Get pixel format

	ddsd.dwSize = sizeof (ddsd);
  	ddsd.dwFlags = DDSD_PIXELFORMAT;
	hRet = g_pDDSPrimary->GetSurfaceDesc (&ddsd);
	if (hRet != DD_OK) 
		 return InitFail(hWnd, S_FALSE , "pixel format not available");

//* fails in full screen -- not sure why it started working
// test some more, if fails more comment back out
		//************* get our color type
	int ColorType;
	int g = ddsd.ddpfPixelFormat.dwGBitMask>>5;// assumes 5 for red
	if (g == 0x1F) 
		ColorType = _5x5x5_;
	 else 
		if 
		(g == 0x3F) 
		 ColorType = _5x6x5_;
	 else 
		 return InitFail(hWnd, S_FALSE , "Color Mode Not Supported.\n\nClick the following:\nStart\nSettings\nControl Panel\nDouble - Display\nSettings\nSet High Color 16Bit");
//*/
	if (g_Full_Screen)
	{
		// Get a pointer to the back buffer
		ZeroMemory(&ddscaps, sizeof(ddscaps));
		ddscaps.dwCaps = DDSCAPS_BACKBUFFER;
		hRet = g_pDDSPrimary->GetAttachedSurface(&ddscaps, &g_pDDSBack);
		if (hRet != DD_OK)
			return InitFail(hWnd, hRet, "GetAttachedSurface FAILED");
	}
	else 
	{
		ddsd.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH;
		ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN | DDSCAPS_VIDEOMEMORY;
		ddsd.dwWidth = Width;
		ddsd.dwHeight = Height;
		hRet = g_pDD->CreateSurface(&ddsd, &g_pDDSBack, NULL);
		if (hRet != DD_OK)
			return InitFail(hWnd, hRet, "back buffer not created");
	}

//daq next 7 lines
//daq next 7 lines    

    g_pDDSminimap = DDLoadBitmap(g_pDD, szMINIMAP, 0, 0);
    if (g_pDDSminimap == NULL)
        return InitFail(hWnd, hRet, "DDLoadBitmap FAILED g_pDDSminimap");

    g_pDDSwall = DDLoadBitmap(g_pDD, szWALL, 0, 0);
    if (g_pDDSwall == NULL)
        return InitFail(hWnd, hRet, "DDLoadBitmap FAILED g_pDDSwall");

    g_pDDSpaddle_V = DDLoadBitmap(g_pDD, szPADDLE_V, 0, 0);
    if (g_pDDSpaddle_V == NULL)
        return InitFail(hWnd, hRet, "DDLoadBitmap FAILED g_pDDSpaddle_V");

    g_pDDSpaddle_H = DDLoadBitmap(g_pDD, szPADDLE_H, 0, 0);
    if (g_pDDSpaddle_H == NULL)
        return InitFail(hWnd, hRet, "DDLoadBitmap FAILED g_pDDSpaddle_H");

    g_pDDScell1 = DDLoadBitmap(g_pDD, szCELL1, 0, 0);
    if (g_pDDScell1 == NULL)
        return InitFail(hWnd, hRet, "DDLoadBitmap FAILED g_pDDScell1");

    g_pDDSabc = DDLoadBitmap(g_pDD, szABC, 0, 0);
    if (g_pDDSabc == NULL)
        return InitFail(hWnd, hRet, "DDLoadBitmap FAILED g_pDDSabc");

    g_pDDSexe_line = DDLoadBitmap(g_pDD, szEXELINE, 0, 0);
    if (g_pDDSexe_line == NULL)
        return InitFail(hWnd, hRet, "DDLoadBitmap FAILED g_pDDSexe_line");

    g_pDDSinterface = DDLoadBitmap(g_pDD, szINTERFACE, 0, 0);
    if (g_pDDSinterface == NULL)
        return InitFail(hWnd, hRet, "DDLoadBitmap FAILED g_pDDSinterface");
	
	// Set the color key for this bitmap (black) as the transparent
	DDSetColorKey(g_pDDSminimap,  RGB(  0, 0, 0));
	DDSetColorKey(g_pDDSwall,     RGB(  0, 0, 0));
	DDSetColorKey(g_pDDSpaddle_V, RGB(  0, 0, 0));
	DDSetColorKey(g_pDDSpaddle_H, RGB(  0, 0, 0));
	DDSetColorKey(g_pDDScell1,	  RGB(  0, 0, 0));
	DDSetColorKey(g_pDDSabc,      RGB(  0, 0, 0));
	DDSetColorKey(g_pDDSexe_line, RGB(  0, 0, 0));
	DDSetColorKey(g_pDDSinterface, RGB(  0, 0, 0));

    return DD_OK;
}




/* Char Codes 
   ----------
	A = 65
	Z = 90

	a = 97
	z = 122

	0 = 30
	9 = 39
   ----------
*/

