#ifndef __HIERARCHY_H_
#define __HIERARCHY_H

#include "input.h"
#include <stdlib.h>
#include "common.h"

class HierarchyCluster{
public:
	enum Similarity{MIN,MAX,GROUP_AVG,CENTER_DIST};
private:

	Dataset dataset;
	int n_center;
	Similarity method;

	int n_remain;
	std::vector<int> upper;

	std::vector<std::vector<float> >colors;
	std::vector<std::vector<float> >proximityMat;
	//std::vector<bool> proximityMat_valid;
	// cluster result
	std::vector<Record> _centers;
	std::vector<std::vector<Record> > _clusters;
	std::vector<int> _clusterOf;

	float SSE(const std::vector<Record> &centers,const std::vector<std::vector<Record> > &clusters)const;
	void assign(const std::vector<Record>&centers,const std::vector<Record>&dataset,std::vector<int>& clusterOf,std::vector<std::vector<Record> > &clusters)const;
	float distance(const Record& x,const Record&y)const;
	Record mean(const std::vector<Record>& a)const;
	std::vector<std::vector<float> > calcProx(const std::vector<std::vector<Record> >&clusters,const std::vector<Record>&centers)const;
	float proximity(const std::vector<std::vector<Record> > &clusters,const std::vector<Record>&centers,int ia,int ib,Similarity method)const;
	float proximityMatMin(int& ia,int &ib)const;
	void mergeClusters(int ia,int ib);
	Record shrink(std::vector<Record>& cluster,float lamda=1.0)const;

	void dye(int n); // dye clusters

	std::vector<Record> gl_data;
	std::vector<Record> gl_centers;
	std::vector<int> gl_clusterOf;
	std::vector<int> gl_clusterOf_last;
	std::vector<std::vector<Record> >gl_clusters;
	
	bool gl_change;
	bool gl_done;
	int gl_iter;

	bool global_done; // for model evaluation,true whenyou are ready for evaluation 
	
	
public:
	HierarchyCluster();
	~HierarchyCluster(){}

	bool cure();
	bool cure_step();
	
	bool load(const std::string& s){ dataset.load(s);}
	void train(int center);
	void evaluate()const;
	bool output(const std::string& outpath)const;
	void draw()const;
	void gl_start(int n_sample,int n_center,int n_remain,Similarity method);
	bool gl_step(int n);

};



#endif
