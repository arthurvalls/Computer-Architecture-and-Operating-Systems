#include "../include/scheduler.h"
#include "../include/process.h"
#include "../include/queue.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define QUANTUM 2
#define MAX_PROCESSES 5


// Função principal do escalonador Round Robin com Feedback
void roundRobinScheduler(Process* processes,
                         Queue* highPriorityQueue,
                         Queue* lowPriorityQueue,
                         Queue* diskQueue,
                         Queue* tapeQueue,
                         Queue* printerQueue)
{
    // imprime na tela info dos processos
    printProcessesInfo(processes);


    int currentTime = 0;
    int finishedProcesses = 0;


    while (finishedProcesses < MAX_PROCESSES)
    {
        printf("\n=========== INSTANTE %d ===========\n\n", currentTime);


        checkNewProcesses(processes, currentTime, highPriorityQueue);

        if (!isQueueEmpty(highPriorityQueue))
        {
            Process currentProcess = queuePop(highPriorityQueue);
            executeProcess(&currentProcess, QUANTUM);

            if (isProcessedFinished(&currentProcess, currentTime))
            {
                finishedProcesses++;
            }
            else if (isQuantumComplete(&currentProcess, QUANTUM))
            {
                printf("P%d sofreu preempção, vai pra fila de baixa prioridade.\n",
                       currentProcess.pid);
                queueInsert(lowPriorityQueue, currentProcess);
            }
            else
            {
                queueInsertFirst(highPriorityQueue, currentProcess);
            }
        }
        else if (!isQueueEmpty(lowPriorityQueue))
        {
            Process currentProcess = queuePop(lowPriorityQueue);
            executeProcess(&currentProcess, QUANTUM);

            if (isProcessedFinished(&currentProcess, currentTime))
            {
                finishedProcesses++;
            }
            else if (isQuantumComplete(&currentProcess, QUANTUM))
            {
                printf("P%d sofreu preempção, vai pro final da fila de baixa prioridade.\n",
                       currentProcess.pid);
                queueInsert(lowPriorityQueue, currentProcess);
            }
            else
            {
                queueInsertFirst(lowPriorityQueue, currentProcess);
            }
        }
        if (isQueueEmpty(highPriorityQueue) && isQueueEmpty(lowPriorityQueue))
            printf("\nFilas vazias, CPU está ociosa.\n");
        else
        {
            printAllQueues(highPriorityQueue,
                           lowPriorityQueue,
                           diskQueue,
                           tapeQueue,
                           printerQueue);
        }
        currentTime++;
    }

    printf("\nNão há mais processos, escalonamento finalizado com sucesso.\n");


    printf("\n=========== FINAL ===========\n");
    printf("Tempos de Turnaround: \n\n");
    printTurnaroundTime(processes);

    // desaloca o bloco de memoria dos processos
    free(processes);

}


void printProcessesInfo(Process* processes)
{
    if (!(processes == NULL))
    {
        printf("%-10s%-15s%-15s%-20s%-10s\n", "PID", "Burst Time", "Arrival Time", "IO Type", "Status");
        printf("---------------------------------------------------------------\n");

        for (int i = 0; i < MAX_PROCESSES; i++)
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


void checkNewProcesses(Process* processes, int currentTime,  Queue* queue)
{
    for (int i = 0; i < MAX_PROCESSES; i++)
        if(processes[i].arrival_time == currentTime)
        {
            queueInsert(queue, processes[i]);
            printf("P%d entrou na fila de alta prioridade.\n\n", processes[i].pid);
        }
}


void printTurnaroundTime(Process* processes)
{
    for (int i = 0; i < MAX_PROCESSES; ++i)
    {
        printf("TT (P%d): %d u.t\n", processes[i].pid, processes[i].turnaround_time);
    }
}