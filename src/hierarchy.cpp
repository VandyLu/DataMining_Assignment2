#include "hierarchy.h"
#include <GL/glut.h>
#include <glog/logging.h>
#include <gflags/gflags.h>
#include "display.h"

HierarchyCluster::HierarchyCluster()
{
	n_center = 1;
	dye(n_center);
	global_done = false;
}
// n_center: if n_center<0, let echa record be a cluster at the beginning
void HierarchyCluster::gl_start(int n_sample,int n_center,int n_remain,Similarity method)
{
	//CHECK_LE(n_sample,dataset.get_data().size()) << "n_sample greater than dataset size";
	// init algrithom
	this->method = method;
	this->n_remain = n_remain;
	this->n_center = n_center;
	if(n_sample<0)
	{
		gl_data = dataset.get_data();
		n_sample = gl_data.size();
	}else gl_data = choice(dataset.get_data(),n_sample);
	// kmeans to divide the dataset
	train(n_center);

/*
	// calc proximity matrix
	proximityMat = std::vector<std::vector<float> >(n_center);
	for(int i=0;i<n_center;i++)
	{
		proximityMat[i] = std::vector<float>(n_center);
		proximityMat[i][i] = 10e10; // to avoid compare with itself 
		for(int j=i+1;j<n_center;j++)
		{
			proximityMat[i][j] = proximity(i,j,method);
			//proximityMat[j][i] = proximityMat[i][j];
		}
	}*/
	
	dye(n_center);

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
	upper = std::vector<int> (n_center);
	for(int i=0;i<upper.size();i++) upper[i]=i;
	gl_clusters = _clusters;
	gl_centers = _centers;
	dye(n_center);
}
	
bool HierarchyCluster::cure_step()
{
	cure();
	return true;
}
bool HierarchyCluster::cure()
{
	// step 1
		std::cout << "n_center" << n_center<<std::endl;
	for(int i=0;i<gl_clusters.size();i++){
		gl_clusters[i] = choice(gl_clusters[i],n_remain);
		gl_centers[i] = mean(gl_clusters[i]);
		//gl_centers[i] = shrink(gl_clusters[i]);
		//std::cout << "ss"<<i+1 << gl_clusters[i].size()<<std::endl;
	}
	proximityMat = calcProx(gl_clusters,gl_centers);

	int ia,ib;
	proximityMatMin(ia,ib);
	mergeClusters(ia,ib);
	shrink(gl_clusters[ia],0.8);
	for(int i=0;i<_clusters[ib].size();i++)
	{
		_clusters[ia].push_back(_clusters[ib][i]);
	}
	rmItem(_clusters,ib);
		//for(int i=0;i<gl_clusters.size();i++)
	//	std::cout << i <<" num:" << gl_clusters[i].size()<<std::endl;
	return true;	
}
// get _clusters _clusterOf _centers
// 1. choice n_remain samples
// 2. shrink them to _center
// 3. calc proximityMat again
// 4. 
/*
bool HierarchyCluster::gl_step(int n)
{
	for(int q=0;q<n;q++)
	{
		if(gl_done){
			break;
		}
		gl_iter++;
		std::cout << "Iter:" << gl_iter << std::endl;

		int ia,ib;
		proximityMatMin(ia,ib);
		// merge two clusters
		//mergeClusters(ia,ib);
		if(n_center<=2)
			gl_done = true;
	}
	if(!gl_done)
	{
		std::cout << "number of clusters:" << n_center<<std::endl;
	}else{
		std::cout << "Cluster Done" << std::endl;
	}
	//gl_data[0].printData();
	//gl_data[1].printData();
	
	dye(n_center);

	_centers = gl_centers;
	_clusters = gl_clusters;
	_clusterOf = gl_clusterOf;
	return gl_done;
}	*/

//for pre-cluster kmeans
void HierarchyCluster::train(int n_center)
{
	global_done = false;
	CHECK_GT(n_center,1) << "cluster centers should be more than 1";
	// pick centers randomly
	std::vector<Record> data = gl_data;
	
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
	}
	
	std::cout << "Kmeans prepart Done"<<std::endl;
	std::cout << "n_center:"<<n_center <<std::endl;
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
}

float HierarchyCluster::SSE(const std::vector<Record> &centers,const std::vector<std::vector<Record> > &clusters)const
{
	float res = 0.0;
	for(int i=0;i<clusters.size();i++)
		for(int j=0;j<clusters[i].size();j++)
			res += distance(clusters[i][j],centers[i]);
	return res;
}
void HierarchyCluster::assign(const std::vector<Record>&centers,const std::vector<Record>&dataset,std::vector<int>& clusterOf,std::vector<std::vector<Record> > &clusters)const // assign records in dataset to clusters,return cluster ID
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
float HierarchyCluster::distance(const Record& a,const Record&b)const
{
	// ignore id
	// d = (x0-x1)^2+(y0-y1)^2+(z0-z1)^2
	return (pow(a.x-b.x,2)+pow(a.y-b.y,2)+pow(a.z-b.z,2));
}
Record HierarchyCluster::mean(const std::vector<Record>& a)const
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

bool HierarchyCluster::output(const std::string& outpath)const
{
	Writer w(outpath);
	return w.write(_clusters);
}

void HierarchyCluster::draw()const
{
	glShadeModel(GL_FLAT); 
	glEnable(GL_POLYGON_OFFSET_FILL);
	glPointSize(3);
	glBegin(GL_POINTS);
	for(int i=0;i<_clusters.size();i++)
	{
		//glColor3f(rand_float(),rand_float(),rand_float());
		//std::vector<float> color = colors[upper[i]];
		std::vector<float> color = colors[i];
		glColor3f(color[0],color[1],color[2]);
		for(int j=0;j<_clusters[i].size();j++)
			glVertex3d(_clusters[i][j].x,_clusters[i][j].y,_clusters[i][j].z);
	}	
	
	glEnd();
	glDisable(GL_POLYGON_OFFSET_FILL);
	
}

void HierarchyCluster::evaluate()const
{
	std::cout << "Hierarchy Cluster" << std::endl <<"SSE:" << SSE(_centers,_clusters)<< std::endl;
}
float HierarchyCluster::proximity(const std::vector<std::vector<Record> > &clusters,const std::vector<Record>&centers,int ia,int ib,Similarity method)const
{
	float t;
	CHECK_LT(ia,n_center) << "ia greater than n_center";
	CHECK_LT(ib,n_center) << "ia greater than n_center";
	const std::vector<Record> &a = clusters[ia];
	const std::vector<Record> &b = clusters[ib];

	if(method == MIN)
	{
		t = 10e10;
		for(int i=0;i<a.size();i++)
			for(int j=0;j<b.size();j++)
			{
				float dis = distance(a[i],b[j]);
				t = (dis<t ? dis:t);
			}
	}else if(method == MAX)
	{
		t = -10e10;
		for(int i=0;i<a.size();i++)
			for(int j=0;j<b.size();j++)
			{
				float dis = distance(a[i],b[j]);
				t = (dis>t ? dis:t);
			}
	}else if(method == GROUP_AVG)
	{
		LOG(WARNING) << "GROUP_AVG Not Implemented";
		for(int i=0;i<a.size();i++)
			for(int j=0;j<b.size();j++)
			{
				float dis = distance(a[i],b[j]);
				t = (dis<t ? dis:t);
			}
	}else if(method == CENTER_DIST)
	{
		t = distance(centers[ia],centers[ib]);
	}

	return t;
}
void HierarchyCluster::dye(int n) // dye clusters
{
	colors = std::vector<std::vector<float> >(n);
	for(int i=0;i<n;i++)
	{
		colors[i] = std::vector<float>(3);
		colors[i][0] = rand_float();
		colors[i][1] = rand_float();
		colors[i][2] = rand_float();
	}
}
float HierarchyCluster::proximityMatMin(int& ia,int &ib)const
{
	ia = 0;
	ib = 1;
	float min = proximityMat[ia][ib];
	for(int i=0;i<n_center;i++)
	{
		for(int j=i+1;j<n_center;j++)
		{
			if(proximityMat[i][j]<min)
			{
				min = proximityMat[i][j];
				ia = i;
				ib = j;
			}
		}
	}
	return min;
}
void HierarchyCluster::mergeClusters(int ia,int ib)
{
	CHECK_LT(ia,n_center) << "Merge ia too big";
	CHECK_LT(ib,n_center) << "Merge ib too big";
	CHECK_NE(ia,ib) << "Merge ia == ib";
	// get new cluster
	if(ia>ib){ int ic = ia; ia = ib;ib = ic;}
	for(int i=0;i<gl_clusters[ib].size();i++)
		gl_clusters[ia].push_back(gl_clusters[ib][i]);
	// cluster ia need recalc prox
	// cluster ib should be rm
	//rmRowCol(proximityMat,ib);
	rmItem(gl_clusters,ib);
	rmItem(gl_centers,ib);
	//gl_centers[ia] = mean(gl_clusters[ia]);

	n_center--;
	/*for(int i=0;i<n_center;i++)
	{
		if(i==ia)continue;
		proximityMat[ia][i] = proximity(ia,i,method);
		proximityMat[i][ia] = proximityMat[ia][i];
	}*/
	// clusters updated
	// proximityMat updated
	// centers updated
}
Record HierarchyCluster::shrink(std::vector<Record>& cluster,float lamda)const
{
	Record t = mean(cluster);
	for(int i=0;i<cluster.size();i++)
	{
		cluster[i].x = lamda*cluster[i].x+(1.0-lamda)*t.x; 
		cluster[i].y = lamda*cluster[i].y+(1.0-lamda)*t.y; 
		cluster[i].z = lamda*cluster[i].z+(1.0-lamda)*t.z; 
	}
	return t;
}
std::vector<std::vector<float> > HierarchyCluster::calcProx(const std::vector<std::vector<Record> >&clusters,const std::vector<Record>&centers)const
{
	std::vector<std::vector<float> >p(n_center);
	for(int i=0;i<n_center;i++){
		p[i] = std::vector<float>(n_center);
		for(int j=i+1;j<n_center;j++)
			p[i][j] = proximity(clusters,centers,i,j,MIN);
	}
	return p;
}
