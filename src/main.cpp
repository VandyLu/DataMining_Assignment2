#include <iostream>
#include <string>
#include <vector>
#include <glog/logging.h>
#include <gflags/gflags.h>
#include "input.h"



DEFINE_string(opt,"input",
		"input -- test data input"
		"test -- test a model"
		"convert -- convert ascii file to binary file");
DEFINE_string(in_path,"","file path");


int main(int argc,char *argv[])
{
	google::ParseCommandLineFlags(&argc,&argv,true);
	google::InitGoogleLogging(argv[0]);

	FLAGS_log_dir = "./log";
	std::cout << "Desired operation:"<< FLAGS_opt << std::endl; 
	if(FLAGS_opt == "input")
	{
		Dataset dataset;
		dataset.load(FLAGS_in_path);
		dataset.printData();
	}

	
	return 0;	
}
