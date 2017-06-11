#ifndef __CLUSTER_H
#define __CLUSTER_H

#include "input.h"
#include <stdlib.h>
#include "common.h"

// k means
class Cluster{
private:
	Dataset dataset;
	int n_center;
	std::vector<std::vector<float> >colors;
	// cluster result
	std::vector<std::vector<Record> > _clusters;
	std::vector<int> _clusterOf;

	std::vector<float> SSE(const std::vector<Record> &centers,const std::vector<Record>&dataset)const;
	void assign(const std::vector<Record>&centers,const std::vector<Record>&dataset,std::vector<int>& clusterOf,std::vector<std::vector<Record> > &clusters)const;
	float distance(const Record& x,const Record&y)const;
	Record mean(const std::vector<Record>& a)const;

	void step();
	
	std::vector<Record> gl_data;
	std::vector<Record> gl_centers;
	std::vector<int> gl_clusterOf;
	std::vector<int> gl_clusterOf_last;
	std::vector<std::vector<Record> >gl_clusters;
	bool gl_change;
	bool gl_done;
	int gl_iter;
	
	
public:
	Cluster();
	~Cluster(){}
	
	bool load(const std::string& s){ dataset.load(s);}
	void train(int center);
	void test();
	bool output(const std::string& outpath)const;
	void draw()const;
	void gl_start(int n_center);
	bool gl_step(int n);

};



#endif
