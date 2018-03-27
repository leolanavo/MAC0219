#ifndef AMPHIBIAN_HPP
#define AMPHIBIAN_HPP

using namespace std;

class Amphibian {
    public:
        bool animal_id;
        int rock;
        pthread_t th;

        Amphibian(bool animal_id, int rock);

        bool can_jump();

        static void* jump(void* instance);
};

#endif
