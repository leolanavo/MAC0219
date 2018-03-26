#ifndef AMPHIBIAN_HPP
#define AMPHIBIAN_HPP

using namespace std;

int free_rock;

class Amphibian {
    public:
        bool animal_id;
        int rock;
        pthread_t th;

        Amphibian(short unsigned int animal_id, int rock, int size);

        bool can_jump(int size);

        void jump(int size);
};

#endif
