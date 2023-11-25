#include "process.c"
#include "queue.c"
#include "scheduler.c"

#include "stdlib.h"
#include "time.h"

#define QUANTUM 2
#define MAX_PROCESSES 5

int main()
{
    srand(time(NULL));

    Queue highPriorityQueue, lowPriorityQueue, diskQueue, tapeQueue, printingQueue;
    initializeQueue(&highPriorityQueue);
    initializeQueue(&lowPriorityQueue);
    initializeQueue(&diskQueue);
    initializeQueue(&tapeQueue);
    initializeQueue(&printingQueue);

    roundRobinScheduler(&highPriorityQueue,
                             &lowPriorityQueue,
                             &diskQueue,
                             QUANTUM,
                             MAX_PROCESSES);

    return 0;
}
