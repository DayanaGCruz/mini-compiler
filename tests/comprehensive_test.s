.data

__array_oob_msg: .asciiz "Runtime error: array index out of bounds\n"

.align 2
globalCounter: .word 0

.align 2
globalArray: .space 80

.align 2
globalResult: .word 0

.text
.globl main

fn_testArithmetic:
    addi $sp, $sp, -400
    sw $ra, 396($sp)
    sw $a0, 0($sp)
    sw $a1, 4($sp)

    lw $t0, 0($sp)
    lw $t1, 4($sp)
    add $t0, $t0, $t1
    sw $t0, 28($sp)
    lw $t0, 28($sp)
    sw $t0, 8($sp)
    lw $t0, 0($sp)
    lw $t1, 4($sp)
    sub $t0, $t0, $t1
    sw $t0, 32($sp)
    lw $t0, 32($sp)
    sw $t0, 12($sp)
    lw $t0, 0($sp)
    lw $t1, 4($sp)
    mul $t0, $t0, $t1
    sw $t0, 36($sp)
    lw $t0, 36($sp)
    sw $t0, 16($sp)
    lw $t0, 0($sp)
    lw $t1, 4($sp)
    div $t0, $t1
    mflo $t0
    sw $t0, 40($sp)
    lw $t0, 40($sp)
    sw $t0, 20($sp)
    li $t0, 3
    li $t1, 4
    mul $t0, $t0, $t1
    sw $t0, 44($sp)
    li $t0, 2
    lw $t1, 44($sp)
    add $t0, $t0, $t1
    sw $t0, 48($sp)
    lw $t0, 48($sp)
    sw $t0, 24($sp)
    li $t0, 2
    li $t1, 3
    add $t0, $t0, $t1
    sw $t0, 52($sp)
    lw $t0, 52($sp)
    li $t1, 4
    mul $t0, $t0, $t1
    sw $t0, 56($sp)
    lw $t0, 56($sp)
    sw $t0, 24($sp)
    lw $t0, 0($sp)
    lw $t1, 4($sp)
    mul $t0, $t0, $t1
    sw $t0, 60($sp)
    lw $t0, 0($sp)
    lw $t1, 4($sp)
    div $t0, $t1
    mflo $t0
    sw $t0, 64($sp)
    lw $t0, 60($sp)
    lw $t1, 64($sp)
    add $t0, $t0, $t1
    sw $t0, 68($sp)
    lw $t0, 68($sp)
    lw $t1, 0($sp)
    sub $t0, $t0, $t1
    sw $t0, 72($sp)
    lw $t0, 72($sp)
    lw $t1, 4($sp)
    add $t0, $t0, $t1
    sw $t0, 76($sp)
    lw $t0, 76($sp)
    sw $t0, 24($sp)
    lw $t0, 8($sp)
    lw $t1, 12($sp)
    add $t0, $t0, $t1
    sw $t0, 80($sp)
    lw $t0, 80($sp)
    lw $t1, 16($sp)
    add $t0, $t0, $t1
    sw $t0, 84($sp)
    lw $t0, 84($sp)
    lw $t1, 20($sp)
    add $t0, $t0, $t1
    sw $t0, 88($sp)
    lw $t0, 88($sp)
    move $v0, $t0
    j __return_fn_testArithmetic
__return_fn_testArithmetic:
    lw $ra, 396($sp)
    addi $sp, $sp, 400
    jr $ra

fn_testRelational:
    addi $sp, $sp, -400
    sw $ra, 396($sp)
    sw $a0, 0($sp)
    sw $a1, 4($sp)

    li $t0, 0
    sw $t0, 8($sp)
    lw $t0, 0($sp)
    lw $t1, 4($sp)
    slt $t2, $t0, $t1
    sw $t2, 12($sp)
    lw $t0, 12($sp)
    sltu $t1, $zero, $t0
    beq $t1, $zero, __if_end_0
    lw $t0, 8($sp)
    li $t1, 1
    add $t0, $t0, $t1
    sw $t0, 16($sp)
    lw $t0, 16($sp)
    sw $t0, 8($sp)
__if_end_0:
    lw $t0, 0($sp)
    lw $t1, 4($sp)
    slt $t2, $t1, $t0
    xori $t2, $t2, 1
    sw $t2, 20($sp)
    lw $t0, 20($sp)
    sltu $t1, $zero, $t0
    beq $t1, $zero, __if_end_1
    lw $t0, 8($sp)
    li $t1, 10
    add $t0, $t0, $t1
    sw $t0, 24($sp)
    lw $t0, 24($sp)
    sw $t0, 8($sp)
__if_end_1:
    lw $t0, 0($sp)
    lw $t1, 4($sp)
    slt $t2, $t1, $t0
    sw $t2, 28($sp)
    lw $t0, 28($sp)
    sltu $t1, $zero, $t0
    beq $t1, $zero, __if_end_2
    lw $t0, 8($sp)
    li $t1, 100
    add $t0, $t0, $t1
    sw $t0, 32($sp)
    lw $t0, 32($sp)
    sw $t0, 8($sp)
__if_end_2:
    lw $t0, 0($sp)
    lw $t1, 4($sp)
    slt $t2, $t0, $t1
    xori $t2, $t2, 1
    sw $t2, 36($sp)
    lw $t0, 36($sp)
    sltu $t1, $zero, $t0
    beq $t1, $zero, __if_end_3
    lw $t0, 8($sp)
    li $t1, 1000
    add $t0, $t0, $t1
    sw $t0, 40($sp)
    lw $t0, 40($sp)
    sw $t0, 8($sp)
__if_end_3:
    lw $t0, 0($sp)
    lw $t1, 4($sp)
    xor $t3, $t0, $t1
    sltiu $t2, $t3, 1
    sw $t2, 44($sp)
    lw $t0, 44($sp)
    sltu $t1, $zero, $t0
    beq $t1, $zero, __if_end_4
    lw $t0, 8($sp)
    li $t1, 10000
    add $t0, $t0, $t1
    sw $t0, 48($sp)
    lw $t0, 48($sp)
    sw $t0, 8($sp)
__if_end_4:
    lw $t0, 0($sp)
    lw $t1, 4($sp)
    xor $t2, $t0, $t1
    sltu $t2, $zero, $t2
    sw $t2, 52($sp)
    lw $t0, 52($sp)
    sltu $t1, $zero, $t0
    beq $t1, $zero, __if_end_5
    lw $t0, 8($sp)
    li $t1, 100000
    add $t0, $t0, $t1
    sw $t0, 56($sp)
    lw $t0, 56($sp)
    sw $t0, 8($sp)
__if_end_5:
    lw $t0, 8($sp)
    move $v0, $t0
    j __return_fn_testRelational
__return_fn_testRelational:
    lw $ra, 396($sp)
    addi $sp, $sp, 400
    jr $ra

fn_testIfElse:
    addi $sp, $sp, -400
    sw $ra, 396($sp)
    sw $a0, 0($sp)

    lw $t0, 0($sp)
    li $t1, 0
    slt $t2, $t1, $t0
    sw $t2, 8($sp)
    lw $t0, 8($sp)
    sltu $t1, $zero, $t0
    beq $t1, $zero, __if_end_6
    li $t0, 1
    sw $t0, 4($sp)
__if_end_6:
    lw $t0, 0($sp)
    li $t1, 0
    slt $t2, $t0, $t1
    sw $t2, 12($sp)
    lw $t0, 12($sp)
    sltu $t1, $zero, $t0
    beq $t1, $zero, __if_else_7
    li $t0, 0
    li $t1, 1
    sub $t0, $t0, $t1
    sw $t0, 16($sp)
    lw $t0, 16($sp)
    sw $t0, 4($sp)
    j __if_end_8
__if_else_7:
    li $t0, 0
    sw $t0, 4($sp)
__if_end_8:
    lw $t0, 0($sp)
    li $t1, 100
    slt $t2, $t1, $t0
    sw $t2, 20($sp)
    lw $t0, 20($sp)
    sltu $t1, $zero, $t0
    beq $t1, $zero, __if_else_9
    lw $t0, 0($sp)
    li $t1, 200
    slt $t2, $t1, $t0
    sw $t2, 24($sp)
    lw $t0, 24($sp)
    sltu $t1, $zero, $t0
    beq $t1, $zero, __if_else_11
    li $t0, 200
    sw $t0, 4($sp)
    j __if_end_12
__if_else_11:
    li $t0, 100
    sw $t0, 4($sp)
__if_end_12:
    j __if_end_10
__if_else_9:
    lw $t0, 0($sp)
    li $t1, 50
    slt $t2, $t1, $t0
    sw $t2, 28($sp)
    lw $t0, 28($sp)
    sltu $t1, $zero, $t0
    beq $t1, $zero, __if_else_13
    li $t0, 50
    sw $t0, 4($sp)
    j __if_end_14
__if_else_13:
    li $t0, 0
    sw $t0, 4($sp)
__if_end_14:
__if_end_10:
    lw $t0, 4($sp)
    move $v0, $t0
    j __return_fn_testIfElse
__return_fn_testIfElse:
    lw $ra, 396($sp)
    addi $sp, $sp, 400
    jr $ra

fn_testWhileLoop:
    addi $sp, $sp, -400
    sw $ra, 396($sp)
    sw $a0, 0($sp)

    li $t0, 0
    sw $t0, 4($sp)
    li $t0, 1
    sw $t0, 8($sp)
__while_start_15:
    lw $t0, 8($sp)
    lw $t1, 0($sp)
    slt $t2, $t1, $t0
    xori $t2, $t2, 1
    sw $t2, 12($sp)
    lw $t0, 12($sp)
    sltu $t1, $zero, $t0
    beq $t1, $zero, __while_end_16
    lw $t0, 4($sp)
    lw $t1, 8($sp)
    add $t0, $t0, $t1
    sw $t0, 16($sp)
    lw $t0, 16($sp)
    sw $t0, 4($sp)
    lw $t0, 8($sp)
    li $t1, 1
    add $t0, $t0, $t1
    sw $t0, 20($sp)
    lw $t0, 20($sp)
    sw $t0, 8($sp)
    j __while_start_15
__while_end_16:
    lw $t0, 4($sp)
    move $v0, $t0
    j __return_fn_testWhileLoop
__return_fn_testWhileLoop:
    lw $ra, 396($sp)
    addi $sp, $sp, 400
    jr $ra

fn_testNestedLoops:
    addi $sp, $sp, -400
    sw $ra, 396($sp)
    sw $a0, 0($sp)
    sw $a1, 4($sp)

    li $t0, 0
    sw $t0, 8($sp)
    li $t0, 0
    sw $t0, 12($sp)
__while_start_17:
    lw $t0, 12($sp)
    lw $t1, 0($sp)
    slt $t2, $t0, $t1
    sw $t2, 20($sp)
    lw $t0, 20($sp)
    sltu $t1, $zero, $t0
    beq $t1, $zero, __while_end_18
    li $t0, 0
    sw $t0, 16($sp)
__while_start_19:
    lw $t0, 8($sp)
    li $t1, 1
    add $t0, $t0, $t1
    sw $t0, 24($sp)
    lw $t0, 24($sp)
    sw $t0, 8($sp)
    lw $t0, 16($sp)
    li $t1, 1
    add $t0, $t0, $t1
    sw $t0, 28($sp)
    lw $t0, 28($sp)
    sw $t0, 16($sp)
    lw $t0, 8($sp)
    li $t1, 1
    add $t0, $t0, $t1
    sw $t0, 24($sp)
    lw $t0, 24($sp)
    sw $t0, 8($sp)
    lw $t0, 16($sp)
    li $t1, 1
    add $t0, $t0, $t1
    sw $t0, 28($sp)
    lw $t0, 28($sp)
    sw $t0, 16($sp)
    lw $t0, 8($sp)
    li $t1, 1
    add $t0, $t0, $t1
    sw $t0, 24($sp)
    lw $t0, 24($sp)
    sw $t0, 8($sp)
    lw $t0, 16($sp)
    li $t1, 1
    add $t0, $t0, $t1
    sw $t0, 28($sp)
    lw $t0, 28($sp)
    sw $t0, 16($sp)
    lw $t0, 8($sp)
    li $t1, 1
    add $t0, $t0, $t1
    sw $t0, 24($sp)
    lw $t0, 24($sp)
    sw $t0, 8($sp)
    lw $t0, 16($sp)
    li $t1, 1
    add $t0, $t0, $t1
    sw $t0, 28($sp)
    lw $t0, 28($sp)
    sw $t0, 16($sp)
    lw $t0, 8($sp)
    li $t1, 1
    add $t0, $t0, $t1
    sw $t0, 24($sp)
    lw $t0, 24($sp)
    sw $t0, 8($sp)
    lw $t0, 16($sp)
    li $t1, 1
    add $t0, $t0, $t1
    sw $t0, 28($sp)
    lw $t0, 28($sp)
    sw $t0, 16($sp)
__while_end_20:
    lw $t0, 12($sp)
    li $t1, 1
    add $t0, $t0, $t1
    sw $t0, 32($sp)
    lw $t0, 32($sp)
    sw $t0, 12($sp)
    j __while_start_17
__while_end_18:
    lw $t0, 8($sp)
    move $v0, $t0
    j __return_fn_testNestedLoops
__return_fn_testNestedLoops:
    lw $ra, 396($sp)
    addi $sp, $sp, 400
    jr $ra

fn_testArrayOperations:
    addi $sp, $sp, -400
    sw $ra, 396($sp)
    sw $a0, 0($sp)
    sw $a1, 4($sp)

    li $t0, 0
    sw $t0, 8($sp)
__while_start_21:
    lw $t0, 8($sp)
    lw $t1, 4($sp)
    slt $t2, $t0, $t1
    sw $t2, 12($sp)
    lw $t0, 12($sp)
    sltu $t1, $zero, $t0
    beq $t1, $zero, __while_end_22
    lw $t0, 8($sp)
    li $t1, 2
    mul $t0, $t0, $t1
    sw $t0, 16($sp)
    lw $t0, 8($sp)
    lw $t1, 0($sp)
    sll $t0, $t0, 2
    add $t1, $t1, $t0
    lw $t2, 16($sp)
    sw $t2, 0($t1)
    lw $t0, 8($sp)
    li $t1, 1
    add $t0, $t0, $t1
    sw $t0, 20($sp)
    lw $t0, 20($sp)
    sw $t0, 8($sp)
    j __while_start_21
__while_end_22:
    li $t0, 0
    sw $t0, 8($sp)
__while_start_23:
    lw $t0, 8($sp)
    lw $t1, 4($sp)
    slt $t2, $t0, $t1
    sw $t2, 24($sp)
    lw $t0, 24($sp)
    sltu $t1, $zero, $t0
    beq $t1, $zero, __while_end_24
    lw $t0, 8($sp)
    lw $t1, 0($sp)
    sll $t0, $t0, 2
    add $t1, $t1, $t0
    lw $t1, 0($t1)
    sw $t1, 28($sp)
    lw $t0, 28($sp)
    li $t1, 1
    add $t0, $t0, $t1
    sw $t0, 32($sp)
    lw $t0, 8($sp)
    lw $t1, 0($sp)
    sll $t0, $t0, 2
    add $t1, $t1, $t0
    lw $t2, 32($sp)
    sw $t2, 0($t1)
    lw $t0, 8($sp)
    li $t1, 1
    add $t0, $t0, $t1
    sw $t0, 36($sp)
    lw $t0, 36($sp)
    sw $t0, 8($sp)
    j __while_start_23
__while_end_24:
__return_fn_testArrayOperations:
    lw $ra, 396($sp)
    addi $sp, $sp, 400
    jr $ra

fn_sumArray:
    addi $sp, $sp, -400
    sw $ra, 396($sp)
    sw $a0, 0($sp)
    sw $a1, 4($sp)

    li $t0, 0
    sw $t0, 8($sp)
    li $t0, 0
    sw $t0, 12($sp)
__while_start_25:
    lw $t0, 12($sp)
    lw $t1, 4($sp)
    slt $t2, $t0, $t1
    sw $t2, 16($sp)
    lw $t0, 16($sp)
    sltu $t1, $zero, $t0
    beq $t1, $zero, __while_end_26
    lw $t0, 12($sp)
    lw $t1, 0($sp)
    sll $t0, $t0, 2
    add $t1, $t1, $t0
    lw $t1, 0($t1)
    sw $t1, 20($sp)
    lw $t0, 8($sp)
    lw $t1, 20($sp)
    add $t0, $t0, $t1
    sw $t0, 24($sp)
    lw $t0, 24($sp)
    sw $t0, 8($sp)
    lw $t0, 12($sp)
    li $t1, 1
    add $t0, $t0, $t1
    sw $t0, 28($sp)
    lw $t0, 28($sp)
    sw $t0, 12($sp)
    j __while_start_25
__while_end_26:
    lw $t0, 8($sp)
    move $v0, $t0
    j __return_fn_sumArray
__return_fn_sumArray:
    lw $ra, 396($sp)
    addi $sp, $sp, 400
    jr $ra

fn_factorial:
    addi $sp, $sp, -400
    sw $ra, 396($sp)
    sw $a0, 0($sp)

    lw $t0, 0($sp)
    li $t1, 1
    slt $t2, $t1, $t0
    xori $t2, $t2, 1
    sw $t2, 8($sp)
    lw $t0, 8($sp)
    sltu $t1, $zero, $t0
    beq $t1, $zero, __if_else_27
    li $t0, 1
    sw $t0, 4($sp)
    j __if_end_28
__if_else_27:
    lw $t0, 0($sp)
    li $t1, 1
    sub $t0, $t0, $t1
    sw $t0, 12($sp)
    lw $t0, 12($sp)
    move $a0, $t0
    jal fn_factorial
    move $t0, $v0
    sw $t0, 16($sp)
    lw $t0, 0($sp)
    lw $t1, 16($sp)
    mul $t0, $t0, $t1
    sw $t0, 20($sp)
    lw $t0, 20($sp)
    sw $t0, 4($sp)
__if_end_28:
    lw $t0, 4($sp)
    move $v0, $t0
    j __return_fn_factorial
__return_fn_factorial:
    lw $ra, 396($sp)
    addi $sp, $sp, 400
    jr $ra

fn_fibonacci:
    addi $sp, $sp, -400
    sw $ra, 396($sp)
    sw $a0, 0($sp)

    lw $t0, 0($sp)
    li $t1, 1
    slt $t2, $t1, $t0
    xori $t2, $t2, 1
    sw $t2, 8($sp)
    lw $t0, 8($sp)
    sltu $t1, $zero, $t0
    beq $t1, $zero, __if_else_29
    lw $t0, 0($sp)
    sw $t0, 4($sp)
    j __if_end_30
__if_else_29:
    lw $t0, 0($sp)
    li $t1, 1
    sub $t0, $t0, $t1
    sw $t0, 12($sp)
    lw $t0, 12($sp)
    move $a0, $t0
    jal fn_fibonacci
    move $t0, $v0
    sw $t0, 16($sp)
    lw $t0, 0($sp)
    li $t1, 2
    sub $t0, $t0, $t1
    sw $t0, 20($sp)
    lw $t0, 20($sp)
    move $a0, $t0
    jal fn_fibonacci
    move $t0, $v0
    sw $t0, 24($sp)
    lw $t0, 16($sp)
    lw $t1, 24($sp)
    add $t0, $t0, $t1
    sw $t0, 28($sp)
    lw $t0, 28($sp)
    sw $t0, 4($sp)
__if_end_30:
    lw $t0, 4($sp)
    move $v0, $t0
    j __return_fn_fibonacci
__return_fn_fibonacci:
    lw $ra, 396($sp)
    addi $sp, $sp, 400
    jr $ra

fn_power:
    addi $sp, $sp, -400
    sw $ra, 396($sp)
    sw $a0, 0($sp)
    sw $a1, 4($sp)

    lw $t0, 4($sp)
    li $t1, 0
    xor $t3, $t0, $t1
    sltiu $t2, $t3, 1
    sw $t2, 12($sp)
    lw $t0, 12($sp)
    sltu $t1, $zero, $t0
    beq $t1, $zero, __if_else_31
    li $t0, 1
    sw $t0, 8($sp)
    j __if_end_32
__if_else_31:
    lw $t0, 0($sp)
    move $a0, $t0
    lw $t0, 4($sp)
    li $t1, 1
    sub $t0, $t0, $t1
    sw $t0, 16($sp)
    lw $t0, 16($sp)
    move $a1, $t0
    jal fn_power
    move $t0, $v0
    sw $t0, 20($sp)
    lw $t0, 0($sp)
    lw $t1, 20($sp)
    mul $t0, $t0, $t1
    sw $t0, 24($sp)
    lw $t0, 24($sp)
    sw $t0, 8($sp)
__if_end_32:
    lw $t0, 8($sp)
    move $v0, $t0
    j __return_fn_power
__return_fn_power:
    lw $ra, 396($sp)
    addi $sp, $sp, 400
    jr $ra

fn_gcd:
    addi $sp, $sp, -400
    sw $ra, 396($sp)
    sw $a0, 0($sp)
    sw $a1, 4($sp)

__while_start_33:
    lw $t0, 4($sp)
    li $t1, 0
    xor $t2, $t0, $t1
    sltu $t2, $zero, $t2
    sw $t2, 12($sp)
    lw $t0, 12($sp)
    sltu $t1, $zero, $t0
    beq $t1, $zero, __while_end_34
    lw $t0, 0($sp)
    lw $t1, 4($sp)
    div $t0, $t1
    mflo $t0
    sw $t0, 16($sp)
    lw $t0, 16($sp)
    lw $t1, 4($sp)
    mul $t0, $t0, $t1
    sw $t0, 20($sp)
    lw $t0, 0($sp)
    lw $t1, 20($sp)
    sub $t0, $t0, $t1
    sw $t0, 24($sp)
    lw $t0, 24($sp)
    sw $t0, 8($sp)
    lw $t0, 4($sp)
    sw $t0, 0($sp)
    lw $t0, 8($sp)
    sw $t0, 4($sp)
    j __while_start_33
__while_end_34:
    lw $t0, 0($sp)
    move $v0, $t0
    j __return_fn_gcd
__return_fn_gcd:
    lw $ra, 396($sp)
    addi $sp, $sp, 400
    jr $ra

fn_linearSearch:
    addi $sp, $sp, -400
    sw $ra, 396($sp)
    sw $a0, 0($sp)
    sw $a1, 4($sp)
    sw $a2, 8($sp)

    li $t0, 0
    sw $t0, 12($sp)
    li $t0, 0
    li $t1, 1
    sub $t0, $t0, $t1
    sw $t0, 20($sp)
    lw $t0, 20($sp)
    sw $t0, 16($sp)
__while_start_35:
    lw $t0, 12($sp)
    lw $t1, 4($sp)
    slt $t2, $t0, $t1
    sw $t2, 24($sp)
    lw $t0, 24($sp)
    sltu $t1, $zero, $t0
    beq $t1, $zero, __while_end_36
    lw $t0, 12($sp)
    lw $t1, 0($sp)
    sll $t0, $t0, 2
    add $t1, $t1, $t0
    lw $t1, 0($t1)
    sw $t1, 28($sp)
    lw $t0, 28($sp)
    lw $t1, 8($sp)
    xor $t3, $t0, $t1
    sltiu $t2, $t3, 1
    sw $t2, 32($sp)
    lw $t0, 32($sp)
    sltu $t1, $zero, $t0
    beq $t1, $zero, __if_else_37
    lw $t0, 12($sp)
    sw $t0, 16($sp)
    lw $t0, 4($sp)
    sw $t0, 12($sp)
    j __if_end_38
__if_else_37:
    lw $t0, 12($sp)
    li $t1, 1
    add $t0, $t0, $t1
    sw $t0, 36($sp)
    lw $t0, 36($sp)
    sw $t0, 12($sp)
__if_end_38:
    j __while_start_35
__while_end_36:
    lw $t0, 16($sp)
    move $v0, $t0
    j __return_fn_linearSearch
__return_fn_linearSearch:
    lw $ra, 396($sp)
    addi $sp, $sp, 400
    jr $ra

fn_bubbleSort:
    addi $sp, $sp, -400
    sw $ra, 396($sp)
    sw $a0, 0($sp)
    sw $a1, 4($sp)

    li $t0, 0
    sw $t0, 8($sp)
__while_start_39:
    lw $t0, 4($sp)
    li $t1, 1
    sub $t0, $t0, $t1
    sw $t0, 20($sp)
    lw $t0, 8($sp)
    lw $t1, 20($sp)
    slt $t2, $t0, $t1
    sw $t2, 24($sp)
    lw $t0, 24($sp)
    sltu $t1, $zero, $t0
    beq $t1, $zero, __while_end_40
    li $t0, 0
    sw $t0, 12($sp)
__while_start_41:
    lw $t0, 4($sp)
    lw $t1, 8($sp)
    sub $t0, $t0, $t1
    sw $t0, 28($sp)
    lw $t0, 28($sp)
    li $t1, 1
    sub $t0, $t0, $t1
    sw $t0, 32($sp)
    lw $t0, 12($sp)
    lw $t1, 32($sp)
    slt $t2, $t0, $t1
    sw $t2, 36($sp)
    lw $t0, 36($sp)
    sltu $t1, $zero, $t0
    beq $t1, $zero, __while_end_42
    lw $t0, 12($sp)
    lw $t1, 0($sp)
    sll $t0, $t0, 2
    add $t1, $t1, $t0
    lw $t1, 0($t1)
    sw $t1, 40($sp)
    lw $t0, 12($sp)
    li $t1, 1
    add $t0, $t0, $t1
    sw $t0, 44($sp)
    lw $t0, 44($sp)
    lw $t1, 0($sp)
    sll $t0, $t0, 2
    add $t1, $t1, $t0
    lw $t1, 0($t1)
    sw $t1, 48($sp)
    lw $t0, 40($sp)
    lw $t1, 48($sp)
    slt $t2, $t1, $t0
    sw $t2, 52($sp)
    lw $t0, 52($sp)
    sltu $t1, $zero, $t0
    beq $t1, $zero, __if_end_43
    lw $t0, 12($sp)
    lw $t1, 0($sp)
    sll $t0, $t0, 2
    add $t1, $t1, $t0
    lw $t1, 0($t1)
    sw $t1, 56($sp)
    lw $t0, 56($sp)
    sw $t0, 16($sp)
    lw $t0, 12($sp)
    li $t1, 1
    add $t0, $t0, $t1
    sw $t0, 60($sp)
    lw $t0, 60($sp)
    lw $t1, 0($sp)
    sll $t0, $t0, 2
    add $t1, $t1, $t0
    lw $t1, 0($t1)
    sw $t1, 64($sp)
    lw $t0, 12($sp)
    lw $t1, 0($sp)
    sll $t0, $t0, 2
    add $t1, $t1, $t0
    lw $t2, 64($sp)
    sw $t2, 0($t1)
    lw $t0, 12($sp)
    li $t1, 1
    add $t0, $t0, $t1
    sw $t0, 68($sp)
    lw $t0, 68($sp)
    lw $t1, 0($sp)
    sll $t0, $t0, 2
    add $t1, $t1, $t0
    lw $t2, 16($sp)
    sw $t2, 0($t1)
__if_end_43:
    lw $t0, 12($sp)
    li $t1, 1
    add $t0, $t0, $t1
    sw $t0, 72($sp)
    lw $t0, 72($sp)
    sw $t0, 12($sp)
    j __while_start_41
__while_end_42:
    lw $t0, 8($sp)
    li $t1, 1
    add $t0, $t0, $t1
    sw $t0, 76($sp)
    lw $t0, 76($sp)
    sw $t0, 8($sp)
    j __while_start_39
__while_end_40:
__return_fn_bubbleSort:
    lw $ra, 396($sp)
    addi $sp, $sp, 400
    jr $ra

fn_findMax:
    addi $sp, $sp, -400
    sw $ra, 396($sp)
    sw $a0, 0($sp)
    sw $a1, 4($sp)

    li $t0, 0
    lw $t1, 0($sp)
    sll $t0, $t0, 2
    add $t1, $t1, $t0
    lw $t1, 0($t1)
    sw $t1, 16($sp)
    lw $t0, 16($sp)
    sw $t0, 8($sp)
    li $t0, 1
    sw $t0, 12($sp)
__while_start_44:
    lw $t0, 12($sp)
    lw $t1, 4($sp)
    slt $t2, $t0, $t1
    sw $t2, 20($sp)
    lw $t0, 20($sp)
    sltu $t1, $zero, $t0
    beq $t1, $zero, __while_end_45
    lw $t0, 12($sp)
    lw $t1, 0($sp)
    sll $t0, $t0, 2
    add $t1, $t1, $t0
    lw $t1, 0($t1)
    sw $t1, 24($sp)
    lw $t0, 24($sp)
    lw $t1, 8($sp)
    slt $t2, $t1, $t0
    sw $t2, 28($sp)
    lw $t0, 28($sp)
    sltu $t1, $zero, $t0
    beq $t1, $zero, __if_end_46
    lw $t0, 12($sp)
    lw $t1, 0($sp)
    sll $t0, $t0, 2
    add $t1, $t1, $t0
    lw $t1, 0($t1)
    sw $t1, 32($sp)
    lw $t0, 32($sp)
    sw $t0, 8($sp)
__if_end_46:
    lw $t0, 12($sp)
    li $t1, 1
    add $t0, $t0, $t1
    sw $t0, 36($sp)
    lw $t0, 36($sp)
    sw $t0, 12($sp)
    j __while_start_44
__while_end_45:
    lw $t0, 8($sp)
    move $v0, $t0
    j __return_fn_findMax
__return_fn_findMax:
    lw $ra, 396($sp)
    addi $sp, $sp, 400
    jr $ra

fn_findMin:
    addi $sp, $sp, -400
    sw $ra, 396($sp)
    sw $a0, 0($sp)
    sw $a1, 4($sp)

    li $t0, 0
    lw $t1, 0($sp)
    sll $t0, $t0, 2
    add $t1, $t1, $t0
    lw $t1, 0($t1)
    sw $t1, 16($sp)
    lw $t0, 16($sp)
    sw $t0, 8($sp)
    li $t0, 1
    sw $t0, 12($sp)
__while_start_47:
    lw $t0, 12($sp)
    lw $t1, 4($sp)
    slt $t2, $t0, $t1
    sw $t2, 20($sp)
    lw $t0, 20($sp)
    sltu $t1, $zero, $t0
    beq $t1, $zero, __while_end_48
    lw $t0, 12($sp)
    lw $t1, 0($sp)
    sll $t0, $t0, 2
    add $t1, $t1, $t0
    lw $t1, 0($t1)
    sw $t1, 24($sp)
    lw $t0, 24($sp)
    lw $t1, 8($sp)
    slt $t2, $t0, $t1
    sw $t2, 28($sp)
    lw $t0, 28($sp)
    sltu $t1, $zero, $t0
    beq $t1, $zero, __if_end_49
    lw $t0, 12($sp)
    lw $t1, 0($sp)
    sll $t0, $t0, 2
    add $t1, $t1, $t0
    lw $t1, 0($t1)
    sw $t1, 32($sp)
    lw $t0, 32($sp)
    sw $t0, 8($sp)
__if_end_49:
    lw $t0, 12($sp)
    li $t1, 1
    add $t0, $t0, $t1
    sw $t0, 36($sp)
    lw $t0, 36($sp)
    sw $t0, 12($sp)
    j __while_start_47
__while_end_48:
    lw $t0, 8($sp)
    move $v0, $t0
    j __return_fn_findMin
__return_fn_findMin:
    lw $ra, 396($sp)
    addi $sp, $sp, 400
    jr $ra

fn_isPrime:
    addi $sp, $sp, -400
    sw $ra, 396($sp)
    sw $a0, 0($sp)

    lw $t0, 0($sp)
    li $t1, 1
    slt $t2, $t1, $t0
    xori $t2, $t2, 1
    sw $t2, 12($sp)
    lw $t0, 12($sp)
    sltu $t1, $zero, $t0
    beq $t1, $zero, __if_else_50
    li $t0, 0
    sw $t0, 8($sp)
    j __if_end_51
__if_else_50:
    li $t0, 1
    sw $t0, 8($sp)
    li $t0, 2
    sw $t0, 4($sp)
__while_start_52:
    lw $t0, 4($sp)
    lw $t1, 0($sp)
    slt $t2, $t0, $t1
    sw $t2, 16($sp)
    lw $t0, 16($sp)
    sltu $t1, $zero, $t0
    beq $t1, $zero, __while_end_53
    lw $t0, 0($sp)
    lw $t1, 4($sp)
    div $t0, $t1
    mflo $t0
    sw $t0, 20($sp)
    lw $t0, 20($sp)
    lw $t1, 4($sp)
    mul $t0, $t0, $t1
    sw $t0, 24($sp)
    lw $t0, 24($sp)
    lw $t1, 0($sp)
    xor $t3, $t0, $t1
    sltiu $t2, $t3, 1
    sw $t2, 28($sp)
    lw $t0, 28($sp)
    sltu $t1, $zero, $t0
    beq $t1, $zero, __if_else_54
    li $t0, 0
    sw $t0, 8($sp)
    lw $t0, 0($sp)
    sw $t0, 4($sp)
    j __if_end_55
__if_else_54:
    lw $t0, 4($sp)
    li $t1, 1
    add $t0, $t0, $t1
    sw $t0, 32($sp)
    lw $t0, 32($sp)
    sw $t0, 4($sp)
__if_end_55:
    j __while_start_52
__while_end_53:
__if_end_51:
    lw $t0, 8($sp)
    move $v0, $t0
    j __return_fn_isPrime
__return_fn_isPrime:
    lw $ra, 396($sp)
    addi $sp, $sp, 400
    jr $ra

fn_countPrimes:
    addi $sp, $sp, -400
    sw $ra, 396($sp)
    sw $a0, 0($sp)

    li $t0, 0
    sw $t0, 4($sp)
    li $t0, 2
    sw $t0, 8($sp)
__while_start_56:
    lw $t0, 8($sp)
    lw $t1, 0($sp)
    slt $t2, $t1, $t0
    xori $t2, $t2, 1
    sw $t2, 12($sp)
    lw $t0, 12($sp)
    sltu $t1, $zero, $t0
    beq $t1, $zero, __while_end_57
    lw $t0, 8($sp)
    move $a0, $t0
    jal fn_isPrime
    move $t0, $v0
    sw $t0, 16($sp)
    lw $t0, 16($sp)
    li $t1, 1
    xor $t3, $t0, $t1
    sltiu $t2, $t3, 1
    sw $t2, 20($sp)
    lw $t0, 20($sp)
    sltu $t1, $zero, $t0
    beq $t1, $zero, __if_end_58
    lw $t0, 4($sp)
    li $t1, 1
    add $t0, $t0, $t1
    sw $t0, 24($sp)
    lw $t0, 24($sp)
    sw $t0, 4($sp)
__if_end_58:
    lw $t0, 8($sp)
    li $t1, 1
    add $t0, $t0, $t1
    sw $t0, 28($sp)
    lw $t0, 28($sp)
    sw $t0, 8($sp)
    j __while_start_56
__while_end_57:
    lw $t0, 4($sp)
    move $v0, $t0
    j __return_fn_countPrimes
__return_fn_countPrimes:
    lw $ra, 396($sp)
    addi $sp, $sp, 400
    jr $ra

fn_reverseArray:
    addi $sp, $sp, -400
    sw $ra, 396($sp)
    sw $a0, 0($sp)
    sw $a1, 4($sp)

    li $t0, 0
    sw $t0, 8($sp)
    lw $t0, 4($sp)
    li $t1, 1
    sub $t0, $t0, $t1
    sw $t0, 20($sp)
    lw $t0, 20($sp)
    sw $t0, 12($sp)
__while_start_59:
    lw $t0, 8($sp)
    lw $t1, 12($sp)
    slt $t2, $t0, $t1
    sw $t2, 24($sp)
    lw $t0, 24($sp)
    sltu $t1, $zero, $t0
    beq $t1, $zero, __while_end_60
    lw $t0, 8($sp)
    lw $t1, 0($sp)
    sll $t0, $t0, 2
    add $t1, $t1, $t0
    lw $t1, 0($t1)
    sw $t1, 28($sp)
    lw $t0, 28($sp)
    sw $t0, 16($sp)
    lw $t0, 12($sp)
    lw $t1, 0($sp)
    sll $t0, $t0, 2
    add $t1, $t1, $t0
    lw $t1, 0($t1)
    sw $t1, 32($sp)
    lw $t0, 8($sp)
    lw $t1, 0($sp)
    sll $t0, $t0, 2
    add $t1, $t1, $t0
    lw $t2, 32($sp)
    sw $t2, 0($t1)
    lw $t0, 12($sp)
    lw $t1, 0($sp)
    sll $t0, $t0, 2
    add $t1, $t1, $t0
    lw $t2, 16($sp)
    sw $t2, 0($t1)
    lw $t0, 8($sp)
    li $t1, 1
    add $t0, $t0, $t1
    sw $t0, 36($sp)
    lw $t0, 36($sp)
    sw $t0, 8($sp)
    lw $t0, 12($sp)
    li $t1, 1
    sub $t0, $t0, $t1
    sw $t0, 40($sp)
    lw $t0, 40($sp)
    sw $t0, 12($sp)
    j __while_start_59
__while_end_60:
__return_fn_reverseArray:
    lw $ra, 396($sp)
    addi $sp, $sp, 400
    jr $ra

fn_testComplexExpressions:
    addi $sp, $sp, -400
    sw $ra, 396($sp)
    sw $a0, 0($sp)
    sw $a1, 4($sp)
    sw $a2, 8($sp)

    lw $t0, 4($sp)
    lw $t1, 8($sp)
    mul $t0, $t0, $t1
    sw $t0, 16($sp)
    lw $t0, 0($sp)
    lw $t1, 16($sp)
    add $t0, $t0, $t1
    sw $t0, 20($sp)
    lw $t0, 0($sp)
    lw $t1, 4($sp)
    div $t0, $t1
    mflo $t0
    sw $t0, 24($sp)
    lw $t0, 20($sp)
    lw $t1, 24($sp)
    sub $t0, $t0, $t1
    sw $t0, 28($sp)
    lw $t0, 28($sp)
    sw $t0, 12($sp)
    lw $t0, 0($sp)
    lw $t1, 4($sp)
    add $t0, $t0, $t1
    sw $t0, 32($sp)
    lw $t0, 8($sp)
    lw $t1, 0($sp)
    sub $t0, $t0, $t1
    sw $t0, 36($sp)
    lw $t0, 32($sp)
    lw $t1, 36($sp)
    mul $t0, $t0, $t1
    sw $t0, 40($sp)
    lw $t0, 4($sp)
    li $t1, 1
    add $t0, $t0, $t1
    sw $t0, 44($sp)
    lw $t0, 40($sp)
    lw $t1, 44($sp)
    div $t0, $t1
    mflo $t0
    sw $t0, 48($sp)
    lw $t0, 48($sp)
    sw $t0, 12($sp)
    lw $t0, 0($sp)
    lw $t1, 4($sp)
    mul $t0, $t0, $t1
    sw $t0, 52($sp)
    lw $t0, 8($sp)
    lw $t1, 0($sp)
    mul $t0, $t0, $t1
    sw $t0, 56($sp)
    lw $t0, 52($sp)
    lw $t1, 56($sp)
    add $t0, $t0, $t1
    sw $t0, 60($sp)
    lw $t0, 4($sp)
    lw $t1, 8($sp)
    div $t0, $t1
    mflo $t0
    sw $t0, 64($sp)
    lw $t0, 60($sp)
    lw $t1, 64($sp)
    sub $t0, $t0, $t1
    sw $t0, 68($sp)
    lw $t0, 68($sp)
    lw $t1, 0($sp)
    add $t0, $t0, $t1
    sw $t0, 72($sp)
    lw $t0, 72($sp)
    lw $t1, 4($sp)
    sub $t0, $t0, $t1
    sw $t0, 76($sp)
    lw $t0, 76($sp)
    lw $t1, 8($sp)
    add $t0, $t0, $t1
    sw $t0, 80($sp)
    lw $t0, 80($sp)
    sw $t0, 12($sp)
    lw $t0, 12($sp)
    move $v0, $t0
    j __return_fn_testComplexExpressions
__return_fn_testComplexExpressions:
    lw $ra, 396($sp)
    addi $sp, $sp, 400
    jr $ra

fn_testVoidFunction:
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
    move $a0, $t0
    jal fn_output
    move $t0, $v0
    sw $t0, 12($sp)
__return_fn_testVoidFunction:
    lw $ra, 396($sp)
    addi $sp, $sp, 400
    jr $ra

fn_printArray:
    addi $sp, $sp, -400
    sw $ra, 396($sp)
    sw $a0, 0($sp)
    sw $a1, 4($sp)

    li $t0, 0
    sw $t0, 8($sp)
__while_start_61:
    lw $t0, 8($sp)
    lw $t1, 0($sp)
    sll $t0, $t0, 2
    add $t1, $t1, $t0
    lw $t1, 0($t1)
    sw $t1, 12($sp)
    lw $t0, 12($sp)
    move $a0, $t0
    jal fn_output
    move $t0, $v0
    sw $t0, 16($sp)
    lw $t0, 8($sp)
    li $t1, 1
    add $t0, $t0, $t1
    sw $t0, 20($sp)
    lw $t0, 20($sp)
    sw $t0, 8($sp)
    lw $t0, 8($sp)
    lw $t1, 0($sp)
    sll $t0, $t0, 2
    add $t1, $t1, $t0
    lw $t1, 0($t1)
    sw $t1, 12($sp)
    lw $t0, 12($sp)
    move $a0, $t0
    jal fn_output
    move $t0, $v0
    sw $t0, 16($sp)
    lw $t0, 8($sp)
    li $t1, 1
    add $t0, $t0, $t1
    sw $t0, 20($sp)
    lw $t0, 20($sp)
    sw $t0, 8($sp)
    lw $t0, 8($sp)
    lw $t1, 0($sp)
    sll $t0, $t0, 2
    add $t1, $t1, $t0
    lw $t1, 0($t1)
    sw $t1, 12($sp)
    lw $t0, 12($sp)
    move $a0, $t0
    jal fn_output
    move $t0, $v0
    sw $t0, 16($sp)
    lw $t0, 8($sp)
    li $t1, 1
    add $t0, $t0, $t1
    sw $t0, 20($sp)
    lw $t0, 20($sp)
    sw $t0, 8($sp)
    lw $t0, 8($sp)
    lw $t1, 0($sp)
    sll $t0, $t0, 2
    add $t1, $t1, $t0
    lw $t1, 0($t1)
    sw $t1, 12($sp)
    lw $t0, 12($sp)
    move $a0, $t0
    jal fn_output
    move $t0, $v0
    sw $t0, 16($sp)
    lw $t0, 8($sp)
    li $t1, 1
    add $t0, $t0, $t1
    sw $t0, 20($sp)
    lw $t0, 20($sp)
    sw $t0, 8($sp)
    lw $t0, 8($sp)
    lw $t1, 0($sp)
    sll $t0, $t0, 2
    add $t1, $t1, $t0
    lw $t1, 0($t1)
    sw $t1, 12($sp)
    lw $t0, 12($sp)
    move $a0, $t0
    jal fn_output
    move $t0, $v0
    sw $t0, 16($sp)
    lw $t0, 8($sp)
    li $t1, 1
    add $t0, $t0, $t1
    sw $t0, 20($sp)
    lw $t0, 20($sp)
    sw $t0, 8($sp)
__while_end_62:
__return_fn_printArray:
    lw $ra, 396($sp)
    addi $sp, $sp, 400
    jr $ra

fn_multiply3:
    addi $sp, $sp, -400
    sw $ra, 396($sp)
    sw $a0, 0($sp)
    sw $a1, 4($sp)
    sw $a2, 8($sp)

    lw $t0, 0($sp)
    lw $t1, 4($sp)
    mul $t0, $t0, $t1
    sw $t0, 12($sp)
    lw $t0, 12($sp)
    lw $t1, 8($sp)
    mul $t0, $t0, $t1
    sw $t0, 16($sp)
    lw $t0, 16($sp)
    move $v0, $t0
    j __return_fn_multiply3
__return_fn_multiply3:
    lw $ra, 396($sp)
    addi $sp, $sp, 400
    jr $ra

fn_add4:
    addi $sp, $sp, -400
    sw $ra, 396($sp)
    sw $a0, 0($sp)
    sw $a1, 4($sp)
    sw $a2, 8($sp)
    sw $a3, 12($sp)

    lw $t0, 0($sp)
    lw $t1, 4($sp)
    add $t0, $t0, $t1
    sw $t0, 16($sp)
    lw $t0, 16($sp)
    lw $t1, 8($sp)
    add $t0, $t0, $t1
    sw $t0, 20($sp)
    lw $t0, 20($sp)
    lw $t1, 12($sp)
    add $t0, $t0, $t1
    sw $t0, 24($sp)
    lw $t0, 24($sp)
    move $v0, $t0
    j __return_fn_add4
__return_fn_add4:
    lw $ra, 396($sp)
    addi $sp, $sp, 400
    jr $ra

fn_max3:
    addi $sp, $sp, -400
    sw $ra, 396($sp)
    sw $a0, 0($sp)
    sw $a1, 4($sp)
    sw $a2, 8($sp)

    lw $t0, 0($sp)
    sw $t0, 12($sp)
    lw $t0, 4($sp)
    lw $t1, 12($sp)
    slt $t2, $t1, $t0
    sw $t2, 16($sp)
    lw $t0, 16($sp)
    sltu $t1, $zero, $t0
    beq $t1, $zero, __if_end_63
    lw $t0, 4($sp)
    sw $t0, 12($sp)
__if_end_63:
    lw $t0, 8($sp)
    lw $t1, 12($sp)
    slt $t2, $t1, $t0
    sw $t2, 20($sp)
    lw $t0, 20($sp)
    sltu $t1, $zero, $t0
    beq $t1, $zero, __if_end_64
    lw $t0, 8($sp)
    sw $t0, 12($sp)
__if_end_64:
    lw $t0, 12($sp)
    move $v0, $t0
    j __return_fn_max3
__return_fn_max3:
    lw $ra, 396($sp)
    addi $sp, $sp, 400
    jr $ra

fn_fillArray:
    addi $sp, $sp, -400
    sw $ra, 396($sp)
    sw $a0, 0($sp)
    sw $a1, 4($sp)
    sw $a2, 8($sp)

    li $t0, 0
    sw $t0, 12($sp)
__while_start_65:
    lw $t0, 12($sp)
    lw $t1, 4($sp)
    slt $t2, $t0, $t1
    sw $t2, 16($sp)
    lw $t0, 16($sp)
    sltu $t1, $zero, $t0
    beq $t1, $zero, __while_end_66
    lw $t0, 12($sp)
    lw $t1, 0($sp)
    sll $t0, $t0, 2
    add $t1, $t1, $t0
    lw $t2, 8($sp)
    sw $t2, 0($t1)
    lw $t0, 12($sp)
    li $t1, 1
    add $t0, $t0, $t1
    sw $t0, 20($sp)
    lw $t0, 20($sp)
    sw $t0, 12($sp)
    j __while_start_65
__while_end_66:
__return_fn_fillArray:
    lw $ra, 396($sp)
    addi $sp, $sp, 400
    jr $ra

fn_copyArray:
    addi $sp, $sp, -400
    sw $ra, 396($sp)
    sw $a0, 0($sp)
    sw $a1, 4($sp)
    sw $a2, 8($sp)

    li $t0, 0
    sw $t0, 12($sp)
__while_start_67:
    lw $t0, 12($sp)
    lw $t1, 8($sp)
    slt $t2, $t0, $t1
    sw $t2, 16($sp)
    lw $t0, 16($sp)
    sltu $t1, $zero, $t0
    beq $t1, $zero, __while_end_68
    lw $t0, 12($sp)
    lw $t1, 0($sp)
    sll $t0, $t0, 2
    add $t1, $t1, $t0
    lw $t1, 0($t1)
    sw $t1, 20($sp)
    lw $t0, 12($sp)
    lw $t1, 4($sp)
    sll $t0, $t0, 2
    add $t1, $t1, $t0
    lw $t2, 20($sp)
    sw $t2, 0($t1)
    lw $t0, 12($sp)
    li $t1, 1
    add $t0, $t0, $t1
    sw $t0, 24($sp)
    lw $t0, 24($sp)
    sw $t0, 12($sp)
    j __while_start_67
__while_end_68:
__return_fn_copyArray:
    lw $ra, 396($sp)
    addi $sp, $sp, 400
    jr $ra

fn_arrayEqual:
    addi $sp, $sp, -400
    sw $ra, 396($sp)
    sw $a0, 0($sp)
    sw $a1, 4($sp)
    sw $a2, 8($sp)

    li $t0, 1
    sw $t0, 16($sp)
    li $t0, 0
    sw $t0, 12($sp)
__while_start_69:
    lw $t0, 12($sp)
    lw $t1, 8($sp)
    slt $t2, $t0, $t1
    sw $t2, 20($sp)
    lw $t0, 20($sp)
    sltu $t1, $zero, $t0
    beq $t1, $zero, __while_end_70
    lw $t0, 12($sp)
    lw $t1, 0($sp)
    sll $t0, $t0, 2
    add $t1, $t1, $t0
    lw $t1, 0($t1)
    sw $t1, 24($sp)
    lw $t0, 12($sp)
    lw $t1, 4($sp)
    sll $t0, $t0, 2
    add $t1, $t1, $t0
    lw $t1, 0($t1)
    sw $t1, 28($sp)
    lw $t0, 24($sp)
    lw $t1, 28($sp)
    xor $t2, $t0, $t1
    sltu $t2, $zero, $t2
    sw $t2, 32($sp)
    lw $t0, 32($sp)
    sltu $t1, $zero, $t0
    beq $t1, $zero, __if_else_71
    li $t0, 0
    sw $t0, 16($sp)
    lw $t0, 8($sp)
    sw $t0, 12($sp)
    j __if_end_72
__if_else_71:
    lw $t0, 12($sp)
    li $t1, 1
    add $t0, $t0, $t1
    sw $t0, 36($sp)
    lw $t0, 36($sp)
    sw $t0, 12($sp)
__if_end_72:
    j __while_start_69
__while_end_70:
    lw $t0, 16($sp)
    move $v0, $t0
    j __return_fn_arrayEqual
__return_fn_arrayEqual:
    lw $ra, 396($sp)
    addi $sp, $sp, 400
    jr $ra

fn_absoluteValue:
    addi $sp, $sp, -400
    sw $ra, 396($sp)
    sw $a0, 0($sp)

    lw $t0, 0($sp)
    li $t1, 0
    slt $t2, $t0, $t1
    sw $t2, 8($sp)
    lw $t0, 8($sp)
    sltu $t1, $zero, $t0
    beq $t1, $zero, __if_else_73
    li $t0, 0
    lw $t1, 0($sp)
    sub $t0, $t0, $t1
    sw $t0, 12($sp)
    lw $t0, 12($sp)
    sw $t0, 4($sp)
    j __if_end_74
__if_else_73:
    lw $t0, 0($sp)
    sw $t0, 4($sp)
__if_end_74:
    lw $t0, 4($sp)
    move $v0, $t0
    j __return_fn_absoluteValue
__return_fn_absoluteValue:
    lw $ra, 396($sp)
    addi $sp, $sp, 400
    jr $ra

fn_sign:
    addi $sp, $sp, -400
    sw $ra, 396($sp)
    sw $a0, 0($sp)

    lw $t0, 0($sp)
    li $t1, 0
    slt $t2, $t0, $t1
    sw $t2, 8($sp)
    lw $t0, 8($sp)
    sltu $t1, $zero, $t0
    beq $t1, $zero, __if_else_75
    li $t0, 0
    li $t1, 1
    sub $t0, $t0, $t1
    sw $t0, 12($sp)
    lw $t0, 12($sp)
    sw $t0, 4($sp)
    j __if_end_76
__if_else_75:
    lw $t0, 0($sp)
    li $t1, 0
    slt $t2, $t1, $t0
    sw $t2, 16($sp)
    lw $t0, 16($sp)
    sltu $t1, $zero, $t0
    beq $t1, $zero, __if_else_77
    li $t0, 1
    sw $t0, 4($sp)
    j __if_end_78
__if_else_77:
    li $t0, 0
    sw $t0, 4($sp)
__if_end_78:
__if_end_76:
    lw $t0, 4($sp)
    move $v0, $t0
    j __return_fn_sign
__return_fn_sign:
    lw $ra, 396($sp)
    addi $sp, $sp, 400
    jr $ra

fn_sumOfSquares:
    addi $sp, $sp, -400
    sw $ra, 396($sp)
    sw $a0, 0($sp)

    li $t0, 0
    sw $t0, 4($sp)
    li $t0, 1
    sw $t0, 8($sp)
__while_start_79:
    lw $t0, 8($sp)
    lw $t1, 8($sp)
    mul $t0, $t0, $t1
    sw $t0, 12($sp)
    lw $t0, 4($sp)
    lw $t1, 12($sp)
    add $t0, $t0, $t1
    sw $t0, 16($sp)
    lw $t0, 16($sp)
    sw $t0, 4($sp)
    lw $t0, 8($sp)
    li $t1, 1
    add $t0, $t0, $t1
    sw $t0, 20($sp)
    lw $t0, 20($sp)
    sw $t0, 8($sp)
    lw $t0, 8($sp)
    lw $t1, 8($sp)
    mul $t0, $t0, $t1
    sw $t0, 12($sp)
    lw $t0, 4($sp)
    lw $t1, 12($sp)
    add $t0, $t0, $t1
    sw $t0, 16($sp)
    lw $t0, 16($sp)
    sw $t0, 4($sp)
    lw $t0, 8($sp)
    li $t1, 1
    add $t0, $t0, $t1
    sw $t0, 20($sp)
    lw $t0, 20($sp)
    sw $t0, 8($sp)
    lw $t0, 8($sp)
    lw $t1, 8($sp)
    mul $t0, $t0, $t1
    sw $t0, 12($sp)
    lw $t0, 4($sp)
    lw $t1, 12($sp)
    add $t0, $t0, $t1
    sw $t0, 16($sp)
    lw $t0, 16($sp)
    sw $t0, 4($sp)
    lw $t0, 8($sp)
    li $t1, 1
    add $t0, $t0, $t1
    sw $t0, 20($sp)
    lw $t0, 20($sp)
    sw $t0, 8($sp)
    lw $t0, 8($sp)
    lw $t1, 8($sp)
    mul $t0, $t0, $t1
    sw $t0, 12($sp)
    lw $t0, 4($sp)
    lw $t1, 12($sp)
    add $t0, $t0, $t1
    sw $t0, 16($sp)
    lw $t0, 16($sp)
    sw $t0, 4($sp)
    lw $t0, 8($sp)
    li $t1, 1
    add $t0, $t0, $t1
    sw $t0, 20($sp)
    lw $t0, 20($sp)
    sw $t0, 8($sp)
    lw $t0, 8($sp)
    lw $t1, 8($sp)
    mul $t0, $t0, $t1
    sw $t0, 12($sp)
    lw $t0, 4($sp)
    lw $t1, 12($sp)
    add $t0, $t0, $t1
    sw $t0, 16($sp)
    lw $t0, 16($sp)
    sw $t0, 4($sp)
    lw $t0, 8($sp)
    li $t1, 1
    add $t0, $t0, $t1
    sw $t0, 20($sp)
    lw $t0, 20($sp)
    sw $t0, 8($sp)
__while_end_80:
    lw $t0, 4($sp)
    move $v0, $t0
    j __return_fn_sumOfSquares
__return_fn_sumOfSquares:
    lw $ra, 396($sp)
    addi $sp, $sp, 400
    jr $ra

fn_sumOfCubes:
    addi $sp, $sp, -400
    sw $ra, 396($sp)
    sw $a0, 0($sp)

    li $t0, 0
    sw $t0, 4($sp)
    li $t0, 1
    sw $t0, 8($sp)
__while_start_81:
    lw $t0, 8($sp)
    lw $t1, 8($sp)
    mul $t0, $t0, $t1
    sw $t0, 12($sp)
    lw $t0, 12($sp)
    lw $t1, 8($sp)
    mul $t0, $t0, $t1
    sw $t0, 16($sp)
    lw $t0, 4($sp)
    lw $t1, 16($sp)
    add $t0, $t0, $t1
    sw $t0, 20($sp)
    lw $t0, 20($sp)
    sw $t0, 4($sp)
    lw $t0, 8($sp)
    li $t1, 1
    add $t0, $t0, $t1
    sw $t0, 24($sp)
    lw $t0, 24($sp)
    sw $t0, 8($sp)
    lw $t0, 8($sp)
    lw $t1, 8($sp)
    mul $t0, $t0, $t1
    sw $t0, 12($sp)
    lw $t0, 12($sp)
    lw $t1, 8($sp)
    mul $t0, $t0, $t1
    sw $t0, 16($sp)
    lw $t0, 4($sp)
    lw $t1, 16($sp)
    add $t0, $t0, $t1
    sw $t0, 20($sp)
    lw $t0, 20($sp)
    sw $t0, 4($sp)
    lw $t0, 8($sp)
    li $t1, 1
    add $t0, $t0, $t1
    sw $t0, 24($sp)
    lw $t0, 24($sp)
    sw $t0, 8($sp)
    lw $t0, 8($sp)
    lw $t1, 8($sp)
    mul $t0, $t0, $t1
    sw $t0, 12($sp)
    lw $t0, 12($sp)
    lw $t1, 8($sp)
    mul $t0, $t0, $t1
    sw $t0, 16($sp)
    lw $t0, 4($sp)
    lw $t1, 16($sp)
    add $t0, $t0, $t1
    sw $t0, 20($sp)
    lw $t0, 20($sp)
    sw $t0, 4($sp)
    lw $t0, 8($sp)
    li $t1, 1
    add $t0, $t0, $t1
    sw $t0, 24($sp)
    lw $t0, 24($sp)
    sw $t0, 8($sp)
    lw $t0, 8($sp)
    lw $t1, 8($sp)
    mul $t0, $t0, $t1
    sw $t0, 12($sp)
    lw $t0, 12($sp)
    lw $t1, 8($sp)
    mul $t0, $t0, $t1
    sw $t0, 16($sp)
    lw $t0, 4($sp)
    lw $t1, 16($sp)
    add $t0, $t0, $t1
    sw $t0, 20($sp)
    lw $t0, 20($sp)
    sw $t0, 4($sp)
    lw $t0, 8($sp)
    li $t1, 1
    add $t0, $t0, $t1
    sw $t0, 24($sp)
    lw $t0, 24($sp)
    sw $t0, 8($sp)
    lw $t0, 8($sp)
    lw $t1, 8($sp)
    mul $t0, $t0, $t1
    sw $t0, 12($sp)
    lw $t0, 12($sp)
    lw $t1, 8($sp)
    mul $t0, $t0, $t1
    sw $t0, 16($sp)
    lw $t0, 4($sp)
    lw $t1, 16($sp)
    add $t0, $t0, $t1
    sw $t0, 20($sp)
    lw $t0, 20($sp)
    sw $t0, 4($sp)
    lw $t0, 8($sp)
    li $t1, 1
    add $t0, $t0, $t1
    sw $t0, 24($sp)
    lw $t0, 24($sp)
    sw $t0, 8($sp)
__while_end_82:
    lw $t0, 4($sp)
    move $v0, $t0
    j __return_fn_sumOfCubes
__return_fn_sumOfCubes:
    lw $ra, 396($sp)
    addi $sp, $sp, 400
    jr $ra

fn_calculateMean:
    addi $sp, $sp, -400
    sw $ra, 396($sp)
    sw $a0, 0($sp)
    sw $a1, 4($sp)

    li $t0, 0
    sw $t0, 8($sp)
    li $t0, 0
    sw $t0, 12($sp)
__while_start_83:
    lw $t0, 12($sp)
    lw $t1, 0($sp)
    sll $t0, $t0, 2
    add $t1, $t1, $t0
    lw $t1, 0($t1)
    sw $t1, 16($sp)
    lw $t0, 8($sp)
    lw $t1, 16($sp)
    add $t0, $t0, $t1
    sw $t0, 20($sp)
    lw $t0, 20($sp)
    sw $t0, 8($sp)
    lw $t0, 12($sp)
    li $t1, 1
    add $t0, $t0, $t1
    sw $t0, 24($sp)
    lw $t0, 24($sp)
    sw $t0, 12($sp)
    lw $t0, 12($sp)
    lw $t1, 0($sp)
    sll $t0, $t0, 2
    add $t1, $t1, $t0
    lw $t1, 0($t1)
    sw $t1, 16($sp)
    lw $t0, 8($sp)
    lw $t1, 16($sp)
    add $t0, $t0, $t1
    sw $t0, 20($sp)
    lw $t0, 20($sp)
    sw $t0, 8($sp)
    lw $t0, 12($sp)
    li $t1, 1
    add $t0, $t0, $t1
    sw $t0, 24($sp)
    lw $t0, 24($sp)
    sw $t0, 12($sp)
    lw $t0, 12($sp)
    lw $t1, 0($sp)
    sll $t0, $t0, 2
    add $t1, $t1, $t0
    lw $t1, 0($t1)
    sw $t1, 16($sp)
    lw $t0, 8($sp)
    lw $t1, 16($sp)
    add $t0, $t0, $t1
    sw $t0, 20($sp)
    lw $t0, 20($sp)
    sw $t0, 8($sp)
    lw $t0, 12($sp)
    li $t1, 1
    add $t0, $t0, $t1
    sw $t0, 24($sp)
    lw $t0, 24($sp)
    sw $t0, 12($sp)
    lw $t0, 12($sp)
    lw $t1, 0($sp)
    sll $t0, $t0, 2
    add $t1, $t1, $t0
    lw $t1, 0($t1)
    sw $t1, 16($sp)
    lw $t0, 8($sp)
    lw $t1, 16($sp)
    add $t0, $t0, $t1
    sw $t0, 20($sp)
    lw $t0, 20($sp)
    sw $t0, 8($sp)
    lw $t0, 12($sp)
    li $t1, 1
    add $t0, $t0, $t1
    sw $t0, 24($sp)
    lw $t0, 24($sp)
    sw $t0, 12($sp)
    lw $t0, 12($sp)
    lw $t1, 0($sp)
    sll $t0, $t0, 2
    add $t1, $t1, $t0
    lw $t1, 0($t1)
    sw $t1, 16($sp)
    lw $t0, 8($sp)
    lw $t1, 16($sp)
    add $t0, $t0, $t1
    sw $t0, 20($sp)
    lw $t0, 20($sp)
    sw $t0, 8($sp)
    lw $t0, 12($sp)
    li $t1, 1
    add $t0, $t0, $t1
    sw $t0, 24($sp)
    lw $t0, 24($sp)
    sw $t0, 12($sp)
__while_end_84:
    lw $t0, 8($sp)
    lw $t1, 4($sp)
    div $t0, $t1
    mflo $t0
    sw $t0, 28($sp)
    lw $t0, 28($sp)
    move $v0, $t0
    j __return_fn_calculateMean
__return_fn_calculateMean:
    lw $ra, 396($sp)
    addi $sp, $sp, 400
    jr $ra

fn_countOccurrences:
    addi $sp, $sp, -400
    sw $ra, 396($sp)
    sw $a0, 0($sp)
    sw $a1, 4($sp)
    sw $a2, 8($sp)

    li $t0, 0
    sw $t0, 12($sp)
    li $t0, 0
    sw $t0, 16($sp)
__while_start_85:
    lw $t0, 16($sp)
    lw $t1, 4($sp)
    slt $t2, $t0, $t1
    sw $t2, 20($sp)
    lw $t0, 20($sp)
    sltu $t1, $zero, $t0
    beq $t1, $zero, __while_end_86
    lw $t0, 16($sp)
    lw $t1, 0($sp)
    sll $t0, $t0, 2
    add $t1, $t1, $t0
    lw $t1, 0($t1)
    sw $t1, 24($sp)
    lw $t0, 24($sp)
    lw $t1, 8($sp)
    xor $t3, $t0, $t1
    sltiu $t2, $t3, 1
    sw $t2, 28($sp)
    lw $t0, 28($sp)
    sltu $t1, $zero, $t0
    beq $t1, $zero, __if_end_87
    lw $t0, 12($sp)
    li $t1, 1
    add $t0, $t0, $t1
    sw $t0, 32($sp)
    lw $t0, 32($sp)
    sw $t0, 12($sp)
__if_end_87:
    lw $t0, 16($sp)
    li $t1, 1
    add $t0, $t0, $t1
    sw $t0, 36($sp)
    lw $t0, 36($sp)
    sw $t0, 16($sp)
    j __while_start_85
__while_end_86:
    lw $t0, 12($sp)
    move $v0, $t0
    j __return_fn_countOccurrences
__return_fn_countOccurrences:
    lw $ra, 396($sp)
    addi $sp, $sp, 400
    jr $ra

fn_leftShift:
    addi $sp, $sp, -400
    sw $ra, 396($sp)
    sw $a0, 0($sp)
    sw $a1, 4($sp)

    lw $t0, 0($sp)
    sw $t0, 8($sp)
    li $t0, 0
    sw $t0, 12($sp)
__while_start_88:
    lw $t0, 8($sp)
    li $t1, 2
    mul $t0, $t0, $t1
    sw $t0, 16($sp)
    lw $t0, 16($sp)
    sw $t0, 8($sp)
    lw $t0, 12($sp)
    li $t1, 1
    add $t0, $t0, $t1
    sw $t0, 20($sp)
    lw $t0, 20($sp)
    sw $t0, 12($sp)
    lw $t0, 8($sp)
    li $t1, 2
    mul $t0, $t0, $t1
    sw $t0, 16($sp)
    lw $t0, 16($sp)
    sw $t0, 8($sp)
    lw $t0, 12($sp)
    li $t1, 1
    add $t0, $t0, $t1
    sw $t0, 20($sp)
    lw $t0, 20($sp)
    sw $t0, 12($sp)
__while_end_89:
    lw $t0, 8($sp)
    move $v0, $t0
    j __return_fn_leftShift
__return_fn_leftShift:
    lw $ra, 396($sp)
    addi $sp, $sp, 400
    jr $ra

fn_rightShift:
    addi $sp, $sp, -400
    sw $ra, 396($sp)
    sw $a0, 0($sp)
    sw $a1, 4($sp)

    lw $t0, 0($sp)
    sw $t0, 8($sp)
    li $t0, 0
    sw $t0, 12($sp)
__while_start_90:
    lw $t0, 8($sp)
    li $t1, 2
    div $t0, $t1
    mflo $t0
    sw $t0, 16($sp)
    lw $t0, 16($sp)
    sw $t0, 8($sp)
    lw $t0, 12($sp)
    li $t1, 1
    add $t0, $t0, $t1
    sw $t0, 20($sp)
    lw $t0, 20($sp)
    sw $t0, 12($sp)
    lw $t0, 8($sp)
    li $t1, 2
    div $t0, $t1
    mflo $t0
    sw $t0, 16($sp)
    lw $t0, 16($sp)
    sw $t0, 8($sp)
    lw $t0, 12($sp)
    li $t1, 1
    add $t0, $t0, $t1
    sw $t0, 20($sp)
    lw $t0, 20($sp)
    sw $t0, 12($sp)
__while_end_91:
    lw $t0, 8($sp)
    move $v0, $t0
    j __return_fn_rightShift
__return_fn_rightShift:
    lw $ra, 396($sp)
    addi $sp, $sp, 400
    jr $ra

fn_arrayLength:
    addi $sp, $sp, -400
    sw $ra, 396($sp)
    sw $a0, 0($sp)
    sw $a1, 4($sp)

    li $t0, 0
    sw $t0, 8($sp)
__while_start_92:
    lw $t0, 8($sp)
    lw $t1, 4($sp)
    slt $t2, $t0, $t1
    sw $t2, 12($sp)
    lw $t0, 12($sp)
    sltu $t1, $zero, $t0
    beq $t1, $zero, __while_end_93
    lw $t0, 8($sp)
    lw $t1, 0($sp)
    sll $t0, $t0, 2
    add $t1, $t1, $t0
    lw $t1, 0($t1)
    sw $t1, 16($sp)
    lw $t0, 16($sp)
    li $t1, 0
    xor $t3, $t0, $t1
    sltiu $t2, $t3, 1
    sw $t2, 20($sp)
    lw $t0, 20($sp)
    sltu $t1, $zero, $t0
    beq $t1, $zero, __if_else_94
    lw $t0, 4($sp)
    sw $t0, 8($sp)
    j __if_end_95
__if_else_94:
    lw $t0, 8($sp)
    li $t1, 1
    add $t0, $t0, $t1
    sw $t0, 24($sp)
    lw $t0, 24($sp)
    sw $t0, 8($sp)
__if_end_95:
    j __while_start_92
__while_end_93:
    lw $t0, 8($sp)
    move $v0, $t0
    j __return_fn_arrayLength
__return_fn_arrayLength:
    lw $ra, 396($sp)
    addi $sp, $sp, 400
    jr $ra

main:
    addi $sp, $sp, -400
    # Declared array testArray[10]
    # Declared array testArray2[10]
    li $t0, 0
    sw $t0, globalCounter
    li $t0, 1
    move $a0, $t0
    jal fn_output
    move $t0, $v0
    sw $t0, 100($sp)
    li $t0, 10
    move $a0, $t0
    li $t0, 5
    move $a1, $t0
    jal fn_testArithmetic
    move $t0, $v0
    sw $t0, 104($sp)
    lw $t0, 104($sp)
    sw $t0, 84($sp)
    lw $t0, 84($sp)
    move $a0, $t0
    jal fn_output
    move $t0, $v0
    sw $t0, 108($sp)
    li $t0, 2
    move $a0, $t0
    jal fn_output
    move $t0, $v0
    sw $t0, 112($sp)
    li $t0, 5
    move $a0, $t0
    li $t0, 10
    move $a1, $t0
    jal fn_testRelational
    move $t0, $v0
    sw $t0, 116($sp)
    lw $t0, 116($sp)
    sw $t0, 84($sp)
    lw $t0, 84($sp)
    move $a0, $t0
    jal fn_output
    move $t0, $v0
    sw $t0, 120($sp)
    li $t0, 3
    move $a0, $t0
    jal fn_output
    move $t0, $v0
    sw $t0, 124($sp)
    li $t0, 75
    move $a0, $t0
    jal fn_testIfElse
    move $t0, $v0
    sw $t0, 128($sp)
    lw $t0, 128($sp)
    sw $t0, 84($sp)
    lw $t0, 84($sp)
    move $a0, $t0
    jal fn_output
    move $t0, $v0
    sw $t0, 132($sp)
    li $t0, 4
    move $a0, $t0
    jal fn_output
    move $t0, $v0
    sw $t0, 136($sp)
    li $t0, 10
    move $a0, $t0
    jal fn_testWhileLoop
    move $t0, $v0
    sw $t0, 140($sp)
    lw $t0, 140($sp)
    sw $t0, 84($sp)
    lw $t0, 84($sp)
    move $a0, $t0
    jal fn_output
    move $t0, $v0
    sw $t0, 144($sp)
    li $t0, 5
    move $a0, $t0
    jal fn_output
    move $t0, $v0
    sw $t0, 148($sp)
    li $t0, 5
    move $a0, $t0
    li $t0, 5
    move $a1, $t0
    jal fn_testNestedLoops
    move $t0, $v0
    sw $t0, 152($sp)
    lw $t0, 152($sp)
    sw $t0, 84($sp)
    lw $t0, 84($sp)
    move $a0, $t0
    jal fn_output
    move $t0, $v0
    sw $t0, 156($sp)
    li $t0, 6
    move $a0, $t0
    jal fn_output
    move $t0, $v0
    sw $t0, 160($sp)
    addi $t0, $sp, 0
    move $a0, $t0
    li $t0, 10
    move $a1, $t0
    jal fn_testArrayOperations
    move $t0, $v0
    sw $t0, 164($sp)
    addi $t0, $sp, 0
    move $a0, $t0
    li $t0, 10
    move $a1, $t0
    jal fn_sumArray
    move $t0, $v0
    sw $t0, 168($sp)
    lw $t0, 168($sp)
    sw $t0, 84($sp)
    lw $t0, 84($sp)
    move $a0, $t0
    jal fn_output
    move $t0, $v0
    sw $t0, 172($sp)
    li $t0, 7
    move $a0, $t0
    jal fn_output
    move $t0, $v0
    sw $t0, 176($sp)
    li $t0, 5
    move $a0, $t0
    jal fn_factorial
    move $t0, $v0
    sw $t0, 180($sp)
    lw $t0, 180($sp)
    sw $t0, 84($sp)
    lw $t0, 84($sp)
    move $a0, $t0
    jal fn_output
    move $t0, $v0
    sw $t0, 184($sp)
    li $t0, 8
    move $a0, $t0
    jal fn_output
    move $t0, $v0
    sw $t0, 188($sp)
    li $t0, 7
    move $a0, $t0
    jal fn_fibonacci
    move $t0, $v0
    sw $t0, 192($sp)
    lw $t0, 192($sp)
    sw $t0, 84($sp)
    lw $t0, 84($sp)
    move $a0, $t0
    jal fn_output
    move $t0, $v0
    sw $t0, 196($sp)
    li $t0, 9
    move $a0, $t0
    jal fn_output
    move $t0, $v0
    sw $t0, 200($sp)
    li $t0, 2
    move $a0, $t0
    li $t0, 5
    move $a1, $t0
    jal fn_power
    move $t0, $v0
    sw $t0, 204($sp)
    lw $t0, 204($sp)
    sw $t0, 84($sp)
    lw $t0, 84($sp)
    move $a0, $t0
    jal fn_output
    move $t0, $v0
    sw $t0, 208($sp)
    li $t0, 10
    move $a0, $t0
    jal fn_output
    move $t0, $v0
    sw $t0, 212($sp)
    li $t0, 48
    move $a0, $t0
    li $t0, 18
    move $a1, $t0
    jal fn_gcd
    move $t0, $v0
    sw $t0, 216($sp)
    lw $t0, 216($sp)
    sw $t0, 84($sp)
    lw $t0, 84($sp)
    move $a0, $t0
    jal fn_output
    move $t0, $v0
    sw $t0, 220($sp)
    li $t0, 11
    move $a0, $t0
    jal fn_output
    move $t0, $v0
    sw $t0, 224($sp)
    li $t0, 0
    sw $t0, 80($sp)
__while_start_96:
    lw $t0, 80($sp)
    li $t1, 10
    slt $t2, $t0, $t1
    sw $t2, 228($sp)
    lw $t0, 228($sp)
    sltu $t1, $zero, $t0
    beq $t1, $zero, __while_end_97
    lw $t0, 80($sp)
    li $t1, 3
    mul $t0, $t0, $t1
    sw $t0, 232($sp)
    lw $t0, 80($sp)
    # Bounds check for array testArray
    bltz $t0, __bounds_error_0
    li $t1, 10
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
    lw $t3, 232($sp)
    sw $t3, 0($t2)
    lw $t0, 80($sp)
    li $t1, 1
    add $t0, $t0, $t1
    sw $t0, 236($sp)
    lw $t0, 236($sp)
    sw $t0, 80($sp)
    j __while_start_96
__while_end_97:
    addi $t0, $sp, 0
    move $a0, $t0
    li $t0, 10
    move $a1, $t0
    li $t0, 15
    move $a2, $t0
    jal fn_linearSearch
    move $t0, $v0
    sw $t0, 240($sp)
    lw $t0, 240($sp)
    sw $t0, 84($sp)
    lw $t0, 84($sp)
    move $a0, $t0
    jal fn_output
    move $t0, $v0
    sw $t0, 244($sp)
    li $t0, 12
    move $a0, $t0
    jal fn_output
    move $t0, $v0
    sw $t0, 248($sp)
    li $t0, 0
    # Bounds check for array testArray
    bltz $t0, __bounds_error_1
    li $t1, 10
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
    li $t0, 1
    # Bounds check for array testArray
    bltz $t0, __bounds_error_2
    li $t1, 10
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
    li $t3, 2
    sw $t3, 0($t2)
    li $t0, 2
    # Bounds check for array testArray
    bltz $t0, __bounds_error_3
    li $t1, 10
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
    li $t0, 3
    # Bounds check for array testArray
    bltz $t0, __bounds_error_4
    li $t1, 10
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
    li $t3, 1
    sw $t3, 0($t2)
    li $t0, 4
    # Bounds check for array testArray
    bltz $t0, __bounds_error_5
    li $t1, 10
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
    li $t3, 9
    sw $t3, 0($t2)
    addi $t0, $sp, 0
    move $a0, $t0
    li $t0, 5
    move $a1, $t0
    jal fn_bubbleSort
    move $t0, $v0
    sw $t0, 252($sp)
    addi $t0, $sp, 0
    move $a0, $t0
    li $t0, 5
    move $a1, $t0
    jal fn_printArray
    move $t0, $v0
    sw $t0, 256($sp)
    li $t0, 13
    move $a0, $t0
    jal fn_output
    move $t0, $v0
    sw $t0, 260($sp)
    addi $t0, $sp, 0
    move $a0, $t0
    li $t0, 5
    move $a1, $t0
    jal fn_findMax
    move $t0, $v0
    sw $t0, 264($sp)
    lw $t0, 264($sp)
    sw $t0, 84($sp)
    lw $t0, 84($sp)
    move $a0, $t0
    jal fn_output
    move $t0, $v0
    sw $t0, 268($sp)
    addi $t0, $sp, 0
    move $a0, $t0
    li $t0, 5
    move $a1, $t0
    jal fn_findMin
    move $t0, $v0
    sw $t0, 272($sp)
    lw $t0, 272($sp)
    sw $t0, 84($sp)
    lw $t0, 84($sp)
    move $a0, $t0
    jal fn_output
    move $t0, $v0
    sw $t0, 276($sp)
    li $t0, 14
    move $a0, $t0
    jal fn_output
    move $t0, $v0
    sw $t0, 280($sp)
    li $t0, 17
    move $a0, $t0
    jal fn_isPrime
    move $t0, $v0
    sw $t0, 284($sp)
    lw $t0, 284($sp)
    sw $t0, 84($sp)
    lw $t0, 84($sp)
    move $a0, $t0
    jal fn_output
    move $t0, $v0
    sw $t0, 288($sp)
    li $t0, 18
    move $a0, $t0
    jal fn_isPrime
    move $t0, $v0
    sw $t0, 292($sp)
    lw $t0, 292($sp)
    sw $t0, 84($sp)
    lw $t0, 84($sp)
    move $a0, $t0
    jal fn_output
    move $t0, $v0
    sw $t0, 296($sp)
    li $t0, 15
    move $a0, $t0
    jal fn_output
    move $t0, $v0
    sw $t0, 300($sp)
    li $t0, 20
    move $a0, $t0
    jal fn_countPrimes
    move $t0, $v0
    sw $t0, 304($sp)
    lw $t0, 304($sp)
    sw $t0, 84($sp)
    lw $t0, 84($sp)
    move $a0, $t0
    jal fn_output
    move $t0, $v0
    sw $t0, 308($sp)
    li $t0, 16
    move $a0, $t0
    jal fn_output
    move $t0, $v0
    sw $t0, 312($sp)
    li $t0, 0
    sw $t0, 80($sp)
__while_start_98:
    lw $t0, 80($sp)
    li $t1, 1
    add $t0, $t0, $t1
    sw $t0, 316($sp)
    lw $t0, 80($sp)
    # Bounds check for array testArray
    bltz $t0, __bounds_error_6
    li $t1, 10
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
    lw $t3, 316($sp)
    sw $t3, 0($t2)
    lw $t0, 80($sp)
    li $t1, 1
    add $t0, $t0, $t1
    sw $t0, 320($sp)
    lw $t0, 320($sp)
    sw $t0, 80($sp)
    lw $t0, 80($sp)
    li $t1, 1
    add $t0, $t0, $t1
    sw $t0, 316($sp)
    lw $t0, 80($sp)
    # Bounds check for array testArray
    bltz $t0, __bounds_error_7
    li $t1, 10
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
    lw $t3, 316($sp)
    sw $t3, 0($t2)
    lw $t0, 80($sp)
    li $t1, 1
    add $t0, $t0, $t1
    sw $t0, 320($sp)
    lw $t0, 320($sp)
    sw $t0, 80($sp)
    lw $t0, 80($sp)
    li $t1, 1
    add $t0, $t0, $t1
    sw $t0, 316($sp)
    lw $t0, 80($sp)
    # Bounds check for array testArray
    bltz $t0, __bounds_error_8
    li $t1, 10
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
    lw $t3, 316($sp)
    sw $t3, 0($t2)
    lw $t0, 80($sp)
    li $t1, 1
    add $t0, $t0, $t1
    sw $t0, 320($sp)
    lw $t0, 320($sp)
    sw $t0, 80($sp)
    lw $t0, 80($sp)
    li $t1, 1
    add $t0, $t0, $t1
    sw $t0, 316($sp)
    lw $t0, 80($sp)
    # Bounds check for array testArray
    bltz $t0, __bounds_error_9
    li $t1, 10
    bge $t0, $t1, __bounds_error_9
    j __bounds_ok_9
__bounds_error_9:
    li $v0, 4
    la $a0, __array_oob_msg
    syscall
    li $v0, 10
    syscall
__bounds_ok_9:
    addi $t2, $sp, 0
    sll $t0, $t0, 2
    add $t2, $t2, $t0
    lw $t3, 316($sp)
    sw $t3, 0($t2)
    lw $t0, 80($sp)
    li $t1, 1
    add $t0, $t0, $t1
    sw $t0, 320($sp)
    lw $t0, 320($sp)
    sw $t0, 80($sp)
    lw $t0, 80($sp)
    li $t1, 1
    add $t0, $t0, $t1
    sw $t0, 316($sp)
    lw $t0, 80($sp)
    # Bounds check for array testArray
    bltz $t0, __bounds_error_10
    li $t1, 10
    bge $t0, $t1, __bounds_error_10
    j __bounds_ok_10
__bounds_error_10:
    li $v0, 4
    la $a0, __array_oob_msg
    syscall
    li $v0, 10
    syscall
__bounds_ok_10:
    addi $t2, $sp, 0
    sll $t0, $t0, 2
    add $t2, $t2, $t0
    lw $t3, 316($sp)
    sw $t3, 0($t2)
    lw $t0, 80($sp)
    li $t1, 1
    add $t0, $t0, $t1
    sw $t0, 320($sp)
    lw $t0, 320($sp)
    sw $t0, 80($sp)
__while_end_99:
    addi $t0, $sp, 0
    move $a0, $t0
    li $t0, 5
    move $a1, $t0
    jal fn_reverseArray
    move $t0, $v0
    sw $t0, 324($sp)
    addi $t0, $sp, 0
    move $a0, $t0
    li $t0, 5
    move $a1, $t0
    jal fn_printArray
    move $t0, $v0
    sw $t0, 328($sp)
    li $t0, 17
    move $a0, $t0
    jal fn_output
    move $t0, $v0
    sw $t0, 332($sp)
    li $t0, 2
    move $a0, $t0
    li $t0, 3
    move $a1, $t0
    li $t0, 4
    move $a2, $t0
    jal fn_multiply3
    move $t0, $v0
    sw $t0, 336($sp)
    lw $t0, 336($sp)
    sw $t0, 84($sp)
    lw $t0, 84($sp)
    move $a0, $t0
    jal fn_output
    move $t0, $v0
    sw $t0, 340($sp)
    li $t0, 1
    move $a0, $t0
    li $t0, 2
    move $a1, $t0
    li $t0, 3
    move $a2, $t0
    li $t0, 4
    move $a3, $t0
    jal fn_add4
    move $t0, $v0
    sw $t0, 344($sp)
    lw $t0, 344($sp)
    sw $t0, 84($sp)
    lw $t0, 84($sp)
    move $a0, $t0
    jal fn_output
    move $t0, $v0
    sw $t0, 348($sp)
    li $t0, 5
    move $a0, $t0
    li $t0, 9
    move $a1, $t0
    li $t0, 3
    move $a2, $t0
    jal fn_max3
    move $t0, $v0
    sw $t0, 352($sp)
    lw $t0, 352($sp)
    sw $t0, 84($sp)
    lw $t0, 84($sp)
    move $a0, $t0
    jal fn_output
    move $t0, $v0
    sw $t0, 356($sp)
    li $t0, 18
    move $a0, $t0
    jal fn_output
    move $t0, $v0
    sw $t0, 360($sp)
    addi $t0, $sp, 0
    move $a0, $t0
    li $t0, 10
    move $a1, $t0
    li $t0, 7
    move $a2, $t0
    jal fn_fillArray
    move $t0, $v0
    sw $t0, 364($sp)
    addi $t0, $sp, 0
    move $a0, $t0
    addi $t0, $sp, 40
    move $a1, $t0
    li $t0, 10
    move $a2, $t0
    jal fn_copyArray
    move $t0, $v0
    sw $t0, 368($sp)
    addi $t0, $sp, 0
    move $a0, $t0
    addi $t0, $sp, 40
    move $a1, $t0
    li $t0, 10
    move $a2, $t0
    jal fn_arrayEqual
    move $t0, $v0
    sw $t0, 372($sp)
    lw $t0, 372($sp)
    sw $t0, 84($sp)
    lw $t0, 84($sp)
    move $a0, $t0
    jal fn_output
    move $t0, $v0
    sw $t0, 376($sp)
    li $t0, 19
    move $a0, $t0
    jal fn_output
    move $t0, $v0
    sw $t0, 380($sp)
    li $t0, 0
    li $t1, 15
    sub $t0, $t0, $t1
    sw $t0, 384($sp)
    lw $t0, 384($sp)
    move $a0, $t0
    jal fn_absoluteValue
    move $t0, $v0
    sw $t0, 388($sp)
    lw $t0, 388($sp)
    sw $t0, 84($sp)
    lw $t0, 84($sp)
    move $a0, $t0
    jal fn_output
    move $t0, $v0
    sw $t0, 392($sp)
    li $t0, 0
    li $t1, 5
    sub $t0, $t0, $t1
    sw $t0, 396($sp)
    lw $t0, 396($sp)
    move $a0, $t0
    jal fn_sign
    move $t0, $v0
    sw $t0, 400($sp)
    lw $t0, 400($sp)
    sw $t0, 84($sp)
    lw $t0, 84($sp)
    move $a0, $t0
    jal fn_output
    move $t0, $v0
    sw $t0, 404($sp)
    li $t0, 5
    move $a0, $t0
    jal fn_sign
    move $t0, $v0
    sw $t0, 408($sp)
    lw $t0, 408($sp)
    sw $t0, 84($sp)
    lw $t0, 84($sp)
    move $a0, $t0
    jal fn_output
    move $t0, $v0
    sw $t0, 412($sp)
    li $t0, 0
    move $a0, $t0
    jal fn_sign
    move $t0, $v0
    sw $t0, 416($sp)
    lw $t0, 416($sp)
    sw $t0, 84($sp)
    lw $t0, 84($sp)
    move $a0, $t0
    jal fn_output
    move $t0, $v0
    sw $t0, 420($sp)
    li $t0, 20
    move $a0, $t0
    jal fn_output
    move $t0, $v0
    sw $t0, 424($sp)
    li $t0, 5
    move $a0, $t0
    jal fn_sumOfSquares
    move $t0, $v0
    sw $t0, 428($sp)
    lw $t0, 428($sp)
    sw $t0, 84($sp)
    lw $t0, 84($sp)
    move $a0, $t0
    jal fn_output
    move $t0, $v0
    sw $t0, 432($sp)
    li $t0, 5
    move $a0, $t0
    jal fn_sumOfCubes
    move $t0, $v0
    sw $t0, 436($sp)
    lw $t0, 436($sp)
    sw $t0, 84($sp)
    lw $t0, 84($sp)
    move $a0, $t0
    jal fn_output
    move $t0, $v0
    sw $t0, 440($sp)
    li $t0, 21
    move $a0, $t0
    jal fn_output
    move $t0, $v0
    sw $t0, 444($sp)
    li $t0, 0
    sw $t0, 80($sp)
__while_start_100:
    lw $t0, 80($sp)
    li $t1, 1
    add $t0, $t0, $t1
    sw $t0, 448($sp)
    lw $t0, 448($sp)
    li $t1, 2
    mul $t0, $t0, $t1
    sw $t0, 452($sp)
    lw $t0, 80($sp)
    # Bounds check for array testArray
    bltz $t0, __bounds_error_11
    li $t1, 10
    bge $t0, $t1, __bounds_error_11
    j __bounds_ok_11
__bounds_error_11:
    li $v0, 4
    la $a0, __array_oob_msg
    syscall
    li $v0, 10
    syscall
__bounds_ok_11:
    addi $t2, $sp, 0
    sll $t0, $t0, 2
    add $t2, $t2, $t0
    lw $t3, 452($sp)
    sw $t3, 0($t2)
    lw $t0, 80($sp)
    li $t1, 1
    add $t0, $t0, $t1
    sw $t0, 456($sp)
    lw $t0, 456($sp)
    sw $t0, 80($sp)
    lw $t0, 80($sp)
    li $t1, 1
    add $t0, $t0, $t1
    sw $t0, 448($sp)
    lw $t0, 448($sp)
    li $t1, 2
    mul $t0, $t0, $t1
    sw $t0, 452($sp)
    lw $t0, 80($sp)
    # Bounds check for array testArray
    bltz $t0, __bounds_error_12
    li $t1, 10
    bge $t0, $t1, __bounds_error_12
    j __bounds_ok_12
__bounds_error_12:
    li $v0, 4
    la $a0, __array_oob_msg
    syscall
    li $v0, 10
    syscall
__bounds_ok_12:
    addi $t2, $sp, 0
    sll $t0, $t0, 2
    add $t2, $t2, $t0
    lw $t3, 452($sp)
    sw $t3, 0($t2)
    lw $t0, 80($sp)
    li $t1, 1
    add $t0, $t0, $t1
    sw $t0, 456($sp)
    lw $t0, 456($sp)
    sw $t0, 80($sp)
    lw $t0, 80($sp)
    li $t1, 1
    add $t0, $t0, $t1
    sw $t0, 448($sp)
    lw $t0, 448($sp)
    li $t1, 2
    mul $t0, $t0, $t1
    sw $t0, 452($sp)
    lw $t0, 80($sp)
    # Bounds check for array testArray
    bltz $t0, __bounds_error_13
    li $t1, 10
    bge $t0, $t1, __bounds_error_13
    j __bounds_ok_13
__bounds_error_13:
    li $v0, 4
    la $a0, __array_oob_msg
    syscall
    li $v0, 10
    syscall
__bounds_ok_13:
    addi $t2, $sp, 0
    sll $t0, $t0, 2
    add $t2, $t2, $t0
    lw $t3, 452($sp)
    sw $t3, 0($t2)
    lw $t0, 80($sp)
    li $t1, 1
    add $t0, $t0, $t1
    sw $t0, 456($sp)
    lw $t0, 456($sp)
    sw $t0, 80($sp)
    lw $t0, 80($sp)
    li $t1, 1
    add $t0, $t0, $t1
    sw $t0, 448($sp)
    lw $t0, 448($sp)
    li $t1, 2
    mul $t0, $t0, $t1
    sw $t0, 452($sp)
    lw $t0, 80($sp)
    # Bounds check for array testArray
    bltz $t0, __bounds_error_14
    li $t1, 10
    bge $t0, $t1, __bounds_error_14
    j __bounds_ok_14
__bounds_error_14:
    li $v0, 4
    la $a0, __array_oob_msg
    syscall
    li $v0, 10
    syscall
__bounds_ok_14:
    addi $t2, $sp, 0
    sll $t0, $t0, 2
    add $t2, $t2, $t0
    lw $t3, 452($sp)
    sw $t3, 0($t2)
    lw $t0, 80($sp)
    li $t1, 1
    add $t0, $t0, $t1
    sw $t0, 456($sp)
    lw $t0, 456($sp)
    sw $t0, 80($sp)
    lw $t0, 80($sp)
    li $t1, 1
    add $t0, $t0, $t1
    sw $t0, 448($sp)
    lw $t0, 448($sp)
    li $t1, 2
    mul $t0, $t0, $t1
    sw $t0, 452($sp)
    lw $t0, 80($sp)
    # Bounds check for array testArray
    bltz $t0, __bounds_error_15
    li $t1, 10
    bge $t0, $t1, __bounds_error_15
    j __bounds_ok_15
__bounds_error_15:
    li $v0, 4
    la $a0, __array_oob_msg
    syscall
    li $v0, 10
    syscall
__bounds_ok_15:
    addi $t2, $sp, 0
    sll $t0, $t0, 2
    add $t2, $t2, $t0
    lw $t3, 452($sp)
    sw $t3, 0($t2)
    lw $t0, 80($sp)
    li $t1, 1
    add $t0, $t0, $t1
    sw $t0, 456($sp)
    lw $t0, 456($sp)
    sw $t0, 80($sp)
__while_end_101:
    addi $t0, $sp, 0
    move $a0, $t0
    li $t0, 5
    move $a1, $t0
    jal fn_calculateMean
    move $t0, $v0
    sw $t0, 460($sp)
    lw $t0, 460($sp)
    sw $t0, 84($sp)
    lw $t0, 84($sp)
    move $a0, $t0
    jal fn_output
    move $t0, $v0
    sw $t0, 464($sp)
    li $t0, 0
    # Bounds check for array testArray
    bltz $t0, __bounds_error_16
    li $t1, 10
    bge $t0, $t1, __bounds_error_16
    j __bounds_ok_16
__bounds_error_16:
    li $v0, 4
    la $a0, __array_oob_msg
    syscall
    li $v0, 10
    syscall
__bounds_ok_16:
    addi $t2, $sp, 0
    sll $t0, $t0, 2
    add $t2, $t2, $t0
    li $t3, 5
    sw $t3, 0($t2)
    li $t0, 1
    # Bounds check for array testArray
    bltz $t0, __bounds_error_17
    li $t1, 10
    bge $t0, $t1, __bounds_error_17
    j __bounds_ok_17
__bounds_error_17:
    li $v0, 4
    la $a0, __array_oob_msg
    syscall
    li $v0, 10
    syscall
__bounds_ok_17:
    addi $t2, $sp, 0
    sll $t0, $t0, 2
    add $t2, $t2, $t0
    li $t3, 5
    sw $t3, 0($t2)
    li $t0, 2
    # Bounds check for array testArray
    bltz $t0, __bounds_error_18
    li $t1, 10
    bge $t0, $t1, __bounds_error_18
    j __bounds_ok_18
__bounds_error_18:
    li $v0, 4
    la $a0, __array_oob_msg
    syscall
    li $v0, 10
    syscall
__bounds_ok_18:
    addi $t2, $sp, 0
    sll $t0, $t0, 2
    add $t2, $t2, $t0
    li $t3, 3
    sw $t3, 0($t2)
    li $t0, 3
    # Bounds check for array testArray
    bltz $t0, __bounds_error_19
    li $t1, 10
    bge $t0, $t1, __bounds_error_19
    j __bounds_ok_19
__bounds_error_19:
    li $v0, 4
    la $a0, __array_oob_msg
    syscall
    li $v0, 10
    syscall
__bounds_ok_19:
    addi $t2, $sp, 0
    sll $t0, $t0, 2
    add $t2, $t2, $t0
    li $t3, 5
    sw $t3, 0($t2)
    li $t0, 4
    # Bounds check for array testArray
    bltz $t0, __bounds_error_20
    li $t1, 10
    bge $t0, $t1, __bounds_error_20
    j __bounds_ok_20
__bounds_error_20:
    li $v0, 4
    la $a0, __array_oob_msg
    syscall
    li $v0, 10
    syscall
__bounds_ok_20:
    addi $t2, $sp, 0
    sll $t0, $t0, 2
    add $t2, $t2, $t0
    li $t3, 7
    sw $t3, 0($t2)
    addi $t0, $sp, 0
    move $a0, $t0
    li $t0, 5
    move $a1, $t0
    li $t0, 5
    move $a2, $t0
    jal fn_countOccurrences
    move $t0, $v0
    sw $t0, 468($sp)
    lw $t0, 468($sp)
    sw $t0, 84($sp)
    lw $t0, 84($sp)
    move $a0, $t0
    jal fn_output
    move $t0, $v0
    sw $t0, 472($sp)
    li $t0, 22
    move $a0, $t0
    jal fn_output
    move $t0, $v0
    sw $t0, 476($sp)
    li $t0, 3
    move $a0, $t0
    li $t0, 2
    move $a1, $t0
    jal fn_leftShift
    move $t0, $v0
    sw $t0, 480($sp)
    lw $t0, 480($sp)
    sw $t0, 84($sp)
    lw $t0, 84($sp)
    move $a0, $t0
    jal fn_output
    move $t0, $v0
    sw $t0, 484($sp)
    li $t0, 16
    move $a0, $t0
    li $t0, 2
    move $a1, $t0
    jal fn_rightShift
    move $t0, $v0
    sw $t0, 488($sp)
    lw $t0, 488($sp)
    sw $t0, 84($sp)
    lw $t0, 84($sp)
    move $a0, $t0
    jal fn_output
    move $t0, $v0
    sw $t0, 492($sp)
    li $t0, 23
    move $a0, $t0
    jal fn_output
    move $t0, $v0
    sw $t0, 496($sp)
    li $t0, 10
    move $a0, $t0
    li $t0, 5
    move $a1, $t0
    li $t0, 3
    move $a2, $t0
    jal fn_testComplexExpressions
    move $t0, $v0
    sw $t0, 500($sp)
    lw $t0, 500($sp)
    sw $t0, 84($sp)
    lw $t0, 84($sp)
    move $a0, $t0
    jal fn_output
    move $t0, $v0
    sw $t0, 504($sp)
    li $t0, 24
    move $a0, $t0
    jal fn_output
    move $t0, $v0
    sw $t0, 508($sp)
    li $t0, 100
    sw $t0, globalCounter
    li $t0, 0
    # Bounds check for array globalArray
    bltz $t0, __bounds_error_21
    li $t1, 20
    bge $t0, $t1, __bounds_error_21
    j __bounds_ok_21
__bounds_error_21:
    li $v0, 4
    la $a0, __array_oob_msg
    syscall
    li $v0, 10
    syscall
__bounds_ok_21:
    la $t2, globalArray
    sll $t0, $t0, 2
    add $t2, $t2, $t0
    li $t3, 10
    sw $t3, 0($t2)
    li $t0, 1
    # Bounds check for array globalArray
    bltz $t0, __bounds_error_22
    li $t1, 20
    bge $t0, $t1, __bounds_error_22
    j __bounds_ok_22
__bounds_error_22:
    li $v0, 4
    la $a0, __array_oob_msg
    syscall
    li $v0, 10
    syscall
__bounds_ok_22:
    la $t2, globalArray
    sll $t0, $t0, 2
    add $t2, $t2, $t0
    li $t3, 20
    sw $t3, 0($t2)
    li $t0, 2
    # Bounds check for array globalArray
    bltz $t0, __bounds_error_23
    li $t1, 20
    bge $t0, $t1, __bounds_error_23
    j __bounds_ok_23
__bounds_error_23:
    li $v0, 4
    la $a0, __array_oob_msg
    syscall
    li $v0, 10
    syscall
__bounds_ok_23:
    la $t2, globalArray
    sll $t0, $t0, 2
    add $t2, $t2, $t0
    li $t3, 30
    sw $t3, 0($t2)
    lw $t0, globalCounter
    move $a0, $t0
    jal fn_output
    move $t0, $v0
    sw $t0, 512($sp)
    li $t0, 0
    # Bounds check for array globalArray
    bltz $t0, __bounds_error_24
    li $t1, 20
    bge $t0, $t1, __bounds_error_24
    j __bounds_ok_24
__bounds_error_24:
    li $v0, 4
    la $a0, __array_oob_msg
    syscall
    li $v0, 10
    syscall
__bounds_ok_24:
    la $t2, globalArray
    sll $t0, $t0, 2
    add $t2, $t2, $t0
    lw $t2, 0($t2)
    sw $t2, 516($sp)
    li $t0, 1
    # Bounds check for array globalArray
    bltz $t0, __bounds_error_25
    li $t1, 20
    bge $t0, $t1, __bounds_error_25
    j __bounds_ok_25
__bounds_error_25:
    li $v0, 4
    la $a0, __array_oob_msg
    syscall
    li $v0, 10
    syscall
__bounds_ok_25:
    la $t2, globalArray
    sll $t0, $t0, 2
    add $t2, $t2, $t0
    lw $t2, 0($t2)
    sw $t2, 520($sp)
    lw $t0, 516($sp)
    lw $t1, 520($sp)
    add $t0, $t0, $t1
    sw $t0, 524($sp)
    li $t0, 2
    # Bounds check for array globalArray
    bltz $t0, __bounds_error_26
    li $t1, 20
    bge $t0, $t1, __bounds_error_26
    j __bounds_ok_26
__bounds_error_26:
    li $v0, 4
    la $a0, __array_oob_msg
    syscall
    li $v0, 10
    syscall
__bounds_ok_26:
    la $t2, globalArray
    sll $t0, $t0, 2
    add $t2, $t2, $t0
    lw $t2, 0($t2)
    sw $t2, 528($sp)
    lw $t0, 524($sp)
    lw $t1, 528($sp)
    add $t0, $t0, $t1
    sw $t0, 532($sp)
    lw $t0, 532($sp)
    move $a0, $t0
    jal fn_output
    move $t0, $v0
    sw $t0, 536($sp)
    li $t0, 25
    move $a0, $t0
    jal fn_output
    move $t0, $v0
    sw $t0, 540($sp)
    li $t0, 5
    move $a0, $t0
    jal fn_testVoidFunction
    move $t0, $v0
    sw $t0, 544($sp)
    li $t0, 999
    move $a0, $t0
    jal fn_output
    move $t0, $v0
    sw $t0, 548($sp)
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
