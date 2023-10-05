#include <stdio.h>

// Função para ordenar um array usando o algoritmo de ordenação por inserção
void insertionSort(int n, int values[]) {
    for (int i = 0; i < n; i++) {
        int element = i;

        // Move o elemento para a posição correta dentro da parte ordenada do array
        while (element > 0 && values[element] < values[element - 1]) {
            int aux = values[element];
            values[element] = values[element - 1];
            values[element - 1] = aux;
            element--;
        }
    }
}

int main() {
    int values[] = {2, 3, 1};
    int n = 3;

    insertionSort(n, values);


    return 0;
}
