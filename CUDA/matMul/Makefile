all:  matMul_gpu_uncoalesced matMul_gpu matMul_gpu_sharedmem_uncoalesced matMul_gpu_sharedmem matMul_cpu

include ../common/Makefile.common

matMul_cpu: 
	$(CC) $(CFLAGS) matMul_cpu.cu -o matMul_cpu

matMul_gpu_uncoalesced.o: matMul_gpu_uncoalesced.cu
		$(CC) $(CFLAGS) -c matMul_gpu_uncoalesced.cu

matMul_gpu_uncoalesced: matMul_gpu_uncoalesced.o
		$(CC) $(CFLAGS) matMul_gpu_uncoalesced.o -o matMul_gpu_uncoalesced

matMul_gpu.o: matMul_gpu.cu
		$(CC) $(CFLAGS) -c matMul_gpu.cu

matMul_gpu: matMul_gpu.o 
		$(CC) $(CFLAGS) matMul_gpu.o -o matMul_gpu

matMul_gpu_sharedmem_uncoalesced.o: matMul_gpu_sharedmem_uncoalesced.cu
		$(CC) $(CFLAGS) -c matMul_gpu_sharedmem_uncoalesced.cu

matMul_gpu_sharedmem_uncoalesced: matMul_gpu_sharedmem_uncoalesced.o
		$(CC) $(CFLAGS) matMul_gpu_sharedmem_uncoalesced.o -o matMul_gpu_sharedmem_uncoalesced

matMul_gpu_sharedmem.o: matMul_gpu_sharedmem.cu
		$(CC) $(CFLAGS) -c matMul_gpu_sharedmem.cu

matMul_gpu_sharedmem: matMul_gpu_sharedmem.o
		$(CC) $(CFLAGS) matMul_gpu_sharedmem.o -o matMul_gpu_sharedmem

tests: all
	./matMul_gpu_uncoalesced $(sizeM) $(DEVICE_ID)
	./matMul_gpu $(sizeM) $(DEVICE_ID) 
	./matMul_gpu_sharedmem_uncoalesced $(sizeM) $(DEVICE_ID)
	./matMul_gpu_sharedmem $(sizeM) $(DEVICE_ID) 
	./matMul_cpu $(sizeM)

clean:
	rm -rf *.o matMul_gpu_uncoalesced matMul_gpu matMul_gpu_sharedmem_uncoalesced matMul_gpu_sharedmem matMul_cpu
