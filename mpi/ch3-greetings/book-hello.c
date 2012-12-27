#include <stdio.h>
#include <string.h>
#include <mpi.h>

/* Version of an MPI Hello, World program
 * Modified from the version in Pacheco.
 */

int main(int argc, char* argv[]) {

    int my_rank;
    int p;
    int source;
    int dest;

    int tag = 0;
    char message[100];
    MPI_Status status;

    // Start up MPI
    MPI_Init(&argc, &argv);

    // Find out process rank.
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    // Find out number of processes.
    MPI_Comm_size(MPI_COMM_WORLD, &p);

    if (my_rank!=0) {
        sprintf(message, "Greetings from process %d!",my_rank);
        dest=0;
        // Use strlen+1 so that '\0' gets transmitted.
        MPI_Send(message, strlen(message)+1, MPI_CHAR, dest, tag, MPI_COMM_WORLD);
    } else {
        for (source = 1; source < p; source++) {
            MPI_Recv(message,100,MPI_CHAR,source,tag,MPI_COMM_WORLD, &status);
            printf("%s\n",message);
        }
    }

    // Shut down MPI
    MPI_Finalize();
}
