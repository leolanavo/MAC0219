#include <iostream>
#include <vector>
#include <pthread.h>
#include <unistd.h>

#include "Lake.hpp"
#include "Amphibian.hpp"
#include "auxiliar_functions.hpp"
#include "globals.hpp"

using namespace std;

#define LIMIT 100

void* deadlock_check(void* arg) {
    while(1) {
        if (counter > LIMIT) {
            cout << "Deadlock" << endl;
            exit(1);
        }
    }
}

int main (int argc, char* argv[]) {
    int n = stoi(argv[1]), m = stoi(argv[2]);
    pthread_mutex_init(&mutex, NULL);

    pthread_t judge;
    pthread_create(&judge, NULL, deadlock_check, NULL);

    Lake l(n, m);

    sleep(1);

    for (int i = 0; i < n_rocks - 1; i++) {
        pthread_join(animals[i].th, NULL);
    }

    if (l.success()) {
        cout << "Finished with success" << endl;
        exit(0);
    }
    return 0;
}
