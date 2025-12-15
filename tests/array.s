.data

__array_oob_msg: .asciiz "Runtime error: array index out of bounds\n"

.text
.globl main

main:
    addi $sp, $sp, -400
    # Declared array values[3]
    li $t0, 0
    # Bounds check for array values
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
    addi $t2, $sp, 0
    sll $t0, $t0, 2
    add $t2, $t2, $t0
    li $t3, 4
    sw $t3, 0($t2)
    li $t0, 1
    # Bounds check for array values
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
    addi $t2, $sp, 0
    sll $t0, $t0, 2
    add $t2, $t2, $t0
    li $t3, 5
    sw $t3, 0($t2)
    li $t0, 0
    # Bounds check for array values
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
    addi $t2, $sp, 0
    sll $t0, $t0, 2
    add $t2, $t2, $t0
    lw $t2, 0($t2)
    sw $t2, 16($sp)
    li $t0, 1
    # Bounds check for array values
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
    addi $t2, $sp, 0
    sll $t0, $t0, 2
    add $t2, $t2, $t0
    lw $t2, 0($t2)
    sw $t2, 20($sp)
    lw $t0, 16($sp)
    lw $t1, 20($sp)
    add $t0, $t0, $t1
    sw $t0, 24($sp)
    li $t0, 2
    # Bounds check for array values
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
    addi $t2, $sp, 0
    sll $t0, $t0, 2
    add $t2, $t2, $t0
    lw $t3, 24($sp)
    sw $t3, 0($t2)
    li $t0, 2
    # Bounds check for array values
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
    addi $t2, $sp, 0
    sll $t0, $t0, 2
    add $t2, $t2, $t0
    lw $t2, 0($t2)
    sw $t2, 28($sp)
    lw $t0, 28($sp)
    move $a0, $t0
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    li $t0, 2
    # Bounds check for array values
    bltz $t0, __bounds_error_6
    li $t1, 3
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
    sw $t2, 32($sp)
    lw $t0, 32($sp)
    li $t1, 3
    sub $t0, $t0, $t1
    sw $t0, 36($sp)
    li $t0, 0
    # Bounds check for array values
    bltz $t0, __bounds_error_7
    li $t1, 3
    bge $t0, $t1, __bounds_error_7
    j __bounds_ok_7
__bounds_error_7:
    li $v0, 4
    la $a0, __array_oob_msg
    syscall
    li $v0, 10
    syscall
__bounds_ok_7:
    addi $t2, $sp, 0
    sll $t0, $t0, 2
    add $t2, $t2, $t0
    lw $t3, 36($sp)
    sw $t3, 0($t2)
    li $t0, 0
    # Bounds check for array values
    bltz $t0, __bounds_error_8
    li $t1, 3
    bge $t0, $t1, __bounds_error_8
    j __bounds_ok_8
__bounds_error_8:
    li $v0, 4
    la $a0, __array_oob_msg
    syscall
    li $v0, 10
    syscall
__bounds_ok_8:
    addi $t2, $sp, 0
    sll $t0, $t0, 2
    add $t2, $t2, $t0
    lw $t2, 0($t2)
    sw $t2, 40($sp)
    lw $t0, 40($sp)
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

