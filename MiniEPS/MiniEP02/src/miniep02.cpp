#include <iostream>
#include <vector>
#include <pthread.h>
#include <unistd.h>
#include <algorithm>

#include "Lake.hpp"
#include "Amphibian.hpp"
#include "auxiliar_functions.hpp"
#include "globals.hpp"

using namespace std;

#define LIMIT 10000

void* deadlock_check(Lake &l) {
    while (!l.success()) {
        if (counter > LIMIT) {
            cout << "Deadlock" << endl;
            print_vector(rocks);
            exit(1);
        }
    }
}

int main (int argc, char* argv[]) {
    int n = stoi(argv[1]), m = stoi(argv[2]);
    pthread_mutex_init(&mutex, NULL);

    Lake l(n, m);

    sleep (1);

    vector<Amphibian> rnd_animals = animals;
    random_shuffle(rnd_animals.begin(), rnd_animals.end());

    for (int i = 0; i < n_rocks - 1; i++) {
        rnd_animals[i].execute_thread(rnd_animals[i].index);
    }

    deadlock_check(l);

    for (int i = 0; i < animals.size(); i++) {
        pthread_join(animals[i].th, NULL);
    }

    if (l.success()) {
        cout << "Finished with success" << endl;
        exit(0);
    }
    return 0;
}
