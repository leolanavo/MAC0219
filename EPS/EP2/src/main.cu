#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <climits>

const int DIMENSION = 3;
const int BLOCK_SIE = 1024;
const int DEVICE_ID = 0;

#define Matrix std::vector<std::vector<int>>

std::ostream& operator<<(std::ostream& os, Matrix m) {
    for (auto line = m.begin(); line != m.end(); line++) {
        for (auto item = (*line).begin(); item != (*line).end(); item++) {
            os << *(item) << " ";
        }
        os << std::endl;
    }
    return os;
}

void add_infinite(Matrix& m) {
    for (int i = 0; i < DIMENSION*DIMENSION; i++)
        m[i].push_back(INT_MAX);
}

void read_file(std::ifstream& file, const int number_of_matrices, Matrix& m) {
    int first, second, third;
    std::string line;

    for (int k = 0; k < number_of_matrices; k++) {
        // This is used to throw away the line of asterisks
        file >> line;

        for (int i = 0; i < DIMENSION; i++) {
            file >> first >> second >> third;

            m[(i * DIMENSION)].push_back(first);
            m[(i * DIMENSION) + 1].push_back(second);
            m[(i * DIMENSION) + 2].push_back(third);
        }
    }
}

int set_host_matrix(std::ifstream& file, Matrix& m) {
    int number_of_matrices;

    if (input_file.is_open())
        input_file >> number_of_matrices;

    read_file(input_file, number_of_matrices, matrices_host);
    if (number_of_matrices % 2 != 0) add_infinite(matrices_host);

    return number_of_matrices;
}

void set_device_matrix(int number_of_matrices, Matrix& device_matrix, Matrix& host_matrix) {
    cudaSetDevice(DEVICE_ID);

    for (int i = 0; i < DIMENSION * DIMENSION; i++) {
        cudaMalloc((void**) matrices_device[i], number_of_matrices);
        cudaMemcpy(device_matrix[i], host_matrix[i], cudaMemcpyHostToDevice);
    }
}

int main(int argc, char* argv[]) {
    Matrix host_matrix (DIMENSION * DIMENSION);
    Matrix device_matrix (DIMENSION * DIMENSION);

    int number_of_matrices = set_host_matrix(std::ifstream(argv[1]), host_matrix);
    set_host_matrix(number_of_matrices, device_matrix, host_matrix);

    return(0);
}
