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
    process->burst_time = rand() % MAX_BURST_TIME + 1; // Random burst time between 1 and 7
    process->arrival_time = rand() % (MAX_ARRIVAL_TIME + 1); // Random arrival time between 0 and 4
    process->remaining_burst_time = process->burst_time;
    process->io_type = getIOType();
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

void executeProcess(Process* process, int quantum)
{
    printf("P%d está sendo executado agora.\n", process->pid);
    process->remaining_burst_time -= 1;
    process->remaining_quantum =+ 1;
    if (process->remaining_quantum == quantum)
    {
        process->remaining_quantum = 0;
    }
}

void executeIO(Process* process)
{
    IOType IOType = process->io_type;
    switch(IOType)
    {
        case DISK_IO:

    }
}

int isProcessedFinished(Process* process, int currentTime)
{
    if (process->remaining_burst_time == 0)
    {
        printf("P%d finalizou.\n", process->pid);
        process->end_time = currentTime;
        printf("P%d com turnaround de %d u.t.\n", process->pid, process->end_time - process->arrival_time);
        return 1;
    }
    return 0;
}



void destroyProcess(Process* process)
{
    free(process);
}

int getIOType()
{
    return rand() % 3;
}


const char* getIOName(IOType ioType)
{
    switch (ioType)
    {
        case DISK_IO:
            return "Disk";
        case TAPE_IO:
            return "Tape";
        case PRINTER_IO:
            return "Printer";
        default:
            return "Unknown IO Type";
    }
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