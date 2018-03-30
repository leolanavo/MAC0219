#ifndef GLOBALS_HPP
#define GLOBALS_HPP

#define TOAD -1
#define FROG 1
#define FREE 0

#include "Amphibian.hpp"

extern int free_rock;
extern int counter;
extern int n_rocks;
extern pthread_mutex_t mutex;
extern vector<int> rocks;
extern vector<Amphibian> animals;

#endif
