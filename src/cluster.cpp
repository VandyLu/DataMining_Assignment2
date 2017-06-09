#include "input.h"
#include <glog/logging.h>
#include <stdlib.h>
#include "common.h"

// k means
class Cluster(){
private:
	Dataset dataset;

public:
	Cluster(){}
	~Cluster(){}
	
	void load(const std::string& s){ dataset.load(s);}
	void train(int center);
	void test();

};

void Cluster::train(int n_center)
{
	CHECK_GT(dataset.size(),0) << "Dataset size is 0!";
	CHECK_GT(n_center,1) << "cluster center should be greater than 1!";
	CHECK_GT(dataset.size(),n_center) << "centers size greater than data size";

	// pick centers randomly
	std::vector<int> init_centers = choice(range(dataset.size()),n_center);
	std::vector<Record> data = dataset.get_data();

	std::vector<float,float,float> init_centers_pt;
	for(int i=0;i<init_centers.size())
	{
		
	}

}
