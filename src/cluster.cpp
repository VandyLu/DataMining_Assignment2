#include "cluster.h"

void Cluster::train(int n_center)
{

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
		if(iter>10)break;
		assign(centers,data,clusterOf,clusters);

		change = false;
		for(int i=0;i<data.size();i++)
			if(clusterOf[i] != clusterOf_last[i])
			{
				change = true;
				break;	
			}
		if(change) // center should be updated
		{
			for(int i=0;i<clusters.size();i++)
				centers[i] = mean(clusters[i]);	
		}
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
	_clusters = clusters;
	_clusterOf = clusterOf;
}
/*
std::vector<float> Cluster::SSE(const std::vector<Record> &centers,const std::vector<Record>&dataset)const
{
	for(int i=0;i<centers;i++)
	{
		
	}
}*/
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
