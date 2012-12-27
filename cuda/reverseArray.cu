#include <assert.h>
#include <stdio.h>
#include <cuda.h>

// declaration of function to check for errors
void checkCudaError(const char* msg);

// kernel
__global__ void reverseArrayBlock(int *d_out, int *d_in) {
    int inOffset = blockDim.x * blockIdx.x;
    int outOffset = blockDim.x * (gridDim.x - 1 - blockIdx.x);
    int in = inOffset + threadIdx.x;
    int out = outOffset + (blockDim.x - 1 - threadIdx.x);
    d_out[out] = d_in[in];
}

// main thread
int main(int argc, char** argv) {
    int *h_a;
    int dimA = 256 * 1024;

    int *d_b, *d_a;

    int numThreadsPerBlock = 256;

    // compute number of blocks needed
    int numBlocks = dimA / numThreadsPerBlock;

    // allocate memory
    size_t memSize = numBlocks * numThreadsPerBlock*sizeof(int);
    h_a = (int *)malloc(memSize);
    cudaMalloc((void **) &d_a, memSize);
    cudaMalloc((void **) &d_b, memSize);

    // init array on host
    for (int i=0; i<dimA; i++) {
        h_a[i] = i;
    }

    cudaMemcpy( d_a, h_a, memSize, cudaMemcpyHostToDevice);

    dim3 dimGrid(numBlocks);
    dim3 dimBlock(numThreadsPerBlock);
    reverseArrayBlock <<< dimGrid, dimBlock >>> (d_b, d_a);
    
    // block until synced
    cudaThreadSynchronize();

    checkCudaError("kernel invocation");

    cudaMemcpy(h_a, d_b, memSize, cudaMemcpyDeviceToHost);

    checkCudaError("memcpy");

    for (int i=0; i<dimA; i++) {
        assert( h_a[i] == dimA - 1 - i);
    }

    cudaFree(d_a); cudaFree(d_b);
    free(h_a);
    return 0;
}

void checkCudaError(const char* msg) {
    cudaError_t err = cudaGetLastError();
    if (cudaSuccess != err) {
        fprintf(stderr, "Cuda error: %s : %s .\n", msg, cudaGetErrorString(err) );
        exit(EXIT_FAILURE);
    }
}

