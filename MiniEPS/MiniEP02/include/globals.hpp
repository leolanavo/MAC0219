#ifndef GLOBALS_HPP
#define GLOBALS_HPP

#define TOAD true
#define FROG false

#include "Amphibian.hpp"

extern int free_rock;
extern int counter;
extern int n_rocks;
extern int initial_free_rock;
extern pthread_mutex_t mutex;
extern vector<int> rocks;
extern vector<Amphibian> animals;

#endif
