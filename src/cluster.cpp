#include "cluster.h"
#include <GL/glut.h>
#include <glog/logging.h>
#include <gflags/gflags.h>
#include "display.h"
#include <iostream>
#include <stdio.h>
#include <fstream>


Cluster::Cluster()
{
	n_center = 1;
	global_done = false;
	colors = std::vector<std::vector<float> >(n_center);
	for(int i=0;i<n_center;i++)
	{
		colors[i] = std::vector<float>(3);
		colors[i][0] = rand_float();
		colors[i][1] = rand_float();
		colors[i][2] = rand_float();
	}
}
void Cluster::gl_start(int n_center)
{
	CHECK_GT(n_center,1) << "cluster centers should be more than 1";
	this->n_center = n_center;
	gl_data = dataset.get_data();
	gl_centers = choice(gl_data,n_center);
	gl_clusterOf = std::vector<int>(gl_data.size());
	gl_clusterOf_last = std::vector<int>(gl_data.size());
	gl_clusters = std::vector<std::vector<Record> >(n_center);

	colors = std::vector<std::vector<float> >(n_center);
	for(int i=0;i<n_center;i++)
	{
		colors[i] = std::vector<float>(3);
		colors[i][0] = rand_float();
		colors[i][1] = rand_float();
		colors[i][2] = rand_float();
	}

	float xmax,xmin,ymax,ymin,zmax,zmin;
	xmin = xmax = gl_data[0].x;
	ymin = ymax = gl_data[0].y;
	zmin = zmax = gl_data[0].z;

	for(int i=1;i<gl_data.size();i++)
	{
		if(gl_data[i].x > xmax) xmax = gl_data[i].x;	
		if(gl_data[i].x < xmin) xmin = gl_data[i].x;	
		if(gl_data[i].y > ymax) ymax = gl_data[i].y;	
		if(gl_data[i].y < ymin) ymin = gl_data[i].y;	
		if(gl_data[i].z > zmax) zmax = gl_data[i].z;	
		if(gl_data[i].z < zmin) zmin = gl_data[i].z;	
	}
	float bmin[3];
	float bmax[3];
	bmin[0] = xmin; bmin[1] = ymin; bmin[2] = zmin;
	bmax[0] = xmax; bmax[1] = ymax; bmax[2] = zmax;
	SetBoundaryBox(bmin,bmax);

	gl_change = true;
	gl_done = false;
	gl_iter = 0;
	gl_step(1);
}
bool Cluster::gl_step(int n)
{
	for(int q=0;q<n;q++)
	{
		if(gl_done)break;
		gl_iter++;
		std::cout << "Iter:" << gl_iter << std::endl;
		assign(gl_centers,gl_data,gl_clusterOf,gl_clusters);

		gl_change = false;
		for(int i=0;i<gl_data.size();i++)
			if(gl_clusterOf[i] != gl_clusterOf_last[i])
			{
				gl_change = true;
				break;	
			}
		gl_clusterOf_last = gl_clusterOf;
		if(gl_change) // center should be updated
		{
			for(int i=0;i<gl_clusters.size();i++)
				gl_centers[i] = mean(gl_clusters[i]);	
		}else{
			gl_done = true;
			global_done = true;
		}
	}
	//gl_data[0].printData();
	//gl_data[1].printData();
	_centers = gl_centers;
	_clusters = gl_clusters;
	_clusterOf = gl_clusterOf;
	return gl_done;
}		

void Cluster::train(int n_center)
{
	char name[100];
	sprintf(name,"./result/Kmeans_result_n%d.txt",n_center);
	std::ofstream out(name);
	out << "Kmeans for " << n_center<< " centers"<<std::endl;
	global_done = false;
	CHECK_GT(n_center,1) << "cluster centers should be more than 1";
	// pick centers randomly
	std::vector<Record> data = dataset.get_data();
	
	std::vector<Record> centers = choice(data,n_center);
	std::vector<int> clusterOf(data.size());
	std::vector<int> clusterOf_last(data.size());
	std::vector<std::vector<Record> > clusters(n_center);
	bool change = true;
	int iter = 0;

	while(change)
	{
		iter++;
		std::cout << "Iter:" << iter << std::endl;
		out << "Iter " << iter << " SSE ";
		assign(centers,data,clusterOf,clusters);

		change = false;
		for(int i=0;i<data.size();i++)
			if(clusterOf[i] != clusterOf_last[i])
			{
				change = true;
				break;	
			}
		clusterOf_last = clusterOf;
		if(change) // center should be updated
		{
			for(int i=0;i<clusters.size();i++)
				centers[i] = mean(clusters[i]);	
		}
		float sse = SSE(centers,clusters);
		out << sse << std::endl;
	}
	
	std::cout << "Cluster Done"<<std::endl;
	for(int i=0;i<clusters.size();i++)
	{
		std::cout << "cluster: "<< i+1 << " size: "<<clusters[i].size()<< std::endl;
		//for(int j=0;j<clusters[i].size();j++)
		//{
		//		std::cout << "\t R:" << j+1;
		//		clusters[i][j].printData();
		//}
		//std::cout << "****************************"<<std::endl;
	}
	_centers = centers;
	_clusters = clusters;
	_clusterOf = clusterOf;
	global_done = true;
}

float Cluster::SSE(const std::vector<Record> &centers,const std::vector<std::vector<Record> > &clusters)const
{
	float res = 0.0;
	for(int i=0;i<clusters.size();i++)
		for(int j=0;j<clusters[i].size();j++)
			res += distance(clusters[i][j],centers[i]);
	return res;
}
void Cluster::assign(const std::vector<Record>&centers,const std::vector<Record>&dataset,std::vector<int>& clusterOf,std::vector<std::vector<Record> > &clusters)const // assign records in dataset to clusters,return cluster ID
{
	int n_centers = centers.size();
	std::vector<float> dis(n_centers);

	clusterOf = std::vector<int>(dataset.size());
	clusters = std::vector<std::vector<Record> >(n_centers);
	
	for(int i=0;i<dataset.size();i++)
	{
		float min;
		int belong=0;
		for(int j=0;j<n_centers;j++)
			dis[j]  = distance(dataset[i],centers[j]);
		argmin(dis,&min,&belong); // min distance
		clusterOf[i] = belong;
		clusters[belong].push_back(dataset[i]);
	}
}
float Cluster::distance(const Record& a,const Record&b)const
{
	// ignore id
	// d = (x0-x1)^2+(y0-y1)^2+(z0-z1)^2
	return (pow(a.x-b.x,2)+pow(a.y-b.y,2)+pow(a.z-b.z,2));
}
Record Cluster::mean(const std::vector<Record>& a)const
{
	Record r(0,0,0,0);
	for(int i=0;i<a.size();i++)
	{
		//r.index += a[i].index;
		r.x += a[i].x;
		r.y += a[i].y;
		r.z += a[i].z;
	}
	r.x /= a.size();
	r.y /= a.size();
	r.z /= a.size();
	return r;
}

bool Cluster::output(const std::string& outpath)const
{
	Writer w(outpath);
	return w.write(_clusters);
}

void Cluster::draw()const
{
	glShadeModel(GL_FLAT); 
	glEnable(GL_POLYGON_OFFSET_FILL);
	glPointSize(3);
	glBegin(GL_POINTS);
	for(int i=0;i<_clusters.size();i++)
	{
		//glColor3f(rand_float(),rand_float(),rand_float());
		glColor3f(colors[i][0],colors[i][1],colors[i][2]);
		for(int j=0;j<_clusters[i].size();j++)
			glVertex3d(_clusters[i][j].x,_clusters[i][j].y,_clusters[i][j].z);
	}	
	
	glEnd();
	glDisable(GL_POLYGON_OFFSET_FILL);
	
}

void Cluster::evaluate()const
{
	std::cout << "Kmeans for "<< n_center << std::endl <<"SSE:" << SSE(_centers,_clusters)<< std::endl;
}
