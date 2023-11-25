#include "process.c"
#include "queue.c"
#include "scheduler.c"

#include "stdlib.h"
#include "time.h"


int main()
{
    srand(time(NULL));

    // cria todos os processos
    Process* processes = initializeProcesses(MAX_PROCESSES);

    // inicaliza todas as filas
    Queue highPriorityQueue, lowPriorityQueue, diskQueue, tapeQueue, printerQueue;

    initializeQueue(&highPriorityQueue);
    initializeQueue(&lowPriorityQueue);
    initializeQueue(&diskQueue);
    initializeQueue(&tapeQueue);
    initializeQueue(&printerQueue);

    // começa o escalonador
    roundRobinScheduler(processes,
                        &highPriorityQueue,
                        &lowPriorityQueue,
                        &diskQueue,
                        &tapeQueue,
                        &printerQueue);


    // libera a memoria de todas as filas
    freeQueue(&highPriorityQueue);
    freeQueue(&lowPriorityQueue);
    freeQueue(&diskQueue);
    freeQueue(&tapeQueue);
    freeQueue(&printerQueue);

    return 0;
}
