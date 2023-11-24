// process.h
#ifndef PROCESS_H
#define PROCESS_H

typedef struct {
    int pid;
    int priority;
    int burst_time;
    int io_type;
    int io_duration;
} Process;

void executeProcess(Process* process);
void performIO(Process* process);

#endif // PROCESS_H
