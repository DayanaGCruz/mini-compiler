.data

__array_oob_msg: .asciiz "Runtime error: array index out of bounds\n"

.text
.globl main

fn_sum_pair:
    addi $sp, $sp, -400
    sw $ra, 396($sp)
    sw $a0, 0($sp)
    sw $a1, 4($sp)

    lw $t0, 0($sp)
    lw $t1, 4($sp)
    add $t0, $t0, $t1
    sw $t0, 12($sp)
    lw $t0, 12($sp)
    sw $t0, 8($sp)
    lw $t0, 8($sp)
    move $v0, $t0
    j __return_fn_sum_pair
__return_fn_sum_pair:
    lw $ra, 396($sp)
    addi $sp, $sp, 400
    jr $ra

fn_diff_pair:
    addi $sp, $sp, -400
    sw $ra, 396($sp)
    sw $a0, 0($sp)
    sw $a1, 4($sp)

    lw $t0, 0($sp)
    lw $t1, 4($sp)
    sub $t0, $t0, $t1
    sw $t0, 12($sp)
    lw $t0, 12($sp)
    sw $t0, 8($sp)
    lw $t0, 8($sp)
    move $v0, $t0
    j __return_fn_diff_pair
__return_fn_diff_pair:
    lw $ra, 396($sp)
    addi $sp, $sp, 400
    jr $ra

main:
    addi $sp, $sp, -400
    li $t0, 10
    move $a0, $t0
    li $t0, 4
    move $a1, $t0
    jal fn_sum_pair
    move $t0, $v0
    sw $t0, 8($sp)
    li $t0, 10
    move $a0, $t0
    li $t0, 4
    move $a1, $t0
    jal fn_diff_pair
    move $t0, $v0
    sw $t0, 12($sp)
    lw $t0, 8($sp)
    move $a0, $t0
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    lw $t0, 12($sp)
    move $a0, $t0
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    li $t0, 0
    move $v0, $t0
    j __return_main
__return_main:
    addi $sp, $sp, 400
    li $v0, 10
    syscall

