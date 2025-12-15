.data

__array_oob_msg: .asciiz "Runtime error: array index out of bounds\n"

.text
.globl main

fn_classify:
    addi $sp, $sp, -400
    sw $ra, 396($sp)
    sw $a0, 0($sp)

    lw $t0, 0($sp)
    li $t1, 0
    xor $t3, $t0, $t1
    sltiu $t2, $t3, 1
    sw $t2, 4($sp)
    lw $t0, 4($sp)
    sltu $t1, $zero, $t0
    bne $t1, $zero, __switch_case_1
    lw $t0, 0($sp)
    li $t1, 1
    xor $t3, $t0, $t1
    sltiu $t2, $t3, 1
    sw $t2, 8($sp)
    lw $t0, 8($sp)
    sltu $t1, $zero, $t0
    bne $t1, $zero, __switch_case_2
    lw $t0, 0($sp)
    li $t1, 2
    xor $t3, $t0, $t1
    sltiu $t2, $t3, 1
    sw $t2, 12($sp)
    lw $t0, 12($sp)
    sltu $t1, $zero, $t0
    bne $t1, $zero, __switch_case_3
    j __switch_default_4
__switch_case_1:
    li $t0, 100
    move $v0, $t0
    j __return_fn_classify
__switch_case_2:
    li $t0, 200
    move $v0, $t0
    j __return_fn_classify
__switch_case_3:
    li $t0, 300
    move $v0, $t0
    j __return_fn_classify
__switch_default_4:
    li $t0, 999
    move $v0, $t0
    j __return_fn_classify
__switch_end_0:
__return_fn_classify:
    lw $ra, 396($sp)
    addi $sp, $sp, 400
    jr $ra

main:
    addi $sp, $sp, -400
    li $t0, 0
    sw $t0, 0($sp)
    li $t0, 2
    sw $t0, 4($sp)
    lw $t0, 4($sp)
    li $t1, 1
    xor $t3, $t0, $t1
    sltiu $t2, $t3, 1
    sw $t2, 8($sp)
    lw $t0, 8($sp)
    sltu $t1, $zero, $t0
    bne $t1, $zero, __switch_case_6
    lw $t0, 4($sp)
    li $t1, 2
    xor $t3, $t0, $t1
    sltiu $t2, $t3, 1
    sw $t2, 12($sp)
    lw $t0, 12($sp)
    sltu $t1, $zero, $t0
    bne $t1, $zero, __switch_case_7
    lw $t0, 4($sp)
    li $t1, 3
    xor $t3, $t0, $t1
    sltiu $t2, $t3, 1
    sw $t2, 16($sp)
    lw $t0, 16($sp)
    sltu $t1, $zero, $t0
    bne $t1, $zero, __switch_case_8
    j __switch_default_9
__switch_case_6:
    lw $t0, 0($sp)
    li $t1, 10
    add $t0, $t0, $t1
    sw $t0, 20($sp)
    lw $t0, 20($sp)
    sw $t0, 0($sp)
    j __switch_end_5
__switch_case_7:
    lw $t0, 0($sp)
    li $t1, 20
    add $t0, $t0, $t1
    sw $t0, 24($sp)
    lw $t0, 24($sp)
    sw $t0, 0($sp)
__switch_case_8:
    lw $t0, 0($sp)
    li $t1, 30
    add $t0, $t0, $t1
    sw $t0, 28($sp)
    lw $t0, 28($sp)
    sw $t0, 0($sp)
    j __switch_end_5
__switch_default_9:
    lw $t0, 0($sp)
    li $t1, 40
    add $t0, $t0, $t1
    sw $t0, 32($sp)
    lw $t0, 32($sp)
    sw $t0, 0($sp)
__switch_end_5:
    lw $t0, 0($sp)
    move $a0, $t0
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    li $t0, 5
    li $t1, 7
    xor $t3, $t0, $t1
    sltiu $t2, $t3, 1
    sw $t2, 36($sp)
    lw $t0, 36($sp)
    sltu $t1, $zero, $t0
    bne $t1, $zero, __switch_case_11
    j __switch_default_12
__switch_case_11:
    li $t0, 777
    move $a0, $t0
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    j __switch_end_10
__switch_default_12:
    li $t0, 888
    move $a0, $t0
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
__switch_end_10:
    li $t0, 3
    sw $t0, 40($sp)
    lw $t0, 40($sp)
    li $t1, 1
    sub $t0, $t0, $t1
    sw $t0, 44($sp)
    lw $t0, 44($sp)
    li $t1, 1
    xor $t3, $t0, $t1
    sltiu $t2, $t3, 1
    sw $t2, 48($sp)
    lw $t0, 48($sp)
    sltu $t1, $zero, $t0
    bne $t1, $zero, __switch_case_14
    lw $t0, 44($sp)
    li $t1, 2
    xor $t3, $t0, $t1
    sltiu $t2, $t3, 1
    sw $t2, 52($sp)
    lw $t0, 52($sp)
    sltu $t1, $zero, $t0
    bne $t1, $zero, __switch_case_15
    j __switch_default_16
__switch_case_14:
    li $t0, 0
    move $a0, $t0
    jal fn_classify
    move $t0, $v0
    sw $t0, 56($sp)
    lw $t0, 56($sp)
    move $a0, $t0
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    j __switch_end_13
__switch_case_15:
    li $t0, 1
    move $a0, $t0
    jal fn_classify
    move $t0, $v0
    sw $t0, 60($sp)
    lw $t0, 60($sp)
    move $a0, $t0
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    j __switch_end_13
__switch_default_16:
    li $t0, 5
    move $a0, $t0
    jal fn_classify
    move $t0, $v0
    sw $t0, 64($sp)
    lw $t0, 64($sp)
    move $a0, $t0
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
__switch_end_13:
    li $t0, 1
    sw $t0, 68($sp)
    lw $t0, 68($sp)
    li $t1, 1
    xor $t3, $t0, $t1
    sltiu $t2, $t3, 1
    sw $t2, 72($sp)
    lw $t0, 72($sp)
    sltu $t1, $zero, $t0
    bne $t1, $zero, __switch_case_18
    lw $t0, 68($sp)
    li $t1, 2
    xor $t3, $t0, $t1
    sltiu $t2, $t3, 1
    sw $t2, 76($sp)
    lw $t0, 76($sp)
    sltu $t1, $zero, $t0
    bne $t1, $zero, __switch_case_19
    j __switch_end_17
__switch_case_18:
    li $t0, 444
    move $a0, $t0
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    j __switch_end_17
__switch_case_19:
    li $t0, 0
    move $a0, $t0
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    j __switch_end_17
__switch_end_17:
    li $t0, 0
    move $v0, $t0
    j __return_main
__return_main:
    addi $sp, $sp, 400
    li $v0, 10
    syscall

