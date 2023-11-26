#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "queue.h"

void roundRobinScheduler(Process* processes,
                         Queue* highPriorityQueue,
                         Queue* lowPriorityQueue,
                         Queue* diskQueue,
                         Queue* tapeQueue,
                         Queue* printerQueue);

void printProcessesInfo(Process* processes);


void checkNewProcesses(Process* processes, int currentTime, Queue* queue);

void formattedPrintQueue(const char* queueName, Queue* queue);

void printTurnaroundTime(Process* processes);

int isCPUActive(Queue* highPriorityQueue, Queue* lowPriorityQueue);

int checkIfHasIo(Queue* diskQueue, Queue* tapeQueue, Queue* printerQueue);

void sendToIO(Process process, Queue* diskQueue, Queue* tapeQueue, Queue* printerQueue);

void setTurnaround(Process* process, int turnaround, Process* processes);

#endif // SCHEDULER_H
