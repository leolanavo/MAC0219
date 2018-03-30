#include <iostream>
#include <vector>
#include <pthread.h>

#include "Amphibian.hpp"
#include "auxiliar_functions.hpp"
#include "globals.hpp"

#include "Lake.hpp"

Lake::Lake (int n_toads, int n_frogs) {
    n_rocks = n_toads + n_frogs + 1;
    free_rock = n_toads;

    for (int i = 0; i < n_rocks; i++) {
        if (i < n_toads) {
            animals.emplace_back(TOAD, i, i);
            rocks.push_back(TOAD);
        }

        else if (i > n_toads) {
            animals.emplace_back(FROG, i, i - 1);
            rocks.push_back(FROG);
        }

        else {
            rocks.emplace_back(FREE);
        }
    }
}

bool Lake::success() {
    for (int i = 0; i < animals.size(); i++) {
        if ((animals[i].animal_id == TOAD && animals[i].rock < free_rock) ||
           (animals[i].animal_id == FROG && animals[i].rock > free_rock))
            return false;
    }

    return true;
}
