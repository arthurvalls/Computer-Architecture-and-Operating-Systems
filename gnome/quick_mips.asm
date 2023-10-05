.data                   # Seção de dados
array: .word 2, 3, 1    # Define os valores do array

.text                   # Seção de texto
.globl main             # Ponto de entrada do programa

main:
    li $t1, 3            # Carrega o tamanho do array em $t1
    la $t0, array        # Carrega o endereço do array em $t0
    
    jal gnome_sort       # Chama a função gnome_sort
    li $t2, 0

end:
    ori $v0, $0, 10      # Código de chamada do sistema para sair
    syscall

gnome_sort:
    addiu $sp, $sp, -4    # Ajusta o ponteiro de pilha para alocar espaço para variáveis locais
    sw $ra, 0($sp)        # Salva o endereço de retorno na pilha
    
    sll $t1, $t1, 2       # Calcula o tamanho total do array em bytes
    
    li $v0, 0             # Inicializa a variável de loop externo

loop:
    slt $t3, $v0, $t1     # $t3 = 1 se loop_counter < tamanho_total, senão $t3 = 0
    beq $t3, $zero, end_while  # Sai do loop externo se loop_counter >= tamanho_total
    
    bne $v0, $zero, compare   # Salta para a comparação se loop_counter != 0
    addiu $v0, $v0, 4    # Incrementa loop_counter em 4 bytes

compare:
    addu $t2, $t0, $v0    # Calcula o endereço da posição atual do array
    
    lw $t4, -4($t2)       # Carrega o valor atual do array
    lw $t5, 0($t2)        # Carrega o próximo valor do array
    
    blt $t5, $t4, swap    # Salta para a troca se o valor atual for maior que o próximo valor
    
    addiu $v0, $v0, 4    # Incrementa loop_counter em 4 bytes
    j loop                # Volta para o início do loop

swap:
    sw $t4, 0($t2)        # Troca os valores no array
    sw $t5, -4($t2)
    
    addiu $v0, $v0, -4    # Decrementa loop_counter em 4 bytes
    j loop                # Volta para o início do loop

end_while:
    srl $t1, $t1, 2       # Divide o tamanho total por 4 para obter o número de elementos
    
    lw $ra, 0($sp)        # Restaura o endereço de retorno da pilha
    
    addi $sp, $sp, 4      # Restaura o ponteiro de pilha
    jr $ra                # Retorna para o endereço de retorno
