#include <stdio.h>
#include <mpi.h>

int main(int argc, char* argv[]) {


float vector[100];
MPI_Status status;
int p;
int my_rank;


MPI_Init(&argc, &argv);
MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
MPI_Comm_size(MPI_COMM_WORLD, &p);


if (my_rank == 0) {

    printf("Rank = %d\n\n");

    for (int i=0; i<100; i++) {
        vector[i] = (float) (2*i);
    }
    printf("Process 0: Hooray!\n");
    MPI_Send(vector+50, 50, MPI_FLOAT, 1, 0, MPI_COMM_WORLD);

} else {

    printf("Process 1: Here we go...\n");
    MPI_Recv(vector+50, 50, MPI_FLOAT, 0, 0, MPI_COMM_WORLD, &status);

    for (int j = 0; j<100; j++) {
        printf("%d = %f    ", j, vector[j]);
    }
}

MPI_Finalize();

}
