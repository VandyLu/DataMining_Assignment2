//
// Created by advanced on 17-6-17.
//
#include "Density_Evaluate.h"
#include "display.h"

void Density_Evaluate::Evaluate_Procedure() {
    read_data_set();
    read_cluster_result();
    calculate_SEE();

	float xmax,xmin,ymax,ymin,zmax,zmin;
	
	xmin = xmax = data[0].x;
	ymin = ymax = data[0].y;
	zmin = zmax = data[0].z;
	for(int i=1;i<data.size();i++)
	{
		if(data[i].x > xmax) xmax = data[i].x;	
		if(data[i].x < xmin) xmin = data[i].x;	
		if(data[i].y > ymax) ymax = data[i].y;	
		if(data[i].y < ymin) ymin = data[i].y;	
		if(data[i].z > zmax) zmax = data[i].z;	
		if(data[i].z < zmin) zmin = data[i].z;	
	}
	float bmin[3];
	float bmax[3];
	bmin[0] = xmin; bmin[1] = ymin; bmin[2] = zmin;
	bmax[0] = xmax; bmax[1] = ymax; bmax[2] = zmax;
	SetBoundaryBox(bmin,bmax);
	
    draw();
}

void Density_Evaluate::read_data_set() {
    srand(static_cast<unsigned int>(time(NULL)));
    std::string line;
    std::ifstream inFile(inputAddress);
    if (!inFile.is_open())
        std::cout << "not open the input text ! \n";
    float R = 6371004; //m
    while (getline(inFile, line)){
        size_t sz1, sz2, sz3;
        DATASTRUCT newData;
        newData.id = stoi(line, &sz1);
        float longitude = stof(line.substr(sz1+1), &sz2);
        float latitude = stof(line.substr(sz1+sz2+2), &sz3);
        float height = stof(line.substr(sz1+sz2+sz3+3));

        toSphere(R, longitude, latitude, height, &newData.x, &newData.y, &newData.z);       //  转直角坐标系

        data.push_back(newData);
    }
}

void Density_Evaluate::read_cluster_result() {
    std::string line;
    std::ifstream inFile(cluster_Result_Address);
    if (!inFile.is_open())
        std::cout << "not open the cluster result text ! \n";
    getline(inFile, line);      //  read cluster number
    int cluster_ID = -1;
    while (getline(inFile, line)) {
        if (line[0] == 'c'){
            std::vector<int> tmp;
            _cluster.push_back(tmp);
            cluster_ID++;
            printf("cluster : %d\n", cluster_ID);
            continue;
        }
        int tmp = stoi(line);
        _cluster[cluster_ID].push_back(tmp);
    }
}

void Density_Evaluate::calculate_SEE() {
    std::ofstream outFile(SEE_result_Address);
    if (!outFile.is_open())
        std::cout << "not open SEE result text  \n" ;

    size_t number_of_cluster = _cluster.size();
    float total_SEE = 0;
    for (int i = 0; i < number_of_cluster; i++){
        DATASTRUCT center;
        size_t size_of_a_cluster = _cluster[i].size();
        for (int j = 0; j < size_of_a_cluster; j++){
            center.x += data[_cluster[i][j]].x;
            center.y += data[_cluster[i][j]].y;
            center.z += data[_cluster[i][j]].z;
        }
        center.x /= size_of_a_cluster;
        center.y /= size_of_a_cluster;
        center.z /= size_of_a_cluster;

        float SEE = 0;
        for (int j = 0; j < size_of_a_cluster; j++){
            SEE += distance(data[_cluster[i][j]], center);
        }
        total_SEE += SEE;

        outFile << "cluster " << i << "'s SEE : " << SEE << "\n";
    }

    outFile << "cluster total SEE : "<< total_SEE << "\n";
}


void Density_Evaluate::draw() {
	glShadeModel(GL_FLAT); 
	glEnable(GL_POLYGON_OFFSET_FILL);
	glPointSize(3);
    glBegin(GL_POINTS);
    size_t number_of_cluster = _cluster.size();
	std::cout << number_of_cluster<<std::endl;
    for(int i=0;i<number_of_cluster;i++)
    {
        glColor3f(((float)rand())/RAND_MAX,((float)rand())/RAND_MAX, (float)rand()/RAND_MAX);
        size_t size_of_a_cluster = _cluster[i].size();
        for(int j=0; j<size_of_a_cluster; j++)
            glVertex3d(data[_cluster[i][j]].x, data[_cluster[i][j]].y, data[_cluster[i][j]].z);
    }
    glEnd();
	glDisable(GL_POLYGON_OFFSET_FILL);
}


void Density_Evaluate::toSphere(float r,float lon,float lat,float h,float *x,float *y,float *z) {
    const float pi = static_cast<float>(3.1415926);
    float R = r+h;
    lon *= (pi/180);
    lat *= (pi/180);
    *z = static_cast<float>(sin(lat)*R);
    *x = static_cast<float>(cos(lat)*R*sin(lon));
    *y = static_cast<float>(cos(lat)*R*cos(lon));
}

int  Density_Evaluate::transfer_str_to_int(std::string line, int start, int end) {
    int ans = 0;
    for (int i = start; i <= end; i++)
        ans = ans * 10 + line[i] - '0';
    return ans;
}

float Density_Evaluate::distance(const DATASTRUCT p1, const DATASTRUCT p2) {
    float tmp = (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y) + (p1.z - p2.z) * (p1.z - p2.z);
    return static_cast<float>(sqrt(tmp));
}
