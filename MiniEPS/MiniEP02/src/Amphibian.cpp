#include <iostream>
#include <vector>
#include <pthread.h>

#include "auxiliar_functions.hpp"
#include "globals.hpp"

#include "Amphibian.hpp"

using namespace std;

Amphibian::Amphibian (bool animal_id, int rock, int index) {
    this->animal_id = animal_id;
    this->rock = rock;
    this->index = index;
}

void Amphibian::execute_thread(int i) {
    pthread_create(&th, NULL, &jump, &i);
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

    cout << __LINE__ << endl;
    if ((animal_id == TOAD && rock <= initial_free_rock) ||
        (animal_id == FROG && rock >= initial_free_rock)) {
        cout << __LINE__ << endl;
        return false;
    }

    cout << __LINE__ << endl;
    if (animal_id == TOAD)
        for (int i = rock; i < rocks.size(); i++)
            if (rocks[i] != animal_id)
                return false;

    cout << __LINE__ << endl;
    if (animal_id == FROG)
        for (int i = rock; i >= 0; i--)
            if (rocks[i] != animal_id)
                return false;
    cout << __LINE__ << endl;


    return true;
}

void* Amphibian::jump(void* index) {
    int i = *((int*) index);
    cout << __LINE__ << endl;

    while (animals[i].finished()) {
    cout << __LINE__ << endl;
        pthread_mutex_lock(&mutex);
    cout << __LINE__ << endl;

        if (animals[i].can_jump()) {
            cout << "pulou de " << free_rock << " para " << animals[i].rock << endl;
            int tmp = animals[i].rock;

            rocks[tmp] = -1;
            rocks[free_rock] = animals[i].animal_id;

            animals[i].rock = free_rock;
            free_rock = tmp;

        }
        pthread_mutex_unlock(&mutex);
    }
}
