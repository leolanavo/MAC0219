#include <vector>
#include <pthread.h>

#include "auxiliar_functions.hpp"

// animal_id = 0 --> toad
// animal_id = 1 --> frog

using namespace std;

int free_rock;
int counter;

class Amphibian {
    public:
        bool animal_id;
        int rock;
        pthread_t th;

        Amphibian(bool animal_id, int rock, int size) {
            this->animal_id = animal_id;
            this->rock = rock;
            pthread_create(this->th, NULL, jump, (void*)size);
        }

        bool can_jump(int size) {
            short int offset = animal_id == 1? 1 : -1;

            if ((rock + 2*offset == free_rock && validate_index(size, rock + 2*offset)) ||
                (rock + offset == free_rock && validate_index(size, rock + offset))) {
                counter = 0;
                return true;
            }

            counter++;
            return false;
        }

        void jump(int size) {
            short unsigned int offset = animal_id == 1? 1 : -1;

            if (can_jump(size)) {
                    int tmp = rock;
                    rock = free_rock;
                    free_rock = tmp;
            }
        }
};
