.data

__array_oob_msg: .asciiz "Runtime error: array index out of bounds\n"

.align 2
globalA: .word 0

.align 2
globalB: .word 0

.align 2
results: .space 256

.align 2
node0: .space 4

.align 2
node1: .space 4

.align 2
node2: .space 4

.align 2
node3: .space 4

.align 2
node4: .space 4

.align 2
node5: .space 4

.align 2
node6: .space 4

.align 2
node7: .space 4

.align 2
localNode0: .space 4

.align 2
localNode1: .space 4

.align 2
localNode2: .space 4

.align 2
localNode3: .space 4

.text
.globl main

    # Struct Node defined
fn_factorial:
    addi $sp, $sp, -192
    sw $ra, 188($sp)

    sw $a0, 0($sp)

    # Declared array temp[20]
    # Declared array mirror[20]
    li $t0, 1
    sw $t0, 8($sp)
    li $t0, 1
    sw $t0, 4($sp)
__while_start_0:
    lw $t0, 4($sp)
    # Bounds check for array temp
    bltz $t0, __bounds_error_0
    li $t1, 20
    bge $t0, $t1, __bounds_error_0
    j __bounds_ok_0
__bounds_error_0:
    li $v0, 4
    la $a0, __array_oob_msg
    syscall
    li $v0, 10
    syscall
__bounds_ok_0:
    addi $t2, $sp, 12
    sll $t0, $t0, 2
    add $t2, $t2, $t0
    lw $t3, 4($sp)
    sw $t3, 0($t2)
    li $t0, 19
    lw $t1, 4($sp)
    sub $t0, $t0, $t1
    sw $t0, 172($sp)
    lw $t0, 4($sp)
    # Bounds check for array temp
    bltz $t0, __bounds_error_1
    li $t1, 20
    bge $t0, $t1, __bounds_error_1
    j __bounds_ok_1
__bounds_error_1:
    li $v0, 4
    la $a0, __array_oob_msg
    syscall
    li $v0, 10
    syscall
__bounds_ok_1:
    addi $t2, $sp, 12
    sll $t0, $t0, 2
    add $t2, $t2, $t0
    lw $t2, 0($t2)
    sw $t2, 176($sp)
    lw $t0, 172($sp)
    # Bounds check for array mirror
    bltz $t0, __bounds_error_2
    li $t1, 20
    bge $t0, $t1, __bounds_error_2
    j __bounds_ok_2
__bounds_error_2:
    li $v0, 4
    la $a0, __array_oob_msg
    syscall
    li $v0, 10
    syscall
__bounds_ok_2:
    addi $t2, $sp, 92
    sll $t0, $t0, 2
    add $t2, $t2, $t0
    lw $t3, 176($sp)
    sw $t3, 0($t2)
    lw $t0, 8($sp)
    lw $t1, 4($sp)
    mul $t0, $t0, $t1
    sw $t0, 180($sp)
    lw $t0, 180($sp)
    sw $t0, 8($sp)
    lw $t0, 4($sp)
    li $t1, 1
    add $t0, $t0, $t1
    sw $t0, 184($sp)
    lw $t0, 184($sp)
    sw $t0, 4($sp)
    lw $t0, 4($sp)
    # Bounds check for array temp
    bltz $t0, __bounds_error_3
    li $t1, 20
    bge $t0, $t1, __bounds_error_3
    j __bounds_ok_3
__bounds_error_3:
    li $v0, 4
    la $a0, __array_oob_msg
    syscall
    li $v0, 10
    syscall
__bounds_ok_3:
    addi $t2, $sp, 12
    sll $t0, $t0, 2
    add $t2, $t2, $t0
    lw $t3, 4($sp)
    sw $t3, 0($t2)
    li $t0, 19
    lw $t1, 4($sp)
    sub $t0, $t0, $t1
    sw $t0, 172($sp)
    lw $t0, 4($sp)
    # Bounds check for array temp
    bltz $t0, __bounds_error_4
    li $t1, 20
    bge $t0, $t1, __bounds_error_4
    j __bounds_ok_4
__bounds_error_4:
    li $v0, 4
    la $a0, __array_oob_msg
    syscall
    li $v0, 10
    syscall
__bounds_ok_4:
    addi $t2, $sp, 12
    sll $t0, $t0, 2
    add $t2, $t2, $t0
    lw $t2, 0($t2)
    sw $t2, 176($sp)
    lw $t0, 172($sp)
    # Bounds check for array mirror
    bltz $t0, __bounds_error_5
    li $t1, 20
    bge $t0, $t1, __bounds_error_5
    j __bounds_ok_5
__bounds_error_5:
    li $v0, 4
    la $a0, __array_oob_msg
    syscall
    li $v0, 10
    syscall
__bounds_ok_5:
    addi $t2, $sp, 92
    sll $t0, $t0, 2
    add $t2, $t2, $t0
    lw $t3, 176($sp)
    sw $t3, 0($t2)
    lw $t0, 8($sp)
    lw $t1, 4($sp)
    mul $t0, $t0, $t1
    sw $t0, 180($sp)
    lw $t0, 180($sp)
    sw $t0, 8($sp)
    lw $t0, 4($sp)
    li $t1, 1
    add $t0, $t0, $t1
    sw $t0, 184($sp)
    lw $t0, 184($sp)
    sw $t0, 4($sp)
    lw $t0, 4($sp)
    # Bounds check for array temp
    bltz $t0, __bounds_error_6
    li $t1, 20
    bge $t0, $t1, __bounds_error_6
    j __bounds_ok_6
__bounds_error_6:
    li $v0, 4
    la $a0, __array_oob_msg
    syscall
    li $v0, 10
    syscall
__bounds_ok_6:
    addi $t2, $sp, 12
    sll $t0, $t0, 2
    add $t2, $t2, $t0
    lw $t3, 4($sp)
    sw $t3, 0($t2)
    li $t0, 19
    lw $t1, 4($sp)
    sub $t0, $t0, $t1
    sw $t0, 172($sp)
    lw $t0, 4($sp)
    # Bounds check for array temp
    bltz $t0, __bounds_error_7
    li $t1, 20
    bge $t0, $t1, __bounds_error_7
    j __bounds_ok_7
__bounds_error_7:
    li $v0, 4
    la $a0, __array_oob_msg
    syscall
    li $v0, 10
    syscall
__bounds_ok_7:
    addi $t2, $sp, 12
    sll $t0, $t0, 2
    add $t2, $t2, $t0
    lw $t2, 0($t2)
    sw $t2, 176($sp)
    lw $t0, 172($sp)
    # Bounds check for array mirror
    bltz $t0, __bounds_error_8
    li $t1, 20
    bge $t0, $t1, __bounds_error_8
    j __bounds_ok_8
__bounds_error_8:
    li $v0, 4
    la $a0, __array_oob_msg
    syscall
    li $v0, 10
    syscall
__bounds_ok_8:
    addi $t2, $sp, 92
    sll $t0, $t0, 2
    add $t2, $t2, $t0
    lw $t3, 176($sp)
    sw $t3, 0($t2)
    lw $t0, 8($sp)
    lw $t1, 4($sp)
    mul $t0, $t0, $t1
    sw $t0, 180($sp)
    lw $t0, 180($sp)
    sw $t0, 8($sp)
    lw $t0, 4($sp)
    li $t1, 1
    add $t0, $t0, $t1
    sw $t0, 184($sp)
    lw $t0, 184($sp)
    sw $t0, 4($sp)
    lw $t0, 4($sp)
    # Bounds check for array temp
    bltz $t0, __bounds_error_9
    li $t1, 20
    bge $t0, $t1, __bounds_error_9
    j __bounds_ok_9
__bounds_error_9:
    li $v0, 4
    la $a0, __array_oob_msg
    syscall
    li $v0, 10
    syscall
__bounds_ok_9:
    addi $t2, $sp, 12
    sll $t0, $t0, 2
    add $t2, $t2, $t0
    lw $t3, 4($sp)
    sw $t3, 0($t2)
    li $t0, 19
    lw $t1, 4($sp)
    sub $t0, $t0, $t1
    sw $t0, 172($sp)
    lw $t0, 4($sp)
    # Bounds check for array temp
    bltz $t0, __bounds_error_10
    li $t1, 20
    bge $t0, $t1, __bounds_error_10
    j __bounds_ok_10
__bounds_error_10:
    li $v0, 4
    la $a0, __array_oob_msg
    syscall
    li $v0, 10
    syscall
__bounds_ok_10:
    addi $t2, $sp, 12
    sll $t0, $t0, 2
    add $t2, $t2, $t0
    lw $t2, 0($t2)
    sw $t2, 176($sp)
    lw $t0, 172($sp)
    # Bounds check for array mirror
    bltz $t0, __bounds_error_11
    li $t1, 20
    bge $t0, $t1, __bounds_error_11
    j __bounds_ok_11
__bounds_error_11:
    li $v0, 4
    la $a0, __array_oob_msg
    syscall
    li $v0, 10
    syscall
__bounds_ok_11:
    addi $t2, $sp, 92
    sll $t0, $t0, 2
    add $t2, $t2, $t0
    lw $t3, 176($sp)
    sw $t3, 0($t2)
    lw $t0, 8($sp)
    lw $t1, 4($sp)
    mul $t0, $t0, $t1
    sw $t0, 180($sp)
    lw $t0, 180($sp)
    sw $t0, 8($sp)
    lw $t0, 4($sp)
    li $t1, 1
    add $t0, $t0, $t1
    sw $t0, 184($sp)
    lw $t0, 184($sp)
    sw $t0, 4($sp)
    lw $t0, 4($sp)
    # Bounds check for array temp
    bltz $t0, __bounds_error_12
    li $t1, 20
    bge $t0, $t1, __bounds_error_12
    j __bounds_ok_12
__bounds_error_12:
    li $v0, 4
    la $a0, __array_oob_msg
    syscall
    li $v0, 10
    syscall
__bounds_ok_12:
    addi $t2, $sp, 12
    sll $t0, $t0, 2
    add $t2, $t2, $t0
    lw $t3, 4($sp)
    sw $t3, 0($t2)
    li $t0, 19
    lw $t1, 4($sp)
    sub $t0, $t0, $t1
    sw $t0, 172($sp)
    lw $t0, 4($sp)
    # Bounds check for array temp
    bltz $t0, __bounds_error_13
    li $t1, 20
    bge $t0, $t1, __bounds_error_13
    j __bounds_ok_13
__bounds_error_13:
    li $v0, 4
    la $a0, __array_oob_msg
    syscall
    li $v0, 10
    syscall
__bounds_ok_13:
    addi $t2, $sp, 12
    sll $t0, $t0, 2
    add $t2, $t2, $t0
    lw $t2, 0($t2)
    sw $t2, 176($sp)
    lw $t0, 172($sp)
    # Bounds check for array mirror
    bltz $t0, __bounds_error_14
    li $t1, 20
    bge $t0, $t1, __bounds_error_14
    j __bounds_ok_14
__bounds_error_14:
    li $v0, 4
    la $a0, __array_oob_msg
    syscall
    li $v0, 10
    syscall
__bounds_ok_14:
    addi $t2, $sp, 92
    sll $t0, $t0, 2
    add $t2, $t2, $t0
    lw $t3, 176($sp)
    sw $t3, 0($t2)
    lw $t0, 8($sp)
    lw $t1, 4($sp)
    mul $t0, $t0, $t1
    sw $t0, 180($sp)
    lw $t0, 180($sp)
    sw $t0, 8($sp)
    lw $t0, 4($sp)
    li $t1, 1
    add $t0, $t0, $t1
    sw $t0, 184($sp)
    lw $t0, 184($sp)
    sw $t0, 4($sp)
    lw $t0, 4($sp)
    # Bounds check for array temp
    bltz $t0, __bounds_error_15
    li $t1, 20
    bge $t0, $t1, __bounds_error_15
    j __bounds_ok_15
__bounds_error_15:
    li $v0, 4
    la $a0, __array_oob_msg
    syscall
    li $v0, 10
    syscall
__bounds_ok_15:
    addi $t2, $sp, 12
    sll $t0, $t0, 2
    add $t2, $t2, $t0
    lw $t3, 4($sp)
    sw $t3, 0($t2)
    li $t0, 19
    lw $t1, 4($sp)
    sub $t0, $t0, $t1
    sw $t0, 172($sp)
    lw $t0, 4($sp)
    # Bounds check for array temp
    bltz $t0, __bounds_error_16
    li $t1, 20
    bge $t0, $t1, __bounds_error_16
    j __bounds_ok_16
__bounds_error_16:
    li $v0, 4
    la $a0, __array_oob_msg
    syscall
    li $v0, 10
    syscall
__bounds_ok_16:
    addi $t2, $sp, 12
    sll $t0, $t0, 2
    add $t2, $t2, $t0
    lw $t2, 0($t2)
    sw $t2, 176($sp)
    lw $t0, 172($sp)
    # Bounds check for array mirror
    bltz $t0, __bounds_error_17
    li $t1, 20
    bge $t0, $t1, __bounds_error_17
    j __bounds_ok_17
__bounds_error_17:
    li $v0, 4
    la $a0, __array_oob_msg
    syscall
    li $v0, 10
    syscall
__bounds_ok_17:
    addi $t2, $sp, 92
    sll $t0, $t0, 2
    add $t2, $t2, $t0
    lw $t3, 176($sp)
    sw $t3, 0($t2)
    lw $t0, 8($sp)
    lw $t1, 4($sp)
    mul $t0, $t0, $t1
    sw $t0, 180($sp)
    lw $t0, 180($sp)
    sw $t0, 8($sp)
    lw $t0, 4($sp)
    li $t1, 1
    add $t0, $t0, $t1
    sw $t0, 184($sp)
    lw $t0, 184($sp)
    sw $t0, 4($sp)
__while_end_1:
    lw $t0, 8($sp)
    move $v0, $t0
    j __return_fn_factorial
__return_fn_factorial:
    lw $ra, 188($sp)
    addi $sp, $sp, 192
    jr $ra

fn_fib_helper:
    addi $sp, $sp, -32
    sw $ra, 28($sp)

    sw $a0, 0($sp)
    sw $a1, 4($sp)
    sw $a2, 8($sp)

    lw $t0, 0($sp)
    li $t1, 0
    xor $t3, $t0, $t1
    sltiu $t2, $t3, 1
    sw $t2, 12($sp)
    lw $t0, 12($sp)
    sltu $t1, $zero, $t0
    beq $t1, $zero, __if_else_2
    lw $t0, 4($sp)
    move $v0, $t0
    j __return_fn_fib_helper
    j __if_end_3
__if_else_2:
    lw $t0, 0($sp)
    li $t1, 1
    sub $t0, $t0, $t1
    sw $t0, 16($sp)
    lw $t0, 16($sp)
    move $a0, $t0
    lw $t0, 8($sp)
    move $a1, $t0
    lw $t0, 4($sp)
    lw $t1, 8($sp)
    add $t0, $t0, $t1
    sw $t0, 20($sp)
    lw $t0, 20($sp)
    move $a2, $t0
    jal fn_fib_helper
    move $t0, $v0
    sw $t0, 24($sp)
    lw $t0, 24($sp)
    move $v0, $t0
    j __return_fn_fib_helper
__if_end_3:
__return_fn_fib_helper:
    lw $ra, 28($sp)
    addi $sp, $sp, 32
    jr $ra

fn_fib:
    addi $sp, $sp, -12
    sw $ra, 8($sp)

    sw $a0, 0($sp)

    lw $t0, 0($sp)
    move $a0, $t0
    li $t0, 0
    move $a1, $t0
    li $t0, 1
    move $a2, $t0
    jal fn_fib_helper
    move $t0, $v0
    sw $t0, 4($sp)
    lw $t0, 4($sp)
    move $v0, $t0
    j __return_fn_fib
__return_fn_fib:
    lw $ra, 8($sp)
    addi $sp, $sp, 12
    jr $ra

fn_set_node_fields:
    addi $sp, $sp, -364
    sw $ra, 360($sp)

    sw $a0, 0($sp)
    sw $a1, 4($sp)

    li $t0, 0
    sw $t0, 8($sp)
    lw $t0, 0($sp)
    li $t1, 0
    xor $t3, $t0, $t1
    sltiu $t2, $t3, 1
    sw $t2, 12($sp)
    lw $t0, 12($sp)
    sltu $t1, $zero, $t0
    beq $t1, $zero, __if_else_4
    la $t0, node0
    addi $t0, $t0, 0
    lw $t1, 4($sp)
    sw $t1, 0($t0)
    lw $t0, 4($sp)
    li $t1, 1
    add $t0, $t0, $t1
    sw $t0, 16($sp)
    la $t0, node0
    addi $t0, $t0, 4
    lw $t1, 16($sp)
    sw $t1, 0($t0)
    lw $t0, 4($sp)
    li $t1, 2
    add $t0, $t0, $t1
    sw $t0, 20($sp)
    la $t0, node0
    addi $t0, $t0, 8
    lw $t1, 20($sp)
    sw $t1, 0($t0)
    lw $t0, 4($sp)
    li $t1, 3
    add $t0, $t0, $t1
    sw $t0, 24($sp)
    la $t0, node0
    addi $t0, $t0, 12
    lw $t1, 24($sp)
    sw $t1, 0($t0)
    la $t0, node0
    addi $t0, $t0, 0
    lw $t1, 0($t0)
    sw $t1, 28($sp)
    la $t0, node0
    addi $t0, $t0, 4
    lw $t1, 0($t0)
    sw $t1, 32($sp)
    lw $t0, 28($sp)
    lw $t1, 32($sp)
    add $t0, $t0, $t1
    sw $t0, 36($sp)
    la $t0, node0
    addi $t0, $t0, 8
    lw $t1, 0($t0)
    sw $t1, 40($sp)
    lw $t0, 36($sp)
    lw $t1, 40($sp)
    add $t0, $t0, $t1
    sw $t0, 44($sp)
    la $t0, node0
    addi $t0, $t0, 12
    lw $t1, 0($t0)
    sw $t1, 48($sp)
    lw $t0, 44($sp)
    lw $t1, 48($sp)
    add $t0, $t0, $t1
    sw $t0, 52($sp)
    lw $t0, 52($sp)
    sw $t0, 8($sp)
    j __if_end_5
__if_else_4:
    lw $t0, 0($sp)
    li $t1, 1
    xor $t3, $t0, $t1
    sltiu $t2, $t3, 1
    sw $t2, 56($sp)
    lw $t0, 56($sp)
    sltu $t1, $zero, $t0
    beq $t1, $zero, __if_else_6
    la $t0, node1
    addi $t0, $t0, 0
    lw $t1, 4($sp)
    sw $t1, 0($t0)
    lw $t0, 4($sp)
    li $t1, 1
    add $t0, $t0, $t1
    sw $t0, 60($sp)
    la $t0, node1
    addi $t0, $t0, 4
    lw $t1, 60($sp)
    sw $t1, 0($t0)
    lw $t0, 4($sp)
    li $t1, 2
    add $t0, $t0, $t1
    sw $t0, 64($sp)
    la $t0, node1
    addi $t0, $t0, 8
    lw $t1, 64($sp)
    sw $t1, 0($t0)
    lw $t0, 4($sp)
    li $t1, 3
    add $t0, $t0, $t1
    sw $t0, 68($sp)
    la $t0, node1
    addi $t0, $t0, 12
    lw $t1, 68($sp)
    sw $t1, 0($t0)
    la $t0, node1
    addi $t0, $t0, 0
    lw $t1, 0($t0)
    sw $t1, 72($sp)
    la $t0, node1
    addi $t0, $t0, 4
    lw $t1, 0($t0)
    sw $t1, 76($sp)
    lw $t0, 72($sp)
    lw $t1, 76($sp)
    add $t0, $t0, $t1
    sw $t0, 80($sp)
    la $t0, node1
    addi $t0, $t0, 8
    lw $t1, 0($t0)
    sw $t1, 84($sp)
    lw $t0, 80($sp)
    lw $t1, 84($sp)
    add $t0, $t0, $t1
    sw $t0, 88($sp)
    la $t0, node1
    addi $t0, $t0, 12
    lw $t1, 0($t0)
    sw $t1, 92($sp)
    lw $t0, 88($sp)
    lw $t1, 92($sp)
    add $t0, $t0, $t1
    sw $t0, 96($sp)
    lw $t0, 96($sp)
    sw $t0, 8($sp)
    j __if_end_7
__if_else_6:
    lw $t0, 0($sp)
    li $t1, 2
    xor $t3, $t0, $t1
    sltiu $t2, $t3, 1
    sw $t2, 100($sp)
    lw $t0, 100($sp)
    sltu $t1, $zero, $t0
    beq $t1, $zero, __if_else_8
    la $t0, node2
    addi $t0, $t0, 0
    lw $t1, 4($sp)
    sw $t1, 0($t0)
    lw $t0, 4($sp)
    li $t1, 1
    add $t0, $t0, $t1
    sw $t0, 104($sp)
    la $t0, node2
    addi $t0, $t0, 4
    lw $t1, 104($sp)
    sw $t1, 0($t0)
    lw $t0, 4($sp)
    li $t1, 2
    add $t0, $t0, $t1
    sw $t0, 108($sp)
    la $t0, node2
    addi $t0, $t0, 8
    lw $t1, 108($sp)
    sw $t1, 0($t0)
    lw $t0, 4($sp)
    li $t1, 3
    add $t0, $t0, $t1
    sw $t0, 112($sp)
    la $t0, node2
    addi $t0, $t0, 12
    lw $t1, 112($sp)
    sw $t1, 0($t0)
    la $t0, node2
    addi $t0, $t0, 0
    lw $t1, 0($t0)
    sw $t1, 116($sp)
    la $t0, node2
    addi $t0, $t0, 4
    lw $t1, 0($t0)
    sw $t1, 120($sp)
    lw $t0, 116($sp)
    lw $t1, 120($sp)
    add $t0, $t0, $t1
    sw $t0, 124($sp)
    la $t0, node2
    addi $t0, $t0, 8
    lw $t1, 0($t0)
    sw $t1, 128($sp)
    lw $t0, 124($sp)
    lw $t1, 128($sp)
    add $t0, $t0, $t1
    sw $t0, 132($sp)
    la $t0, node2
    addi $t0, $t0, 12
    lw $t1, 0($t0)
    sw $t1, 136($sp)
    lw $t0, 132($sp)
    lw $t1, 136($sp)
    add $t0, $t0, $t1
    sw $t0, 140($sp)
    lw $t0, 140($sp)
    sw $t0, 8($sp)
    j __if_end_9
__if_else_8:
    lw $t0, 0($sp)
    li $t1, 3
    xor $t3, $t0, $t1
    sltiu $t2, $t3, 1
    sw $t2, 144($sp)
    lw $t0, 144($sp)
    sltu $t1, $zero, $t0
    beq $t1, $zero, __if_else_10
    la $t0, node3
    addi $t0, $t0, 0
    lw $t1, 4($sp)
    sw $t1, 0($t0)
    lw $t0, 4($sp)
    li $t1, 1
    add $t0, $t0, $t1
    sw $t0, 148($sp)
    la $t0, node3
    addi $t0, $t0, 4
    lw $t1, 148($sp)
    sw $t1, 0($t0)
    lw $t0, 4($sp)
    li $t1, 2
    add $t0, $t0, $t1
    sw $t0, 152($sp)
    la $t0, node3
    addi $t0, $t0, 8
    lw $t1, 152($sp)
    sw $t1, 0($t0)
    lw $t0, 4($sp)
    li $t1, 3
    add $t0, $t0, $t1
    sw $t0, 156($sp)
    la $t0, node3
    addi $t0, $t0, 12
    lw $t1, 156($sp)
    sw $t1, 0($t0)
    la $t0, node3
    addi $t0, $t0, 0
    lw $t1, 0($t0)
    sw $t1, 160($sp)
    la $t0, node3
    addi $t0, $t0, 4
    lw $t1, 0($t0)
    sw $t1, 164($sp)
    lw $t0, 160($sp)
    lw $t1, 164($sp)
    add $t0, $t0, $t1
    sw $t0, 168($sp)
    la $t0, node3
    addi $t0, $t0, 8
    lw $t1, 0($t0)
    sw $t1, 172($sp)
    lw $t0, 168($sp)
    lw $t1, 172($sp)
    add $t0, $t0, $t1
    sw $t0, 176($sp)
    la $t0, node3
    addi $t0, $t0, 12
    lw $t1, 0($t0)
    sw $t1, 180($sp)
    lw $t0, 176($sp)
    lw $t1, 180($sp)
    add $t0, $t0, $t1
    sw $t0, 184($sp)
    lw $t0, 184($sp)
    sw $t0, 8($sp)
    j __if_end_11
__if_else_10:
    lw $t0, 0($sp)
    li $t1, 4
    xor $t3, $t0, $t1
    sltiu $t2, $t3, 1
    sw $t2, 188($sp)
    lw $t0, 188($sp)
    sltu $t1, $zero, $t0
    beq $t1, $zero, __if_else_12
    la $t0, node4
    addi $t0, $t0, 0
    lw $t1, 4($sp)
    sw $t1, 0($t0)
    lw $t0, 4($sp)
    li $t1, 1
    add $t0, $t0, $t1
    sw $t0, 192($sp)
    la $t0, node4
    addi $t0, $t0, 4
    lw $t1, 192($sp)
    sw $t1, 0($t0)
    lw $t0, 4($sp)
    li $t1, 2
    add $t0, $t0, $t1
    sw $t0, 196($sp)
    la $t0, node4
    addi $t0, $t0, 8
    lw $t1, 196($sp)
    sw $t1, 0($t0)
    lw $t0, 4($sp)
    li $t1, 3
    add $t0, $t0, $t1
    sw $t0, 200($sp)
    la $t0, node4
    addi $t0, $t0, 12
    lw $t1, 200($sp)
    sw $t1, 0($t0)
    la $t0, node4
    addi $t0, $t0, 0
    lw $t1, 0($t0)
    sw $t1, 204($sp)
    la $t0, node4
    addi $t0, $t0, 4
    lw $t1, 0($t0)
    sw $t1, 208($sp)
    lw $t0, 204($sp)
    lw $t1, 208($sp)
    add $t0, $t0, $t1
    sw $t0, 212($sp)
    la $t0, node4
    addi $t0, $t0, 8
    lw $t1, 0($t0)
    sw $t1, 216($sp)
    lw $t0, 212($sp)
    lw $t1, 216($sp)
    add $t0, $t0, $t1
    sw $t0, 220($sp)
    la $t0, node4
    addi $t0, $t0, 12
    lw $t1, 0($t0)
    sw $t1, 224($sp)
    lw $t0, 220($sp)
    lw $t1, 224($sp)
    add $t0, $t0, $t1
    sw $t0, 228($sp)
    lw $t0, 228($sp)
    sw $t0, 8($sp)
    j __if_end_13
__if_else_12:
    lw $t0, 0($sp)
    li $t1, 5
    xor $t3, $t0, $t1
    sltiu $t2, $t3, 1
    sw $t2, 232($sp)
    lw $t0, 232($sp)
    sltu $t1, $zero, $t0
    beq $t1, $zero, __if_else_14
    la $t0, node5
    addi $t0, $t0, 0
    lw $t1, 4($sp)
    sw $t1, 0($t0)
    lw $t0, 4($sp)
    li $t1, 1
    add $t0, $t0, $t1
    sw $t0, 236($sp)
    la $t0, node5
    addi $t0, $t0, 4
    lw $t1, 236($sp)
    sw $t1, 0($t0)
    lw $t0, 4($sp)
    li $t1, 2
    add $t0, $t0, $t1
    sw $t0, 240($sp)
    la $t0, node5
    addi $t0, $t0, 8
    lw $t1, 240($sp)
    sw $t1, 0($t0)
    lw $t0, 4($sp)
    li $t1, 3
    add $t0, $t0, $t1
    sw $t0, 244($sp)
    la $t0, node5
    addi $t0, $t0, 12
    lw $t1, 244($sp)
    sw $t1, 0($t0)
    la $t0, node5
    addi $t0, $t0, 0
    lw $t1, 0($t0)
    sw $t1, 248($sp)
    la $t0, node5
    addi $t0, $t0, 4
    lw $t1, 0($t0)
    sw $t1, 252($sp)
    lw $t0, 248($sp)
    lw $t1, 252($sp)
    add $t0, $t0, $t1
    sw $t0, 256($sp)
    la $t0, node5
    addi $t0, $t0, 8
    lw $t1, 0($t0)
    sw $t1, 260($sp)
    lw $t0, 256($sp)
    lw $t1, 260($sp)
    add $t0, $t0, $t1
    sw $t0, 264($sp)
    la $t0, node5
    addi $t0, $t0, 12
    lw $t1, 0($t0)
    sw $t1, 268($sp)
    lw $t0, 264($sp)
    lw $t1, 268($sp)
    add $t0, $t0, $t1
    sw $t0, 272($sp)
    lw $t0, 272($sp)
    sw $t0, 8($sp)
    j __if_end_15
__if_else_14:
    lw $t0, 0($sp)
    li $t1, 6
    xor $t3, $t0, $t1
    sltiu $t2, $t3, 1
    sw $t2, 276($sp)
    lw $t0, 276($sp)
    sltu $t1, $zero, $t0
    beq $t1, $zero, __if_else_16
    la $t0, node6
    addi $t0, $t0, 0
    lw $t1, 4($sp)
    sw $t1, 0($t0)
    lw $t0, 4($sp)
    li $t1, 1
    add $t0, $t0, $t1
    sw $t0, 280($sp)
    la $t0, node6
    addi $t0, $t0, 4
    lw $t1, 280($sp)
    sw $t1, 0($t0)
    lw $t0, 4($sp)
    li $t1, 2
    add $t0, $t0, $t1
    sw $t0, 284($sp)
    la $t0, node6
    addi $t0, $t0, 8
    lw $t1, 284($sp)
    sw $t1, 0($t0)
    lw $t0, 4($sp)
    li $t1, 3
    add $t0, $t0, $t1
    sw $t0, 288($sp)
    la $t0, node6
    addi $t0, $t0, 12
    lw $t1, 288($sp)
    sw $t1, 0($t0)
    la $t0, node6
    addi $t0, $t0, 0
    lw $t1, 0($t0)
    sw $t1, 292($sp)
    la $t0, node6
    addi $t0, $t0, 4
    lw $t1, 0($t0)
    sw $t1, 296($sp)
    lw $t0, 292($sp)
    lw $t1, 296($sp)
    add $t0, $t0, $t1
    sw $t0, 300($sp)
    la $t0, node6
    addi $t0, $t0, 8
    lw $t1, 0($t0)
    sw $t1, 304($sp)
    lw $t0, 300($sp)
    lw $t1, 304($sp)
    add $t0, $t0, $t1
    sw $t0, 308($sp)
    la $t0, node6
    addi $t0, $t0, 12
    lw $t1, 0($t0)
    sw $t1, 312($sp)
    lw $t0, 308($sp)
    lw $t1, 312($sp)
    add $t0, $t0, $t1
    sw $t0, 316($sp)
    lw $t0, 316($sp)
    sw $t0, 8($sp)
    j __if_end_17
__if_else_16:
    la $t0, node7
    addi $t0, $t0, 0
    lw $t1, 4($sp)
    sw $t1, 0($t0)
    lw $t0, 4($sp)
    li $t1, 1
    add $t0, $t0, $t1
    sw $t0, 320($sp)
    la $t0, node7
    addi $t0, $t0, 4
    lw $t1, 320($sp)
    sw $t1, 0($t0)
    lw $t0, 4($sp)
    li $t1, 2
    add $t0, $t0, $t1
    sw $t0, 324($sp)
    la $t0, node7
    addi $t0, $t0, 8
    lw $t1, 324($sp)
    sw $t1, 0($t0)
    lw $t0, 4($sp)
    li $t1, 3
    add $t0, $t0, $t1
    sw $t0, 328($sp)
    la $t0, node7
    addi $t0, $t0, 12
    lw $t1, 328($sp)
    sw $t1, 0($t0)
    la $t0, node7
    addi $t0, $t0, 0
    lw $t1, 0($t0)
    sw $t1, 332($sp)
    la $t0, node7
    addi $t0, $t0, 4
    lw $t1, 0($t0)
    sw $t1, 336($sp)
    lw $t0, 332($sp)
    lw $t1, 336($sp)
    add $t0, $t0, $t1
    sw $t0, 340($sp)
    la $t0, node7
    addi $t0, $t0, 8
    lw $t1, 0($t0)
    sw $t1, 344($sp)
    lw $t0, 340($sp)
    lw $t1, 344($sp)
    add $t0, $t0, $t1
    sw $t0, 348($sp)
    la $t0, node7
    addi $t0, $t0, 12
    lw $t1, 0($t0)
    sw $t1, 352($sp)
    lw $t0, 348($sp)
    lw $t1, 352($sp)
    add $t0, $t0, $t1
    sw $t0, 356($sp)
    lw $t0, 356($sp)
    sw $t0, 8($sp)
__if_end_17:
__if_end_15:
__if_end_13:
__if_end_11:
__if_end_9:
__if_end_7:
__if_end_5:
    lw $t0, 8($sp)
    move $v0, $t0
    j __return_fn_set_node_fields
__return_fn_set_node_fields:
    lw $ra, 360($sp)
    addi $sp, $sp, 364
    jr $ra

fn_update_local_node:
    addi $sp, $sp, -124
    sw $ra, 120($sp)

    sw $a0, 0($sp)
    sw $a1, 4($sp)

    li $t0, 0
    sw $t0, 8($sp)
    lw $t0, 0($sp)
    li $t1, 0
    xor $t3, $t0, $t1
    sltiu $t2, $t3, 1
    sw $t2, 12($sp)
    lw $t0, 12($sp)
    sltu $t1, $zero, $t0
    beq $t1, $zero, __if_else_18
    la $t0, localNode0
    addi $t0, $t0, 0
    lw $t1, 4($sp)
    sw $t1, 0($t0)
    lw $t0, 4($sp)
    li $t1, 100
    add $t0, $t0, $t1
    sw $t0, 16($sp)
    la $t0, localNode0
    addi $t0, $t0, 4
    lw $t1, 16($sp)
    sw $t1, 0($t0)
    la $t0, localNode0
    addi $t0, $t0, 4
    lw $t1, 0($t0)
    sw $t1, 20($sp)
    lw $t0, 20($sp)
    li $t1, 10
    add $t0, $t0, $t1
    sw $t0, 24($sp)
    la $t0, localNode0
    addi $t0, $t0, 8
    lw $t1, 24($sp)
    sw $t1, 0($t0)
    la $t0, localNode0
    addi $t0, $t0, 8
    lw $t1, 0($t0)
    sw $t1, 28($sp)
    lw $t0, 28($sp)
    li $t1, 10
    add $t0, $t0, $t1
    sw $t0, 32($sp)
    la $t0, localNode0
    addi $t0, $t0, 12
    lw $t1, 32($sp)
    sw $t1, 0($t0)
    la $t0, localNode0
    addi $t0, $t0, 12
    lw $t1, 0($t0)
    sw $t1, 36($sp)
    lw $t0, 36($sp)
    sw $t0, 8($sp)
    j __if_end_19
__if_else_18:
    lw $t0, 0($sp)
    li $t1, 1
    xor $t3, $t0, $t1
    sltiu $t2, $t3, 1
    sw $t2, 40($sp)
    lw $t0, 40($sp)
    sltu $t1, $zero, $t0
    beq $t1, $zero, __if_else_20
    la $t0, localNode1
    addi $t0, $t0, 0
    lw $t1, 4($sp)
    sw $t1, 0($t0)
    lw $t0, 4($sp)
    li $t1, 100
    add $t0, $t0, $t1
    sw $t0, 44($sp)
    la $t0, localNode1
    addi $t0, $t0, 4
    lw $t1, 44($sp)
    sw $t1, 0($t0)
    la $t0, localNode1
    addi $t0, $t0, 4
    lw $t1, 0($t0)
    sw $t1, 48($sp)
    lw $t0, 48($sp)
    li $t1, 10
    add $t0, $t0, $t1
    sw $t0, 52($sp)
    la $t0, localNode1
    addi $t0, $t0, 8
    lw $t1, 52($sp)
    sw $t1, 0($t0)
    la $t0, localNode1
    addi $t0, $t0, 8
    lw $t1, 0($t0)
    sw $t1, 56($sp)
    lw $t0, 56($sp)
    li $t1, 10
    add $t0, $t0, $t1
    sw $t0, 60($sp)
    la $t0, localNode1
    addi $t0, $t0, 12
    lw $t1, 60($sp)
    sw $t1, 0($t0)
    la $t0, localNode1
    addi $t0, $t0, 12
    lw $t1, 0($t0)
    sw $t1, 64($sp)
    lw $t0, 64($sp)
    sw $t0, 8($sp)
    j __if_end_21
__if_else_20:
    lw $t0, 0($sp)
    li $t1, 2
    xor $t3, $t0, $t1
    sltiu $t2, $t3, 1
    sw $t2, 68($sp)
    lw $t0, 68($sp)
    sltu $t1, $zero, $t0
    beq $t1, $zero, __if_else_22
    la $t0, localNode2
    addi $t0, $t0, 0
    lw $t1, 4($sp)
    sw $t1, 0($t0)
    lw $t0, 4($sp)
    li $t1, 100
    add $t0, $t0, $t1
    sw $t0, 72($sp)
    la $t0, localNode2
    addi $t0, $t0, 4
    lw $t1, 72($sp)
    sw $t1, 0($t0)
    la $t0, localNode2
    addi $t0, $t0, 4
    lw $t1, 0($t0)
    sw $t1, 76($sp)
    lw $t0, 76($sp)
    li $t1, 10
    add $t0, $t0, $t1
    sw $t0, 80($sp)
    la $t0, localNode2
    addi $t0, $t0, 8
    lw $t1, 80($sp)
    sw $t1, 0($t0)
    la $t0, localNode2
    addi $t0, $t0, 8
    lw $t1, 0($t0)
    sw $t1, 84($sp)
    lw $t0, 84($sp)
    li $t1, 10
    add $t0, $t0, $t1
    sw $t0, 88($sp)
    la $t0, localNode2
    addi $t0, $t0, 12
    lw $t1, 88($sp)
    sw $t1, 0($t0)
    la $t0, localNode2
    addi $t0, $t0, 12
    lw $t1, 0($t0)
    sw $t1, 92($sp)
    lw $t0, 92($sp)
    sw $t0, 8($sp)
    j __if_end_23
__if_else_22:
    la $t0, localNode3
    addi $t0, $t0, 0
    lw $t1, 4($sp)
    sw $t1, 0($t0)
    lw $t0, 4($sp)
    li $t1, 100
    add $t0, $t0, $t1
    sw $t0, 96($sp)
    la $t0, localNode3
    addi $t0, $t0, 4
    lw $t1, 96($sp)
    sw $t1, 0($t0)
    la $t0, localNode3
    addi $t0, $t0, 4
    lw $t1, 0($t0)
    sw $t1, 100($sp)
    lw $t0, 100($sp)
    li $t1, 10
    add $t0, $t0, $t1
    sw $t0, 104($sp)
    la $t0, localNode3
    addi $t0, $t0, 8
    lw $t1, 104($sp)
    sw $t1, 0($t0)
    la $t0, localNode3
    addi $t0, $t0, 8
    lw $t1, 0($t0)
    sw $t1, 108($sp)
    lw $t0, 108($sp)
    li $t1, 10
    add $t0, $t0, $t1
    sw $t0, 112($sp)
    la $t0, localNode3
    addi $t0, $t0, 12
    lw $t1, 112($sp)
    sw $t1, 0($t0)
    la $t0, localNode3
    addi $t0, $t0, 12
    lw $t1, 0($t0)
    sw $t1, 116($sp)
    lw $t0, 116($sp)
    sw $t0, 8($sp)
__if_end_23:
__if_end_21:
__if_end_19:
    lw $t0, 8($sp)
    move $v0, $t0
    j __return_fn_update_local_node
__return_fn_update_local_node:
    lw $ra, 120($sp)
    addi $sp, $sp, 124
    jr $ra

fn_sum_structs:
    addi $sp, $sp, -36
    sw $ra, 32($sp)

    sw $a0, 0($sp)

    li $t0, 0
    sw $t0, 4($sp)
    li $t0, 0
    sw $t0, 8($sp)
__while_start_24:
    lw $t0, 4($sp)
    lw $t1, 0($sp)
    slt $t2, $t0, $t1
    sw $t2, 12($sp)
    lw $t0, 12($sp)
    sltu $t1, $zero, $t0
    beq $t1, $zero, __while_end_25
    lw $t0, 4($sp)
    move $a0, $t0
    lw $t0, 4($sp)
    li $t1, 7
    mul $t0, $t0, $t1
    sw $t0, 16($sp)
    lw $t0, 16($sp)
    move $a1, $t0
    jal fn_set_node_fields
    move $t0, $v0
    sw $t0, 20($sp)
    lw $t0, 8($sp)
    lw $t1, 20($sp)
    add $t0, $t0, $t1
    sw $t0, 24($sp)
    lw $t0, 24($sp)
    sw $t0, 8($sp)
    lw $t0, 4($sp)
    li $t1, 1
    add $t0, $t0, $t1
    sw $t0, 28($sp)
    lw $t0, 28($sp)
    sw $t0, 4($sp)
    j __while_start_24
__while_end_25:
    lw $t0, 8($sp)
    move $v0, $t0
    j __return_fn_sum_structs
__return_fn_sum_structs:
    lw $ra, 32($sp)
    addi $sp, $sp, 36
    jr $ra

fn_heavy_loop:
    addi $sp, $sp, -476
    sw $ra, 472($sp)

    sw $a0, 0($sp)

    # Declared array table[50]
    # Declared array scratch[50]
    li $t0, 0
    sw $t0, 4($sp)
    li $t0, 0
    sw $t0, 8($sp)
__while_start_26:
    lw $t0, 8($sp)
    lw $t1, 0($sp)
    slt $t2, $t0, $t1
    sw $t2, 416($sp)
    lw $t0, 416($sp)
    sltu $t1, $zero, $t0
    beq $t1, $zero, __while_end_27
    li $t0, 0
    sw $t0, 12($sp)
__while_start_28:
    lw $t0, 12($sp)
    li $t1, 50
    slt $t2, $t0, $t1
    sw $t2, 420($sp)
    lw $t0, 420($sp)
    sltu $t1, $zero, $t0
    beq $t1, $zero, __while_end_29
    lw $t0, 8($sp)
    lw $t1, 12($sp)
    add $t0, $t0, $t1
    sw $t0, 424($sp)
    lw $t0, 8($sp)
    lw $t1, 12($sp)
    sub $t0, $t0, $t1
    sw $t0, 428($sp)
    lw $t0, 428($sp)
    li $t1, 7
    add $t0, $t0, $t1
    sw $t0, 432($sp)
    lw $t0, 424($sp)
    lw $t1, 432($sp)
    mul $t0, $t0, $t1
    sw $t0, 436($sp)
    lw $t0, 12($sp)
    # Bounds check for array table
    bltz $t0, __bounds_error_18
    li $t1, 50
    bge $t0, $t1, __bounds_error_18
    j __bounds_ok_18
__bounds_error_18:
    li $v0, 4
    la $a0, __array_oob_msg
    syscall
    li $v0, 10
    syscall
__bounds_ok_18:
    addi $t2, $sp, 16
    sll $t0, $t0, 2
    add $t2, $t2, $t0
    lw $t3, 436($sp)
    sw $t3, 0($t2)
    lw $t0, 12($sp)
    # Bounds check for array table
    bltz $t0, __bounds_error_19
    li $t1, 50
    bge $t0, $t1, __bounds_error_19
    j __bounds_ok_19
__bounds_error_19:
    li $v0, 4
    la $a0, __array_oob_msg
    syscall
    li $v0, 10
    syscall
__bounds_ok_19:
    addi $t2, $sp, 16
    sll $t0, $t0, 2
    add $t2, $t2, $t0
    lw $t2, 0($t2)
    sw $t2, 440($sp)
    lw $t0, 12($sp)
    li $t1, 5
    div $t0, $t1
    mflo $t0
    sw $t0, 444($sp)
    lw $t0, 444($sp)
    li $t1, 1
    add $t0, $t0, $t1
    sw $t0, 448($sp)
    lw $t0, 440($sp)
    lw $t1, 448($sp)
    div $t0, $t1
    mflo $t0
    sw $t0, 452($sp)
    lw $t0, 12($sp)
    # Bounds check for array scratch
    bltz $t0, __bounds_error_20
    li $t1, 50
    bge $t0, $t1, __bounds_error_20
    j __bounds_ok_20
__bounds_error_20:
    li $v0, 4
    la $a0, __array_oob_msg
    syscall
    li $v0, 10
    syscall
__bounds_ok_20:
    addi $t2, $sp, 216
    sll $t0, $t0, 2
    add $t2, $t2, $t0
    lw $t3, 452($sp)
    sw $t3, 0($t2)
    lw $t0, 12($sp)
    # Bounds check for array scratch
    bltz $t0, __bounds_error_21
    li $t1, 50
    bge $t0, $t1, __bounds_error_21
    j __bounds_ok_21
__bounds_error_21:
    li $v0, 4
    la $a0, __array_oob_msg
    syscall
    li $v0, 10
    syscall
__bounds_ok_21:
    addi $t2, $sp, 216
    sll $t0, $t0, 2
    add $t2, $t2, $t0
    lw $t2, 0($t2)
    sw $t2, 456($sp)
    lw $t0, 4($sp)
    lw $t1, 456($sp)
    add $t0, $t0, $t1
    sw $t0, 460($sp)
    lw $t0, 460($sp)
    sw $t0, 4($sp)
    lw $t0, 12($sp)
    li $t1, 1
    add $t0, $t0, $t1
    sw $t0, 464($sp)
    lw $t0, 464($sp)
    sw $t0, 12($sp)
    j __while_start_28
__while_end_29:
    lw $t0, 8($sp)
    li $t1, 1
    add $t0, $t0, $t1
    sw $t0, 468($sp)
    lw $t0, 468($sp)
    sw $t0, 8($sp)
    j __while_start_26
__while_end_27:
    lw $t0, 4($sp)
    move $v0, $t0
    j __return_fn_heavy_loop
__return_fn_heavy_loop:
    lw $ra, 472($sp)
    addi $sp, $sp, 476
    jr $ra

fn_switch_magic:
    addi $sp, $sp, -48
    sw $ra, 44($sp)

    sw $a0, 0($sp)

    li $t0, 0
    sw $t0, 4($sp)
    lw $t0, 0($sp)
    li $t1, 0
    xor $t3, $t0, $t1
    sltiu $t2, $t3, 1
    sw $t2, 8($sp)
    lw $t0, 8($sp)
    sltu $t1, $zero, $t0
    bne $t1, $zero, __switch_case_31
    lw $t0, 0($sp)
    li $t1, 1
    xor $t3, $t0, $t1
    sltiu $t2, $t3, 1
    sw $t2, 12($sp)
    lw $t0, 12($sp)
    sltu $t1, $zero, $t0
    bne $t1, $zero, __switch_case_32
    lw $t0, 0($sp)
    li $t1, 2
    xor $t3, $t0, $t1
    sltiu $t2, $t3, 1
    sw $t2, 16($sp)
    lw $t0, 16($sp)
    sltu $t1, $zero, $t0
    bne $t1, $zero, __switch_case_33
    lw $t0, 0($sp)
    li $t1, 3
    xor $t3, $t0, $t1
    sltiu $t2, $t3, 1
    sw $t2, 20($sp)
    lw $t0, 20($sp)
    sltu $t1, $zero, $t0
    bne $t1, $zero, __switch_case_34
    j __switch_default_35
__switch_case_31:
    lw $t0, 4($sp)
    li $t1, 1
    add $t0, $t0, $t1
    sw $t0, 24($sp)
    lw $t0, 24($sp)
    sw $t0, 4($sp)
    j __switch_end_30
__switch_case_32:
    lw $t0, 4($sp)
    li $t1, 3
    add $t0, $t0, $t1
    sw $t0, 28($sp)
    lw $t0, 28($sp)
    sw $t0, 4($sp)
    j __switch_end_30
__switch_case_33:
    lw $t0, 4($sp)
    li $t1, 6
    add $t0, $t0, $t1
    sw $t0, 32($sp)
    lw $t0, 32($sp)
    sw $t0, 4($sp)
    j __switch_end_30
__switch_case_34:
    lw $t0, 4($sp)
    li $t1, 10
    add $t0, $t0, $t1
    sw $t0, 36($sp)
    lw $t0, 36($sp)
    sw $t0, 4($sp)
    j __switch_end_30
__switch_default_35:
    lw $t0, 4($sp)
    li $t1, 15
    add $t0, $t0, $t1
    sw $t0, 40($sp)
    lw $t0, 40($sp)
    sw $t0, 4($sp)
    j __switch_end_30
__switch_end_30:
    lw $t0, 4($sp)
    move $v0, $t0
    j __return_fn_switch_magic
__return_fn_switch_magic:
    lw $ra, 44($sp)
    addi $sp, $sp, 48
    jr $ra

fn_ternary_test:
    addi $sp, $sp, -28
    sw $ra, 24($sp)

    sw $a0, 0($sp)

    lw $t0, 0($sp)
    li $t1, 10
    slt $t2, $t1, $t0
    sw $t2, 8($sp)
    lw $t0, 8($sp)
    sltu $t1, $zero, $t0
    beq $t1, $zero, __cond_false_36
    lw $t0, 0($sp)
    li $t1, 2
    mul $t0, $t0, $t1
    sw $t0, 12($sp)
    lw $t0, 12($sp)
    sw $t0, 16($sp)
    j __cond_end_37
__cond_false_36:
    lw $t0, 0($sp)
    li $t1, 100
    add $t0, $t0, $t1
    sw $t0, 20($sp)
    lw $t0, 20($sp)
    sw $t0, 16($sp)
__cond_end_37:
    lw $t0, 16($sp)
    sw $t0, 4($sp)
    lw $t0, 4($sp)
    move $v0, $t0
    j __return_fn_ternary_test
__return_fn_ternary_test:
    lw $ra, 24($sp)
    addi $sp, $sp, 28
    jr $ra

fn_bool_mix:
    addi $sp, $sp, -40
    sw $ra, 36($sp)

    sw $a0, 0($sp)
    sw $a1, 4($sp)

    li $t0, 0
    sw $t0, 8($sp)
    lw $t0, 0($sp)
    lw $t1, 4($sp)
    slt $t2, $t1, $t0
    sw $t2, 12($sp)
    lw $t0, 12($sp)
    sltu $t1, $zero, $t0
    beq $t1, $zero, __if_end_38
    li $t0, 1
    sw $t0, 8($sp)
__if_end_38:
    lw $t0, 0($sp)
    li $t1, 0
    slt $t2, $t1, $t0
    sw $t2, 16($sp)
    lw $t0, 8($sp)
    sltu $t1, $zero, $t0
    lw $t2, 16($sp)
    sltu $t3, $zero, $t2
    and $t4, $t1, $t3
    sltu $t4, $zero, $t4
    sw $t4, 20($sp)
    lw $t0, 20($sp)
    sltu $t1, $zero, $t0
    beq $t1, $zero, __if_end_39
    li $t0, 1
    move $v0, $t0
    j __return_fn_bool_mix
__if_end_39:
    lw $t0, 0($sp)
    li $t1, 0
    slt $t2, $t0, $t1
    sw $t2, 24($sp)
    lw $t0, 4($sp)
    li $t1, 0
    slt $t2, $t0, $t1
    sw $t2, 28($sp)
    lw $t0, 24($sp)
    sltu $t1, $zero, $t0
    lw $t2, 28($sp)
    sltu $t3, $zero, $t2
    or $t4, $t1, $t3
    sltu $t4, $zero, $t4
    sw $t4, 32($sp)
    lw $t0, 32($sp)
    sltu $t1, $zero, $t0
    beq $t1, $zero, __if_end_40
    li $t0, 2
    move $v0, $t0
    j __return_fn_bool_mix
__if_end_40:
    li $t0, 3
    move $v0, $t0
    j __return_fn_bool_mix
__return_fn_bool_mix:
    lw $ra, 36($sp)
    addi $sp, $sp, 40
    jr $ra

fn_nested_arrays:
    addi $sp, $sp, -120
    sw $ra, 116($sp)

    # Declared array outer[10]
    # Declared array inner[10]
    li $t0, 0
    sw $t0, 80($sp)
    li $t0, 0
    sw $t0, 84($sp)
__while_start_41:
    lw $t0, 84($sp)
    li $t1, 10
    slt $t2, $t0, $t1
    sw $t2, 88($sp)
    lw $t0, 88($sp)
    sltu $t1, $zero, $t0
    beq $t1, $zero, __while_end_42
    lw $t0, 84($sp)
    lw $t1, 84($sp)
    mul $t0, $t0, $t1
    sw $t0, 92($sp)
    lw $t0, 84($sp)
    # Bounds check for array outer
    bltz $t0, __bounds_error_22
    li $t1, 10
    bge $t0, $t1, __bounds_error_22
    j __bounds_ok_22
__bounds_error_22:
    li $v0, 4
    la $a0, __array_oob_msg
    syscall
    li $v0, 10
    syscall
__bounds_ok_22:
    addi $t2, $sp, 0
    sll $t0, $t0, 2
    add $t2, $t2, $t0
    lw $t3, 92($sp)
    sw $t3, 0($t2)
    lw $t0, 84($sp)
    # Bounds check for array outer
    bltz $t0, __bounds_error_23
    li $t1, 10
    bge $t0, $t1, __bounds_error_23
    j __bounds_ok_23
__bounds_error_23:
    li $v0, 4
    la $a0, __array_oob_msg
    syscall
    li $v0, 10
    syscall
__bounds_ok_23:
    addi $t2, $sp, 0
    sll $t0, $t0, 2
    add $t2, $t2, $t0
    lw $t2, 0($t2)
    sw $t2, 96($sp)
    lw $t0, 96($sp)
    lw $t1, 84($sp)
    sub $t0, $t0, $t1
    sw $t0, 100($sp)
    lw $t0, 84($sp)
    # Bounds check for array inner
    bltz $t0, __bounds_error_24
    li $t1, 10
    bge $t0, $t1, __bounds_error_24
    j __bounds_ok_24
__bounds_error_24:
    li $v0, 4
    la $a0, __array_oob_msg
    syscall
    li $v0, 10
    syscall
__bounds_ok_24:
    addi $t2, $sp, 40
    sll $t0, $t0, 2
    add $t2, $t2, $t0
    lw $t3, 100($sp)
    sw $t3, 0($t2)
    lw $t0, 84($sp)
    # Bounds check for array inner
    bltz $t0, __bounds_error_25
    li $t1, 10
    bge $t0, $t1, __bounds_error_25
    j __bounds_ok_25
__bounds_error_25:
    li $v0, 4
    la $a0, __array_oob_msg
    syscall
    li $v0, 10
    syscall
__bounds_ok_25:
    addi $t2, $sp, 40
    sll $t0, $t0, 2
    add $t2, $t2, $t0
    lw $t2, 0($t2)
    sw $t2, 104($sp)
    lw $t0, 80($sp)
    lw $t1, 104($sp)
    add $t0, $t0, $t1
    sw $t0, 108($sp)
    lw $t0, 108($sp)
    sw $t0, 80($sp)
    lw $t0, 84($sp)
    li $t1, 1
    add $t0, $t0, $t1
    sw $t0, 112($sp)
    lw $t0, 112($sp)
    sw $t0, 84($sp)
    j __while_start_41
__while_end_42:
    lw $t0, 80($sp)
    move $v0, $t0
    j __return_fn_nested_arrays
__return_fn_nested_arrays:
    lw $ra, 116($sp)
    addi $sp, $sp, 120
    jr $ra

fn_cascade:
    addi $sp, $sp, -72
    sw $ra, 68($sp)

    sw $a0, 0($sp)

    lw $t0, 0($sp)
    li $t1, 1
    add $t0, $t0, $t1
    sw $t0, 36($sp)
    lw $t0, 36($sp)
    sw $t0, 4($sp)
    lw $t0, 4($sp)
    li $t1, 2
    mul $t0, $t0, $t1
    sw $t0, 40($sp)
    lw $t0, 40($sp)
    sw $t0, 8($sp)
    lw $t0, 8($sp)
    li $t1, 3
    add $t0, $t0, $t1
    sw $t0, 44($sp)
    lw $t0, 44($sp)
    sw $t0, 12($sp)
    lw $t0, 12($sp)
    li $t1, 4
    mul $t0, $t0, $t1
    sw $t0, 48($sp)
    lw $t0, 48($sp)
    sw $t0, 16($sp)
    lw $t0, 16($sp)
    li $t1, 5
    add $t0, $t0, $t1
    sw $t0, 52($sp)
    lw $t0, 52($sp)
    sw $t0, 20($sp)
    lw $t0, 20($sp)
    li $t1, 6
    mul $t0, $t0, $t1
    sw $t0, 56($sp)
    lw $t0, 56($sp)
    sw $t0, 24($sp)
    lw $t0, 24($sp)
    li $t1, 7
    add $t0, $t0, $t1
    sw $t0, 60($sp)
    lw $t0, 60($sp)
    sw $t0, 28($sp)
    lw $t0, 28($sp)
    li $t1, 8
    mul $t0, $t0, $t1
    sw $t0, 64($sp)
    lw $t0, 64($sp)
    sw $t0, 32($sp)
    lw $t0, 32($sp)
    move $v0, $t0
    j __return_fn_cascade
__return_fn_cascade:
    lw $ra, 68($sp)
    addi $sp, $sp, 72
    jr $ra

fn_mod3:
    addi $sp, $sp, -28
    sw $ra, 24($sp)

    sw $a0, 0($sp)

    lw $t0, 0($sp)
    li $t1, 3
    div $t0, $t1
    mflo $t0
    sw $t0, 12($sp)
    lw $t0, 12($sp)
    sw $t0, 4($sp)
    lw $t0, 4($sp)
    li $t1, 3
    mul $t0, $t0, $t1
    sw $t0, 16($sp)
    lw $t0, 0($sp)
    lw $t1, 16($sp)
    sub $t0, $t0, $t1
    sw $t0, 20($sp)
    lw $t0, 20($sp)
    sw $t0, 8($sp)
    lw $t0, 8($sp)
    move $v0, $t0
    j __return_fn_mod3
__return_fn_mod3:
    lw $ra, 24($sp)
    addi $sp, $sp, 28
    jr $ra

fn_stress_branch:
    addi $sp, $sp, -64
    sw $ra, 60($sp)

    sw $a0, 0($sp)

    li $t0, 0
    sw $t0, 4($sp)
    li $t0, 0
    sw $t0, 8($sp)
__while_start_43:
    lw $t0, 4($sp)
    lw $t1, 0($sp)
    slt $t2, $t0, $t1
    sw $t2, 16($sp)
    lw $t0, 16($sp)
    sltu $t1, $zero, $t0
    beq $t1, $zero, __while_end_44
    lw $t0, 4($sp)
    move $a0, $t0
    jal fn_mod3
    move $t0, $v0
    sw $t0, 20($sp)
    lw $t0, 20($sp)
    sw $t0, 12($sp)
    lw $t0, 12($sp)
    li $t1, 0
    xor $t3, $t0, $t1
    sltiu $t2, $t3, 1
    sw $t2, 24($sp)
    lw $t0, 24($sp)
    sltu $t1, $zero, $t0
    beq $t1, $zero, __if_else_45
    lw $t0, 4($sp)
    li $t1, 2
    mul $t0, $t0, $t1
    sw $t0, 28($sp)
    lw $t0, 8($sp)
    lw $t1, 28($sp)
    add $t0, $t0, $t1
    sw $t0, 32($sp)
    lw $t0, 32($sp)
    sw $t0, 8($sp)
    j __if_end_46
__if_else_45:
    lw $t0, 12($sp)
    li $t1, 1
    xor $t3, $t0, $t1
    sltiu $t2, $t3, 1
    sw $t2, 36($sp)
    lw $t0, 36($sp)
    sltu $t1, $zero, $t0
    beq $t1, $zero, __if_else_47
    lw $t0, 4($sp)
    li $t1, 3
    mul $t0, $t0, $t1
    sw $t0, 40($sp)
    lw $t0, 8($sp)
    lw $t1, 40($sp)
    add $t0, $t0, $t1
    sw $t0, 44($sp)
    lw $t0, 44($sp)
    sw $t0, 8($sp)
    j __if_end_48
__if_else_47:
    lw $t0, 4($sp)
    li $t1, 4
    mul $t0, $t0, $t1
    sw $t0, 48($sp)
    lw $t0, 8($sp)
    lw $t1, 48($sp)
    add $t0, $t0, $t1
    sw $t0, 52($sp)
    lw $t0, 52($sp)
    sw $t0, 8($sp)
__if_end_48:
__if_end_46:
    lw $t0, 4($sp)
    li $t1, 1
    add $t0, $t0, $t1
    sw $t0, 56($sp)
    lw $t0, 56($sp)
    sw $t0, 4($sp)
    j __while_start_43
__while_end_44:
    lw $t0, 8($sp)
    move $v0, $t0
    j __return_fn_stress_branch
__return_fn_stress_branch:
    lw $ra, 60($sp)
    addi $sp, $sp, 64
    jr $ra

fn_mega_stack:
    addi $sp, $sp, -2004
    sw $ra, 2000($sp)

    # Declared array block1[60]
    # Declared array block2[60]
    # Declared array block3[60]
    # Declared array block4[60]
    # Declared array block5[60]
    # Declared array block6[60]
    # Declared array block7[60]
    # Declared array block8[60]
    li $t0, 0
    sw $t0, 1924($sp)
    li $t0, 0
    sw $t0, 1920($sp)
__while_start_49:
    lw $t0, 1920($sp)
    li $t1, 60
    slt $t2, $t0, $t1
    sw $t2, 1928($sp)
    lw $t0, 1928($sp)
    sltu $t1, $zero, $t0
    beq $t1, $zero, __while_end_50
    lw $t0, 1920($sp)
    # Bounds check for array block1
    bltz $t0, __bounds_error_26
    li $t1, 60
    bge $t0, $t1, __bounds_error_26
    j __bounds_ok_26
__bounds_error_26:
    li $v0, 4
    la $a0, __array_oob_msg
    syscall
    li $v0, 10
    syscall
__bounds_ok_26:
    addi $t2, $sp, 0
    sll $t0, $t0, 2
    add $t2, $t2, $t0
    lw $t3, 1920($sp)
    sw $t3, 0($t2)
    lw $t0, 1920($sp)
    # Bounds check for array block1
    bltz $t0, __bounds_error_27
    li $t1, 60
    bge $t0, $t1, __bounds_error_27
    j __bounds_ok_27
__bounds_error_27:
    li $v0, 4
    la $a0, __array_oob_msg
    syscall
    li $v0, 10
    syscall
__bounds_ok_27:
    addi $t2, $sp, 0
    sll $t0, $t0, 2
    add $t2, $t2, $t0
    lw $t2, 0($t2)
    sw $t2, 1932($sp)
    lw $t0, 1932($sp)
    li $t1, 1
    add $t0, $t0, $t1
    sw $t0, 1936($sp)
    lw $t0, 1920($sp)
    # Bounds check for array block2
    bltz $t0, __bounds_error_28
    li $t1, 60
    bge $t0, $t1, __bounds_error_28
    j __bounds_ok_28
__bounds_error_28:
    li $v0, 4
    la $a0, __array_oob_msg
    syscall
    li $v0, 10
    syscall
__bounds_ok_28:
    addi $t2, $sp, 240
    sll $t0, $t0, 2
    add $t2, $t2, $t0
    lw $t3, 1936($sp)
    sw $t3, 0($t2)
    lw $t0, 1920($sp)
    # Bounds check for array block2
    bltz $t0, __bounds_error_29
    li $t1, 60
    bge $t0, $t1, __bounds_error_29
    j __bounds_ok_29
__bounds_error_29:
    li $v0, 4
    la $a0, __array_oob_msg
    syscall
    li $v0, 10
    syscall
__bounds_ok_29:
    addi $t2, $sp, 240
    sll $t0, $t0, 2
    add $t2, $t2, $t0
    lw $t2, 0($t2)
    sw $t2, 1940($sp)
    lw $t0, 1940($sp)
    li $t1, 2
    add $t0, $t0, $t1
    sw $t0, 1944($sp)
    lw $t0, 1920($sp)
    # Bounds check for array block3
    bltz $t0, __bounds_error_30
    li $t1, 60
    bge $t0, $t1, __bounds_error_30
    j __bounds_ok_30
__bounds_error_30:
    li $v0, 4
    la $a0, __array_oob_msg
    syscall
    li $v0, 10
    syscall
__bounds_ok_30:
    addi $t2, $sp, 480
    sll $t0, $t0, 2
    add $t2, $t2, $t0
    lw $t3, 1944($sp)
    sw $t3, 0($t2)
    lw $t0, 1920($sp)
    # Bounds check for array block3
    bltz $t0, __bounds_error_31
    li $t1, 60
    bge $t0, $t1, __bounds_error_31
    j __bounds_ok_31
__bounds_error_31:
    li $v0, 4
    la $a0, __array_oob_msg
    syscall
    li $v0, 10
    syscall
__bounds_ok_31:
    addi $t2, $sp, 480
    sll $t0, $t0, 2
    add $t2, $t2, $t0
    lw $t2, 0($t2)
    sw $t2, 1948($sp)
    lw $t0, 1948($sp)
    li $t1, 3
    add $t0, $t0, $t1
    sw $t0, 1952($sp)
    lw $t0, 1920($sp)
    # Bounds check for array block4
    bltz $t0, __bounds_error_32
    li $t1, 60
    bge $t0, $t1, __bounds_error_32
    j __bounds_ok_32
__bounds_error_32:
    li $v0, 4
    la $a0, __array_oob_msg
    syscall
    li $v0, 10
    syscall
__bounds_ok_32:
    addi $t2, $sp, 720
    sll $t0, $t0, 2
    add $t2, $t2, $t0
    lw $t3, 1952($sp)
    sw $t3, 0($t2)
    lw $t0, 1920($sp)
    # Bounds check for array block4
    bltz $t0, __bounds_error_33
    li $t1, 60
    bge $t0, $t1, __bounds_error_33
    j __bounds_ok_33
__bounds_error_33:
    li $v0, 4
    la $a0, __array_oob_msg
    syscall
    li $v0, 10
    syscall
__bounds_ok_33:
    addi $t2, $sp, 720
    sll $t0, $t0, 2
    add $t2, $t2, $t0
    lw $t2, 0($t2)
    sw $t2, 1956($sp)
    lw $t0, 1956($sp)
    li $t1, 4
    add $t0, $t0, $t1
    sw $t0, 1960($sp)
    lw $t0, 1920($sp)
    # Bounds check for array block5
    bltz $t0, __bounds_error_34
    li $t1, 60
    bge $t0, $t1, __bounds_error_34
    j __bounds_ok_34
__bounds_error_34:
    li $v0, 4
    la $a0, __array_oob_msg
    syscall
    li $v0, 10
    syscall
__bounds_ok_34:
    addi $t2, $sp, 960
    sll $t0, $t0, 2
    add $t2, $t2, $t0
    lw $t3, 1960($sp)
    sw $t3, 0($t2)
    lw $t0, 1920($sp)
    # Bounds check for array block5
    bltz $t0, __bounds_error_35
    li $t1, 60
    bge $t0, $t1, __bounds_error_35
    j __bounds_ok_35
__bounds_error_35:
    li $v0, 4
    la $a0, __array_oob_msg
    syscall
    li $v0, 10
    syscall
__bounds_ok_35:
    addi $t2, $sp, 960
    sll $t0, $t0, 2
    add $t2, $t2, $t0
    lw $t2, 0($t2)
    sw $t2, 1964($sp)
    lw $t0, 1964($sp)
    li $t1, 5
    add $t0, $t0, $t1
    sw $t0, 1968($sp)
    lw $t0, 1920($sp)
    # Bounds check for array block6
    bltz $t0, __bounds_error_36
    li $t1, 60
    bge $t0, $t1, __bounds_error_36
    j __bounds_ok_36
__bounds_error_36:
    li $v0, 4
    la $a0, __array_oob_msg
    syscall
    li $v0, 10
    syscall
__bounds_ok_36:
    addi $t2, $sp, 1200
    sll $t0, $t0, 2
    add $t2, $t2, $t0
    lw $t3, 1968($sp)
    sw $t3, 0($t2)
    lw $t0, 1920($sp)
    # Bounds check for array block6
    bltz $t0, __bounds_error_37
    li $t1, 60
    bge $t0, $t1, __bounds_error_37
    j __bounds_ok_37
__bounds_error_37:
    li $v0, 4
    la $a0, __array_oob_msg
    syscall
    li $v0, 10
    syscall
__bounds_ok_37:
    addi $t2, $sp, 1200
    sll $t0, $t0, 2
    add $t2, $t2, $t0
    lw $t2, 0($t2)
    sw $t2, 1972($sp)
    lw $t0, 1972($sp)
    li $t1, 6
    add $t0, $t0, $t1
    sw $t0, 1976($sp)
    lw $t0, 1920($sp)
    # Bounds check for array block7
    bltz $t0, __bounds_error_38
    li $t1, 60
    bge $t0, $t1, __bounds_error_38
    j __bounds_ok_38
__bounds_error_38:
    li $v0, 4
    la $a0, __array_oob_msg
    syscall
    li $v0, 10
    syscall
__bounds_ok_38:
    addi $t2, $sp, 1440
    sll $t0, $t0, 2
    add $t2, $t2, $t0
    lw $t3, 1976($sp)
    sw $t3, 0($t2)
    lw $t0, 1920($sp)
    # Bounds check for array block7
    bltz $t0, __bounds_error_39
    li $t1, 60
    bge $t0, $t1, __bounds_error_39
    j __bounds_ok_39
__bounds_error_39:
    li $v0, 4
    la $a0, __array_oob_msg
    syscall
    li $v0, 10
    syscall
__bounds_ok_39:
    addi $t2, $sp, 1440
    sll $t0, $t0, 2
    add $t2, $t2, $t0
    lw $t2, 0($t2)
    sw $t2, 1980($sp)
    lw $t0, 1980($sp)
    li $t1, 7
    add $t0, $t0, $t1
    sw $t0, 1984($sp)
    lw $t0, 1920($sp)
    # Bounds check for array block8
    bltz $t0, __bounds_error_40
    li $t1, 60
    bge $t0, $t1, __bounds_error_40
    j __bounds_ok_40
__bounds_error_40:
    li $v0, 4
    la $a0, __array_oob_msg
    syscall
    li $v0, 10
    syscall
__bounds_ok_40:
    addi $t2, $sp, 1680
    sll $t0, $t0, 2
    add $t2, $t2, $t0
    lw $t3, 1984($sp)
    sw $t3, 0($t2)
    lw $t0, 1920($sp)
    # Bounds check for array block8
    bltz $t0, __bounds_error_41
    li $t1, 60
    bge $t0, $t1, __bounds_error_41
    j __bounds_ok_41
__bounds_error_41:
    li $v0, 4
    la $a0, __array_oob_msg
    syscall
    li $v0, 10
    syscall
__bounds_ok_41:
    addi $t2, $sp, 1680
    sll $t0, $t0, 2
    add $t2, $t2, $t0
    lw $t2, 0($t2)
    sw $t2, 1988($sp)
    lw $t0, 1924($sp)
    lw $t1, 1988($sp)
    add $t0, $t0, $t1
    sw $t0, 1992($sp)
    lw $t0, 1992($sp)
    sw $t0, 1924($sp)
    lw $t0, 1920($sp)
    li $t1, 1
    add $t0, $t0, $t1
    sw $t0, 1996($sp)
    lw $t0, 1996($sp)
    sw $t0, 1920($sp)
    j __while_start_49
__while_end_50:
    lw $t0, 1924($sp)
    move $v0, $t0
    j __return_fn_mega_stack
__return_fn_mega_stack:
    lw $ra, 2000($sp)
    addi $sp, $sp, 2004
    jr $ra

main:
    addi $sp, $sp, -1176

    # Declared array arr[100]
    # Declared array mirror[100]
    # Declared array bools[10]
    # Declared array toggles[10]
    li $t0, 0
    sw $t0, 0($sp)
    li $t0, 0
    sw $t0, 4($sp)
    li $t0, 0
    sw $t0, 808($sp)
    li $t0, 0
    sw $t0, 812($sp)
__while_start_51:
    lw $t0, 0($sp)
    li $t1, 100
    slt $t2, $t0, $t1
    sw $t2, 900($sp)
    lw $t0, 900($sp)
    sltu $t1, $zero, $t0
    beq $t1, $zero, __while_end_52
    lw $t0, 0($sp)
    li $t1, 11
    mul $t0, $t0, $t1
    sw $t0, 904($sp)
    lw $t0, 904($sp)
    li $t1, 7
    sub $t0, $t0, $t1
    sw $t0, 908($sp)
    lw $t0, 0($sp)
    # Bounds check for array arr
    bltz $t0, __bounds_error_42
    li $t1, 100
    bge $t0, $t1, __bounds_error_42
    j __bounds_ok_42
__bounds_error_42:
    li $v0, 4
    la $a0, __array_oob_msg
    syscall
    li $v0, 10
    syscall
__bounds_ok_42:
    addi $t2, $sp, 8
    sll $t0, $t0, 2
    add $t2, $t2, $t0
    lw $t3, 908($sp)
    sw $t3, 0($t2)
    li $t0, 99
    lw $t1, 0($sp)
    sub $t0, $t0, $t1
    sw $t0, 912($sp)
    lw $t0, 0($sp)
    # Bounds check for array arr
    bltz $t0, __bounds_error_43
    li $t1, 100
    bge $t0, $t1, __bounds_error_43
    j __bounds_ok_43
__bounds_error_43:
    li $v0, 4
    la $a0, __array_oob_msg
    syscall
    li $v0, 10
    syscall
__bounds_ok_43:
    addi $t2, $sp, 8
    sll $t0, $t0, 2
    add $t2, $t2, $t0
    lw $t2, 0($t2)
    sw $t2, 916($sp)
    lw $t0, 912($sp)
    # Bounds check for array mirror
    bltz $t0, __bounds_error_44
    li $t1, 100
    bge $t0, $t1, __bounds_error_44
    j __bounds_ok_44
__bounds_error_44:
    li $v0, 4
    la $a0, __array_oob_msg
    syscall
    li $v0, 10
    syscall
__bounds_ok_44:
    addi $t2, $sp, 408
    sll $t0, $t0, 2
    add $t2, $t2, $t0
    lw $t3, 916($sp)
    sw $t3, 0($t2)
    lw $t0, 0($sp)
    li $t1, 2
    div $t0, $t1
    mflo $t0
    sw $t0, 920($sp)
    lw $t0, 920($sp)
    li $t1, 2
    mul $t0, $t0, $t1
    sw $t0, 924($sp)
    lw $t0, 924($sp)
    lw $t1, 0($sp)
    xor $t3, $t0, $t1
    sltiu $t2, $t3, 1
    sw $t2, 928($sp)
    lw $t0, 928($sp)
    sltu $t1, $zero, $t0
    beq $t1, $zero, __if_else_53
    lw $t0, 0($sp)
    # Bounds check for array arr
    bltz $t0, __bounds_error_45
    li $t1, 100
    bge $t0, $t1, __bounds_error_45
    j __bounds_ok_45
__bounds_error_45:
    li $v0, 4
    la $a0, __array_oob_msg
    syscall
    li $v0, 10
    syscall
__bounds_ok_45:
    addi $t2, $sp, 8
    sll $t0, $t0, 2
    add $t2, $t2, $t0
    lw $t2, 0($t2)
    sw $t2, 932($sp)
    lw $t0, 808($sp)
    lw $t1, 932($sp)
    add $t0, $t0, $t1
    sw $t0, 936($sp)
    lw $t0, 936($sp)
    sw $t0, 808($sp)
    j __if_end_54
__if_else_53:
    lw $t0, 0($sp)
    # Bounds check for array arr
    bltz $t0, __bounds_error_46
    li $t1, 100
    bge $t0, $t1, __bounds_error_46
    j __bounds_ok_46
__bounds_error_46:
    li $v0, 4
    la $a0, __array_oob_msg
    syscall
    li $v0, 10
    syscall
__bounds_ok_46:
    addi $t2, $sp, 8
    sll $t0, $t0, 2
    add $t2, $t2, $t0
    lw $t2, 0($t2)
    sw $t2, 940($sp)
    lw $t0, 812($sp)
    lw $t1, 940($sp)
    add $t0, $t0, $t1
    sw $t0, 944($sp)
    lw $t0, 944($sp)
    sw $t0, 812($sp)
__if_end_54:
    lw $t0, 0($sp)
    li $t1, 10
    div $t0, $t1
    mflo $t0
    sw $t0, 948($sp)
    lw $t0, 948($sp)
    li $t1, 10
    mul $t0, $t0, $t1
    sw $t0, 952($sp)
    lw $t0, 0($sp)
    lw $t1, 952($sp)
    sub $t0, $t0, $t1
    sw $t0, 956($sp)
    lw $t0, 956($sp)
    sw $t0, 896($sp)
    lw $t0, 0($sp)
    # Bounds check for array arr
    bltz $t0, __bounds_error_47
    li $t1, 100
    bge $t0, $t1, __bounds_error_47
    j __bounds_ok_47
__bounds_error_47:
    li $v0, 4
    la $a0, __array_oob_msg
    syscall
    li $v0, 10
    syscall
__bounds_ok_47:
    addi $t2, $sp, 8
    sll $t0, $t0, 2
    add $t2, $t2, $t0
    lw $t2, 0($t2)
    sw $t2, 960($sp)
    lw $t0, 960($sp)
    li $t1, 0
    slt $t2, $t1, $t0
    sw $t2, 964($sp)
    lw $t0, 964($sp)
    sltu $t1, $zero, $t0
    beq $t1, $zero, __if_else_55
    lw $t0, 896($sp)
    # Bounds check for array toggles
    bltz $t0, __bounds_error_48
    li $t1, 10
    bge $t0, $t1, __bounds_error_48
    j __bounds_ok_48
__bounds_error_48:
    li $v0, 4
    la $a0, __array_oob_msg
    syscall
    li $v0, 10
    syscall
__bounds_ok_48:
    addi $t2, $sp, 856
    sll $t0, $t0, 2
    add $t2, $t2, $t0
    li $t3, 1
    sw $t3, 0($t2)
    j __if_end_56
__if_else_55:
    lw $t0, 896($sp)
    # Bounds check for array toggles
    bltz $t0, __bounds_error_49
    li $t1, 10
    bge $t0, $t1, __bounds_error_49
    j __bounds_ok_49
__bounds_error_49:
    li $v0, 4
    la $a0, __array_oob_msg
    syscall
    li $v0, 10
    syscall
__bounds_ok_49:
    addi $t2, $sp, 856
    sll $t0, $t0, 2
    add $t2, $t2, $t0
    li $t3, 0
    sw $t3, 0($t2)
__if_end_56:
    lw $t0, 0($sp)
    li $t1, 1
    add $t0, $t0, $t1
    sw $t0, 968($sp)
    lw $t0, 968($sp)
    sw $t0, 0($sp)
    j __while_start_51
__while_end_52:
    li $t0, 6
    move $a0, $t0
    jal fn_factorial
    move $t0, $v0
    sw $t0, 972($sp)
    lw $t0, 972($sp)
    sw $t0, globalA
    li $t0, 12
    move $a0, $t0
    jal fn_fib
    move $t0, $v0
    sw $t0, 976($sp)
    lw $t0, 976($sp)
    sw $t0, globalB
    li $t0, 5
    move $a0, $t0
    jal fn_heavy_loop
    move $t0, $v0
    sw $t0, 980($sp)
    li $t0, 0
    # Bounds check for array results
    bltz $t0, __bounds_error_50
    li $t1, 64
    bge $t0, $t1, __bounds_error_50
    j __bounds_ok_50
__bounds_error_50:
    li $v0, 4
    la $a0, __array_oob_msg
    syscall
    li $v0, 10
    syscall
__bounds_ok_50:
    la $t2, results
    sll $t0, $t0, 2
    add $t2, $t2, $t0
    lw $t3, 980($sp)
    sw $t3, 0($t2)
    li $t0, 8
    move $a0, $t0
    jal fn_sum_structs
    move $t0, $v0
    sw $t0, 984($sp)
    li $t0, 1
    # Bounds check for array results
    bltz $t0, __bounds_error_51
    li $t1, 64
    bge $t0, $t1, __bounds_error_51
    j __bounds_ok_51
__bounds_error_51:
    li $v0, 4
    la $a0, __array_oob_msg
    syscall
    li $v0, 10
    syscall
__bounds_ok_51:
    la $t2, results
    sll $t0, $t0, 2
    add $t2, $t2, $t0
    lw $t3, 984($sp)
    sw $t3, 0($t2)
    li $t0, 3
    move $a0, $t0
    jal fn_switch_magic
    move $t0, $v0
    sw $t0, 988($sp)
    li $t0, 2
    # Bounds check for array results
    bltz $t0, __bounds_error_52
    li $t1, 64
    bge $t0, $t1, __bounds_error_52
    j __bounds_ok_52
__bounds_error_52:
    li $v0, 4
    la $a0, __array_oob_msg
    syscall
    li $v0, 10
    syscall
__bounds_ok_52:
    la $t2, results
    sll $t0, $t0, 2
    add $t2, $t2, $t0
    lw $t3, 988($sp)
    sw $t3, 0($t2)
    li $t0, 5
    move $a0, $t0
    jal fn_ternary_test
    move $t0, $v0
    sw $t0, 992($sp)
    li $t0, 3
    # Bounds check for array results
    bltz $t0, __bounds_error_53
    li $t1, 64
    bge $t0, $t1, __bounds_error_53
    j __bounds_ok_53
__bounds_error_53:
    li $v0, 4
    la $a0, __array_oob_msg
    syscall
    li $v0, 10
    syscall
__bounds_ok_53:
    la $t2, results
    sll $t0, $t0, 2
    add $t2, $t2, $t0
    lw $t3, 992($sp)
    sw $t3, 0($t2)
    li $t0, 0
    li $t1, 1
    sub $t0, $t0, $t1
    sw $t0, 996($sp)
    lw $t0, 996($sp)
    move $a0, $t0
    li $t0, 2
    move $a1, $t0
    jal fn_bool_mix
    move $t0, $v0
    sw $t0, 1000($sp)
    li $t0, 4
    # Bounds check for array results
    bltz $t0, __bounds_error_54
    li $t1, 64
    bge $t0, $t1, __bounds_error_54
    j __bounds_ok_54
__bounds_error_54:
    li $v0, 4
    la $a0, __array_oob_msg
    syscall
    li $v0, 10
    syscall
__bounds_ok_54:
    la $t2, results
    sll $t0, $t0, 2
    add $t2, $t2, $t0
    lw $t3, 1000($sp)
    sw $t3, 0($t2)
    jal fn_nested_arrays
    move $t0, $v0
    sw $t0, 1004($sp)
    li $t0, 5
    # Bounds check for array results
    bltz $t0, __bounds_error_55
    li $t1, 64
    bge $t0, $t1, __bounds_error_55
    j __bounds_ok_55
__bounds_error_55:
    li $v0, 4
    la $a0, __array_oob_msg
    syscall
    li $v0, 10
    syscall
__bounds_ok_55:
    la $t2, results
    sll $t0, $t0, 2
    add $t2, $t2, $t0
    lw $t3, 1004($sp)
    sw $t3, 0($t2)
    li $t0, 9
    move $a0, $t0
    jal fn_cascade
    move $t0, $v0
    sw $t0, 1008($sp)
    li $t0, 6
    # Bounds check for array results
    bltz $t0, __bounds_error_56
    li $t1, 64
    bge $t0, $t1, __bounds_error_56
    j __bounds_ok_56
__bounds_error_56:
    li $v0, 4
    la $a0, __array_oob_msg
    syscall
    li $v0, 10
    syscall
__bounds_ok_56:
    la $t2, results
    sll $t0, $t0, 2
    add $t2, $t2, $t0
    lw $t3, 1008($sp)
    sw $t3, 0($t2)
    li $t0, 20
    move $a0, $t0
    jal fn_stress_branch
    move $t0, $v0
    sw $t0, 1012($sp)
    li $t0, 7
    # Bounds check for array results
    bltz $t0, __bounds_error_57
    li $t1, 64
    bge $t0, $t1, __bounds_error_57
    j __bounds_ok_57
__bounds_error_57:
    li $v0, 4
    la $a0, __array_oob_msg
    syscall
    li $v0, 10
    syscall
__bounds_ok_57:
    la $t2, results
    sll $t0, $t0, 2
    add $t2, $t2, $t0
    lw $t3, 1012($sp)
    sw $t3, 0($t2)
    jal fn_mega_stack
    move $t0, $v0
    sw $t0, 1016($sp)
    li $t0, 8
    # Bounds check for array results
    bltz $t0, __bounds_error_58
    li $t1, 64
    bge $t0, $t1, __bounds_error_58
    j __bounds_ok_58
__bounds_error_58:
    li $v0, 4
    la $a0, __array_oob_msg
    syscall
    li $v0, 10
    syscall
__bounds_ok_58:
    la $t2, results
    sll $t0, $t0, 2
    add $t2, $t2, $t0
    lw $t3, 1016($sp)
    sw $t3, 0($t2)
    li $t0, 0
    sw $t0, 0($sp)
__while_start_57:
    lw $t0, 0($sp)
    move $a0, $t0
    lw $t0, 0($sp)
    move $a1, $t0
    jal fn_cascade
    move $t0, $v0
    sw $t0, 1020($sp)
    lw $t0, 1020($sp)
    move $a0, $t0
    jal fn_update_local_node
    move $t0, $v0
    sw $t0, 1024($sp)
    lw $t0, 4($sp)
    lw $t1, 1024($sp)
    add $t0, $t0, $t1
    sw $t0, 1028($sp)
    lw $t0, 1028($sp)
    sw $t0, 4($sp)
    lw $t0, 0($sp)
    li $t1, 1
    add $t0, $t0, $t1
    sw $t0, 1032($sp)
    lw $t0, 1032($sp)
    sw $t0, 0($sp)
    lw $t0, 0($sp)
    move $a0, $t0
    lw $t0, 0($sp)
    move $a1, $t0
    jal fn_cascade
    move $t0, $v0
    sw $t0, 1020($sp)
    lw $t0, 1020($sp)
    move $a0, $t0
    jal fn_update_local_node
    move $t0, $v0
    sw $t0, 1024($sp)
    lw $t0, 4($sp)
    lw $t1, 1024($sp)
    add $t0, $t0, $t1
    sw $t0, 1028($sp)
    lw $t0, 1028($sp)
    sw $t0, 4($sp)
    lw $t0, 0($sp)
    li $t1, 1
    add $t0, $t0, $t1
    sw $t0, 1032($sp)
    lw $t0, 1032($sp)
    sw $t0, 0($sp)
    lw $t0, 0($sp)
    move $a0, $t0
    lw $t0, 0($sp)
    move $a1, $t0
    jal fn_cascade
    move $t0, $v0
    sw $t0, 1020($sp)
    lw $t0, 1020($sp)
    move $a0, $t0
    jal fn_update_local_node
    move $t0, $v0
    sw $t0, 1024($sp)
    lw $t0, 4($sp)
    lw $t1, 1024($sp)
    add $t0, $t0, $t1
    sw $t0, 1028($sp)
    lw $t0, 1028($sp)
    sw $t0, 4($sp)
    lw $t0, 0($sp)
    li $t1, 1
    add $t0, $t0, $t1
    sw $t0, 1032($sp)
    lw $t0, 1032($sp)
    sw $t0, 0($sp)
    lw $t0, 0($sp)
    move $a0, $t0
    lw $t0, 0($sp)
    move $a1, $t0
    jal fn_cascade
    move $t0, $v0
    sw $t0, 1020($sp)
    lw $t0, 1020($sp)
    move $a0, $t0
    jal fn_update_local_node
    move $t0, $v0
    sw $t0, 1024($sp)
    lw $t0, 4($sp)
    lw $t1, 1024($sp)
    add $t0, $t0, $t1
    sw $t0, 1028($sp)
    lw $t0, 1028($sp)
    sw $t0, 4($sp)
    lw $t0, 0($sp)
    li $t1, 1
    add $t0, $t0, $t1
    sw $t0, 1032($sp)
    lw $t0, 1032($sp)
    sw $t0, 0($sp)
__while_end_58:
    li $t0, 0
    sw $t0, 0($sp)
__while_start_59:
    lw $t0, 0($sp)
    li $t1, 10
    slt $t2, $t0, $t1
    sw $t2, 1036($sp)
    lw $t0, 1036($sp)
    sltu $t1, $zero, $t0
    beq $t1, $zero, __while_end_60
    lw $t0, 0($sp)
    li $t1, 1
    add $t0, $t0, $t1
    sw $t0, 1080($sp)
    lw $t0, 1080($sp)
    sw $t0, 1040($sp)
    lw $t0, 1040($sp)
    li $t1, 2
    mul $t0, $t0, $t1
    sw $t0, 1084($sp)
    lw $t0, 1084($sp)
    sw $t0, 1044($sp)
    lw $t0, 1044($sp)
    li $t1, 3
    add $t0, $t0, $t1
    sw $t0, 1088($sp)
    lw $t0, 1088($sp)
    sw $t0, 1048($sp)
    lw $t0, 1048($sp)
    li $t1, 4
    mul $t0, $t0, $t1
    sw $t0, 1092($sp)
    lw $t0, 1092($sp)
    sw $t0, 1052($sp)
    lw $t0, 1052($sp)
    li $t1, 5
    add $t0, $t0, $t1
    sw $t0, 1096($sp)
    lw $t0, 1096($sp)
    sw $t0, 1056($sp)
    lw $t0, 1056($sp)
    li $t1, 6
    mul $t0, $t0, $t1
    sw $t0, 1100($sp)
    lw $t0, 1100($sp)
    sw $t0, 1060($sp)
    lw $t0, 1060($sp)
    li $t1, 7
    add $t0, $t0, $t1
    sw $t0, 1104($sp)
    lw $t0, 1104($sp)
    sw $t0, 1064($sp)
    lw $t0, 1064($sp)
    li $t1, 8
    mul $t0, $t0, $t1
    sw $t0, 1108($sp)
    lw $t0, 1108($sp)
    sw $t0, 1068($sp)
    lw $t0, 1068($sp)
    li $t1, 9
    add $t0, $t0, $t1
    sw $t0, 1112($sp)
    lw $t0, 1112($sp)
    sw $t0, 1072($sp)
    lw $t0, 1072($sp)
    li $t1, 10
    mul $t0, $t0, $t1
    sw $t0, 1116($sp)
    lw $t0, 1116($sp)
    sw $t0, 1076($sp)
    lw $t0, 0($sp)
    # Bounds check for array bools
    bltz $t0, __bounds_error_59
    li $t1, 10
    bge $t0, $t1, __bounds_error_59
    j __bounds_ok_59
__bounds_error_59:
    li $v0, 4
    la $a0, __array_oob_msg
    syscall
    li $v0, 10
    syscall
__bounds_ok_59:
    addi $t2, $sp, 816
    sll $t0, $t0, 2
    add $t2, $t2, $t0
    lw $t3, 1076($sp)
    sw $t3, 0($t2)
    lw $t0, 4($sp)
    lw $t1, 1076($sp)
    add $t0, $t0, $t1
    sw $t0, 1120($sp)
    lw $t0, 1120($sp)
    sw $t0, 4($sp)
    lw $t0, 0($sp)
    li $t1, 1
    add $t0, $t0, $t1
    sw $t0, 1124($sp)
    lw $t0, 1124($sp)
    sw $t0, 0($sp)
    j __while_start_59
__while_end_60:
    li $t0, 0
    sw $t0, 0($sp)
__while_start_61:
    lw $t0, 0($sp)
    li $t1, 9
    slt $t2, $t0, $t1
    sw $t2, 1128($sp)
    lw $t0, 1128($sp)
    sltu $t1, $zero, $t0
    beq $t1, $zero, __while_end_62
    lw $t0, 0($sp)
    move $a0, $t0
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    lw $t0, 0($sp)
    # Bounds check for array results
    bltz $t0, __bounds_error_60
    li $t1, 64
    bge $t0, $t1, __bounds_error_60
    j __bounds_ok_60
__bounds_error_60:
    li $v0, 4
    la $a0, __array_oob_msg
    syscall
    li $v0, 10
    syscall
__bounds_ok_60:
    la $t2, results
    sll $t0, $t0, 2
    add $t2, $t2, $t0
    lw $t2, 0($t2)
    sw $t2, 1132($sp)
    lw $t0, 1132($sp)
    move $a0, $t0
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    lw $t0, 0($sp)
    li $t1, 1
    add $t0, $t0, $t1
    sw $t0, 1136($sp)
    lw $t0, 1136($sp)
    sw $t0, 0($sp)
    j __while_start_61
__while_end_62:
    lw $t0, globalA
    move $a0, $t0
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    lw $t0, globalB
    move $a0, $t0
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    lw $t0, 808($sp)
    move $a0, $t0
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    lw $t0, 812($sp)
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
    li $t0, 0
    # Bounds check for array arr
    bltz $t0, __bounds_error_61
    li $t1, 100
    bge $t0, $t1, __bounds_error_61
    j __bounds_ok_61
__bounds_error_61:
    li $v0, 4
    la $a0, __array_oob_msg
    syscall
    li $v0, 10
    syscall
__bounds_ok_61:
    addi $t2, $sp, 8
    sll $t0, $t0, 2
    add $t2, $t2, $t0
    lw $t2, 0($t2)
    sw $t2, 1140($sp)
    lw $t0, 1140($sp)
    move $a0, $t0
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    li $t0, 99
    # Bounds check for array arr
    bltz $t0, __bounds_error_62
    li $t1, 100
    bge $t0, $t1, __bounds_error_62
    j __bounds_ok_62
__bounds_error_62:
    li $v0, 4
    la $a0, __array_oob_msg
    syscall
    li $v0, 10
    syscall
__bounds_ok_62:
    addi $t2, $sp, 8
    sll $t0, $t0, 2
    add $t2, $t2, $t0
    lw $t2, 0($t2)
    sw $t2, 1144($sp)
    lw $t0, 1144($sp)
    move $a0, $t0
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    li $t0, 0
    # Bounds check for array mirror
    bltz $t0, __bounds_error_63
    li $t1, 100
    bge $t0, $t1, __bounds_error_63
    j __bounds_ok_63
__bounds_error_63:
    li $v0, 4
    la $a0, __array_oob_msg
    syscall
    li $v0, 10
    syscall
__bounds_ok_63:
    addi $t2, $sp, 408
    sll $t0, $t0, 2
    add $t2, $t2, $t0
    lw $t2, 0($t2)
    sw $t2, 1148($sp)
    lw $t0, 1148($sp)
    move $a0, $t0
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    li $t0, 99
    # Bounds check for array mirror
    bltz $t0, __bounds_error_64
    li $t1, 100
    bge $t0, $t1, __bounds_error_64
    j __bounds_ok_64
__bounds_error_64:
    li $v0, 4
    la $a0, __array_oob_msg
    syscall
    li $v0, 10
    syscall
__bounds_ok_64:
    addi $t2, $sp, 408
    sll $t0, $t0, 2
    add $t2, $t2, $t0
    lw $t2, 0($t2)
    sw $t2, 1152($sp)
    lw $t0, 1152($sp)
    move $a0, $t0
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    li $t0, 3
    move $a0, $t0
    jal fn_sum_structs
    move $t0, $v0
    sw $t0, 1156($sp)
    lw $t0, 1156($sp)
    move $a0, $t0
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    li $t0, 3
    move $a0, $t0
    jal fn_heavy_loop
    move $t0, $v0
    sw $t0, 1160($sp)
    lw $t0, 1160($sp)
    move $a0, $t0
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    li $t0, 0
    sw $t0, 0($sp)
__while_start_63:
    lw $t0, 0($sp)
    li $t1, 5
    slt $t2, $t0, $t1
    sw $t2, 1164($sp)
    lw $t0, 1164($sp)
    sltu $t1, $zero, $t0
    beq $t1, $zero, __while_end_64
    lw $t0, 0($sp)
    # Bounds check for array toggles
    bltz $t0, __bounds_error_65
    li $t1, 10
    bge $t0, $t1, __bounds_error_65
    j __bounds_ok_65
__bounds_error_65:
    li $v0, 4
    la $a0, __array_oob_msg
    syscall
    li $v0, 10
    syscall
__bounds_ok_65:
    addi $t2, $sp, 856
    sll $t0, $t0, 2
    add $t2, $t2, $t0
    lw $t2, 0($t2)
    sw $t2, 1168($sp)
    lw $t0, 1168($sp)
    sltu $t1, $zero, $t0
    beq $t1, $zero, __if_else_65
    li $t0, 1
    move $a0, $t0
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    j __if_end_66
__if_else_65:
    li $t0, 0
    move $a0, $t0
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
__if_end_66:
    lw $t0, 0($sp)
    li $t1, 1
    add $t0, $t0, $t1
    sw $t0, 1172($sp)
    lw $t0, 1172($sp)
    sw $t0, 0($sp)
    j __while_start_63
__while_end_64:
    li $t0, 0
    move $v0, $t0
    j __return_main
__return_main:
    addi $sp, $sp, 1176
    li $v0, 10
    syscall

