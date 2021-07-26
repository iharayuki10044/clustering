#include "clustering/clustering.h"

Clustering::Clustering(void)
{

}

void Clustering::executor(const double command_line)
{
    Clustering::formattor(command_line);
    Clustering::data_inputter(input_file_name, input_data, input_data_dim);
    Clustering::cal_cluster_distance(input_data, input_data_dim, cluster_distance);
    Clustering::full_clustering(input_data, full_clusters, cluster_distance);

    // int i;
    // i = Clustering::get_disarray_id_from_id_pair(0,1);
    // std::cout << "dis index = " << i << std::endl;
    // i = Clustering::get_disarray_id_from_id_pair(1,0);
    // std::cout << "dis index = " << i << std::endl;
    // i = Clustering::get_disarray_id_from_id_pair(3,2);
    // std::cout << "dis index = " << i << std::endl;
    // i = Clustering::get_disarray_id_from_id_pair(2,3);
    // std::cout << "dis index = " << i << std::endl;
    // i = Clustering::get_disarray_id_from_id_pair(4,3);
    // std::cout << "dis index = " << i << std::endl;
    // i = Clustering::get_disarray_id_from_id_pair(3,4);
    // std::cout << "dis index = " << i << std::endl;

}

void Clustering::formattor(const double input)
{
    input_file_name = "../../dataset/input_data_file.csv";
    input_data.clear();
    cluster_distance.clear();
    cluster_num.clear();
    threshold = input;
}

void Clustering::data_inputter(std::string input_data_file, Clusters& input_data, int &input_data_dim)
{
    std::ifstream ifs(input_data_file);
    if(!ifs){
        std::cout << "== cant file open!! ==" << std::endl;
    }
    std::string line;
    int i = 0;
    Clustering::Cluster temp_data;
    while(std::getline(ifs, line)){
        std::vector<std::string> point= Clustering::split_string(line, ',');

        // std::cout << "input data num = " << i <<std::endl;
        temp_data.point.clear();
        std::vector<double> coordinate;
        coordinate.clear();

        for(int j=0; j<point.size(); j++){
            double coordinate_temp = std::stod(point.at(j));
            coordinate.push_back(coordinate_temp);
            temp_data.point.push_back(coordinate_temp);
            temp_data.cluster_id = i;

            if(i==0){
                input_data_dim = j +1;
            }
        }

        //for debag
        // std::cout << "input data 0 = " << temp_data.point[0] << std::endl;
        // std::cout << "input data 1 = " << temp_data.point[1] << std::endl;

        input_data.push_back(temp_data);
        cluster_num.push_back(1);
        i++;
    }
}

std::vector<std::string> Clustering::split_string(std::string& input, char delimiter)
{
    std::istringstream stream(input);
    std::string field;
    std::vector<std::string> result;
    while (getline(stream, field, delimiter)) {
        result.push_back(field);
    }
    return result;
}

double Clustering::cal_distance(Cluster cluster_a, Cluster cluster_b, const int input_data_dim)
{
    double distance =0;
    double temp;
    for(int i=0; i<input_data_dim; i++){
        temp = cluster_a.point[i]- cluster_b.point[i];
        distance += temp *temp;
    }
    return sqrt(distance);
}

void Clustering::cal_cluster_distance(Clusters& input_data, int input_data_dim, std::vector<double> &cluster_distance)
{
    for(int i=0;i<input_data.size();i++){
        input_data[i].distance.clear();
        for(int j=i+1;j<input_data.size();j++){
        double distance = cal_distance(input_data[i], input_data[j], input_data_dim);
        input_data[i].distance.push_back(cal_distance(input_data[i], input_data[j], input_data_dim));
        cluster_distance.push_back(distance);
        // for debag
        // std::cout <<"cluster" << std::endl <<i << " & " << j << std::endl;
        // std::cout <<"cal dis = " << input_data[i].distance[j-i-1] <<" sin dis = "<<distance << std::endl;
        }
    }
}


std::vector<double> Clustering::serchi_min_distance(std::vector<double> &cluster_distance)
{
    double min_dis = threshold;
    double min_index = -1;
    for(int i=0; i<cluster_distance.size(); i++){

        std::cout << "cluster array " << i << " = "<<cluster_distance[i]<<std::endl; 
        if(cluster_distance[i] >= 0){
            if(min_dis >= cluster_distance[i]){
                min_dis = cluster_distance[i];
                min_index = i;
                // std::cout << "i = " << i << "min ind = " << min_index <<std::endl;
            }
        }
    }

    std::vector<double> result;
    result.clear();
    result.push_back(min_dis);
    result.push_back(min_index);
    cluster_distance[min_index] = cluster_distance[min_index] *-1;

    for(int i=0;i<cluster_distance.size();i++){
        if(result[1] > cluster_distance[i]){
            cluster_distance[i] = cluster_distance[i] *1; 
        }
    }

    return result;
}

std::vector<int> Clustering::get_id_from_distance_array_id(int index)
{
    std::vector<int> result;
    int index_minus = input_data.size() -2;
    int counter = 0;
    while(true){
        if(index - index_minus < 1){
            result.push_back(counter);
            result.push_back(index +counter *1 +1);
            break;
        }
        else{
            index_minus = index_minus +1;
            index = index - index_minus;
            index_minus = index_minus -2;
            counter++;
        }
    }
    return result;
}

void Clustering::full_clustering(Clusters &input_data, FullClusters &full_clusters, std::vector<double> &cluster_distance)
{
    FullCluster temp;
    for(int i=0;i<input_data.size();i++){
        temp.member_id.push_back(i);
        for(int j=0;j<input_data.size();j++){
            if(i == j){
                temp.distance.push_back(0);
                std::cout << " " << temp.distance[0];

            }
            else{
                int index = get_disarray_id_from_id_pair(i, j);
                temp.distance.push_back(cluster_distance[index]);
                std::cout << " " << cluster_distance[index];
            }
        }
        std::cout << std::endl;
        full_clusters.push_back(temp);
        temp.member_id.clear();
        temp.distance.clear();
    }

    std::cout << "==show full cluster data==" << std::endl;
    for(int i=0;i<full_clusters.size();i++){
        std::cout << "id : " << full_clusters[i].member_id[0]<< " || ";
        for(int j=0;j<full_clusters.size();j++){
            std::cout << std::fixed << std::setprecision(3) << " " << full_clusters[i].distance[j] << " " ;
        }
        std::cout << std::endl;
    }

    std::cout << "input member id size : " << full_clusters[0].member_id.size() << std::endl; 


    std::vector<int> min_dis_id;
    min_dis_id.resize(2);
    min_dis_id = serchi_min_dis_from_fullclusters();
    std::cout << "min dis id = " << min_dis_id[0] << " "<< min_dis_id[1] << std::endl;

    FullClusters next_step;
    next_step = create_new_clusters(min_dis_id);

    std::cout << "==show next cluster data==" << std::endl;

    std::cout << "next dis seize : " << next_step[0].distance.size() << std::endl;
    for(int i=0; i<next_step.size();i++){
            std::cout << "show input " << std::endl;
            std::cout << " id : ";
            for(int j=0; j<next_step[i].member_id.size();j++){
                std::cout << next_step[i].member_id[j]<<" " ;
            }
            std::cout << std::endl;
            std::cout << " dis : " ;
            for(int j=0; j<next_step[i].distance.size();j++){
                std::cout << next_step[i].distance[j]<<" " ;
            }
            std::cout<<std::endl;
    }

}

std::vector<int> Clustering::serchi_min_dis_from_fullclusters()
{
    std::vector<int> min_id;
    min_id.resize(2);

    if(full_clusters.size() > 1){
        double min_distance = full_clusters[0].distance[1];
        for(int i=0;i<full_clusters.size();i++){
            for(int j=0;j<full_clusters.size();j++){

                if(i == j){
                    std::cout << "skip"<<std::endl;
                }

                else if(min_distance > full_clusters[i].distance[j]){
                    min_distance = full_clusters[i].distance[j];
                    min_id[0] = i;
                    min_id[1] = j;
                }
            }
        }
    }
    return min_id;
}

std::vector<Clustering::FullCluster> Clustering::create_new_clusters(std::vector<int> pair_id)
{
    FullCluster temp;
    FullClusters next_clusters;
    for(int i=0; i<full_clusters.size();i++){
        if(i == pair_id[0]){
            std::cout << "||== " << i << " ==||" <<std::endl;
            for(int j = 0 ; j<full_clusters.size() ;j++){
                if(j==i){
                    temp.distance.push_back(0);
                }
                else if(j == pair_id[1]){
                    std::cout << " pattern B dis = 0" << std::endl;
                }
                else{
                    double dis = full_clusters[i].distance[j];
                        if(dis < full_clusters[pair_id[1]].distance[j]){
                            dis = full_clusters[pair_id[1]].distance[j];
                        }
                    temp.distance.push_back(dis);
                    std::cout << " pattern A dis = " << dis << std::endl;
                }
            }

            // temp.member_id.clear();

            std::cout << " dis : " ;
            for(int j=0; j<temp.distance.size();j++){
                std::cout << temp.distance[j]<<" " ;
            }
            std::cout<<std::endl;

            for(int j=0; j<full_clusters[i].member_id.size();j++){
                temp.member_id.push_back(full_clusters[i].member_id[j]);
            }

            temp.member_id.push_back(pair_id[1]);
            next_clusters.push_back(temp);

            int id = next_clusters.size() -1 ;
            std::cout << "show input " << std::endl;
            std::cout << " id : ";
            for(int j=0; j<next_clusters[id].member_id.size();j++){
                std::cout << next_clusters[id].member_id[j]<<" " ;
            }
            std::cout << std::endl;
            std::cout << " dis : " ;
            for(int j=0; j<temp.distance.size();j++){
                std::cout << next_clusters[id].distance[j]<<" " ;
            }
            std::cout<<std::endl;
        }

        else if(i == pair_id[1]){
        }

        else{
            if(i != pair_id[0]){
                std::cout << "==== " << i << " ====" <<std::endl;
                for(int j = 0 ; j<full_clusters.size() ;j++){
                    temp.member_id.push_back(i);
                    if(j == pair_id[0]){
                        double dis = full_clusters[i].distance[j];
                            if(dis < full_clusters[i].distance[pair_id[1]]){
                                dis = full_clusters[i].distance[pair_id[1]];
                            }
                        temp.distance.push_back(dis);

                        std::cout << " pattern A dis = " << dis << std::endl;
                    }
                    else if(j ==pair_id[1]){
                        std::cout << " pattern B dis = 0" << std::endl;
                    }
                    else{
                        temp.distance.push_back(full_clusters[i].distance[j]);
                        std::cout << " pattern C dis = " << full_clusters[i].distance[j] << std::endl;
                    }
                }
                temp.member_id.clear();

                for(int j=0; j<full_clusters[i].member_id.size();j++){
                    temp.member_id.push_back(full_clusters[i].member_id[j]);
                }
                next_clusters.push_back(temp);

            int id = next_clusters.size() -1 ;
            std::cout << "show input " << std::endl;
            std::cout << " id : ";
            for(int j=0; j<next_clusters[id].member_id.size();j++){
                std::cout << next_clusters[id].member_id[j]<<" " ;
            }
            std::cout << std::endl;
            std::cout << " dis : " ;
            for(int j=0; j<temp.distance.size();j++){
                std::cout << next_clusters[id].distance[j]<<" " ;
            }
            std::cout<<std::endl;

            }
        }
        temp.distance.clear();
        temp.member_id.clear();
    }
    return next_clusters;
}


int Clustering::get_disarray_id_from_id_pair(int id_a, int id_b)
{

    int id_a_cal = id_a;
    int id_b_cal = id_b;

    if(id_a_cal > id_b_cal){
        int temp = id_b_cal;
        id_b_cal = id_a_cal;
        id_a_cal = temp;
    }

    int triangular_number = input_data.size() -1;
    int result_id = id_b_cal -1;

    // std::cout << "== cal cluster dis id == " << std::endl;
    // std::cout << "triangular num = " << triangular_number << std::endl;
    // std::cout << "first cluster dis id = " << result_id << std::endl;

    for(int i = 0; i < id_a_cal; i++){
        result_id += triangular_number;
        triangular_number--;
        result_id--;
        // std::cout << "triangular num = " << triangular_number << std::endl;
        // std::cout << "second cluster dis id = " << result_id << std::endl;
    }
    // std::cout << "cluster dis id = " << result_id << std::endl;
    // std::cout << std::endl;
    return result_id;
}


int main(int argc, char* argv[])
{
    Clustering clustering;

    double threshold = std::stod(argv[1]);

    clustering.executor(threshold);

    return 0;
}