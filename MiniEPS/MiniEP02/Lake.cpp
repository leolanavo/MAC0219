#include <vector>
#include <pthread.h>
#include "Amphibian.hpp"
#include "auxiliar_functions.hpp"

#define TOAD 0
#define FROG 1

class Lake {
    public:
        vector<Amphibian> animals;
        int initial_free_rock;

    Lake (int n_toads, int n_frogs) {

        Amphibian entry(0, 0);
        for (int i = 0; i <= n_toads + n_frogs + 1; i++) {

            if (i < n_toads)
                entry = Amphibian(TOAD, i);
            else if (i > n_toads)
                entry = Amphibian(FROG, i);
            else
                free_rock = i;

            initial_free_rock = free_rock;

            if (i != n_toads)
                animals.push_back(entry);
        }
    }

    bool sucess() {
        if (initial_free_rock != free_rock)
            return false;

        for (int i = 0; i < animals.size(); i++) {
            Amphibian animal = animals[i];

            if ((animal.animal_id == TOAD && animal.rock < free_rock) ||
               (animal.animal_id == FROG && animal.rock > free_rock))
                return false;
        }

        return true;
    }
};
