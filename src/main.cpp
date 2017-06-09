#include <iostream>
#include <string>
#include <vector>
#include <glog/logging.h>
#include <gflags/gflags.h>
#include "input.h"
#include "common.h"
#include <map>

DEFINE_string(opt,"input",
		"input -- test data input"
		"test -- test a model"
		"convert -- convert ascii file to binary file");
DEFINE_string(in_path,"","file path");


int test(void);
int input(void);


int main(int argc,char *argv[])
{
	google::ParseCommandLineFlags(&argc,&argv,true);
	google::InitGoogleLogging(argv[0]);

	FLAGS_log_dir = "./log";
	std::cout << "Desired operation:"<< FLAGS_opt << std::endl; 
	if(FLAGS_opt == "input")
	{
		input();
	}else if(FLAGS_opt == "test")
	{
		test();
	}

	
	return 0;	
}
int test(void)
{
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
