#include <mpi.h>
#include <stdio.h>

int main(int argc, char* argv[]) {

    int my_rank;
    float a;
    float b;
    int n;
    char buffer[100];
    int position;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    if (my_rank==0) {
        a = 32.0; b = 42.0; n = 321;
        position = 0;
        MPI_Pack(&a, 1, MPI_FLOAT, buffer, 100, &position, MPI_COMM_WORLD);
        MPI_Pack(&b, 1, MPI_FLOAT, buffer, 100, &position, MPI_COMM_WORLD);
        MPI_Pack(&n, 1, MPI_INT, buffer, 100, &position, MPI_COMM_WORLD);

        MPI_Bcast(buffer,100,MPI_PACKED,0,MPI_COMM_WORLD);
    } else {
        MPI_Bcast(buffer,100,MPI_PACKED,0,MPI_COMM_WORLD);
        
        position = 0;

        MPI_Unpack(buffer,100,&position,&a,1,MPI_FLOAT,MPI_COMM_WORLD);
        MPI_Unpack(buffer,100,&position,&b,1,MPI_FLOAT,MPI_COMM_WORLD);
        MPI_Unpack(buffer,100,&position,&n,1,MPI_FLOAT,MPI_COMM_WORLD);

        printf("%d: a = %f, b = %f, n = %d \n\n", my_rank, a, b, n);
    }

    MPI_Finalize();
}
