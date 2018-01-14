数据挖掘大作业2：聚类算法
==========================
#数据集：丹麦道路网络
	434875个数据： ID,longitude,latitude,height
#代码介绍：

Kmeans 聚类算法在 cluster.h cluster.cpp 中 <br>
层次型聚类算法在 hierarchy.h hierarchy.cpp 中<br>
DBscan 算法在 Density_Evaluate.h Density_Evaluate.cpp 中<br>

#环境配置：
linux,google-gflags,google-glog,OpenGL/freeglut

#运行：
git clone https://github.com/VandyLu/DataMining_Assignment2.git<br>

cd DataMining_Assignment2<br>
./build.sh<br>
make<br>

图形化结果显示<br>
./bin/assignment2 --opt gl [--n_sample number --n_center number --n_remain]<br>
在界面中右键选择 kmeans/hierarchy/dbscan<br>


Kmeans聚类 --n_center 指定簇的数量<br>
./bin/assignment2 --opt kmeans [--n_center number]<br>

Hierarchy聚类 --n_center 指定初始簇的数量 --n_remain 制定cure保留特征点数目<br>
./bin/assignment2 --opt hierarchy [--n_center number --n_sample number --n_remain number]<br>

DBscan聚类<br>
./bin/assignment2 --opt dbscan

![kmeans](https://github.com/VandyLu/DataMining_Assignment2/blob/master/kmeans_example.png)
