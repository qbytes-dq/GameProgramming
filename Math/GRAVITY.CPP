#include <stdio.h>
#include <math.h>
#include <conio.h>

#define gravity 9.8

void main (void)
{float	ball_pos   =      0,
	ball_y   =        0,
	ball_yv  =       10,
	ball_acc = gravity;
int     seconds;
int     data;

while (ball_yv > 0)
	{
	ball_y  += ball_yv;
	ball_yv -= (ball_acc *.1);
	printf ("y=  %2.3f  yv= %2.3f \n",ball_y,ball_yv);
	for (seconds = 0; seconds < 18.1; seconds++)
		{
                ball_pos += ball_yv/18;
		printf ("%3.3f\n",ball_pos);
		}
         data =   getche();
	}
return;
}