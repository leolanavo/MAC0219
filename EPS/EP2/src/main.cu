#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <climits>
#include <cmath>

const int DIMENSION = 3;
const int BLOCK_SIZE = 1024;
const int BLOCK_ITEMS = 2048;
const int EXPONENT = 11;
const int DEVICE_ID = 0;
const int ELEMENTS = DIMENSION * DIMENSION;

void read_file(std::ifstream& file, const int number_of_matrices,
        const int number_of_matrices_std, std::vector<int>& v) {
    int first, second, third;
    std::string dump;

    for (int k = 0; k < number_of_matrices; k++) {
        file >> dump;

        for (int i = 0; i < ELEMENTS; i += DIMENSION) {
            file >> first >> second >> third;
            v[(number_of_matrices_std * i) + k] = first;
            v[(number_of_matrices_std * (i + 1)) + k] = second;
            v[(number_of_matrices_std * (i + 2)) + k] = third;
        }
    }
}

std::vector<int> set_host_v(char* filename) {
    int number_of_matrices;
    std::ifstream file(filename);

    if (file.is_open()) file >> number_of_matrices;

    int number_of_matrices_std = ceil(number_of_matrices / (double) BLOCK_ITEMS) * BLOCK_ITEMS;
    std::vector<int> v (ELEMENTS * number_of_matrices_std, INT_MAX);
    read_file(file, number_of_matrices, number_of_matrices_std, v);

    file.close();
    return v;
}

void set_device_v(int number_of_matrices, std::vector<int>& host_v, void*& device_v) {
    int block_size = ELEMENTS * number_of_matrices * sizeof(int);
    cudaMalloc(&device_v, block_size);
    cudaMemcpy(device_v, host_v.data(), block_size, cudaMemcpyHostToDevice);
}

__global__ void reduce_block(void* m) {
    int* m_int = (int*) m;
    int index = (BLOCK_ITEMS * blockIdx.x) + threadIdx.x;
    __shared__ int m_shared[BLOCK_ITEMS];

    m_shared[threadIdx.x] = m_int[index];
    m_shared[BLOCK_SIZE + threadIdx.x] = m_int[BLOCK_SIZE + index];

    for (int block_size = BLOCK_ITEMS; block_size > 1; block_size >>= 1) {
        int index_1 = threadIdx.x;
        int index_2 = index_1 + (block_size / 2);

        if (threadIdx.x >= (block_size >> 1))
            return;

        m_shared[index_1] = min(m_shared[index_1], m_shared[index_2]);
        __syncthreads();
    }

    if (threadIdx.x == 0)
        m_int[index] = m_shared[0];
}

__global__ void compress_block(void* v, int number_of_matrices, int offset) {
    int* v_int = (int*) v;

    int index_compressed =
        (blockIdx.x * number_of_matrices) + threadIdx.x +
        (offset * BLOCK_SIZE);

    int index_expanded =
        (blockIdx.x * number_of_matrices) + threadIdx.x * BLOCK_ITEMS +
        (offset * BLOCK_ITEMS * BLOCK_SIZE);

    v_int[index_compressed] = v_int[index_expanded];
    __syncthreads();
}

__global__ void compress_line(void* v, int line,
        int number_of_blocks, int next_number_of_blocks) {

    int index_expanded_1 = line * number_of_blocks * BLOCK_ITEMS + threadIdx.x;
    int index_compressed_1 = line * next_number_of_blocks * BLOCK_ITEMS + threadIdx.x;

    int index_expanded_2 = line * number_of_blocks * BLOCK_ITEMS +
        BLOCK_SIZE + threadIdx.x;
    int index_compressed_2 = line * next_number_of_blocks * BLOCK_ITEMS +
        BLOCK_SIZE + threadIdx.x;

    int* v_int = (int*) v;
    v_int[index_compressed_1] = v_int[index_expanded_1];
    v_int[index_compressed_2] = v_int[index_expanded_2];
}

__global__ void final_compress(void* v, int number_of_matrices) {
    int* v_int = (int*) v;
    for (int i = 0; i < ELEMENTS; i++) {
        v_int[i] = v_int[i * BLOCK_ITEMS];
    }
}

void print_result_matrix(void* device_v) {
    int result[ELEMENTS];

    cudaMemcpy((void*)result, device_v, ELEMENTS * sizeof(int), cudaMemcpyDeviceToHost);

    for (int i = 0; i < ELEMENTS; i++) {
        std::cout << result[i];
        if ((i + 1) % DIMENSION) std::cout << " ";
        else std::cout << std::endl;
    }
}

int main(int argc, char* argv[]) {
    void* device_v;
    cudaSetDevice(DEVICE_ID);

    std::vector<int> host_v = set_host_v(argv[1]);
    int number_of_matrices = host_v.size() / ELEMENTS;

    set_device_v(number_of_matrices, host_v, device_v);

    for (int k = number_of_matrices; k > 1; k >>= EXPONENT) {
        k = ceil(k / (double) BLOCK_ITEMS) * BLOCK_ITEMS;

        // Reduction
        int number_of_blocks = k >> EXPONENT;
        reduce_block<<< number_of_blocks * ELEMENTS, BLOCK_SIZE >>>(device_v);

        int next_number_of_blocks = ceil (number_of_blocks / (double) BLOCK_ITEMS);
        /* std::cout << next_number_of_blocks << " " << number_of_blocks << std::endl; */

        // Compression
        int threads_per_block = (number_of_blocks < BLOCK_SIZE)?
            number_of_blocks : BLOCK_SIZE;
        for (int i = 0; i < number_of_blocks >> 10; i++)
            compress_block<<< ELEMENTS, threads_per_block >>> (device_v, k, i);

        for (int i = 1; i < ELEMENTS && number_of_blocks > 1; i++)
            compress_line<<< 1, BLOCK_SIZE >>>
                (device_v, i, number_of_blocks, next_number_of_blocks);
    }

    final_compress<<<1,1>>>(device_v, number_of_matrices);
    print_result_matrix(device_v);

    cudaDeviceReset();
    return(0);
}
