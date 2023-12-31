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
    // imprime na tela info dos process
    printProcessesInfo(processes);

    int currentTime = 0;
    int finishedProcesses = 0;


    while (finishedProcesses < MAX_PROCESSES)
    {
        printf("\n=========== INSTANTE %d ===========\n\n", currentTime);
        //sleep(1);

        checkNewProcesses(processes, currentTime, highPriorityQueue);

        if (!isQueueEmpty(highPriorityQueue))
        {
            Process currentProcess = queuePop(highPriorityQueue);
            executeProcess(&currentProcess);

            if (isProcessedFinished(&currentProcess))
            {
                setTurnaround(&currentProcess, currentTime, processes);
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

            if (isProcessedFinished(&currentProcess))
            {
                setTurnaround(&currentProcess, currentTime, processes);
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
            {
                printf(" vai pra fila de baixa prioridade.\n");
                queueInsert(lowPriorityQueue, currentIO);
            }
            else
                queueInsertFirst(diskQueue, currentIO);
        }
        if (!isQueueEmpty(tapeQueue))
        {
            Process currentIO = queuePop(tapeQueue);
            executeIO(&currentIO);
            if (isIoFinished(&currentIO))
            {
                printf(" vai pra fila de alta prioridade.\n");
                queueInsert(highPriorityQueue, currentIO);
            }
            else
                queueInsertFirst(tapeQueue, currentIO);
        }
        if (!isQueueEmpty(printerQueue))
        {
            Process currentIO = queuePop(printerQueue);
            executeIO(&currentIO);
            if (isIoFinished(&currentIO))
            {
                printf(" vai pra fila de alta prioridade.\n");
                queueInsert(highPriorityQueue, currentIO);
            }
            else
                queueInsertFirst(printerQueue, currentIO);
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

    // desaloca o bloco de memoria dos process
    free(processes);
}


void printProcessesInfo(Process* process)
{
    if (process != NULL)
    {
        printf("================= Processos ================= \n\n");

        printf("PID\tTempo de serviço\tTempo de chegada\tI/O (Tempo chegada)\n");

        for (int i = 0; i < MAX_PROCESSES; i++)
        {
            printf(" %d\t\t%d\t\t\t%d\t\t", process[i].pid, process[i].burst_time, process[i].arrival_time);

            if (process[i].num_io_operations == 0)
            {
                printf("Sem I/O");
            }
            else
            {
                for (int j = 0; j < process[i].num_io_operations; j++)
                {
                    printf("%s (%d)", getIOName(process[i].io_operations[j].io_type),
                           process[i].io_operations[j].start_time);

                    if (j < process[i].num_io_operations - 1)
                        printf(", ");
                }
            }
            printf("\n");
        }
    }
    else
    {
        printf("Sem processo.\n");
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
    float averageTurnaround = 0;
    for (int i = 0; i < MAX_PROCESSES; ++i)
    {
        printf("TT (P%d): %d u.t\n", processes[i].pid, processes[i].turnaround_time);
        averageTurnaround += (float)processes[i].turnaround_time;
    }
    printf("\nTurnaround Médio: %.2f u.t.\n", averageTurnaround/MAX_PROCESSES);
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
    printf("P%d vai para a fila de %s.\n", process.pid,
           getIOName(process.io_operations[process.current_io_operation].io_type));
    switch (process.io_operations[process.current_io_operation].io_type)
    {
        case(DISK_IO):
            if (!isQueueEmpty(diskQueue))
                process.status = IO;
            queueInsert(diskQueue, process);
            break;
        case(TAPE_IO):
            if (!isQueueEmpty(tapeQueue))
                process.status = IO;
            queueInsert(tapeQueue, process);
            break;
        case(PRINTER_IO):
            if (!isQueueEmpty(printerQueue))
                process.status = IO;
            queueInsert(printerQueue, process);
            break;
    }
}

void setTurnaround(Process* process, int turnaround, Process* processes)
{
    for (int i = 0; i < MAX_PROCESSES; ++i)
    {
        if (processes[i].pid == process->pid)
        {
            processes[i].turnaround_time = turnaround - processes[i].arrival_time;
        }
    }
}