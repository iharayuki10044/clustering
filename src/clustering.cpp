#include "clustering/clustering.h"

Clustering::Clustering(void)
{

}

void Clustering::executor(void)
{
    Clustering::formattor();
    Clustering::data_inputter(input_file_name, input_data, input_data_dim, input_data_num);
    Clustering::simple_clustering(input_data, input_data_dim, input_data_num);
}

void Clustering::formattor(void)
{
    input_file_name = "../../dataset/input_data_file.csv";
    input_data.clear();
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

        std::cout << "input data num = " << i <<std::endl;
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
            std::cout << std::endl;
        }

        std::cout << "input data 0 = " << temp_data.point[0] << std::endl;
        std::cout << "input data 1 = " << temp_data.point[1] << std::endl;

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

void Clustering::simple_clustering(Clusters& input_data, int input_data_dim,int input_data_num)
{
    for(int i=0;i<input_data_num;i++){
        input_data[i].distance.clear();
        for(int j=i+1;j<input_data_num;j++){

        double distance = cal_distance(input_data[i], input_data[j], input_data_dim);
        input_data[i].distance.push_back(cal_distance(input_data[i], input_data[j], input_data_dim));

        std::cout <<"cluster" << std::endl <<i << " & " << j << std::endl
        std::cout <<"cal dis = " << input_data[i].distance[j-i-1] <<" sin dis = "<<distance << std::endl;

        }
    }
}

int main(int argc, char** argv)
{
    Clustering clustering;
    clustering.executor();

    return 0;
}