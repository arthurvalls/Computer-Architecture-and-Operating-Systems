#include <stdio.h>

int main() {
    int array[] = {5, 2, 6, 1, 3, 8, 7, 9, 4, 0};
    int array_size = 10;
    int i, j, temp;

    for (i = 0; i < array_size - 1; i++) {
        for (j = 0; j < array_size - i - 1; j++) {
            if (array[j] > array[j + 1]) {
                // Troca os elementos se estiverem fora de ordem
                temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }
    return 0;
}
