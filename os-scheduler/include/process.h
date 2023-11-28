#ifndef PROCESS_H
#define PROCESS_H


#define DISK_TIME 2
#define TAPE_TIME 3
#define PRINTER_TIME 4

// Definição do tipo de E/S
typedef enum {
    DISK_IO,
    TAPE_IO,
    PRINTER_IO,
} IOType;

// Definição dos atributos de uma operacao de E/S
typedef struct {
    IOType io_type;
    int io_duration;
    int start_time;
    int remaining_duration;
} IOOperation;


// Possíveis status que o processo assume neste S.O.
typedef enum {
    READY,
    RUNNING,
    IO
} ProcessStatus;

// Estrutura que define atributos de um processo.
typedef struct {

    int pid;

    // Dados de tempo
    int arrival_time;       // Instante de chegada
    int burst_time;         // Tempo de CPU
    int end_time;           // Intante de encerramento
    int turnaround_time;    // Tempo de execução

    // Atributos temporários.
    int remaining_quantum;
    int remaining_burst_time;
    int current_burst_time;

    // Atributos relacionados as operacoes de E/S deste processo.
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
