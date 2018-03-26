#include <iostream>
#include <vector>
#include <pthread.h>

using namespace std;

// animal_id = 0 --> vazio
// animal_id = 1 --> rã
// animal_id = 2 --> sapo
vector<int> rocks;

bool validate_index (int size, int index) {
    return index >= 0 && index < size;
}

class Amphibian {
    public:
        short unsigned int animal_id;
        int index;
        pthread_t th;

        Amphibian(short unsigned int animal_id, int index) {
            this->animal_id = animal_id;
            this->index = index;
            this->th = pthread_create(this->th, NULL, this->jump, rocks);
        }

        short unsigned int can_jump(vector<int> &v) {
            short unsigned int offset = this->animal_id == 1? 1 : -1;

            if (v[index + offset] != 0 && v[index + 2*offset] == 0 && validate_index(v.size(), index + 2*offset))
                return 2;

            else if (v[index + offset] == 0 && validate_index(v.size(), index + offset))
                return 1;

            return 0;
        }

        void jump(vector<int> &v) {
            short unsigned int offset = animal_id == 1? 1 : -1;

            switch(this->can_jump(v)) {
                case 1:
                    v[index + 2*offset] = v[index];
                    v[index] = 0;
                    break;
                case 2:
                    v[index + offset] = v[index];
                    v[index] = 0;
                    break;
            }
        }
};




void print_vector(vector<int> &v) {
    cout << "[";
    for (vector<int>::iterator it = v.begin(); it != v.end(); ++it) {
        if (distance(v.begin(), it) < v.size() - 1)
            cout << *it << ", ";
        else
            cout << *it;
    }
    cout << "]" << endl;
}

vector<int> initializer(int n, int m) {
    vector<int> v (n + m + 1);

    for (int i = 0; i < n; i ++)
        v[i] = 1;

    for (int i = v.size(); i > v.size() - m; i--)
        v[i] = 2;
}

int main (int argc, char* argv[]) {
    int n = stoi(argv[1]), m = stoi(argv[2]);

     = initializer(n, m);

    return 0;
}
