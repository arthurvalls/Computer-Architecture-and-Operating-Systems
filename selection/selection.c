#include <stdio.h>

int main() {
    char *print_message = "Array após ordenação: ";
    int array[] = {5, 2, 6, 1, 3, 8, 7, 9, 4, 0};
    int array_size = sizeof(array) / sizeof(array[0]);
    int i, j, temp;

    printf("%s\n", print_message);
    // Selection Sort
    for (i = 0; i < array_size - 1; i++) {
        int minIndex = i;
        for (j = i + 1; j < array_size; j++) {
            if (array[j] < array[minIndex]) {
                minIndex = j;
            }
        }
        // Troca o elemento atual com o menor elemento encontrado
        temp = array[i];
        array[i] = array[minIndex];
        array[minIndex] = temp;
    }

    for (i = 0; i < array_size; i++) {
        printf("%d ", array[i]);
    }

    printf("\n");

    return 0;
}
