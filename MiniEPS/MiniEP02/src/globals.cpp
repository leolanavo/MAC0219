#include <vector>
#include <pthread.h>

#include "Amphibian.hpp"

int free_rock = 0;
int counter = 0;
int n_rocks = 0;

pthread_mutex_t mutex;

std::vector<int> rocks;

std::vector<Amphibian> animals;
