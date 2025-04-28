#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ROWS 3
#define COLS 5

int compare_desc(const void *a, const void *b) {
    return (*(int *)b - *(int *)a);
}

int main() {
    int p[ROWS][COLS];

    srand(time(NULL));

    printf("Згенерований масив (%d x %d):\n", ROWS, COLS);
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            p[i][j] = rand() % 100;
            printf("%d\t", p[i][j]);
        }
        printf("\n");
    }

    for (int i = 0; i < ROWS; i++) {
        qsort(p[i], COLS, sizeof(int), compare_desc);
    }

    printf("\nВідсортований масив за спаданням у кожному рядку:\n");
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            printf("%d\t", p[i][j]);
        }
        printf("\n");
    }

    return 0;
}
