#include <mpi.h>
#include <stdio.h>

void Build_type( float* a, float* b, float* n, MPI_Datatype* point_t ) {

    int block_lengths[3];
    MPI_Aint displacements[3];
    MPI_Datatype typelist[3];
    MPI_Aint start_address;
    MPI_Aint address;

    block_lengths[0] = block_lengths[1] = block_lengths[2] = 1;
    typelist[0] = MPI_FLOAT;
    typelist[1] = MPI_FLOAT;
    typelist[2] = MPI_INT;

    displacements[0] = 0;
    MPI_Address(a, &start_address);
    MPI_Address(b, &address);
    displacements[1] = address - start_address;
    
    MPI_Address(n, &address);
    displacements[2] = address - start_address;

    MPI_Type_struct(3, block_lengths, displacements, typelist, point_t);
    MPI_Type_commit(point_t);

}

int main(int argc, char* argv[]) {
    
    int my_rank;
    int size;
    float* a; 
    float* b;
    int* n;
    MPI_Status status;
    MPI_Datatype point_t;

    MPI_Initialize(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (my_rank == 0) {
        printf("%d: Hello, world!\n", my_rank);

        a = 15.0; b = 42.0; n = 312;
        Build_type(a, b, n, &point_t);
    }
    MPI_Bcast(a,1,point_t,0,MPI_COMM_WORLD);

    if (my_rank==1) {

        printf("%d: Goodbye, cruel world!\n", my_rank);
        

    MPI_Finalize();

}
