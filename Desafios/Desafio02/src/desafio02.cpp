#include <iostream>
#include <vector>

#include <pthread.h>
#include <time.h>
#include <sched.h>

#define OFFSET 64
#define ITERATIONS 1e10

pthread_barrier_t barrier;
pthread_mutex_t mutex;


double time_diff(clock_t start, clock_t end) {
    return (((double) (end - start) / CLOCKS_PER_SEC));
}

void* work_load_continuous(void* arg) {
    int id = *((int *) arg);
    clock_t start, end;

    // CPU_ZERO(&id);
    // CPU_SET(id%2

    pthread_barrier_wait(&barrier);
    start = clock();

    for (long long unsigned int a = 0; a < ITERATIONS; a++) {
        int i = a;
        i = a/2;
        i = a%i;
    }

    end = clock();
    pthread_mutex_lock(&mutex);
    std::cout << "Elapsed time " << time_diff(start, end) << " for thread " << id << std::endl;
    pthread_mutex_unlock(&mutex);
}

int main(int argc, char* argv[])
{
    int n_threads = std::stoi(argv[1]);

    pthread_barrier_init(&barrier, NULL, n_threads);
    pthread_mutex_init(&mutex, NULL);

    std::vector<pthread_t> v_pth(n_threads);

    for (int i = 0; i < n_threads; i++) {
        int* th_id = new int(i);
        pthread_create(&v_pth[i], NULL, &work_load_continuous, th_id);
    }

    for (int i = 0; i < n_threads; i++)
        pthread_join(v_pth[i], NULL);
}
