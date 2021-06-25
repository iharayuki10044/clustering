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
        std::vector<double> distance;
        int cluster_id;
    private:
    };
    typedef std::vector<Cluster> Clusters;

    Clustering(void);

    void executor(void);
    void formattor(void);
    void data_inputter(std::string, Clusters& input_data, int&, int&);
    void cal_cluster_distance(Clusters& input_data, const int, const int, std::vector<double>&);
    void simple_clustering(Clusters& input_data, std::vector<double>);
    std::vector<std::string> split_string(std::string& input, char delimiter);
    double cal_distance(const Cluster,const Cluster,const int);
    std::vector<double> serch_min_distance(std::vector<double>);
    std::vector<int> get_id_from_distance_arry_id(const int);

private:
    int input_data_num;
    int input_data_dim;
    std::string input_file_name;

    std::vector<double> cluster_distance;

    Clusters input_data;
    
    
};

#endif