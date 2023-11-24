.data
array: .word 5, 2, 6, 1, 3, 8, 7, 9, 4, 0         # O array de números a serem ordenados
array_size: .word 10                            # tamanho do array

.text
main:
    la $s7, array      # Carrega o endereço base do array em $s7
    li $s0, 0          # Inicializa $s0 com 0 (índice do loop externo)
    lw $s6, array_size          # Inicializa $s6 com 9 (número de elementos no array)
    li $s1, 0          # Inicializa $s1 com 0 (índice do loop interno)

loop:
    sll $t7, $s1, 2    # Calcula o deslocamento para o índice do loop interno
    add $t7, $s7, $t7  # Adiciona o deslocamento ao endereço base para acessar os elementos do array
    lw $t0, 0($t7)     # Carrega o primeiro elemento no deslocamento $s1 em $t0
    lw $t1, 4($t7)     # Carrega o segundo elemento no deslocamento $s1+4 em $t1
    slt $t2, $t1, $t0  # Define $t2 como 1 se $t1 < $t0, senão 0
    beqz $t2, increment  # Se $t1 >= $t0, vá para increment
    sw $t1, 0($t7)     # Armazena $t1 no primeiro elemento
    sw $t0, 4($t7)     # Armazena $t0 no segundo elemento

increment:
    addi $s1, $s1, 1  # Incrementa o índice do loop interno
    sub $s5, $s6, $s0  # Calcula o número de iterações necessárias para o loop interno
    beq $s1, $s5, next_iteration  # Se terminou, vá para next_iteration
    j loop

next_iteration:
    addi $s0, $s0, 1  # Incrementa o índice do loop externo
    li $s1, 0          # Reinicializa o índice do loop interno para 0
    beq $s0, $s6, final  # Se terminou, vá para final
    j loop

final:
    li $v0, 10         # Carrega 10 em $v0 (código da chamada do sistema para sair do programa)
    syscall            # Encerra o programa
