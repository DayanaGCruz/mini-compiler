.data

__array_oob_msg: .asciiz "Runtime error: array index out of bounds\n"

.text
.globl main

fn_swap:
    addi $sp, $sp, -400
    sw $ra, 396($sp)
    sw $a0, 0($sp)
    sw $a1, 4($sp)
    sw $a2, 8($sp)

    lw $t0, 4($sp)
    lw $t1, 0($sp)
    sll $t0, $t0, 2
    add $t1, $t1, $t0
    lw $t1, 0($t1)
    sw $t1, 16($sp)
    lw $t0, 16($sp)
    sw $t0, 12($sp)
    lw $t0, 8($sp)
    lw $t1, 0($sp)
    sll $t0, $t0, 2
    add $t1, $t1, $t0
    lw $t1, 0($t1)
    sw $t1, 20($sp)
    lw $t0, 4($sp)
    lw $t1, 0($sp)
    sll $t0, $t0, 2
    add $t1, $t1, $t0
    lw $t2, 20($sp)
    sw $t2, 0($t1)
    lw $t0, 8($sp)
    lw $t1, 0($sp)
    sll $t0, $t0, 2
    add $t1, $t1, $t0
    lw $t2, 12($sp)
    sw $t2, 0($t1)
__return_fn_swap:
    lw $ra, 396($sp)
    addi $sp, $sp, 400
    jr $ra

fn_printArray:
    addi $sp, $sp, -400
    sw $ra, 396($sp)
    sw $a0, 0($sp)
    sw $a1, 4($sp)

    li $t0, 10
    sb $t0, 12($sp)
    li $t0, 0
    sw $t0, 8($sp)
__while_start_0:
    lw $t0, 8($sp)
    lw $t1, 4($sp)
    slt $t2, $t0, $t1
    sw $t2, 16($sp)
    lw $t0, 16($sp)
    sltu $t1, $zero, $t0
    beq $t1, $zero, __while_end_1
    lw $t0, 8($sp)
    lw $t1, 0($sp)
    sll $t0, $t0, 2
    add $t1, $t1, $t0
    lw $t1, 0($t1)
    sw $t1, 20($sp)
    lw $t0, 20($sp)
    move $a0, $t0
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    lw $t0, 8($sp)
    li $t1, 1
    add $t0, $t0, $t1
    sw $t0, 24($sp)
    lw $t0, 24($sp)
    sw $t0, 8($sp)
    j __while_start_0
__while_end_1:
    lb $t0, 12($sp)
    li $v0, 11
    move $a0, $t0
    syscall
    li $v0, 11
    li $a0, 10
    syscall
__return_fn_printArray:
    lw $ra, 396($sp)
    addi $sp, $sp, 400
    jr $ra

main:
    addi $sp, $sp, -400
    # Declared array num[5]
    li $t0, 5
    sw $t0, 24($sp)
    li $t0, 0
    # Bounds check for array num
    bltz $t0, __bounds_error_0
    li $t1, 5
    bge $t0, $t1, __bounds_error_0
    j __bounds_ok_0
__bounds_error_0:
    li $v0, 4
    la $a0, __array_oob_msg
    syscall
    li $v0, 10
    syscall
__bounds_ok_0:
    addi $t2, $sp, 0
    sll $t0, $t0, 2
    add $t2, $t2, $t0
    li $t3, 2
    sw $t3, 0($t2)
    li $t0, 1
    # Bounds check for array num
    bltz $t0, __bounds_error_1
    li $t1, 5
    bge $t0, $t1, __bounds_error_1
    j __bounds_ok_1
__bounds_error_1:
    li $v0, 4
    la $a0, __array_oob_msg
    syscall
    li $v0, 10
    syscall
__bounds_ok_1:
    addi $t2, $sp, 0
    sll $t0, $t0, 2
    add $t2, $t2, $t0
    li $t3, 4
    sw $t3, 0($t2)
    li $t0, 2
    # Bounds check for array num
    bltz $t0, __bounds_error_2
    li $t1, 5
    bge $t0, $t1, __bounds_error_2
    j __bounds_ok_2
__bounds_error_2:
    li $v0, 4
    la $a0, __array_oob_msg
    syscall
    li $v0, 10
    syscall
__bounds_ok_2:
    addi $t2, $sp, 0
    sll $t0, $t0, 2
    add $t2, $t2, $t0
    li $t3, 6
    sw $t3, 0($t2)
    li $t0, 3
    # Bounds check for array num
    bltz $t0, __bounds_error_3
    li $t1, 5
    bge $t0, $t1, __bounds_error_3
    j __bounds_ok_3
__bounds_error_3:
    li $v0, 4
    la $a0, __array_oob_msg
    syscall
    li $v0, 10
    syscall
__bounds_ok_3:
    addi $t2, $sp, 0
    sll $t0, $t0, 2
    add $t2, $t2, $t0
    li $t3, 8
    sw $t3, 0($t2)
    li $t0, 4
    # Bounds check for array num
    bltz $t0, __bounds_error_4
    li $t1, 5
    bge $t0, $t1, __bounds_error_4
    j __bounds_ok_4
__bounds_error_4:
    li $v0, 4
    la $a0, __array_oob_msg
    syscall
    li $v0, 10
    syscall
__bounds_ok_4:
    addi $t2, $sp, 0
    sll $t0, $t0, 2
    add $t2, $t2, $t0
    li $t3, 10
    sw $t3, 0($t2)
    addi $t0, $sp, 0
    move $a0, $t0
    lw $t0, 24($sp)
    move $a1, $t0
    jal fn_printArray
    move $t0, $v0
    sw $t0, 28($sp)
    li $t0, 0
    sw $t0, 20($sp)
__while_start_2:
    lw $t0, 24($sp)
    li $t1, 1
    sub $t0, $t0, $t1
    sw $t0, 32($sp)
    lw $t0, 20($sp)
    lw $t1, 32($sp)
    slt $t2, $t0, $t1
    sw $t2, 36($sp)
    lw $t0, 36($sp)
    sltu $t1, $zero, $t0
    beq $t1, $zero, __while_end_3
    lw $t0, 20($sp)
    # Bounds check for array num
    bltz $t0, __bounds_error_5
    li $t1, 5
    bge $t0, $t1, __bounds_error_5
    j __bounds_ok_5
__bounds_error_5:
    li $v0, 4
    la $a0, __array_oob_msg
    syscall
    li $v0, 10
    syscall
__bounds_ok_5:
    addi $t2, $sp, 0
    sll $t0, $t0, 2
    add $t2, $t2, $t0
    lw $t2, 0($t2)
    sw $t2, 40($sp)
    lw $t0, 20($sp)
    li $t1, 1
    add $t0, $t0, $t1
    sw $t0, 44($sp)
    lw $t0, 44($sp)
    # Bounds check for array num
    bltz $t0, __bounds_error_6
    li $t1, 5
    bge $t0, $t1, __bounds_error_6
    j __bounds_ok_6
__bounds_error_6:
    li $v0, 4
    la $a0, __array_oob_msg
    syscall
    li $v0, 10
    syscall
__bounds_ok_6:
    addi $t2, $sp, 0
    sll $t0, $t0, 2
    add $t2, $t2, $t0
    lw $t2, 0($t2)
    sw $t2, 48($sp)
    lw $t0, 40($sp)
    lw $t1, 48($sp)
    slt $t2, $t0, $t1
    sw $t2, 52($sp)
    lw $t0, 52($sp)
    sltu $t1, $zero, $t0
    beq $t1, $zero, __if_end_4
    addi $t0, $sp, 0
    move $a0, $t0
    lw $t0, 20($sp)
    move $a1, $t0
    lw $t0, 20($sp)
    li $t1, 1
    add $t0, $t0, $t1
    sw $t0, 56($sp)
    lw $t0, 56($sp)
    move $a2, $t0
    jal fn_swap
    move $t0, $v0
    sw $t0, 60($sp)
__if_end_4:
    lw $t0, 20($sp)
    li $t1, 1
    add $t0, $t0, $t1
    sw $t0, 64($sp)
    lw $t0, 64($sp)
    sw $t0, 20($sp)
    j __while_start_2
__while_end_3:
    addi $t0, $sp, 0
    move $a0, $t0
    lw $t0, 24($sp)
    move $a1, $t0
    jal fn_printArray
    move $t0, $v0
    sw $t0, 68($sp)
    li $t0, 0
    move $v0, $t0
    j __return_main
__return_main:
    addi $sp, $sp, 400
    li $v0, 10
    syscall

