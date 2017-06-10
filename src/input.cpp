#include "input.h"

using namespace std;

bool Dataset::load(const string &dbpath)
{
	return load(dbpath.c_str());
}
bool Dataset::load(const char* dbpath)
{
	ifstream in(dbpath);
	//CHECK(in.is_open()) << "Reading dataset failed!";

	int index;
	char c;
	float x,y,z;
	while(!in.eof())
	{
		in >> index >> c >> x >> c >> y >> c >> z;
		push(index,x,y,z);
	}
	in.close();
	return true;
}
int Dataset::push(int i,float x,float y,float z)
{
	data.push_back(Record(i,x,y,z));
	return 1;
}
void Dataset::printData()
{
	for(int i=0;i<data.size();i++)
	{
		Record r = data[i];
		cout << r.index << ',' << r.x << ',' << r.y <<',' << r.z <<endl;
	}
	cout << "Total records:" << data.size() << endl;
}
void Record::printData()
{
	cout << index << ',' << x << ',' << y <<',' << z <<endl;
}


