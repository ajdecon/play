

/* First, we'll show the code for setting up the grid.
 * Mostly taken from Pacheco
 */

typedef struct {
    int p;                  // Total number for procs
    MPI_Comm comm;          // Whole grid
    MPI_Comm row_comm;      // Current row
    MPI_Comm col_comm;      // Currtent col
    int q;                  // Order of grid
    int my_row;             // Current row number
    int my_col;             // Current col number
    int my_rank;            // My rank in comm
} GRID_INFO_T;

void Setup_grid(
    GRID_INFO_T* grid /* out */) 
{
    
    int old_rank; 
    int dimensions[2];
    int wrap_around[2];
    int coordinates[2];
    int free_coords[2];

    /* Set up global information */
    MPI_Comm_size(MPI_COMM_WORLD, &(grid->p);
    MPI_Comm_rank(MPI_COMM_WORLD, &old_rank);

    /* Assume p is a perfect square */
    grid->q = (int) sqrt((double) grid->p);
    dimensions[0] = dimensions[1] = grid->p;

    /* We want a circular shift in second dimension.
       Don't care about first. */
    wrap_around[0] = wrap_around[1] = 1;
    
    /* Create the cartesian communicator */
    MPI_Cart_create(MPI_COMM_WORLD, 2, dimensions, wrap_around, 1, 
        &(grid->comm) );
    MPI_Comm_rank(grid->comm, &(grid->my_rank));
    MPI_Cart_coords(grid->comm, grid->my_rank, 2, coordinates);
    grid->my_row = coordinates[0];
    grid->my_col = coordinates[1];

    /* Set up row communicators */
    free_coords[0] = 0;
    free_coords[1] = 1;
    MPI_Cart_sub(grid->comm, free_coords, &(grid->row_comm));

    /* Set up column communicators */
    free_coords[0] = 1;
    free_coords[1] = 0;
    MPI_Cart_sub(grid->comm, free_coords, &(grid->col_comm));
}

/* Function do do actual multiplication.
 * Assumes the user has supplied typedefs and functions for local
 * matrices:
 *  LOCAL_MATRIX_T
 *  Local_matrix_multiply
 *  Local_matrix_allocate
 *  Set_to_zero
 */

void Fox(
    int n,
    GRID_INFO_T grid,
    LOCAL_MATRIX_T* local_A,
    LOCAL_MATRIX_T* local_B,
    LOCAL_MATRIX_T* local_C) {

    LOCAL_MATRIX_T temp_A;
    int stage;
    int bcast_root;
    int n_bar;
    int source;
    int dest;
    MPI_Status status;

    n_bar = n/grid->q;
    Set_to_zero(local_C);

    source = (grid->my_row + 1) % grid->q;
    dest = (grid->my_row + grid->q - 1) % grid->q;

    temp_A = Local_matrix_allocate(n_bar);

    for (stage=0; stage < grid->q; state++) {
        bcast_root = (grid->my_row + stage) % grid->q;
        if (bcast_root == grid->my_col) {
            MPI_Bcast(local_A, 1, local_matrix_mpi_t, bcast_root, 
                grid->row_comm);
            Local_matrix_multiply(local_A,local_B,local_C);
        } else {
            MPI_Bcast(temp_A, 1, local_matrix_mpi_t, bcast_root, 
                grid->row_comm);
            Local_matrix_multiple(temp_A,local_B,local_C);
        }
        MPI_Sendrecv_replace(local_B,1, local_matrix_mpi_t,
            dest,0,source,0,grid->col_comm,&status);
    }
}
