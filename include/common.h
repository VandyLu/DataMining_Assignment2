#ifndef __COMMOM_H
#define __COMMOM_H

#include <vector>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>
#include <glog/logging.h>
#include <gflags/gflags.h>


void toSphere(float r,float lon,float lat,float h,float *x,float *y,float *z);

inline int rand_int(int high=1)
{
	CHECK_GE(high,1) << "rand_int error";
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
	if(a.size()<=size)
		return a;

	std::vector<Dtype> tmp = a; // copy
	std::vector<Dtype> r;

	for(int i=0;i<size;i++)
	{
		CHECK_GE(tmp.size(),1) << "choice error";
		int del = rand_int((tmp.size()));
		typename std::vector<Dtype>::iterator it = tmp.begin()+del;
		r.push_back(*it);
		tmp.erase(it);
	}
	return r;	
}
template<typename Dtype>
void rmRow(std::vector<std::vector<Dtype> >& mat,int row)
{
	typename std::vector<std::vector<Dtype> >::iterator it = mat.begin()+row;
	mat.erase(it);
}
template<typename Dtype>
void rmCol(std::vector<std::vector<Dtype> >& mat,int col)
{
	for(int i=0;i<mat.size();i++)
	{
		typename std::vector<Dtype>::iterator it = mat[i].begin()+col;
		mat[i].erase(it);
	}
}
template<typename Dtype>
void rmRowCol(std::vector<std::vector<Dtype> >& mat,int n)
{
	rmRow(mat,n);
	rmCol(mat,n);
}

template<typename Dtype>
void rmItem(std::vector<Dtype> &v,int n)
{
	typename std::vector<Dtype>::iterator it = v.begin()+n;
	v.erase(it);
}
#endif
