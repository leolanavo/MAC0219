#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iterator>
#include <sstream>
#include <pthread.h>


using namespace std;

// this is failing to compile
//  "18: error: Matrix does not name a type"
// this can be probably fixed with a modularization
// of the project, so that the definition of the types
// are ensured to happen before the uses

typedef struct {
    int x;
    int y;
    float ai;
    float bj;
    Matrix target;
} *params;

void *combineUnit(void *prm) {
    params p = (params) prm;

    p->target.data[p->x][p->y] = p->ai;
    p->target.data[p->x][p->y + 1] = p->bj;
}

class Matrix {
    public:
        int lines;
        int columns;
        vector<vector<float>> data;

        Matrix(ifstream file, bool transpose) {
            string line;

            if (file.is_open()) {
                getline(file, line);
                istringstream iss(line);

                if (transpose)
                    iss >> columns >> lines;
                else
                    iss >> lines >> columns;
            }
            else {
                cout << "File isn't open, ABORTING" << endl;
                exit(1);
            }

            data = vector<vector<float>>(lines);
            for (vector<vector<float>>::iterator it = data.begin();
                    it != data.end(); ++it) {
                *it = vector<float>(columns, 0);
            }

            int i, j;
            while (getline(file, line)) {
                istringstream iss(line);

                if (transpose)
                    iss >> j >> i >> this->data[i][j];
                else
                    iss >> i >> j >> this->data[i][j];
            }
        }

        Matrix(int x, int y):
            lines(x), columns(y)
        {
            data = vector<vector<float>>(lines);
            for (vector<vector<float>>::iterator it = data.begin();
                    it != data.end(); ++it) {
                *it = vector<float>(columns, 0);
            }
        }


        // The column of the super matrix is calculated with the j*2 and j*2 + 1
        // The line of the super matrix is calculated with the line = (i1 * m2.lines) + i2
        Matrix CombineMatrixes(Matrix m2) {
            Matrix result = Matrix(this->lines * m2.lines, this->columns *  m2.columns);

            int max;

            vector<params> prms;
            vector<pthread_t> tids;

            for (int i1 = 0; i1 < this->lines; i1++) {
                for (int i2 = 0; i2 < m2.lines; i2++) {
                    for (int j = 0; j < this->columns; j++) {
                        pthread_t tid;
                        params p = (params) malloc(sizeof(params));
                        
                        p->ai = this->data[i1][j];
                        p->bj = m2.data[i2][j];
                        p->x = i1 *m2.lines + i2;
                        p->y = j*2;
                        p->target = result;

                        if (pthread_create(&tid, NULL, combineUnit, (void *) p)) {
                            cout << "Failed to create thread. Exiting..." << endl;
                            exit(1);
                        }

                        prms.push_back(p);
                        tids.push_back(tid);

                        // result.data[i1 * m2.lines + i2][j*2] = this->data[i1][j];
                        // result.data[i1 * m2.lines + i2][j*2 + 1] = m2.data[i2][j];
                    }
                }
            }

            max = this->lines * m2.lines * this->columns;

            for (int t = 0; t < max; t++) {
                pthread_join(tids[t], NULL);
            }

            for (int t = 0; t < max; t++) {
                free(prms[t]);
                prms[t] = NULL;
            }

            return result;
        }

        Matrix ReduceCombinedMatrix(int lines, int columns) {
            Matrix result = Matrix(lines, columns);

            int val;
            for (int i = 0; i < this->lines; i++) {
                val = 0;
                for (int j = 0; j < this->columns; j += 2) {
                    val += this->data[i][j] * this->data[i][j+1];
                }
                result.data[i/columns][i%columns] = val;
            }

            return result;
        }

};


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
    Matrix m3 = m1.CombineMatrixes(m2);
    Matrix m4 = m3.ReduceCombinedMatrix(m1.lines, m2.lines);

    cout << m1 << endl;
    cout << m2 << endl;
    cout << m3 << endl;
    cout << m4 << endl;

    return 0;
}
