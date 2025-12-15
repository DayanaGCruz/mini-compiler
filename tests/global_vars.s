.data

__array_oob_msg: .asciiz "Runtime error: array index out of bounds\n"

.align 2
counter: .word 0

.align 2
data: .space 12

.text
.globl main

fn_bump:
    addi $sp, $sp, -400
    sw $ra, 396($sp)
    sw $a0, 0($sp)

    lw $t0, counter
    lw $t1, 0($sp)
    add $t0, $t0, $t1
    sw $t0, 4($sp)
    lw $t0, 4($sp)
    sw $t0, counter
    lw $t0, counter
    move $v0, $t0
    j __return_fn_bump
__return_fn_bump:
    lw $ra, 396($sp)
    addi $sp, $sp, 400
    jr $ra

main:
    addi $sp, $sp, -400
    li $t0, 0
    # Bounds check for array data
    bltz $t0, __bounds_error_0
    li $t1, 3
    bge $t0, $t1, __bounds_error_0
    j __bounds_ok_0
__bounds_error_0:
    li $v0, 4
    la $a0, __array_oob_msg
    syscall
    li $v0, 10
    syscall
__bounds_ok_0:
    la $t2, data
    sll $t0, $t0, 2
    add $t2, $t2, $t0
    li $t3, 7
    sw $t3, 0($t2)
    li $t0, 1
    # Bounds check for array data
    bltz $t0, __bounds_error_1
    li $t1, 3
    bge $t0, $t1, __bounds_error_1
    j __bounds_ok_1
__bounds_error_1:
    li $v0, 4
    la $a0, __array_oob_msg
    syscall
    li $v0, 10
    syscall
__bounds_ok_1:
    la $t2, data
    sll $t0, $t0, 2
    add $t2, $t2, $t0
    li $t3, 9
    sw $t3, 0($t2)
    li $t0, 2
    # Bounds check for array data
    bltz $t0, __bounds_error_2
    li $t1, 3
    bge $t0, $t1, __bounds_error_2
    j __bounds_ok_2
__bounds_error_2:
    li $v0, 4
    la $a0, __array_oob_msg
    syscall
    li $v0, 10
    syscall
__bounds_ok_2:
    la $t2, data
    sll $t0, $t0, 2
    add $t2, $t2, $t0
    li $t3, 11
    sw $t3, 0($t2)
    li $t0, 0
    # Bounds check for array data
    bltz $t0, __bounds_error_3
    li $t1, 3
    bge $t0, $t1, __bounds_error_3
    j __bounds_ok_3
__bounds_error_3:
    li $v0, 4
    la $a0, __array_oob_msg
    syscall
    li $v0, 10
    syscall
__bounds_ok_3:
    la $t2, data
    sll $t0, $t0, 2
    add $t2, $t2, $t0
    lw $t2, 0($t2)
    sw $t2, 4($sp)
    lw $t0, 4($sp)
    move $a0, $t0
    jal fn_bump
    move $t0, $v0
    sw $t0, 8($sp)
    lw $t0, 8($sp)
    sw $t0, 0($sp)
    lw $t0, 0($sp)
    move $a0, $t0
    jal fn_output
    move $t0, $v0
    sw $t0, 12($sp)
    li $t0, 1
    # Bounds check for array data
    bltz $t0, __bounds_error_4
    li $t1, 3
    bge $t0, $t1, __bounds_error_4
    j __bounds_ok_4
__bounds_error_4:
    li $v0, 4
    la $a0, __array_oob_msg
    syscall
    li $v0, 10
    syscall
__bounds_ok_4:
    la $t2, data
    sll $t0, $t0, 2
    add $t2, $t2, $t0
    lw $t2, 0($t2)
    sw $t2, 16($sp)
    lw $t0, 16($sp)
    move $a0, $t0
    jal fn_bump
    move $t0, $v0
    sw $t0, 20($sp)
    lw $t0, 20($sp)
    sw $t0, 0($sp)
    lw $t0, 0($sp)
    move $a0, $t0
    jal fn_output
    move $t0, $v0
    sw $t0, 24($sp)
    li $t0, 2
    # Bounds check for array data
    bltz $t0, __bounds_error_5
    li $t1, 3
    bge $t0, $t1, __bounds_error_5
    j __bounds_ok_5
__bounds_error_5:
    li $v0, 4
    la $a0, __array_oob_msg
    syscall
    li $v0, 10
    syscall
__bounds_ok_5:
    la $t2, data
    sll $t0, $t0, 2
    add $t2, $t2, $t0
    lw $t2, 0($t2)
    sw $t2, 28($sp)
    lw $t0, 28($sp)
    move $a0, $t0
    jal fn_bump
    move $t0, $v0
    sw $t0, 32($sp)
    lw $t0, 32($sp)
    sw $t0, 0($sp)
    lw $t0, 0($sp)
    move $a0, $t0
    jal fn_output
    move $t0, $v0
    sw $t0, 36($sp)
    li $t0, 0
    move $v0, $t0
    j __return_main
__return_main:
    addi $sp, $sp, 400
    li $v0, 10
    syscall


fn_output:
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    jr $ra
