#include "common.h"


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
