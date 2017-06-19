//
// Created by advanced on 17-6-17.
//

#ifndef DENSITY_EVALUATE_DENSITY_EVALUATE_H
#define DENSITY_EVALUATE_DENSITY_EVALUATE_H
#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include <string>
#include <cstdio>
#include <cstdlib>

class Density_Evaluate
{
public:
    void Evaluate_Procedure();
    void read_data_set();                        //  get input data
    void read_cluster_result();
    void calculate_SEE();
    void draw();

private:
    struct DATASTRUCT {
        int id;
        float x, y, z;
        bool core, noise;                        // if is core -- core = 1
        int border_master;                       // A's border_master is the point containing it
        int cluster_ID;

        DATASTRUCT(){
            core = noise = 0;                 //  not core  or noise
            border_master = -1;               //  not a border
            cluster_ID = -1;                  //  not belong to a cluster
            x = y = z = 0;
        }
    };

    std::vector<DATASTRUCT> data;
    std::vector<std::vector<int> > _cluster;         // cluster[i][j] is ith cluster's jth point

public:
    void toSphere(float r,float lon,float lat,float h,float *x,float *y,float *z);      //  transfer input to (x, y, z)
    int transfer_str_to_int(std::string line, int start, int end);
    float distance(const DATASTRUCT p1, const DATASTRUCT p2);
};

const char inputAddress[] = "/home/lfb/Projects/data_mining/assignment2/data/3D_spatial_network.txt";
const char cluster_Result_Address[] = "/home/lfb/Projects/data_mining/assignment2/result.txt";
const char SEE_result_Address[] = "/home/lfb/Projects/data_mining/assignment2/SEE_result.txt";

#endif //DENSITY_EVALUATE_DENSITY_EVALUATE_H
