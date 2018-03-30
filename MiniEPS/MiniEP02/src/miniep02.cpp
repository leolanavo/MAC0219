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

void deadlock_kill() {
    cout << "Deadlock" << endl;
    cout << "Pedras: ";
    print_vector(rocks);
    exit(0);
}

void deadlock_check_counter(Lake &l) {
    while (!l.success()) {
        if (counter > LIMIT)
            deadlock_kill();
    }
}

void deadlock_check_vector(Lake &l) {
    int pos1, pos2, pos3, pos4;
    while (!l.success()) {
        pos1 = free_rock + 1 < rocks.size()? free_rock + 1 : free_rock;
        pos2 = free_rock + 2 < rocks.size()? free_rock + 2 : free_rock;

        pos3 = free_rock - 1 >= 0? free_rock - 1: free_rock;
        pos4 = free_rock - 2 >= 0? free_rock - 2: free_rock;

        if ((rocks[pos1] == TOAD || rocks[pos1] == FREE) &&
            (rocks[pos2] == TOAD || rocks[pos2] == FREE) &&
            (rocks[pos3] == FROG || rocks[pos3] == FREE) &&
            (rocks[pos4] == FROG || rocks[pos4] == FREE))
            deadlock_kill();
    }
}

int main (int argc, char* argv[]) {
    int n = stoi(argv[1]);
    int m = stoi(argv[2]);
    bool deadlock_check = stoi(argv[3]);

    pthread_mutex_init(&mutex, NULL);

    Lake l(n, m);

    sleep (1);

    vector<Amphibian> rnd_animals = animals;
    random_shuffle(rnd_animals.begin(), rnd_animals.end());

    for (int i = 0; i < n_rocks - 1; i++) {
        rnd_animals[i].execute_thread(rnd_animals[i].index);
    }

    if (deadlock_check)
        deadlock_check_counter(l);
    else
        deadlock_check_vector(l);

    for (int i = 0; i < animals.size(); i++) {
        pthread_join(animals[i].th, NULL);
    }

    if (l.success()) {
        cout << "Finished with success" << endl;
        exit(0);
    }
    return 0;
}
