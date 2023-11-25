#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "queue.h"

void roundRobinScheduler(Queue* highPriorityQueue,
                         Queue* lowPriorityQueue,
                         Queue* diskQueue,
                         Queue* tapeQueue,
                         Queue* printerQueue,
                         int quantum,
                         int maxProcesses);

void printProcessesInfo(Process* processes, int maxProcesses);


void checkNewProcesses(Process* processes, int maxProcesses, int currentTime, Queue* queue);

#endif // SCHEDULER_H
