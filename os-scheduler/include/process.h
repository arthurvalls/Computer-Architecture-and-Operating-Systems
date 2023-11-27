#ifndef PROCESS_H
#define PROCESS_H


#define DISK_TIME 3
#define TAPE_TIME 4
#define PRINTER_TIME 5





typedef enum {
    DISK_IO,
    TAPE_IO,
    PRINTER_IO,
} IOType;


typedef struct {
    IOType io_type;
    int io_duration;
    int start_time;
    int remaining_duration;
} IOOperation;


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
    int turnaround_time;

    int io_duration;
    int remaining_io_duration;
    int io_start;
    int remaining_quantum;
    int remaining_burst_time; // To keep track of remaining burst time during round-robin
    int current_burst_time;


    IOOperation* io_operations;
    int num_io_operations;
    int current_io_operation;
    IOType io_type;
    ProcessStatus status;
} Process;


Process* newProcess(int pid);

Process* initializeProcesses(int maxProcesses);

void executeProcess(Process* process);

int isProcessedFinished(Process* process);

int isIoFinished(Process* process);

int isIoTime(Process* process);

int isQuantumComplete(Process* process, int quantum);

void executeIO(Process* process);

const char* getIOName(IOType ioType);

IOType getIOType();

int getIOTime(IOType ioType);

const char* getStatus(ProcessStatus processStatus);

int compareIOOperations(const void* a, const void* b);

#endif // PROCESS_H
