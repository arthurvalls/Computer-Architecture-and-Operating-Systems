// scheduler.c
#include "../include/scheduler.h"
#include "../include/process.h"
#include "../include/queue.h"
#include <stdio.h>
#include <stdlib.h>

// Função principal do escalonador Round Robin com Feedback
void roundRobinScheduler(Queue* highPriorityQueue, Queue* lowPriorityQueue, Queue* ioQueue, int quantum, int maxProcesses) {

    Process* processes = initializeProcesses(maxProcesses);
    printProcessesInfo(processes, maxProcesses);
}


void printProcessesInfo(Process* processes, int maxProcesses)
{
    if (!(processes == NULL))
    {
        printf("%-10s%-15s%-15s%-20s%-10s\n", "PID", "Burst Time", "Arrival Time", "IO Type", "Status");
        printf("---------------------------------------------------------------\n");

        for (int i = 0; i < maxProcesses; i++)
        {
            printf("%-10d%-15d%-15d%-20s%-10s\n",
                   processes[i].pid,
                   processes[i].burst_time,
                   processes[i].arrival_time,
                   getIOName(processes[i].io_type),
                   getStatus(processes[i].status));
        }
    }
    else
    {
        printf("Processes array is empty\n");
    }
}
