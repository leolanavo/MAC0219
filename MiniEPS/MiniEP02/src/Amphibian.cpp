#include <iostream>
#include <vector>
#include <pthread.h>

#include "auxiliar_functions.hpp"
#include "globals.hpp"

#include "Amphibian.hpp"

using namespace std;

Amphibian::Amphibian (bool animal_id, int rock) {
    this->animal_id = animal_id;
    this->rock = rock;
}

void Amphibian::execute_thread() {
    pthread_create(&th, NULL, jump, this);
}

bool Amphibian::can_jump() {
    short int offset = animal_id == 1? 1 : -1;

    if ((rock + 2*offset == free_rock && validate_index(n_rocks, rock + 2*offset)) ||
        (rock + offset == free_rock && validate_index(n_rocks, rock + offset))) {
        counter = 0;
        return true;
    }

    counter++;
    return false;
}

bool Amphibian::finished() {
    if ((animal_id == TOAD && rock <= n_rocks/2) ||
        (animal_id == FROG && rock >= n_rocks/2))
        return false;

    int direction = animal_id == TOAD? 1 : -1;
    int limit = animal_id == TOAD? n_rocks : -1;


    for (int i = rock; i != limit; i += direction) {
        cout << i << endl;
        if (rocks[i] != animal_id)
            return false;
    }

    return true;
}

void* Amphibian::jump(void* instance) {
    Amphibian* amp = (Amphibian*) instance;

    while (!amp->finished()) {
        pthread_mutex_lock(&mutex);

        if (amp->can_jump()) {
            int tmp = amp->rock;

            rocks[tmp] = -1;
            rocks[free_rock] = amp->animal_id;

            amp->rock = free_rock;
            free_rock = tmp;

        }
        pthread_mutex_unlock(&mutex);
    }
}
