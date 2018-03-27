#include <iostream>
#include <vector>

using namespace std;

bool validate_index (int size, int index) {
    return index >= 0 && index < size;
}

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
