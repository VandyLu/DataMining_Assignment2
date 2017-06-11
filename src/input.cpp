#include "input.h"
#include "common.h"

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
	float lon,lat,h;
	float x,y,z;
	float R = 6371004; //m
	while(!in.eof())
	{
		in >> index >> c >> lon >> c >> lat >> c >> h;
		toSphere(R,lon,lat,h,&x,&y,&z);
		// regularize
		x /= R;
		y /= R;
		z /= R;
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
void Record::printData()const
{
	cout << ToString() << endl;
}

string Record::ToString()const
{
	ostringstream ostr;
	ostr << index << ',' << x << ',' << y <<',' << z;
	return ostr.str();
}

bool Writer::write(const std::vector<std::vector<Record> >& clusters)
{
	ofstream out(path.c_str());
	if(!out.is_open())return false;
	for(int i=0;i<clusters.size();i++)
	{
		for(int j=0;j<clusters[i].size();j++)
		{
			out << clusters[i][j].ToString() << ","<< i<<endl;
		}
	}
	return true;
}
