#ifndef __CLUSTER_H
#define __CLUSTER_H

#include "input.h"
#include <stdlib.h>
#include "common.h"

// k means
class Cluster{
private:
	Dataset dataset;
	std::vector<float> SSE(const std::vector<Record> &centers,const std::vector<Record>&dataset)const;
	void assign(const std::vector<Record>&centers,const std::vector<Record>&dataset,std::vector<int>& clusterOf,std::vector<std::vector<Record> > &clusters)const;
	float distance(const Record& x,const Record&y)const;
	Record mean(const std::vector<Record>& a)const;

	void step();
	
	
public:
	Cluster(){}
	~Cluster(){}
	
	bool load(const std::string& s){ dataset.load(s);}
	void train(int center);
	void test();

};



#endif
