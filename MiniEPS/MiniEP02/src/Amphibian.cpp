#include <iostream>
#include <vector>
#include <pthread.h>
#include <unistd.h>

#include "auxiliar_functions.hpp"
#include "globals.hpp"

#include "Amphibian.hpp"

using namespace std;

Amphibian::Amphibian (int animal_id, int rock, int index) {
    this->animal_id = animal_id;
    this->rock = rock;
    this->index = index;
}

void Amphibian::execute_thread(int i) {
    int *index = new int(i);
    pthread_create(&th, NULL, &jump, index);
}

bool Amphibian::can_jump() {
    short int offset = animal_id == TOAD? 1 : -1;

    if ((rock + 2*offset == free_rock) || (rock + offset == free_rock)) {
        counter = 0;
        return true;
    }

    counter++;
    return false;
}

bool Amphibian::finished() {

    if (animal_id == TOAD)
        for (int i = rock; i < rocks.size(); i++)
            if (rocks.at(i) != animal_id)
                return false;

    if (animal_id == FROG)
        for (int i = rock; i >= 0; i--)
            if (rocks.at(i) != animal_id)
                return false;

    return true;
}

void* Amphibian::jump(void* index) {
    int i = *((int*) index);

    while (!animals.at(i).finished()) {
        pthread_mutex_lock(&mutex);

        if (animals[i].can_jump()) {
            int tmp = animals[i].rock;

            rocks[tmp] = FREE;
            rocks[free_rock] = animals[i].animal_id;

            animals[i].rock = free_rock;
            free_rock = tmp;

        }
        pthread_mutex_unlock(&mutex);
    }
    delete((int*) index);
}
