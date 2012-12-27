
/*
 * Simple algorithm for serial matrix multiplication
 * (square matrices order n)
 */
void Serial_matrix_mult(
    MATRIX_T A,
    MATRIX_T B,
    MATRIX_T C,
    int n) {

    int i,j,k;

    for (i = 0; i < n; i++) {
        for (j=0; j<n; j++) {
            C[i][j] = 0.0;
            for (k=0; k<n; k++) {
                C[i][j] = C[i][j] + A[i][k]*B[k][j];
            }
        }
    }
}
