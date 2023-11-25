#ifndef QUEUE_H
#define QUEUE_H

#include "process.h"

typedef struct Node {
    Process process;
    struct Node* next;
} Node;

typedef struct {
    Node* front;
    Node* rear;
} Queue;

void initializeQueue(Queue* queue);

void freeNode(Node* node);

void freeQueue(Queue* queue);

int isQueueEmpty(Queue* queue);

void queueInsert(Queue* queue, Process process);

void queueInsertFirst(Queue* queue, Process process);

Process queuePop(Queue* queue);

void printQueue(Queue* queue);

void printAllQueues(Queue* highPriorityQueue,
                    Queue* lowPriorityQueue,
                    Queue* diskQueue,
                    Queue* tapeQueue,
                    Queue* printerQueue);

#endif // QUEUE_H
