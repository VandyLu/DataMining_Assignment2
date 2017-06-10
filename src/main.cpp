#include <iostream>
#include <string>
#include <vector>
#include "input.h"
#include "common.h"
#include <map>
#include "cluster.h"


int test(void);
int input(void);
int cluster(void);


std::string FLAGS_opt("cluster");
std::string FLAGS_in_path("data/3D_spatial_network.txt");
int main(int argc,char *argv[])
{
	std::cout << "Desired operation:"<< FLAGS_opt << std::endl; 

	if(FLAGS_opt == "input")
	{
		input();
	}else if(FLAGS_opt == "test")
	{
		test();
	}else if(FLAGS_opt == "cluster")
	{
		cluster();
	}
	return 0;	
}
int test(void)
{
		Record r(12,3.0,4.0,5.0);
		std::cout << r.ToString() << std::endl;
		Writer w(std::string("test.txt"));
		std::vector<std::vector<Record> > clusters(2);
		clusters[0].push_back(r);
		clusters[0].push_back(r);
		clusters[1].push_back(r);
		r.x = 10;
		clusters[1].push_back(r);
		w.write(clusters);

	std::cout << "rand_int(10)" << std::endl;
	for(int i=0;i<10;i++)
		std::cout << rand_int(10) << ',';
	std::cout << std::endl;

	std::cout << "range(10)" << std::endl;
	std::vector<int> x = range(10);
	for(int i=0;i<x.size();i++)
		std::cout << x[i] << ',';
	std::cout << std::endl;
	
	std::cout << "shuffle(range(10))" << std::endl;
	x = range(10);
	x = shuffle(x);
	for(int i=0;i<x.size();i++)
		std::cout << x[i] << ',';
	std::cout << std::endl;

	x = range(10);
	x = choice(x,3);
	for(int i=0;i<3;i++)
		std::cout<< x[i] << ',';
	std::cout << std::endl;
	return 0;
}
int input(void)
{
	Dataset dataset;
	dataset.load(FLAGS_in_path);
	dataset.printData();
	return 0;
}
int cluster(void)
{
	Cluster kmeans;
	kmeans.load(FLAGS_in_path);
	kmeans.train(10);
	std::cout << kmeans.output("data_for_python/r.txt") << std::endl;
	return 0;
}
