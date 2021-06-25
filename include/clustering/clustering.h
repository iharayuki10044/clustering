#ifndef __CLUSTERING_H_
#define __CLUSTERING_H_

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <fstream>
#include <sstream>

//#include "Eigen/Geometry"

class Clustering
{
public:

class Cluster
    {
    public:
        std::vector<double> point;
        int cluster_id;
    private:
    };
    typedef std::vector<Cluster> Clusters;

    Clustering(void);

    void executor(void);
    void formattor(void);
    void data_inputter(std::string, Clusters& input_data, int&, int&);
    void simple_cluster(Clusters& input_data);
    std::vector<std::string> split_string(std::string& input, char delimiter);
    double cal_distance_2d(const Cluster,const Cluster,const int);

private:
    int input_data_num;
    int input_dim;
    std::string input_file_name;

    Clusters input_data;
    
    
};

#endif