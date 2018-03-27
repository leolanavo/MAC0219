#include <iostream>
#include <vector>
#include <pthread.h>

#include "Amphibian.hpp"
#include "auxiliar_functions.hpp"
#include "globals.hpp"

#include "Lake.hpp"

#define TOAD true
#define FROG false

Lake::Lake (int n_toads, int n_frogs) {
    n_rocks = n_toads + n_frogs + 1;
    initial_free_rock = free_rock = n_toads;

    for (int i = 0; i < n_rocks; i++) {
        if (i < n_toads) {
            animals.push_back(Amphibian(TOAD, i));
        }

        else if (i > n_toads) {
            animals.push_back(Amphibian(FROG, i));
        }

        else {
            free_rock = i;
        }
    }

    // cout << "++" << endl;
    // for (int i = 0; i < n_rocks - 1; i++) {
        // cout << animals[i].rock << endl;
    // }
}

bool Lake::success() {
    if (initial_free_rock != free_rock)
        return false;

    for (int i = 0; i < n_rocks; i++) {
        Amphibian animal = animals[i];

        if ((animal.animal_id == TOAD && animal.rock < free_rock) ||
           (animal.animal_id == FROG && animal.rock > free_rock))
            return false;
    }

    return true;
}
