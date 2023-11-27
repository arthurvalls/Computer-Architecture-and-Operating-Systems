#include "../include/queue.h"
#include <stdlib.h>
#include <stdio.h>

void initializeQueue(Queue* queue) {
    queue->front = queue->rear = NULL;
}

void freeNode(Node* node)
{
    free(node);
}

void freeQueue(Queue* queue)
{
    while (!isQueueEmpty(queue)) {
        Node* temp = queue->front;
        queue->front = temp->next;
        freeNode(temp);
    }
    // printf("Queue desalocada com sucesso\n");
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

void queueInsertFirst(Queue* queue, Process process)
{
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->process = process;
    newNode->next = NULL;

    if (isQueueEmpty(queue))
    {
        queue->front = queue->rear = newNode;
    } else
    {
        newNode->next = queue->front;
        queue->front = newNode;
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
        printf("\n");
        return;
    }

    Node* current = queue->front;
    while (current != NULL) {
        printf("P%d ", current->process.pid);
        current = current->next;
    }
    printf("\n");
}

void formattedPrintQueue(const char* queueName, Queue* queue)
{
    printf("%s: ", queueName);
    printQueue(queue);
}

void printAllQueues(Queue* highPriorityQueue,
                   Queue* lowPriorityQueue,
                   Queue* diskQueue,
                   Queue* tapeQueue,
                   Queue* printerQueue)
{
    printf("\n");
    formattedPrintQueue("Fila de alta prioridade", highPriorityQueue);
    formattedPrintQueue("Fila de baixa prioridade", lowPriorityQueue);
    formattedPrintQueue("Fila de I/O Disco", diskQueue);
    formattedPrintQueue("Fila de I/O Fita", tapeQueue);
    formattedPrintQueue("Fila de I/O Impressão", printerQueue);
    printf("\n");
}