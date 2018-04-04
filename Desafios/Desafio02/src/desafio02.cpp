#include <iostream>
#include <vector>
#include <chrono>
#include <thread>

#include <pthread.h>
#include <time.h>
#include <sched.h>

#define OFFSET 64
#define ITERATIONS 1e10
#define EXECUTIONS 2

pthread_barrier_t barrier;
pthread_mutex_t mutex;


double time_diff(clock_t start, clock_t end) {
    return (((double) (end - start) / CLOCKS_PER_SEC));
}

void* work_load_continuous(void* arg) {
    int id = *((int *) arg);

    pthread_barrier_wait(&barrier);

    auto t1 = std::chrono::system_clock::now();
    for (long long unsigned int a = 0; a < ITERATIONS; a++) {
        int i = a;
        i = a/2;
        i = a%i;
    }
    auto t2 = std::chrono::system_clock::now();
    std::chrono::duration<double> duration = t2 - t1;

    pthread_mutex_lock(&mutex);
    std::cout << "Elapsed time " << duration.count() << "s for thread " << id << std::endl;
    pthread_mutex_unlock(&mutex);
}

int main(int argc, char* argv[])
{
    pthread_mutex_init(&mutex, NULL);

    unsigned int n_threads;

    for (int j = 0; j < EXECUTIONS; j++) {
        n_threads = std::thread::hardware_concurrency();
        n_threads = j > 0? n_threads/2 : n_threads;
        std::cout << "Executing with " << n_threads << std::endl;

        pthread_barrier_init(&barrier, NULL, n_threads);
        std::vector<pthread_t> v_pth(n_threads);

        for (int i = 0; i < n_threads; i++) {
            int* th_id = new int(i);
            pthread_create(&v_pth[i], NULL, &work_load_continuous, th_id);
        }

        for (int i = 0; i < n_threads; i++)
            pthread_join(v_pth[i], NULL);

        std::cout << "----------" << std::endl;
    }
}
