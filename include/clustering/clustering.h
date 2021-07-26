#ifndef __CLUSTERING_H_
#define __CLUSTERING_H_

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <fstream>
#include <sstream>
#include <iomanip>

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

class FullCluster
    {
    public:
        std::vector<double> distance;
        std::vector<int> member_id;
    private:
    };
    typedef std::vector<FullCluster> FullClusters;


    Clustering(void);

    void executor(const double);
    void formattor(const double);
    void data_inputter(std::string, Clusters& input_data, int&);
    void cal_cluster_distance(Clusters& input_data, const int, std::vector<double>&);
    void simple_clustering(Clusters& input_data, std::vector<double>);
    std::vector<std::string> split_string(std::string& input, char delimiter);
    double cal_distance(const Cluster,const Cluster,const int);
    std::vector<double> serchi_min_distance(std::vector<double>&);
    std::vector<int> get_id_from_distance_array_id(const int);
    void change_id(Clusters& input_data, const std::vector<int>);

    void full_clustering(Clusters&, FullClusters&, std::vector<double>&);
    int get_disarray_id_from_id_pair(int, int);
    std::vector<int> serchi_min_dis_from_fullclusters();
    std::vector<FullCluster> create_new_clusters(std::vector<int>);


private:
    int input_data_dim;
    double threshold;
    std::string input_file_name;
    std::vector<double> cluster_distance;
    std::vector<int> cluster_num;

    Clusters input_data;
    FullClusters full_clusters;
};

#endif