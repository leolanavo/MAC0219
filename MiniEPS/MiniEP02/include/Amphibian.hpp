#ifndef AMPHIBIAN_HPP
#define AMPHIBIAN_HPP

using namespace std;

class Amphibian {
    public:
        int animal_id;
        int rock;
        int index;
        pthread_t th;

        Amphibian(int animal_id, int rock, int index);

        void execute_thread(int i);

        bool finished();

        bool can_jump();

        static void* jump(void* index);
};

#endif
