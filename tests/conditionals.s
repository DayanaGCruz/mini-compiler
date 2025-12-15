.data

__array_oob_msg: .asciiz "Runtime error: array index out of bounds\n"

.text
.globl main

main:
    addi $sp, $sp, -400
    li $t0, 1
    sw $t0, 0($sp)
    li $t0, 0
    sw $t0, 4($sp)
    li $t0, 0
    sw $t0, 8($sp)
    lw $t0, 0($sp)
    sltu $t1, $zero, $t0
    beq $t1, $zero, __if_else_0
    lw $t0, 8($sp)
    li $t1, 1
    add $t0, $t0, $t1
    sw $t0, 12($sp)
    lw $t0, 12($sp)
    sw $t0, 8($sp)
    lw $t0, 4($sp)
    sltu $t1, $zero, $t0
    xori $t2, $t1, 1
    sw $t2, 16($sp)
    lw $t0, 8($sp)
    li $t1, 1
    xor $t3, $t0, $t1
    sltiu $t2, $t3, 1
    sw $t2, 20($sp)
    lw $t0, 16($sp)
    sltu $t1, $zero, $t0
    lw $t2, 20($sp)
    sltu $t3, $zero, $t2
    and $t4, $t1, $t3
    sltu $t4, $zero, $t4
    sw $t4, 24($sp)
    lw $t0, 24($sp)
    sltu $t1, $zero, $t0
    beq $t1, $zero, __if_else_2
    lw $t0, 8($sp)
    move $a0, $t0
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    j __if_end_3
__if_else_2:
    li $t0, 99
    move $a0, $t0
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
__if_end_3:
    j __if_end_1
__if_else_0:
    li $t0, 1000
    move $a0, $t0
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
__if_end_1:
    li $t0, 4
    sw $t0, 28($sp)
    lw $t0, 28($sp)
    li $t1, 5
    slt $t2, $t1, $t0
    sw $t2, 32($sp)
    lw $t0, 32($sp)
    sltu $t1, $zero, $t0
    beq $t1, $zero, __if_else_4
    li $t0, 200
    move $a0, $t0
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    j __if_end_5
__if_else_4:
    lw $t0, 28($sp)
    li $t1, 3
    slt $t2, $t1, $t0
    sw $t2, 36($sp)
    lw $t0, 36($sp)
    sltu $t1, $zero, $t0
    beq $t1, $zero, __if_else_6
    li $t0, 300
    move $a0, $t0
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    j __if_end_7
__if_else_6:
    li $t0, 400
    move $a0, $t0
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
__if_end_7:
__if_end_5:
    lw $t0, 0($sp)
    sltu $t1, $zero, $t0
    beq $t1, $zero, __cond_false_8
    li $t0, 7
    sw $t0, 48($sp)
    j __cond_end_9
__cond_false_8:
    li $t0, 8
    sw $t0, 48($sp)
__cond_end_9:
    lw $t0, 48($sp)
    sw $t0, 40($sp)
    lw $t0, 28($sp)
    li $t1, 0
    slt $t2, $t0, $t1
    sw $t2, 52($sp)
    lw $t0, 52($sp)
    sltu $t1, $zero, $t0
    beq $t1, $zero, __cond_false_10
    li $t0, 9
    sw $t0, 56($sp)
    j __cond_end_11
__cond_false_10:
    lw $t0, 4($sp)
    sltu $t1, $zero, $t0
    beq $t1, $zero, __cond_false_12
    li $t0, 10
    sw $t0, 60($sp)
    j __cond_end_13
__cond_false_12:
    li $t0, 11
    sw $t0, 60($sp)
__cond_end_13:
    lw $t0, 60($sp)
    sw $t0, 56($sp)
__cond_end_11:
    lw $t0, 56($sp)
    sw $t0, 44($sp)
    lw $t0, 40($sp)
    move $a0, $t0
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    lw $t0, 44($sp)
    move $a0, $t0
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    li $t0, 0
    sw $t0, 64($sp)
    lw $t0, 0($sp)
    sltu $t1, $zero, $t0
    beq $t1, $zero, __if_end_14
    lw $t0, 64($sp)
    sltu $t1, $zero, $t0
    beq $t1, $zero, __if_else_15
    li $t0, 500
    move $a0, $t0
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    j __if_end_16
__if_else_15:
    li $t0, 600
    move $a0, $t0
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
__if_end_16:
__if_end_14:
    li $t0, 0
    move $v0, $t0
    j __return_main
__return_main:
    addi $sp, $sp, 400
    li $v0, 10
    syscall

