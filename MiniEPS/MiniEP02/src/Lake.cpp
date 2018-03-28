#include <iostream>
#include <vector>
#include <pthread.h>
#include <ctime>
#include <cstdlib>
#include <algorithm>

#include "Amphibian.hpp"
#include "auxiliar_functions.hpp"
#include "globals.hpp"

#include "Lake.hpp"

Lake::Lake (int n_toads, int n_frogs) {
    n_rocks = n_toads + n_frogs + 1;
    initial_free_rock = free_rock = n_toads;
    rocks.resize(n_rocks);

    for (int i = 0; i < n_rocks; i++) {
        if (i < n_toads) {
            animals.push_back(Amphibian(TOAD, i));
            rocks[i] = TOAD;
        }

        else if (i > n_toads) {
            animals.push_back(Amphibian(FROG, i));
            rocks[i] = FROG;
        }

        else {
            free_rock = i;
            rocks[i] = -1;
        }
    }

    srand(time(NULL));
    vector<Amphibian> rnd_animals = animals;
    random_shuffle(rnd_animals.begin(), rnd_animals.end());

    for (int i = 0; i < n_rocks - 1; i++)
        rnd_animals[i].execute_thread();

}

bool Lake::success() {
    if (initial_free_rock != free_rock)
        return false;

    for (int i = 0; i < n_rocks - 1; i++) {
        Amphibian animal = animals[i];

        if ((animal.animal_id == TOAD && animal.rock < free_rock) ||
           (animal.animal_id == FROG && animal.rock > free_rock))
            return false;
    }

    return true;
}
