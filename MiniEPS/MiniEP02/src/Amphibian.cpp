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
    pthread_create(&th, NULL, jump, this);
    cout << this->rock << " = " << rock << endl;
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

void* Amphibian::jump(void* instance) {
    Amphibian* amp = (Amphibian*) instance;

    pthread_mutex_lock(&mutex);
    if (amp->can_jump()) {
        int tmp = amp->rock;
        amp->rock = free_rock;
        free_rock = tmp;
    }
    pthread_mutex_unlock(&mutex);
}
