#include "../include/queue.h"
#include <stdlib.h>
#include <stdio.h>

void initializeQueue(Queue* queue) {
    queue->front = queue->rear = NULL;
}

int isQueueEmpty(Queue* queue) {
    return queue->front == NULL;
}

void queueInsert(Queue* queue, Process process) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->process = process;
    newNode->next = NULL;

    if (isQueueEmpty(queue)) {
        queue->front = queue->rear = newNode;
    } else {
        queue->rear->next = newNode;
        queue->rear = newNode;
    }
}

Process queuePop(Queue* queue) {
    if (isQueueEmpty(queue)) {
        // Tratar fila vazia conforme necessário
        exit(EXIT_FAILURE);
    }

    Node* temp = queue->front;
    Process process = temp->process;

    queue->front = temp->next;
    free(temp);

    return process;
}


void printQueue(Queue* queue) {
    if (isQueueEmpty(queue)) {
        printf("Fila vazia, CPU esta ociosa.\n");
        return;
    }

    printf("Queue: ");
    Node* current = queue->front;
    while (current != NULL) {
        printf("%d ", current->process.pid);
        current = current->next;
    }
    printf("\n");
}
