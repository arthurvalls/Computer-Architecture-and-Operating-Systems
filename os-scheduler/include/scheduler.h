#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "queue.h"

void roundRobinScheduler(Queue* highPriorityQueue,
                         Queue* lowPriorityQueue,
                         Queue* diskQueue,
                         Queue* tapeQueue,
                         Queue* printerQueue);

void printProcessesInfo(Process* processes);


void checkNewProcesses(Process* processes, int currentTime, Queue* queue);

void formattedPrintQueue(const char* queueName, Queue* queue);

void printTurnaroundTime(Process* processes);

#endif // SCHEDULER_H
