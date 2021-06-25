#include "clustering/clustering.h"

Clustering::Clustering(void)
{

}

void Clustering::executor(void)
{
    Clustering::formattor();

    std::cout << "input data size = " << input_data.size() << std::endl;

    Clustering::data_inputter(input_file_name, input_data, input_dim, input_data_num);

    std::cout << "input data num = " << input_data_num << std::endl;
    std::cout << "input data dim = " << input_dim << std::endl;

}

void Clustering::formattor(void)
{
    input_file_name = "../../dataset/input_data_file.csv";
    input_data.clear();
}

void Clustering::data_inputter(std::string input_data_file, Clusters& input_data, int &input_dim, int &input_data_num)
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
                input_dim = j +1;
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

double Clustering::cal_distance_2d(Cluster cluster_a, Cluster cluster_b, const int input_dim)
{
    double distance =0;
    double temp;
    for(int i=0; i<input_dim ; i++){
        temp = cluster_a.point[i]- cluster_a.point[i];
        distance += temp *temp;
    }

    return sqrt(distance);
}

void Clustering::simple_cluster(Clusters& input_data)
{
    
}

int main(int argc, char** argv)
{
    Clustering clustering;
    clustering.executor();

    return 0;
}