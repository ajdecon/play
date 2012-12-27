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
 *
 * This version is started for Chapter 5, "Collective Communication"; begins with modifying
 * the Get_data function.
 */

/*
 * The following functions implement a tree-structrue of 
 * process communication.
 *
 */

/* Ceiling of log_2(x) is the number of times x-1 can be
 * divided by 2 until the quotient is 0. Div by 2 is the same
 * as a right shift.
 */

int Ceiling_log2(int x) {
    unsigned temp = (unsigned) x-1;
    int result=0;

    while(temp != 0) {
        temp = temp >> 1;
        result = result + 1;
    }

    return result;
}

int I_receive(
    int  stage       /* in  */,
    int  my_rank     /* in  */,
    int* source_ptr  /* out */) {

    int power_2_stage;
    
    /* 2^stage = 1 << stage */
    power_2_stage = 1 << stage;
    if ((power_2_stage <= my_rank) && 
        (my_rank < 2*power_2_stage)) {

        *source_ptr = my_rank - power_2_stage;
        return 1;
    } else return 0;
} /* I_receive */

int I_send(
    int     stage   /* in  */,
    int     my_rank /* in  */,
    int     p       /* in  */,
    int*    dest_ptr /* out */) {

    int power_2_stage;

    power_2_stage = 1 << stage;

    if (my_rank < power_2_stage) {
        *dest_ptr = my_rank + power_2_stage;
        if (*dest_ptr >= p) return 0;
        else return 1;
    }
    else return 0;
} /* I_send */

void Send(
    float a,
    float b,
    int n,
    int dest) {

    MPI_Send(&a, 1, MPI_FLOAT, dest, 0, MPI_COMM_WORLD);
    MPI_Send(&b, 1, MPI_FLOAT, dest, 1, MPI_COMM_WORLD);
    MPI_Send(&n, 1, MPI_INT, dest, 2, MPI_COMM_WORLD);
} /* Send */

void Receive(
    float* a,
    float* b, 
    int* n,
    int source) {

    MPI_Status status;

    MPI_Recv(a,1,MPI_FLOAT,source,0,MPI_COMM_WORLD,&status);
    MPI_Recv(b,1,MPI_FLOAT,source,1,MPI_COMM_WORLD,&status);
    MPI_Recv(n,1,MPI_INT,source,2,MPI_COMM_WORLD,&status);

} /* Receive */

void Get_data1(
    float* a_ptr,
    float* b_ptr,
    int* n_ptr,
    int my_rank,
    int p) {

    int source;
    int dest;
    int stage;

    if (my_rank == 0) {
        printf("Enter a, b, and n\n");
        scanf("%f %f %d", a_ptr, b_ptr, n_ptr);
    }

    for (stage = 0; stage < Ceiling_log2(p); stage++) {
        if (I_receive(stage,my_rank,&source)) {
            Receive(a_ptr,b_ptr,n_ptr,source);
            printf("I am %d and received data from %d.\n",my_rank,source);
        }
        else if (I_send(stage,my_rank,p,&dest)) {
            Send(*a_ptr,*b_ptr,*n_ptr,dest);
            printf("I am %d and sent data to %d.\n",my_rank,dest);
        }
    }
} /* Get_data1 */

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

    Get_data1(&a, &b, &n, my_rank, p);

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
