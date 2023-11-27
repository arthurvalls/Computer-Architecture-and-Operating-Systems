#include "../include/process.h"
#include <stdio.h>
#include <stdlib.h>


#define MAX_BURST_TIME 7
#define MAX_ARRIVAL_TIME 4


Process* newProcess(int pid)
{
    Process* process = (Process*)malloc(sizeof(Process));

    // process->ppid = getppid();
    // process->priority = rand() % 5 + 1; // Random priority between 1 and 5

    process->pid = pid;
    process->burst_time = rand() % (MAX_BURST_TIME - 1) + 2; // Random burst time between 2 and 7
    process->arrival_time = rand() % (MAX_ARRIVAL_TIME + 1); // Random arrival time between 0 and 4

    process->num_io_operations = rand() % 2 + 1;
    process->current_io_operation = 0;
    process->io_operations = (IOOperation*)malloc(process->num_io_operations * sizeof(IOOperation));

    for (int i = 0; i < process->num_io_operations; ++i) {
        process->io_operations[i].io_type = getIOType();
        process->io_operations[i].io_duration = getIOTime(process->io_operations[i].io_type);
        process->io_operations[i].start_time = rand() % (process->burst_time - 1) + 1; // Random start time within burst time

        process->io_operations[i].remaining_duration = process->io_operations[i].io_duration;
    }
    qsort(process->io_operations, process->num_io_operations, sizeof(IOOperation), compareIOOperations);


    process->remaining_burst_time = process->burst_time;

    process->remaining_quantum = 0;
    process->current_burst_time = 0;
    //process->io_type = getIOType();
    //process->io_duration = getIOTime(process->io_type);
    //process->remaining_io_duration = process->io_duration;
    process->status = READY;
    return process;
}

Process* initializeProcesses(int maxProcesses)
{
    Process* processes = (Process*)malloc(maxProcesses * sizeof(Process));

    for (int i = 0; i < maxProcesses; i++)
    {
        processes[i] = *newProcess(i);
    }

    return processes;
}

void executeProcess(Process* process)
{
    printf("P%d executou por 1 u.t.\n", process->pid);
    process->remaining_burst_time -= 1;
    process->current_burst_time += 1;
    process->remaining_quantum += 1;
    process->status = RUNNING;
}

void executeIO(Process* process)
{
    if (process->status == RUNNING)
    {
        process->status = IO;
    }
    else
    {
        process->io_operations[process->current_io_operation].remaining_duration -= 1;
        printf("P%d executou 1 u.t. do seu I/O de %s, faltam %d u.t.\n",
               process->pid,
               getIOName(process->io_operations[process->current_io_operation].io_type),
               process->io_operations[process->current_io_operation].remaining_duration);
    }
}

int isIoFinished(Process* process)
{
    if (process->io_operations[process->current_io_operation].remaining_duration == 0)
    {
        printf("P%d finalizou seu I/O de %s,", process->pid,
               getIOName(process->io_operations[process->current_io_operation].io_type));
        process->remaining_quantum = 0;
        process->current_io_operation++;
        return 1;
    }
    return 0;
}


int compareIOOperations(const void* a, const void* b)
{
    return ((IOOperation*)a)->start_time - ((IOOperation*)b)->start_time;
}

int isProcessedFinished(Process* process)
{
    if (process->remaining_burst_time == 0)
    {
        printf("P%d finalizou.\n", process->pid);
        return 1;
    }
    return 0;
}



int isIoTime(Process* process)
{
    if (process->current_burst_time == process->io_operations[process->current_io_operation].start_time)
        return 1;
    else
        return 0;
}

IOType getIOType()
{
    return rand() % 3;
}

int getIOTime(IOType ioType)
{
    switch(ioType)
    {
        case(DISK_IO):
            return DISK_TIME;
        case(TAPE_IO):
            return TAPE_TIME;
        case(PRINTER_IO):
            return PRINTER_TIME;
        default:
            return 0;
    }
}


const char* getIOName(IOType ioType)
{
    switch (ioType)
    {
        case DISK_IO:
            return "Disco";
        case TAPE_IO:
            return "Fita";
        case PRINTER_IO:
            return "Impressão";
        default:
            return "Unknown IO Type";
    }
}

int isQuantumComplete(Process* process, int quantum)
{
    if (process->remaining_quantum == quantum)
    {
        process->remaining_quantum = 0;
        return 1;
    }
    return 0;
}

const char* getStatus(ProcessStatus processStatus)
{
    switch (processStatus)
    {
        case READY:
            return "READY";
        case RUNNING:
            return "RUNNING";
        case IO:
            return "IO";
        case FINISHED:
            return "FINISHED";
        default:
            return "Unknown Status Type";
    }
}





int getTurnaround(Process* process, int endtime)
{
    return endtime - process->arrival_time;
}