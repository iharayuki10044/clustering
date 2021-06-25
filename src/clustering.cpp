#include "clustering/clustering.hpp"

Clustering::Clustering(void)
{

}

void Clustering::executor(void)
{
    std::cout << "kk" << std::endl;
}

double Clustering::cal_distance_2d(Cluster cluster_a, Cluster cluster_b)
{
    double distance;
    distance = sqrt( (cluster_a.point_x - cluster_b.point_x)*(cluster_a.point_x - cluster_b.point_x) 
                    +(cluster_a.point_y - cluster_b.point_y)*(cluster_a.point_y - cluster_b.point_y) );
    return distance;
}

int main(int argc, char** argv)
{
    Clustering clustering;
    clustering.executor();

    return 0;
}