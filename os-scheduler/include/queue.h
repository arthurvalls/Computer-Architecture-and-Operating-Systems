#ifndef QUEUE_H
#define QUEUE_H

#include "process.h"

typedef struct Node {
    Process data;
    struct Node* next;
} Node;

typedef struct {
    Node* front;
    Node* rear;
} Queue;

void initializeQueue(Queue* queue);
int isQueueEmpty(Queue* queue);
void enqueue(Queue* queue, Process process);
Process dequeue(Queue* queue);

#endif // QUEUE_H
