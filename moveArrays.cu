// moveArrays.cu
//      From Dr Dobbs tutorial: http://drdobbs.com/parallel/207200659?pgno=2

#include <assert.h>
#include <stdio.h>
#include <cuda.h>

int main(void) {
    float *a_h, *b_h;
    float *a_d, *b_d;
    int N = 14;
    int i;

    a_h = (float *)malloc(sizeof(float)*N);
    b_h = (float *)malloc(sizeof(float)*N);
    
    cudaMalloc((void **) &a_d, sizeof(float)*N);
    cudaMalloc((void **) &b_d, sizeof(float)*N);

    //initialize host data
    for (i=0; i<N; i++) {
        a_h[i] = 10.f+i;
        b_h[i] = 0.f;
    }

    // send data from host to device
    cudaMemcpy(a_d, a_h, sizeof(float)*N, cudaMemcpyHostToDevice);
    // copy data within device
    cudaMemcpy(b_d, a_d, sizeof(float)*N, cudaMemcpyDeviceToDevice);
    // retrieve data from device: b_d to b_h
    cudaMemcpy(b_h, b_d, sizeof(float)*N, cudaMemcpyDeviceToHost);

    // check result
    for (i=0; i<N; i++) 
        assert(a_h[i]==b_h[i]);

    free(a_h); free(b_h);
    cudaFree(a_d); cudaFree(b_d);
}
