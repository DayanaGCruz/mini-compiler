.data

__array_oob_msg: .asciiz "Runtime error: array index out of bounds\n"

.text
.globl main

fn_duplicate:
    addi $sp, $sp, -400
    sw $ra, 396($sp)
    sw $a0, 0($sp)

    lw $t0, 0($sp)
    li $t1, 10
    add $t0, $t0, $t1
    sw $t0, 8($sp)
    lw $t0, 8($sp)
    sw $t0, 4($sp)
    lw $t0, 4($sp)
    move $v0, $t0
    j __return_fn_duplicate
__return_fn_duplicate:
    lw $ra, 396($sp)
    addi $sp, $sp, 400
    jr $ra

fn_duplicate_helper:
    addi $sp, $sp, -400
    sw $ra, 396($sp)
    sw $a0, 0($sp)

    lw $t0, 0($sp)
    li $t1, 2
    mul $t0, $t0, $t1
    sw $t0, 8($sp)
    lw $t0, 8($sp)
    sw $t0, 4($sp)
    lw $t0, 4($sp)
    move $v0, $t0
    j __return_fn_duplicate_helper
__return_fn_duplicate_helper:
    lw $ra, 396($sp)
    addi $sp, $sp, 400
    jr $ra

main:
    addi $sp, $sp, -400
    li $t0, 5
    move $a0, $t0
    jal fn_duplicate
    move $t0, $v0
    sw $t0, 4($sp)
    lw $t0, 4($sp)
    move $a0, $t0
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    li $t0, 5
    move $a0, $t0
    jal fn_duplicate_helper
    move $t0, $v0
    sw $t0, 8($sp)
    lw $t0, 8($sp)
    move $a0, $t0
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
__return_main:
    addi $sp, $sp, 400
    li $v0, 10
    syscall

