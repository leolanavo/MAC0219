#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <climits>
#include <cmath>

const int DIMENSION = 3;
const int ELEMENTS = DIMENSION * DIMENSION;

std::ostream& operator<<(std::ostream& os, std::vector<std::vector<int>> v) {
    for (auto it_line = v.begin(); it_line != v.end(); it_line++) {
        for (auto it_col = it_line->begin(); it_col != it_line->end(); it_col++)
            os << *it_col << ' ';
        os << std::endl;
    }
    
    return os;
}

void read_file(std::ifstream& file, std::vector<std::vector<int>>& v) {
    int first, second, third, n;
    std::string dump;

    file >> n;

    for (int matrix = 0; matrix < n; matrix++) {
        file >> dump;

        for (int i = 0; i < DIMENSION; i++) {
            file >> first >> second >> third;

            v[i][0] = first < v[i][0] ? first : v[i][0];
            v[i][1] = second < v[i][1] ? second : v[i][1];
            v[i][2] = third < v[i][2] ? third : v[i][2];
        }
    }
}

int main(int argc, char **argv) {
    std::vector<std::vector<int>> m;
    for (int i = 0; i < 3; i++)
        m.push_back(std::vector<int>(3, INT_MAX));
    
    std::ifstream file(argv[1]);

    read_file(file, m);

    std::cout << m;
}