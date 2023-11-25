#ifndef PROCESS_H
#define PROCESS_H


#define DISK_TIME 3
#define TAPE_TIME 3
#define PRINTER_TIME 3


#define MAX_BURST_TIME 7
#define MAX_ARRIVAL_TIME 4


typedef enum {
    DISK_IO,
    TAPE_IO,
    PRINTER_IO,
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
    int turnaround_time;

    int io_duration;
    int remaining_io_duration;

    int remaining_quantum;
    int remaining_burst_time; // To keep track of remaining burst time during round-robin

    IOType io_type;
    ProcessStatus status;
} Process;


Process* newProcess(int pid);
Process* initializeProcesses(int maxProcesses);
void executeProcess(Process* process, int quantum);
int isProcessedFinished(Process* process, int current_time);

int isQuantumComplete(Process* process, int quantum);

const char* getIOName(IOType ioType);
IOType getIOType();
int getIOTime(IOType ioType);
const char* getStatus(ProcessStatus processStatus);
void setTurnaround(Process* process,int startTime, int endTime);


#endif // PROCESS_H
