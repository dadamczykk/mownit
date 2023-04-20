#include <stdio.h>
#include <gsl/gsl_blas.h>
#include <stdlib.h>
#include <time.h>


double * rand_arr(int size){
    double * arr = malloc(size * size * sizeof(double));
    for (int i = 0; i < size * size; i++){
        arr[i] = (double) rand();
    }
    return (arr);
}

double * zero_arr(int size){
    double * arr = malloc(size * size * sizeof(double));
    for (int i = 0; i < size * size; i++){
        arr[i] = 0;
    }
    return (arr);
}

double** arr_to_matrix(double * arr, int size){
    double ** mat = (double **) malloc (size * sizeof(double*));
    for (int i = 0; i < size; i++){
        mat[i] = (double *) malloc(size * sizeof(double));
        for (int j = 0; j <  size; j++){
            mat[i][j] = arr[i * size + j];
        }
    }
    return mat;
}

double** naive_multiplication(double** A, double** B, int m, int n, int p) {
    double** C = (double**) malloc(m * sizeof(double*)); 
    for (int i = 0; i < m; i++) {
        C[i] = (double*) calloc(p, sizeof(double));
    }

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < p; j++) {
            for (int k = 0; k < n; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return C;
}

double** better_multiplication(double** A, double** B, int m, int n, int p) {
    double** C = (double**) malloc(m * sizeof(double*)); 
    for (int i = 0; i < m; i++) {
        C[i] = (double*) calloc(p, sizeof(double));
    }

    for (int i = 0; i < m; i++) {
        for (int k = 0; k < n; k++) {
            for (int j = 0; j < p; j++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return C;
}

int BLAS_multiplication(gsl_matrix_view A, gsl_matrix_view B, gsl_matrix_view C){
    return gsl_blas_dgemm(CblasNoTrans, CblasNoTrans, 1.0, &A.matrix, &B.matrix, 0.0, &C.matrix);
}

void single_test(int repeats, int size){
    clock_t start_time, end_time;
    double elapsed_time;
    for (int i = 0; i < repeats; i++){
        double * A_lin = rand_arr(size);
        double * B_lin = rand_arr(size);
        double * C_lin = zero_arr(size);
        double ** A = arr_to_matrix(A_lin, size);
        double ** B = arr_to_matrix(B_lin, size);
        gsl_matrix_view A_blas = gsl_matrix_view_array(A_lin, size, size);
        gsl_matrix_view B_blas = gsl_matrix_view_array(B_lin, size, size);
        gsl_matrix_view C_blas = gsl_matrix_view_array(C_lin, size, size);

        start_time = clock();
        double ** D = naive_multiplication(A, B, size, size, size);
        end_time = clock();
        elapsed_time = ((double) (end_time - start_time)) / CLOCKS_PER_SEC;
        printf("naive_multiplication,%d,%f\n", size, elapsed_time);
        
        
        start_time = clock();
        double ** E = better_multiplication(A, B, size, size, size);
        end_time = clock();
        elapsed_time = ((double) (end_time - start_time)) / CLOCKS_PER_SEC;
        printf("better_multiplication,%d,%f\n", size, elapsed_time);


        start_time = clock();
        BLAS_multiplication(A_blas, B_blas, C_blas);
        end_time = clock();
        elapsed_time = ((double) (end_time - start_time)) / CLOCKS_PER_SEC;
        printf("BLAS_multiplication,%d,%f\n", size, elapsed_time);

        free(A_lin);
        free(B_lin);
        free(C_lin);
        for(int j = 0; j < size; j++){
            free(A[j]);
            free(B[j]);
            free(E[j]);
            free(D[j]);
        }
        free(E);
        free(D);
        free(A);
        free(B);
    }
}

int main (void){
    srand(time(NULL));
    
    printf("type,size,time\n");

    for (int i = 150; i <= 1500; i += 150){
        single_test(10, i);
    }
    
    return 0;
}