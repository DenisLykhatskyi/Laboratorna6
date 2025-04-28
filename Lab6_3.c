#include <stdio.h>
#include <stdlib.h>

int **allocate_matrix(int rows, int cols) {
    int **matrix = (int **)malloc(rows * sizeof(int *));
    if (matrix == NULL) {
        return NULL;
    }
    for (int i = 0; i < rows; i++) {
        matrix[i] = (int *)malloc(cols * sizeof(int));
        if (matrix[i] == NULL) {
            for (int k = 0; k < i; k++) {
                free(matrix[k]);
            }
            free(matrix);
            return NULL;
        }
    }
    return matrix;
}

void free_matrix(int **matrix, int rows) {
    if (matrix == NULL) return;
    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

void read_matrix(int rows, int cols, int **matrix) {
    printf("Введіть елементи матриці (%d x %d):\n", rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (scanf("%d", &matrix[i][j]) != 1) {
                 printf("Некоректне введення. Будь ласка, вводьте лише цілі числа.\n");
            }
        }
    }
}

void print_matrix(int rows, int cols, int **matrix) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d\t", matrix[i][j]);
        }
        printf("\n");
    }
}

void transpose_matrix(int rows, int cols, int **matrix, int **result) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result[j][i] = matrix[i][j];
        }
    }
}

void add_matrices(int rows, int cols, int **matrix1, int **matrix2, int **result) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result[i][j] = matrix1[i][j] + matrix2[i][j];
        }
    }
}

int main() {
    int m, n;
    int **c = NULL, **x = NULL, **x_t = NULL, **b = NULL;

    printf("Введіть кількість рядків (M): ");
    if (scanf("%d", &m) != 1 || m <= 0) {
        printf("Некоректне введення кількості рядків (M).\n");
        return 1;
    }

    printf("Введіть кількість стовпців (N): ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Некоректне введення кількості стовпців (N).\n");
        return 1;
    }

    if (m != n) {
        printf("Помилка: для додавання матриць C (%dx%d) + X_T (%dx%d) необхідно, щоб M = N.\n", m, n, n, m);
        printf("Матриці неможливо додати через несумісні розміри.\n");
        return 1;
    }

    c = allocate_matrix(m, n);
    x = allocate_matrix(m, n);
    x_t = allocate_matrix(n, m);
    b = allocate_matrix(m, n);

    if (c == NULL || x == NULL || x_t == NULL || b == NULL) {
        printf("Помилка: не вдалося виділити пам'ять.\n");
        free_matrix(c, m);
        free_matrix(x, m);
        free_matrix(x_t, n);
        free_matrix(b, m);
        return 1;
    }

    printf("\nВведіть матрицю C:\n");
    read_matrix(m, n, c);

    printf("\nВведіть матрицю X:\n");
    read_matrix(m, n, x);

    transpose_matrix(m, n, x, x_t);

    add_matrices(m, n, c, x_t, b);

    printf("\nМатриця C:\n");
    print_matrix(m, n, c);

    printf("\nМатриця X:\n");
    print_matrix(m, n, x);

    printf("\nТранспонована матриця X (Xt):\n");
    print_matrix(n, m, x_t);

    printf("\nРезультат матриці B = C + Xt:\n");
    print_matrix(m, n, b);

    free_matrix(c, m);
    free_matrix(x, m);
    free_matrix(x_t, n);
    free_matrix(b, m);

    return 0;
}
