.data                   # Seção de dados
array: .word 2, 3, 1    # Define os valores do array
array_size: .word 3     # Define o tamanho do array

.text                   # Seção de texto
.globl main             # Ponto de entrada do programa

main:
    li $a0, array_size  # Carrega o tamanho do array em $a0
    la $a1, array       # Carrega o endereço do array em $a1
    
    jal insertion_sort   # Chama a função insertion_sort
    
end:
    li $v0, 10           # Código de chamada do sistema para sair
    syscall

insertion_sort:
    addi $sp, $sp, -40   # Ajusta o ponteiro de pilha para alocar espaço para variáveis locais
    
    sw $ra, 36($sp)      # Salva o endereço de retorno na pilha
    sw $a0, 32($sp)      # Salva $a0 (tamanho do array) na pilha
    sw $a1, 28($sp)      # Salva $a1 (endereço do array) na pilha

    sw $t0, 24($sp)      # Salva registradores temporários na pilha
    sw $t1, 20($sp)
    sw $t2, 16($sp)
    sw $t3, 12($sp)
    sw $t4, 8($sp)
    sw $t5, 4($sp)
    sw $t6, 0($sp)

    move $t0, $zero      # Inicializa o índice do loop externo com 0
    
for:
    add $t1, $t0, $zero  # Inicializa o índice do loop interno com o índice externo
    
while:
    slt $t2, $t1, $zero     # $t2 = 1 se $t1 < 0, senão $t2 = 0
    beq $t2, 1, end_while   # Sai do loop interno se $t1 < 0
    beq $t1, $zero, end_while # Sai do loop interno se $t1 = 0

    mul $t2, $t1, 4      # Calcula o deslocamento: índice * tamanho da palavra (4 bytes)
    add $t2, $t2, $a1    # Adiciona o deslocamento ao endereço base do array
    lw $t3, 0($t2)       # Carrega values[i] em $t3

    subi $t4, $t1, 1     # Calcula o índice anterior: $t1 - 1
    mul $t4, $t4, 4      # Calcula o deslocamento do índice anterior
    add $t4, $t4, $a1    # Adiciona o deslocamento ao endereço base do array
    lw $t5, 0($t4)       # Carrega values[i-1] em $t5

    slt $t6, $t3, $t5    # $t6 = 1 se values[i] < values[i-1], senão $t6 = 0
    beq $t6, 0, end_while # Sai do loop interno se values[i] >= values[i-1]

    sw $t5, 0($t2)       # Armazena values[i-1] em values[i]
    sw $t3, 0($t4)       # Armazena values[i] em values[i-1]

    sub $t1, $t1, 1      # Decrementa o índice interno
    j while               # Volta para o início do loop interno

end_while:
    addi $t0, $t0, 1     # Incrementa o índice externo
    slt $t2, $t0, $a0     # $t2 = 1 se índice externo < tamanho do array, senão $t2 = 0
    beq $t2, 1, for       # Volta para o início do loop externo se índice externo < tamanho do array
    
    lw $t6, 0($sp)        # Restaura os valores dos registradores salvos da pilha
    lw $t5, 4($sp)
    lw $t4, 8($sp)
    lw $t3, 12($sp)
    lw $t2, 16($sp)
    lw $t1, 20($sp)
    lw $t0, 24($sp)
    lw $a1, 28($sp)
    lw $a0, 32($sp)
    lw $ra, 36($sp)

    addi $sp, $sp, 40     # Restaura o ponteiro de pilha
    jr $ra                # Retorna para o endereço de retorno