#include "common.h"
#include <math.h>

void toSphere(float r,float lon,float lat,float h,float *x,float *y,float *z)
{
	const float pi = 3.1415926;
	float R = r+h;
	lon *= (pi/180);
	lat *= (pi/180);
	*z = sin(lat)*R;
	*x = cos(lat)*R*sin(lon);
	*y = cos(lat)*R*cos(lon);
}

std::vector<int> rand_int(int low,int high,int size)
{
		std::vector<int> r;
		for(int i=0;i<size;i++)
			r.push_back(rand_int(low,high));
		return r;
}

std::vector<int> range(int high)
{
	std::vector<int> r;
	for(int i=0;i<high;i++)
		r.push_back(i);
	return r;
}
