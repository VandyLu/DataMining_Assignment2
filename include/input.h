#ifndef __INPUT_H
#define __INPUT_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>


class Record{
public:
	int index;
	float x,y,z;
	Record(int i=0,float _x=0,float _y=0,float _z=0):index(i),x(_x),y(_y),z(_z){}
	void printData()const;
	std::string ToString()const;
};
class Dataset{
		private:
				std::vector<Record> data;	
		public:
	Dataset(){}
	~Dataset(){}

	bool load(const std::string &dbpath);
	bool load(const char* c);
	int push(int i,float x,float y,float z);
	std::vector<Record>& get_data() { return data;}
	void printData();
	int size()const{ return data.size();}
	
};

class Writer
{
public:

Writer(){}
Writer(const std::string& outpath):path(outpath){}
~Writer(){}

bool write(const std::vector<std::vector<Record> >& clusters);

private:
	std::string path;

};
#endif
