#include "clustering/clustering.h"

Clustering::Clustering(void)
{

}

void Clustering::executor(const double command_line)
{
    Clustering::formattor(command_line);
    Clustering::data_inputter(input_file_name, input_data, input_data_dim, input_data_num);
    Clustering::cal_cluster_distance(input_data, input_data_dim, input_data_num, cluster_distance);
    Clustering::simple_clustering(input_data, cluster_distance);
}

void Clustering::formattor(const double input)
{
    input_file_name = "../../dataset/input_data_file.csv";
    input_data.clear();
    cluster_distance.clear();
    threshold = input;
}

void Clustering::data_inputter(std::string input_data_file, Clusters& input_data, int &input_data_dim, int &input_data_num)
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
        i++;
    }

    input_data_num = i;
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

void Clustering::cal_cluster_distance(Clusters& input_data, int input_data_dim,int input_data_num, std::vector<double> &cluster_distance)
{
    for(int i=0;i<input_data_num;i++){
        input_data[i].distance.clear();
        for(int j=i+1;j<input_data_num;j++){
        double distance = cal_distance(input_data[i], input_data[j], input_data_dim);
        input_data[i].distance.push_back(cal_distance(input_data[i], input_data[j], input_data_dim));
        cluster_distance.push_back(distance);
        // for debag
        // std::cout <<"cluster" << std::endl <<i << " & " << j << std::endl;
        // std::cout <<"cal dis = " << input_data[i].distance[j-i-1] <<" sin dis = "<<distance << std::endl;
        }
    }
}

void Clustering::simple_clustering(Clusters& input_data, std::vector<double> cluster_distance)
{
    std::vector<double> serchi_result;
    std::vector<int> cluster_id_array;
    int serchi_result_id;

    while (true){
        serchi_result = Clustering::serch_min_distance(cluster_distance);
        serchi_result_id = serchi_result[1];

        // std::cout << "mindis = " << serchi_result[0] << " index = " << serchi_result[1] << std::endl;

        cluster_id_array = Clustering::get_id_from_distance_array_id(serchi_result_id);
        std::cout << "id_ " << cluster_id_array[0]<< " & "<<" id_ " <<cluster_id_array[1]<<std::endl;

        Clustering::change_id(input_data, cluster_id_array);

        std::cout << "clustering"<<std::endl;
        std::cout << "id_ " << input_data[cluster_id_array[0]].cluster_id << " & "<<" id_ " <<input_data[cluster_id_array[1]].cluster_id<<std::endl;

        std::cout << " " << input_data[0].cluster_id << " " <<input_data[1].cluster_id<< " " <<input_data[2].cluster_id<< " " <<input_data[3].cluster_id << " " <<input_data[4].cluster_id<<std::endl;

        if(threshold <= serchi_result[0]){
            break;
        }
        // std::cout << "serchi reslut size = " << serchi_result.size()<< std::endl;
        // std::cout << "mindis = " << serchi_result[0] << " index = " << serchi_result[1] << std::endl;

    }
}

std::vector<double> Clustering::serch_min_distance(std::vector<double> &cluster_distance)
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

    cluster_distance[min_index] = cluster_distance[min_index] *-1;
    std::vector<double> result;
    result.clear();
    result.push_back(min_dis);
    result.push_back(min_index);
    return result;
}

std::vector<int> Clustering::get_id_from_distance_array_id(int index)
{
    std::vector<int> result;
    int index_minus = input_data_num -2;
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

void Clustering::change_id(Clusters &input_data, const std::vector<int> pair_id)
{
    input_data[pair_id[1]].cluster_id = input_data[pair_id[0]].cluster_id;
}

int main(int argc, char* argv[])
{
    Clustering clustering;

    double threshold = std::stod(argv[1]);

    clustering.executor(threshold);

    return 0;
}