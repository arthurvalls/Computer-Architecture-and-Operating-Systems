#include <stdio.h>

int main() {
    char *print_message = "Array após ordenação: ";
    int array[] = {5, 2, 6, 1, 3, 8, 7, 9, 4, 0};
    int array_size = sizeof(array) / sizeof(array[0]);
    int i, j, temp;

    printf("%s\n", print_message);

    for (i = 0; i < array_size - 1; i++) {
        for (j = 0; j < array_size - i - 1; j++) {
            if (array[j] > array[j + 1]) {
                temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }

    for (i = 0; i < array_size; i++) {
        printf("%d ", array[i]);
    }

    printf("\n");

    return 0;
}
