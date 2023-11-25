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

    // Gera um io_start entre [arrival_time, burst_time]
    process->io_start = rand() % (process->burst_time - process->arrival_time) + process->arrival_time;

    if (process->io_start >= process->burst_time) {
        process->io_start = process->burst_time - 1;
    }

    process->remaining_quantum = 0;
    process->current_burst_time = 0;
    process->io_type = getIOType();
    process->io_duration = getIOTime(process->io_type);
    process->remaining_io_duration = process->io_duration;
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
        process->status = IO;
    else
    {
        process->remaining_io_duration -= 1;
        printf("P%d executou seu I/O por 1 u.t., faltam %d u.t.\n",
               process->pid, process->remaining_io_duration);
    }
}


void setTurnaround(Process* process,int startTime, int endTime)
{
    process->turnaround_time = endTime - startTime;
}


int isProcessedFinished(Process* process, int currentTime)
{
    if (process->remaining_burst_time == 0)
    {
        printf("P%d finalizou.\n", process->pid);
        process->end_time = currentTime;
        setTurnaround(process, process->arrival_time, process->end_time);
        // printf("P%d com turnaround de %d u.t.\n", process->turnaround_time);
        return 1;
    }
    return 0;
}

int isIoFinished(Process* process)
{
    if (process->remaining_io_duration == 0)
    {
        printf("P%d finalizou seu IO.\n", process->pid);
        return 1;
    }
    return 0;
}

int isIoTime(Process* process)
{
    if (process->current_burst_time == process->io_start)
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
            return "Disk";
        case TAPE_IO:
            return "Tape";
        case PRINTER_IO:
            return "Printer";
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
