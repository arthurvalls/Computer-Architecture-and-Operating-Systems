#include "process.c"
#include "queue.c"
#include "scheduler.c"

#include "stdlib.h"
#include "time.h"

#define QUANTUM 2
#define MAX_PROCESSES 5
#define MAX_BURST_TIME 7
#define MAX_IO_TIME 4


int main()
{
    srand(time(NULL));

    Queue highPriorityQueue, lowPriorityQueue, ioQueue;
    initializeQueue(&highPriorityQueue);
    initializeQueue(&lowPriorityQueue);
    initializeQueue(&ioQueue);

    roundRobinScheduler(&highPriorityQueue,
                             &lowPriorityQueue,
                             &ioQueue,
                             QUANTUM,
                             MAX_PROCESSES);

    return 0;
}
