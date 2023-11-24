// process.c
#include "../include/process.h"
#include <stdio.h>
#include <stdlib.h>

void executeProcess(Process* process) {
    printf("Executing process %d\n", process->pid);
    process->burst_time -= rand() % 10 + 1; // Simulação de execução com tempo aleatório
}

void performIO(Process* process) {
    printf("Process %d performing I/O of type %d for %d units\n", process->pid, process->io_type, process->io_duration);
    process->priority = (process->io_type == 1) ? 0 : 1;
}
