#ifndef __INPUT_H
#define __INPUT_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>


class Record{
public:
	int index;
	float x,y,z;
	Record(int i=0,float _x=0,float _y=0,float _z=0):index(i),x(_x),y(_y),z(_z){}
};
class Dataset{
		private:
				std::vector<Record> data;	
		public:
	Dataset(){}
	~Dataset(){}

	void load(const std::string &dbpath);
	void load(const char* c);
	int push(int i,float x,float y,float z);
	std::vector<Record>& get_data() { return data;}
	void printData();
	
};

#endif
