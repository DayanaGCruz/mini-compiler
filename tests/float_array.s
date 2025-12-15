.data

__array_oob_msg: .asciiz "Runtime error: array index out of bounds\n"

.text
.globl main

main:
    addi $sp, $sp, -400
    # Declared array samples[3]
    li $t0, 0
    # Bounds check for array samples
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
    li.s $f0, 1.250000
    swc1 $f0, 0($t2)
    li $t0, 1
    # Bounds check for array samples
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
    li.s $f0, 2.500000
    swc1 $f0, 0($t2)
    li $t0, 0
    # Bounds check for array samples
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
    lwc1 $f0, 0($t2)
    swc1 $f0, 20($sp)
    li $t0, 1
    # Bounds check for array samples
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
    lwc1 $f0, 0($t2)
    swc1 $f0, 24($sp)
    lwc1 $f0, 20($sp)
    lwc1 $f1, 24($sp)
    add.s $f0, $f0, $f1
    swc1 $f0, 28($sp)
    li $t0, 2
    # Bounds check for array samples
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
    lwc1 $f0, 28($sp)
    swc1 $f0, 0($t2)
    li $t0, 2
    # Bounds check for array samples
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
    lwc1 $f0, 0($t2)
    swc1 $f0, 32($sp)
    lwc1 $f0, 32($sp)
    li.s $f1, 2.000000
    mul.s $f0, $f0, $f1
    swc1 $f0, 36($sp)
    li $t0, 2
    # Bounds check for array samples
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
    lwc1 $f0, 0($t2)
    swc1 $f0, 40($sp)
    lwc1 $f0, 40($sp)
    mov.s $f12, $f0
    li $v0, 2
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    lwc1 $f0, 36($sp)
    mov.s $f12, $f0
    li $v0, 2
    syscall
    li $v0, 11
    li $a0, 10
    syscall
__return_main:
    addi $sp, $sp, 400
    li $v0, 10
    syscall

