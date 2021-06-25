#ifndef __CLUSTERING_H_
#define __CLUSTERING_H_

#include 
#include "Eigen/Core"
#include "Eigen/Dense"
#include "Eigen/LU"
//#include "Eigen/Geometry"

class Clustering
{
public:

class Cluster
    {
    public:
        int index_x;
        int index_y;
        double point_x;
        double point_y;
        int cluster_id;
    private:
    };
    typedef std::vector<Cluster> Clusters;

    Clustering(void);

    void Clustering_executor();
    double cal_distance_2d(const Cluster,const Cluster);

private:
    int input_data_num;
    
    
    
};

#endif