#include <stdio.h>
#include <math.h>

#define pi 3.14159

double x,y;
double a,b;
double degree;
double rad;
double cs,sn;

void main (void)

{
x=5;
y=5;

for (degree=0;degree < 361; degree +=18)
	{
	/*convert degree to rad for the c compiler*/
	rad = pi * (degree/180);                      
	cs = cos(rad);
	sn = sin(rad);

	a = (x * cs) - (y * sn);
	b = (y * cs) + (x * sn);

	printf ("deg= %3.0f rad= %1.3f cs= %1.2f \t sn= %1.2f \t a= %1.6f;  b= %1.6f\n",
	degree,
        rad,
	cs,
	sn,
	 a,
	 b);
	}
return;
}