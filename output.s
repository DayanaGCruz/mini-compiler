.data

__array_oob_msg: .asciiz "Runtime error: array index out of bounds\n"

.text
.globl main

main:
    addi $sp, $sp, -400
    li $t0, 10
    sw $t0, 0($sp)
    li $t0, 5
    sw $t0, 4($sp)
    li $t0, 20
    sw $t0, 8($sp)
    li $t0, 10
    sw $t0, 12($sp)
    li $t0, 10
    sb $t0, 16($sp)
    li $t0, 114
    sb $t0, 17($sp)
    li $t0, 61
    sb $t0, 18($sp)
    li $t0, 97
    sb $t0, 19($sp)
__while_start_0:
    lw $t0, 0($sp)
    lw $t1, 4($sp)
    slt $t2, $t1, $t0
    sw $t2, 20($sp)
    lw $t0, 8($sp)
    lw $t1, 12($sp)
    slt $t2, $t1, $t0
    sw $t2, 24($sp)
    lw $t0, 20($sp)
    lw $t1, 24($sp)
    mul $t0, $t0, $t1
    sw $t0, 28($sp)
    lw $t0, 28($sp)
    sltu $t1, $zero, $t0
    beq $t1, $zero, __while_end_1
    lb $t0, 17($sp)
    li $v0, 11
    move $a0, $t0
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    lb $t0, 18($sp)
    li $v0, 11
    move $a0, $t0
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    lw $t0, 0($sp)
    lw $t1, 4($sp)
    slt $t2, $t1, $t0
    sw $t2, 32($sp)
    lw $t0, 8($sp)
    lw $t1, 12($sp)
    slt $t2, $t1, $t0
    sw $t2, 36($sp)
    lw $t0, 32($sp)
    lw $t1, 36($sp)
    mul $t0, $t0, $t1
    sw $t0, 40($sp)
    lw $t0, 40($sp)
    move $a0, $t0
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    lb $t0, 16($sp)
    li $v0, 11
    move $a0, $t0
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    lb $t0, 19($sp)
    li $v0, 11
    move $a0, $t0
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    lb $t0, 18($sp)
    li $v0, 11
    move $a0, $t0
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    lw $t0, 0($sp)
    move $a0, $t0
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    lw $t0, 0($sp)
    li $t1, 1
    sub $t0, $t0, $t1
    sw $t0, 44($sp)
    lw $t0, 44($sp)
    sw $t0, 0($sp)
    j __while_start_0
__while_end_1:
    li $t0, 0
    move $v0, $t0
    j __return_main
__return_main:
    addi $sp, $sp, 400
    li $v0, 10
    syscall

