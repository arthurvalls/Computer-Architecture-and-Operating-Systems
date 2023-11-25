#ifndef PROCESS_H
#define PROCESS_H


#define DISK_TIME 3
#define TAPE_TIME 3
#define PRINTING_TIME 3


#define MAX_BURST_TIME 7
#define MAX_ARRIVAL_TIME 4


typedef enum {
    DISK_IO,
    TAPE_IO,
    PRINTING_IO,
} IOType;

typedef enum {
    READY,
    RUNNING,
    WAITING,
    BLOCKED,
    IO,
    FINISHED
} ProcessStatus;

typedef struct {
    int pid;
    int ppid;
    int priority;

    int arrival_time;
    int burst_time;
    int end_time;

    int io_duration;

    int remaining_quantum;
    int remaining_burst_time; // To keep track of remaining burst time during round-robin

    IOType io_type;
    ProcessStatus status;
} Process;


Process* newProcess(int pid);
Process* initializeProcesses(int maxProcesses);
void executeProcess(Process* process, int quantum);

const char* getIOName(IOType ioType);
int getIOType();
const char* getStatus(ProcessStatus processStatus);


#endif // PROCESS_H
