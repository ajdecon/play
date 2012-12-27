#include <stdio.h>
#include <mpi.h>
#include <math.h>

/* 
 * Parallel version of the trapezoidal rule.
 * Algorithm:
 * 1. Each process calculates its interval.
 * 2. Each process estimates the integral of f(x) over its interval, using the trap rule.
 * 3. Each process != 0 sends its integral to 0.
 * 4. Process 0 sums the results.
 */

void Get_data(
        float* a_ptr    /* out */,
        float* b_ptr    /* out */,
        int*   n_ptr    /* out */,
        int    my_rank  /* in  */,
        int    p        /* in  */) {

    int source = 0;
    int dest;
    int tag; 
    MPI_Status status;

    if (my_rank == source) {
        printf("Enter a, b, and n\n");
        scanf("%f %f %d", a_ptr, b_ptr, n_ptr);
        for (dest = 1; dest < p; dest++) {
            tag = 0;
            MPI_Send(a_ptr, 1, MPI_FLOAT, dest, tag, MPI_COMM_WORLD);
            tag = 1;
            MPI_Send(b_ptr, 1, MPI_FLOAT, dest, tag, MPI_COMM_WORLD);
            tag = 2;
            MPI_Send(n_ptr, 1, MPI_FLOAT, dest, tag, MPI_COMM_WORLD);
        }
    } else {
        tag = 0;
        MPI_Recv(a_ptr, 1, MPI_FLOAT, source, tag, MPI_COMM_WORLD, &status);
        tag = 1;
        MPI_Recv(b_ptr, 1, MPI_FLOAT, source, tag, MPI_COMM_WORLD, &status);
        tag = 2;
        MPI_Recv(n_ptr, 1, MPI_FLOAT, source, tag, MPI_COMM_WORLD, &status);
    }
} /* Get_data */

int main(int argc, char* argv[]) {

    int my_rank, p;
    float a;
    float b;
    int n;
    float h;
    float local_a, local_b;
    int local_n;
    float integral, total;
    int source; 
    int dest = 0;
    int tag = 0;
    MPI_Status status;

    float Trap(float local_a, float local_b, int local_n, float h);

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &p);

    Get_data(&a, &b, &n, my_rank, p);

    h = (b-a)/n;
    local_n = n/p;

    local_a = a + my_rank*local_n*h;
    local_b = local_a + local_n*h;

    integral = Trap(local_a, local_b, local_n, h);
    printf("This is process %d with local a, b, and n = %f, %f, %d.\n",my_rank,local_a,local_b,local_n);
    

    if (my_rank == 0) {
        total = integral;
        for (source = 1; source < p; source++) {
            MPI_Recv(&integral, 1, MPI_FLOAT, source, tag, MPI_COMM_WORLD, &status);
            total = total + integral;
        }
    } else { 
        MPI_Send(&integral, 1, MPI_FLOAT, dest, tag, MPI_COMM_WORLD);
    }

    if (my_rank==0) {
        printf("With n = %d traps, our estimate from %f to %f is %f\n", n, a, b, total);
    }

    MPI_Finalize();

}

float Trap(float local_a, float local_b, int local_n, float h) {

    float integral;
    float x;
    int i;

    float f(float x);

    integral = (f(local_a) + f(local_b))/2.0;
    x = local_a;
    for (i=1; i<=local_n-1; i++) {
        x = x+h;
        integral = integral + f(x);
    }

    integral = integral*h;
    return integral;
}

float f(float x) {
    float r;
    r = x*x;
    return r;
}
