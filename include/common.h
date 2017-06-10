#ifndef __COMMOM_H
#define __COMMOM_H

#include <vector>
#include <stdlib.h>
#include <math.h>


inline int rand_int(int high)
{
	return rand()%high;
}
inline int rand_int(int low,int high)
{
	return low+rand()%(high-low);
}
inline float rand_float()
{
	return (float)rand()/RAND_MAX;
}	

// return x , low <= x < high
std::vector<int> rand_int(int low,int high,int size);
std::vector<int> range(int high);

template<typename Dtype>
void argmax(const std::vector<Dtype>& a,Dtype*max,int*arg)
{
	Dtype m = a[0];
	int n=0;
	for(int i=1;i<a.size();i++)
	{
		if(a[i]>m)
		{
			m = a[i];
			n = i;	
		}
	}
	*max = m;
	*arg = n;
}
template<typename Dtype>
void argmin(const std::vector<Dtype>& a,Dtype*min,int*arg)
{
	Dtype m = a[0];
	int n=0;
	for(int i=1;i<a.size();i++)
	{
		if(a[i]<m)
		{
			m = a[i];
			n = i;	
		}
	}
	*min = m;
	*arg = n;
}
template<typename Dtype>
std::vector<Dtype> shuffle(const std::vector<Dtype> &a)
{
	std::vector<Dtype> tmp = a; // copy
	std::vector<Dtype> r;
	int size = a.size();

	for(int i=0;i<size;i++)
	{
		int del = rand_int(tmp.size());
		typename std::vector<Dtype>::iterator it = tmp.begin()+del;
		r.push_back(*it);
		tmp.erase(it);
	}
	return r;
}
template<typename Dtype>
std::vector<Dtype> choice(const std::vector<Dtype> &a,int size)
{
	std::vector<Dtype> tmp = a; // copy
	std::vector<Dtype> r;

	for(int i=0;i<size;i++)
	{
		int del = rand_int(tmp.size());
		typename std::vector<Dtype>::iterator it = tmp.begin()+del;
		r.push_back(*it);
		tmp.erase(it);
	}
	return r;	
}
#endif
