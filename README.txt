Kmeans 聚类算法在 cluster.h cluster.cpp 中
draw 在cluster.cpp 的Cluster::draw中
Record,Dataset 在input.h input.cpp中

代码接口定义:

类型名称不可为Cluster 除非定义在namespace中
假设类型名称为 DensityCluster
class DensityCluster{
private:
	vector<vector> color; // 用于保存每个簇的颜色 
public:
	bool step(int n); // return true if done
	void draw()const; 
}

draw example:
void DensityCluster::draw()
{
	glBegin();
	for(int i=0;i<_clusters.size();i++)
	{
		glColor3f(colors[i][0],colors[i][1],colors[i][2]);
		for(int j=0;j<_clusters[i].size();j++)
			glVertex3d(_clusters[i][j].x,_clusters[i][j].y,_clusters[i][j].z);
	}
	glEnd();	
}
