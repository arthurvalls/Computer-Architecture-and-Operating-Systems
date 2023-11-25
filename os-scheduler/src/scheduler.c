#include "../include/scheduler.h"
#include "../include/process.h"
#include "../include/queue.h"

#include <stdio.h>
#include <stdlib.h>


// Função principal do escalonador Round Robin com Feedback
void roundRobinScheduler(Queue* highPriorityQueue, Queue* lowPriorityQueue, Queue* diskQueue,
                         Queue* tapeQueue, Queue* printerQueue,
                         int quantum,
                         int maxProcesses)
{

    // cria todos os processos e imprime na tela suas infos
    Process* processes = initializeProcesses(maxProcesses);
    printProcessesInfo(processes, maxProcesses);


    int currentTime = 0;
    int finishedProcesses = 0;


    while (finishedProcesses < maxProcesses)
    {
        printf("=========== INSTANTE %d ===========\n", currentTime);

        checkNewProcesses(processes, maxProcesses, currentTime, highPriorityQueue);

        if (!isQueueEmpty(highPriorityQueue))
        {
            Process currentProcess = queuePop(highPriorityQueue);
            executeProcess(&currentProcess, quantum);

            if (isProcessedFinished(&currentProcess, currentTime))
                finishedProcesses++;
            else
            {
                printf("P%d sofreu preempção, voltou pro fim da fila.\n", currentProcess.pid);
                queueInsert(highPriorityQueue, currentProcess);
            }
        }
        printQueue(highPriorityQueue);
        currentTime++;
    }

    printf("Escalonamento finalizado com sucesso.\n");

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


void checkNewProcesses(Process* processes, int maxProcesses, int currentTime,  Queue* queue)
{
    for (int i = 0; i < maxProcesses; i++)
        if(processes[i].arrival_time == currentTime)
        {
            queueInsert(queue, processes[i]);
            printf("P%d entrou na fila.\n", processes[i].pid);
        }
}