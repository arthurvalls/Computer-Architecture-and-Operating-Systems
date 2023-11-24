#include <stdio.h>

void gnome_sort(int array[], int size) {
    int i = 0;
    while (i < size) {
        if (i == 0 || array[i] >= array[i - 1]) {
            i++;
        } else {
            int temp = array[i];
            array[i] = array[i - 1];
            array[i - 1] = temp;
            i--;
        }
    }
}

int main() {
    int array[] = {5, 6, 7, 4, 2, 3, 1};
    int size = 7;
    
    gnome_sort(array, size);

    return 0;
}
