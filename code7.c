#include <stdio.h>
#include <stdlib.h>

double abs_val(double number);
int argmax_abs(double* array, int lower_bound, int n);
void print_array(double* array, int n);
void print_matrix(double** matrix, int n);
double* column(double** matrix, int a, int n);
void swap_rows(double** matrix, int a, int b, int n);
int gaussian(double** matrix, int n);
double det(double** matrix, int row_swaps, int n);

int main(){
    int n, row_swaps;
    printf("Input side length of the matrix: ");
    scanf("%d", &n);

    double** matrix;

    matrix = (double**)malloc(n * sizeof(double*)); 
    
    for (int i = 0; i < n; i++)
        matrix[i] = (double*)malloc(n * sizeof(double));
    
    printf("Input elements of array:\n");

    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            scanf("%lf", &matrix[i][j]);

    row_swaps = gaussian(matrix, n);

    printf("\nMatrix after Gaussian elimination:\n");
    print_matrix(matrix, n);

    printf("Number of row swaps recorded: %d\n", row_swaps);

    printf("\ndet(matrix) = %lf\n", det(matrix, row_swaps, n));

    for(int i = 0; i < n; i++)
        free(matrix[i]);
}

double abs_val(double number){
    double abs;
    if(number < 0)
        abs = -number;
    else
        abs = number;

    return abs;
}

int argmax_abs(double* array, int lower_bound, int n){
    int max = array[lower_bound];
    int index = lower_bound;

    for(int i = lower_bound; i < n; i++){
        if(abs_val(max) < abs_val(array[i])){
            max = array[i];
            index = i;
        }
    }
    return index;
}

void print_array(double* array, int n){
    for(int i = 0; i < n; i++){
        if(i == n - 1)
            printf("%lf\n", array[i]);
        else
            printf("%lf ", array[i]);
    }
}

void print_matrix(double** matrix, int n){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(j == n - 1)
                printf("%lf\n", matrix[i][j]);
            else if(j == n - 1 && i == n -1)
                printf("%lf\n\n", matrix[i][j]);
            else
                printf("%lf\t", matrix[i][j]);
        }
    }
}

double* column(double** matrix, int a, int n){
    double* column = malloc(n * sizeof(double));
    
    for(int i = 0; i < n; i++)
        column[i] = matrix[i][a];

    return column;
}

void swap_rows(double** matrix, int a, int b, int n){
    double temp;

    for(int i = 0; i < n; i++){
        temp = matrix[a][i];
        matrix[a][i] = matrix[b][i];
        matrix[b][i] = temp;
    }
}

int gaussian(double** matrix, int n){
    int h = 0;
    int k = 0;
    double f;
    int i_max;
    int row_swaps = 0;

    while(h < n && k < n){
        i_max = argmax_abs(column(matrix, k, n), h, n);
        if(matrix[i_max][k] == 0)
            k++;
        else{
            if(i_max != h){
                swap_rows(matrix, h, i_max, n);
                row_swaps++;
            }
            for(int i = h + 1; i < n; i++){
                f = matrix[i][k] / matrix[h][k];
                matrix[i][k] = 0;
                for(int j = k + 1; j < n; j++)
                    matrix[i][j] = matrix[i][j] - matrix[h][j] * f;
            }
            h++;
            k++;
        }
    }

    return row_swaps;
}

double det(double** matrix, int row_swaps, int n){
    double det = 1;

    for(int i = 0; i < n; i++)
        det *= matrix[i][i];

    if(row_swaps % 2 != 0)
        det = -det;

    return det;
}
