// queue.c
#include "../include/queue.h"
#include <stdlib.h>
#include <stdio.h>

void initializeQueue(Queue* queue) {
    queue->front = queue->rear = NULL;
}

int isQueueEmpty(Queue* queue) {
    return queue->front == NULL;
}

void enqueue(Queue* queue, Process process) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = process;
    newNode->next = NULL;

    if (isQueueEmpty(queue)) {
        queue->front = queue->rear = newNode;
    } else {
        queue->rear->next = newNode;
        queue->rear = newNode;
    }
}

Process dequeue(Queue* queue) {
    if (isQueueEmpty(queue)) {
        // Tratar fila vazia conforme necessário
        exit(EXIT_FAILURE);
    }

    Node* temp = queue->front;
    Process process = temp->data;

    queue->front = temp->next;
    free(temp);

    return process;
}
