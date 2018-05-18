#include "../include/matrix.hpp"

using namespace std;

ostream& operator<<(ostream& os, Matrix& m) {
    for (vector<vector<float>>::iterator it_line = m.data.begin();
            it_line != m.data.end(); it_line++) {
        for (vector<float>::iterator  it_column = it_line->begin();
                it_column != it_line->end(); it_column++) {
            os << *it_column << " ";
        }
        os << endl;
    }

    return os;
}

int main(int argc, char* argv[]) {
    string line;

    Matrix m1 = Matrix(ifstream(argv[1]), false);
    Matrix m2 = Matrix(ifstream(argv[2]), true);
    Matrix m3 = m1.CombineMatrices(m2);
    Matrix m4 = m3.ReduceCombinedMatrix(m1.lines, m2.lines);

    cout << m1 << endl;
    cout << m2 << endl;
    cout << m3 << endl;
    cout << m4 << endl;

    return 0;
}
