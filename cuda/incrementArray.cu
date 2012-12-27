// incrementArray.cu
//      Second program from Dr Dobbs tutorial. http://drdobbs.com/parallel/207402986

#include <cuda.h>
#include <stdio.h>
#include <assert.h>

// Host kernel = increment each element by 1
void incOnHost(float *a, int N) {
    int i;
    for (i=0; i<N; i++) 
        a[i] = a[i] + 1.f;
}

// Device Kernel = increment each element by 1
__global__ void incOnDevice(float *a, int N) {
    int idx = (blockIdx.x * blockDim.x) + threadIdx.x;
    if (idx<N)
        a[idx] = a[idx] + 1.f;
}

// Main thread
int main(void) {
    float *a_h, *b_h;
    float *a_d;
    int i, N=10;
    size_t size = N*sizeof(float);

    a_h = (float *)malloc(size);
    b_h = (float *)malloc(size);

    cudaMalloc((void **) &a_d, size);

    for (i=0; i<N; i++) 
        a_h[i] = (float)i;

    cudaMemcpy(a_d, a_h, size, cudaMemcpyHostToDevice);
    
    // do calculation on host
    incOnHost(a_h, N);

    // do calculation on device
    int blockSize = 4;
    int nBlocks = N/blockSize + (N%blockSize == 0?0:1);
    incOnDevice <<< nBlocks, blockSize >>> (a_d, N);

    // Retrieve results and compare
    cudaMemcpy(b_h,a_d,size,cudaMemcpyDeviceToHost);
    for (i=0; i<N; i++) {
        printf("value from host %d = %1.1f\n",i,a_h[i]);
        printf("value from device %d = %1.1f\n",i,b_h[i]);
        assert(a_h[i] == b_h[i]);
    }

    free(a_h); free(b_h); cudaFree(a_d);
}
