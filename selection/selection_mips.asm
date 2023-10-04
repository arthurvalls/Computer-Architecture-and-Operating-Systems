.data
array:     .word   5, 2, 9, 3, 8, 4    # Seu array de inteiros
n:         .word   6                  # Número de elementos no array

.text
.globl main

main:
    # Carregar o endereço do array e do número de elementos em registradores
    la $a0, array
    lw $t1, n

outer_loop:
    # Inicializar o mínimo como o índice atual do loop externo
    move $t2, $t3         # $t2: Índice mínimo, $t3: Índice atual

inner_loop:
    # Carregar o valor mínimo atual
    lw $t4, 0($a0)       # $t4: valor mínimo atual
    # Comparar com o valor mínimo anterior
    lw $t5, 0($a0)       # $t5: valor atual

    # Comparar $t5 < $t4 (valor atual < valor mínimo)
    blt $t5, $t4, update_min

    # Se não for menor, continue o loop interno
    j continue_inner_loop

update_min:
    move $t4, $t5         # Atualizar o valor mínimo
    move $t2, $t3         # Atualizar o índice mínimo

continue_inner_loop:
    addi $a0, $a0, 4     # Avançar para o próximo elemento na matriz
    addi $t3, $t3, 1     # Avançar o índice atual
    bne $t3, $t1, inner_loop  # Continue o loop interno até o final da matriz

    # Trocar os elementos na posição $t2 e $t3
    la $a0, array
    lw $t5, 0($a0)      # $t5: elemento em $t2
    lw $t6, 0($a0)      # $t6: elemento em $t3

    # Trocar os elementos
    sw $t6, 0($a0)      # Coloque o valor mínimo em $t2
    la $a0, array
    addi $a0, $a0, ($t2)  # Avance para a posição $t2
    sw $t5, 0($a0)      # Coloque o valor atual em $t3

    addi $t1, $t1, -1    # Decrementar o número de elementos

    # Verificar se há mais elementos para ordenar
    bnez $t1, outer_loop

    # Fim do programa
    li $v0, 10
    syscall
