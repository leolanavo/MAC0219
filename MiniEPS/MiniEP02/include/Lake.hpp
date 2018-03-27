#ifndef LAKE_HPP
#define LAKE_HPP

#include <vector>

#include "Amphibian.hpp"

class Lake {
    public:
        vector<Amphibian> animals;
        int initial_free_rock;

        Lake (int n_toads, int n_frogs);

        bool success();
};

#endif
