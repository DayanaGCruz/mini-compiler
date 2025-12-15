.data

__array_oob_msg: .asciiz "Runtime error: array index out of bounds\n"

.text
.globl main

fn_maxOf:
    addi $sp, $sp, -400
    sw $ra, 396($sp)
    sw $a0, 0($sp)
    sw $a1, 4($sp)

    lw $t0, 0($sp)
    lw $t1, 4($sp)
    slt $t2, $t1, $t0
    sw $t2, 8($sp)
    lw $t0, 8($sp)
    sltu $t1, $zero, $t0
    beq $t1, $zero, __if_end_0
    lw $t0, 0($sp)
    move $v0, $t0
    j __return_fn_maxOf
__if_end_0:
    lw $t0, 4($sp)
    move $v0, $t0
    j __return_fn_maxOf
__return_fn_maxOf:
    lw $ra, 396($sp)
    addi $sp, $sp, 400
    jr $ra

fn_accumulateTo:
    addi $sp, $sp, -400
    sw $ra, 396($sp)
    sw $a0, 0($sp)

    li $t0, 0
    sw $t0, 4($sp)
    li $t0, 1
    sw $t0, 8($sp)
__while_start_1:
    lw $t0, 4($sp)
    lw $t1, 8($sp)
    add $t0, $t0, $t1
    sw $t0, 12($sp)
    lw $t0, 12($sp)
    sw $t0, 4($sp)
    lw $t0, 8($sp)
    li $t1, 1
    add $t0, $t0, $t1
    sw $t0, 16($sp)
    lw $t0, 16($sp)
    sw $t0, 8($sp)
    lw $t0, 4($sp)
    lw $t1, 8($sp)
    add $t0, $t0, $t1
    sw $t0, 12($sp)
    lw $t0, 12($sp)
    sw $t0, 4($sp)
    lw $t0, 8($sp)
    li $t1, 1
    add $t0, $t0, $t1
    sw $t0, 16($sp)
    lw $t0, 16($sp)
    sw $t0, 8($sp)
    lw $t0, 4($sp)
    lw $t1, 8($sp)
    add $t0, $t0, $t1
    sw $t0, 12($sp)
    lw $t0, 12($sp)
    sw $t0, 4($sp)
    lw $t0, 8($sp)
    li $t1, 1
    add $t0, $t0, $t1
    sw $t0, 16($sp)
    lw $t0, 16($sp)
    sw $t0, 8($sp)
__while_end_2:
    lw $t0, 4($sp)
    move $v0, $t0
    j __return_fn_accumulateTo
__return_fn_accumulateTo:
    lw $ra, 396($sp)
    addi $sp, $sp, 400
    jr $ra

main:
    addi $sp, $sp, -400
    li $t0, 7
    move $a0, $t0
    li $t0, 4
    move $a1, $t0
    jal fn_maxOf
    move $t0, $v0
    sw $t0, 8($sp)
    lw $t0, 8($sp)
    sw $t0, 0($sp)
    li $t0, 3
    move $a0, $t0
    jal fn_accumulateTo
    move $t0, $v0
    sw $t0, 12($sp)
    lw $t0, 12($sp)
    sw $t0, 4($sp)
    lw $t0, 0($sp)
    move $a0, $t0
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    lw $t0, 4($sp)
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

