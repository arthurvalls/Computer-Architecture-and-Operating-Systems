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
        sleep(1);

        checkNewProcesses(processes, currentTime, highPriorityQueue);

        if (!isQueueEmpty(highPriorityQueue))
        {
            Process currentProcess = queuePop(highPriorityQueue);
            executeProcess(&currentProcess);

            if (isProcessedFinished(&currentProcess, currentTime))
            {
                finishedProcesses++;
            }
            else if (isIoTime(&currentProcess))
            {
                sendToIO(currentProcess, diskQueue, tapeQueue, printerQueue);
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
            executeProcess(&currentProcess);

            if (isProcessedFinished(&currentProcess, currentTime))
            {
                finishedProcesses++;
            }
            else if (isIoTime(&currentProcess))
            {
                sendToIO(currentProcess, diskQueue, tapeQueue, printerQueue);
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
        if (!isQueueEmpty(diskQueue))
        {
            Process currentIO = queuePop(diskQueue);
            executeIO(&currentIO);
            if (isIoFinished(&currentIO))
                queueInsert(lowPriorityQueue, currentIO);
            else
                queueInsert(diskQueue, currentIO);
        }
        if (!isQueueEmpty(tapeQueue))
        {
            Process currentIO = queuePop(tapeQueue);
            executeIO(&currentIO);
            if (isIoFinished(&currentIO))
                queueInsert(highPriorityQueue, currentIO);
            else
                queueInsert(tapeQueue, currentIO);
        }
        if (!isQueueEmpty(printerQueue))
        {
            Process currentIO = queuePop(printerQueue);
            executeIO(&currentIO);
            if (isIoFinished(&currentIO))
                queueInsert(highPriorityQueue, currentIO);
            else
                queueInsert(printerQueue, currentIO);
        }
        if (!isCPUActive(highPriorityQueue, lowPriorityQueue) &&
            !checkIfHasIo(diskQueue, tapeQueue, printerQueue))
        {
            printf("\nNenhuma fila com processos, CPU ociosa.\n");
        }
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
        printf("%-10s%-15s%-15s%-20s%-20s%-10s\n", "PID", "Burst Time", "Arrival Time", "IO Type", "IO Start", "Status");
        printf("---------------------------------------------------------------\n");

        for (int i = 0; i < MAX_PROCESSES; i++)
        {
            printf("%-10d%-15d%-15d%-20s%-15d%-10s\n",
                   processes[i].pid,
                   processes[i].burst_time,
                   processes[i].arrival_time,
                   getIOName(processes[i].io_type),
                   processes[i].io_start,
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

int isCPUActive(Queue* highPriorityQueue, Queue* lowPriorityQueue)
{
    if (!isQueueEmpty(highPriorityQueue) || !isQueueEmpty(lowPriorityQueue))
        return 1;
    else
        return 0;
}

int checkIfHasIo(Queue* diskQueue, Queue* tapeQueue, Queue* printerQueue)
{
    if (!isQueueEmpty(diskQueue) || !isQueueEmpty(tapeQueue) || !isQueueEmpty(printerQueue))
        return 1;
    else
        return 0;
}

void sendToIO(Process process, Queue* diskQueue, Queue* tapeQueue, Queue* printerQueue)
{
    switch (process.io_type)
    {
        case(DISK_IO):
            printf("P%d vai para a fila de disco\n", process.pid);
            queueInsert(diskQueue, process);
            break;
        case(TAPE_IO):
            printf("P%d vai para a fila de fita\n", process.pid);
            queueInsert(tapeQueue, process);
            break;
        case(PRINTER_IO):
            printf("P%d vai para a fila de impressora\n", process.pid);
            queueInsert(printerQueue, process);
            break;
    }
}