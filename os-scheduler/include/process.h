#ifndef PROCESS_H
#define PROCESS_H


#define DISK_TIME 3
#define TAPE_TIME 3
#define PRINTING_TIME 3


typedef enum {
    DISK_IO,
    TAPE_IO,
    PRINTING_IO,
} IOType;

typedef enum {
    READY,
    RUNNING,
    WAITING,
    IO,
    FINISHED
} ProcessStatus;

typedef struct {
    int pid;
    int ppid;
    int priority;
    int arrival_time;
    int burst_time;
    int io_duration;
    int remaining_burst_time; // To keep track of remaining burst time during round-robin

    IOType io_type;
    ProcessStatus status;
} Process;

void executeProcess(Process* process);
void changePriority(Process* process, int priority);
int getIOType();
Process* newProcess(int pid);
Process* initializeProcesses(int maxProcesses);
const char* getIOName(IOType ioType);
const char* getStatus(ProcessStatus processStatus);
#endif // PROCESS_H
