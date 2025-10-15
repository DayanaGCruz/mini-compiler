.data

.text
.globl main

fn_add:
    addi $sp, $sp, -404
    sw $ra, 400($sp)
    sw $a0, 0($sp)
    sw $a1, 4($sp)

    # Declared sum at offset 8
    lw $t0, 0($sp)
    lw $t1, 4($sp)
    add $t0, $t0, $t1
    sw $t0, 8($sp)
    lw $t0, 8($sp)
    move $v0, $t0
    j __return_fn_add
__return_fn_add:
    lw $ra, 400($sp)
    addi $sp, $sp, 404
    jr $ra

fn_echoChar:
    addi $sp, $sp, -404
    sw $ra, 400($sp)
    sb $a0, 0($sp)

    lb $t0, 0($sp)
    move $v0, $t0
    j __return_fn_echoChar
__return_fn_echoChar:
    lw $ra, 400($sp)
    addi $sp, $sp, 404
    jr $ra

main:
    addi $sp, $sp, -400
    # Declared total at offset 0
    # Declared ch at offset 4
    li $t0, 7
    move $a0, $t0
    li $t0, 5
    move $a1, $t0
    jal fn_add
    move $t0, $v0
    sw $t0, 0($sp)
    lw $t0, 0($sp)
    # Print integer
    move $a0, $t0
    li $v0, 1
    syscall
    # Print newline
    li $v0, 11
    li $a0, 10
    syscall
    li $t0, 122
    move $a0, $t0
    jal fn_echoChar
    move $t0, $v0
    # Print integer
    move $a0, $t0
    li $v0, 1
    syscall
    # Print newline
    li $v0, 11
    li $a0, 10
    syscall
__return_main:
    addi $sp, $sp, 400
    li $v0, 10
    syscall

