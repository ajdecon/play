#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    int rank, size;
    int key;
    void* extra_arg; /* unused */
    MPI_Status status;

    /* Broadcast value for sync */
    int x;

    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    MPI_Keyval_create(MPI_DUP_FN, MPI_NULL_DELETE_FN,
        &key, extra_arg);

    if (rank==0) {
        int value, value1, flag;
        value = 42;
        MPI_Comm_set_attr(MPI_COMM_WORLD, key, &value);
        x=17;
        MPI_Comm_get_attr(MPI_COMM_WORLD, key, &value1,&flag);
        printf("Same proc: value1 = %d \n", value1);
        MPI_Send(&x,1,MPI_INT,1,0,MPI_COMM_WORLD);
    } else if (rank==1) {
        MPI_Recv(&x,1,MPI_INT,0,0,MPI_COMM_WORLD,&status);
        int newval;
        int flag;
        MPI_Comm_get_attr(MPI_COMM_WORLD,key,&newval,&flag);
        if (flag) 
            printf("Value = %d \n", newval);
    }
    MPI_Finalize();
    return 0;
}
