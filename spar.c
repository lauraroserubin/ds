#include <stdio.h>
#define MAX 100
int convertToSparse(int mat[10][10], int sparse[MAX][3], int rows, int cols) {
    int i, j, k = 1;

    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            if (mat[i][j] != 0) {
                sparse[k][0] = i;
                sparse[k][1] = j;
                sparse[k][2] = mat[i][j];
                k++;
            }
        }
    }

    sparse[0][0] = rows;
    sparse[0][1] = cols;
    sparse[0][2] = k - 1;

    return k;
}
int addSparse(int a[MAX][3], int b[MAX][3], int result[MAX][3]) {
    int i = 1, j = 1, k = 1;

    if (a[0][0] != b[0][0] || a[0][1] != b[0][1]) {
        printf("Matrix dimensions must match.\n");
        return -1;
    }

    result[0][0] = a[0][0];
    result[0][1] = a[0][1];

    while (i <= a[0][2] && j <= b[0][2]) {
        if (a[i][0] < b[j][0] || (a[i][0] == b[j][0] && a[i][1] < b[j][1])) {
            result[k][0] = a[i][0];
            result[k][1] = a[i][1];
            result[k][2] = a[i][2];
            i++; k++;
        } else if (b[j][0] < a[i][0] || (b[j][0] == a[i][0] && b[j][1] < a[i][1])) {
            result[k][0] = b[j][0];
            result[k][1] = b[j][1];
            result[k][2] = b[j][2];
            j++; k++;
        } else {
            int sum = a[i][2] + b[j][2];
            if (sum != 0) {
                result[k][0] = a[i][0];
                result[k][1] = a[i][1];
                result[k][2] = sum;
                k++;
            }
            i++; j++;
        }
    }

    while (i <= a[0][2]) {
        result[k][0] = a[i][0];
        result[k][1] = a[i][1];
        result[k][2] = a[i][2];
        i++; k++;
    }

    while (j <= b[0][2]) {
        result[k][0] = b[j][0];
        result[k][1] = b[j][1];
        result[k][2] = b[j][2];
        j++; k++;
    }

    result[0][2] = k - 1;
    return k;
}


void transposeSparse(int input[MAX][3], int output[MAX][3]) {
    int i, j, k = 1;
    int rows = input[0][1];  
    int cols = input[0][0];  
    int terms = input[0][2];

    output[0][0] = rows;
    output[0][1] = cols;
    output[0][2] = terms;

    for (i = 0; i < input[0][1]; i++) { 
        for (j = 1; j <= terms; j++) {
            if (input[j][1] == i) {
                output[k][0] = input[j][1]; 
                output[k][1] = input[j][0]; 
                output[k][2] = input[j][2];
                k++;
            }
        }
    }
}

void printSparse(int sparse[MAX][3], int count) {
    printf("Row Col Val\n");
    for (int i = 0; i < count; i++) {
        printf("%d   %d   %d\n", sparse[i][0], sparse[i][1], sparse[i][2]);
    }
}

int main() {
    int mat1[10][10], mat2[10][10];
    int sparse1[MAX][3], sparse2[MAX][3], sum[MAX][3], transpose[MAX][3];
    int m, n, matrix1, matrix2, matrixSum;

    printf("Enter rows and columns of matrices: ");
    scanf("%d %d", &m, &n);

    printf("Enter first matrix:\n");
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &mat1[i][j]);

    printf("Enter second matrix:\n");
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &mat2[i][j]);

    matrix1 = convertToSparse(mat1, sparse1, m, n);
    matrix2 = convertToSparse(mat2, sparse2, m, n);

    printf("\nSparse Matrix 1:\n");
    printSparse(sparse1, matrix1);

    printf("\nSparse Matrix 2:\n");
    printSparse(sparse2, matrix2);

    matrixSum = addSparse(sparse1, sparse2, sum);

    if (matrixSum != -1) {
        printf("\nSum of Sparse Matrices:\n");
        printSparse(sum, matrixSum);

        transposeSparse(sum, transpose);
        printf("\nTranspose of the Resultant Sparse Matrix:\n");
        printSparse(transpose, transpose[0][2] + 1);  
}
    return 0;
}
