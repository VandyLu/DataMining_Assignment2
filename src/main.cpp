#include <iostream>
#include <string>
#include <vector>
#include "input.h"
#include "common.h"
#include <map>
#include "cluster.h"
#include "display.h"

int mode = KMEANS;
Cluster kmeans;

int test(void);
int input(void);
int cluster(void);


DEFINE_string(opt,"test",
				"test for some testing"
				"cluster for clustering"
				"gl for OpenGL plotting");
DEFINE_string(in_path,"data/3D_spatial_network.txt","dataset path");
DEFINE_string(out_path,"data_for_python/r.txt","info out path");
DEFINE_int32(n,10,"centers for clustering");


//std::string FLAGS_opt("cluster");
//std::string FLAGS_in_path("data/3D_spatial_network.txt");
int main(int argc,char *argv[])
{
	google::InitGoogleLogging(argv[0]);
	google::ParseCommandLineFlags(&argc,&argv,true);
	// for showing data
	glutInit(&argc,argv);

	std::cout << "Desired operation:"<< FLAGS_opt << std::endl; 
//	FLAGS_opt = std::string("gl");

	if(FLAGS_opt == "gl")
	{
		InitGL();
		InitMenu();
		glutMainLoop();		
	}else if(FLAGS_opt == "test")
	{
		test();
	}else if(FLAGS_opt == "cluster")
	{
		cluster();
	}
	return 0;	
}

// GLUT menu callback function
void MenuCallback(int value) {
	switch (value) {
	case 99: exit(0); break;
	case KMEANS:
	{
		kmeans.load(FLAGS_in_path);
		kmeans.gl_start(FLAGS_n);
		//kmeans.train(10);
		//CHECK(kmeans.output(FLAGS_out_path)) << "Output failed";
		break;
	}
	default: 
		mode = value;
				glutPostRedisplay();
		break;
	}
}
// GLUT keyboard callback function
void KeyboardFunc(unsigned char ch, int x, int y) { 
	switch (ch) { 
	case 'c':
			while(!kmeans.gl_step(1));
			break;
	case 'n':kmeans.gl_step(1);break;
	case 27:
		exit(0);
		break;
	}
	glutPostRedisplay();
}

void DrawKmeans() {
	kmeans.draw();
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
	kmeans.train(FLAGS_n);
	CHECK(kmeans.output(FLAGS_out_path)) << "Output failed";
	return 0;
}
