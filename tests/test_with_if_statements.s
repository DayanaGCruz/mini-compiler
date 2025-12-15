.data

__array_oob_msg: .asciiz "Runtime error: array index out of bounds\n"

.text
.globl main

fn_max:
    addi $sp, $sp, -400
    sw $ra, 396($sp)
    sw $a0, 0($sp)
    sw $a1, 4($sp)

    lw $t0, 0($sp)
    lw $t1, 4($sp)
    slt $t2, $t1, $t0
    sw $t2, 8($sp)
    lw $t0, 8($sp)
    sltu $t1, $zero, $t0
    beq $t1, $zero, __if_else_0
    lw $t0, 0($sp)
    move $v0, $t0
    j __return_fn_max
    j __if_end_1
__if_else_0:
    lw $t0, 4($sp)
    move $v0, $t0
    j __return_fn_max
__if_end_1:
__return_fn_max:
    lw $ra, 396($sp)
    addi $sp, $sp, 400
    jr $ra

fn_min:
    addi $sp, $sp, -400
    sw $ra, 396($sp)
    sw $a0, 0($sp)
    sw $a1, 4($sp)

    lw $t0, 0($sp)
    lw $t1, 4($sp)
    slt $t2, $t0, $t1
    sw $t2, 8($sp)
    lw $t0, 8($sp)
    sltu $t1, $zero, $t0
    beq $t1, $zero, __if_else_2
    lw $t0, 0($sp)
    move $v0, $t0
    j __return_fn_min
    j __if_end_3
__if_else_2:
    lw $t0, 4($sp)
    move $v0, $t0
    j __return_fn_min
__if_end_3:
__return_fn_min:
    lw $ra, 396($sp)
    addi $sp, $sp, 400
    jr $ra

fn_absolute:
    addi $sp, $sp, -400
    sw $ra, 396($sp)
    sw $a0, 0($sp)

    lw $t0, 0($sp)
    li $t1, 0
    slt $t2, $t0, $t1
    sw $t2, 4($sp)
    lw $t0, 4($sp)
    sltu $t1, $zero, $t0
    beq $t1, $zero, __if_else_4
    li $t0, 0
    lw $t1, 0($sp)
    sub $t0, $t0, $t1
    sw $t0, 8($sp)
    lw $t0, 8($sp)
    move $v0, $t0
    j __return_fn_absolute
    j __if_end_5
__if_else_4:
    lw $t0, 0($sp)
    move $v0, $t0
    j __return_fn_absolute
__if_end_5:
__return_fn_absolute:
    lw $ra, 396($sp)
    addi $sp, $sp, 400
    jr $ra

fn_sign:
    addi $sp, $sp, -400
    sw $ra, 396($sp)
    sw $a0, 0($sp)

    lw $t0, 0($sp)
    li $t1, 0
    slt $t2, $t1, $t0
    sw $t2, 4($sp)
    lw $t0, 4($sp)
    sltu $t1, $zero, $t0
    beq $t1, $zero, __if_else_6
    li $t0, 1
    move $v0, $t0
    j __return_fn_sign
    j __if_end_7
__if_else_6:
    lw $t0, 0($sp)
    li $t1, 0
    slt $t2, $t0, $t1
    sw $t2, 8($sp)
    lw $t0, 8($sp)
    sltu $t1, $zero, $t0
    beq $t1, $zero, __if_else_8
    li $t0, 0
    li $t1, 1
    sub $t0, $t0, $t1
    sw $t0, 12($sp)
    lw $t0, 12($sp)
    move $v0, $t0
    j __return_fn_sign
    j __if_end_9
__if_else_8:
    li $t0, 0
    move $v0, $t0
    j __return_fn_sign
__if_end_9:
__if_end_7:
__return_fn_sign:
    lw $ra, 396($sp)
    addi $sp, $sp, 400
    jr $ra

fn_compare:
    addi $sp, $sp, -400
    sw $ra, 396($sp)
    sw $a0, 0($sp)
    sw $a1, 4($sp)

    lw $t0, 0($sp)
    lw $t1, 4($sp)
    slt $t2, $t1, $t0
    sw $t2, 12($sp)
    lw $t0, 12($sp)
    sltu $t1, $zero, $t0
    beq $t1, $zero, __if_else_10
    li $t0, 1
    sw $t0, 8($sp)
    j __if_end_11
__if_else_10:
    lw $t0, 0($sp)
    lw $t1, 4($sp)
    slt $t2, $t0, $t1
    sw $t2, 16($sp)
    lw $t0, 16($sp)
    sltu $t1, $zero, $t0
    beq $t1, $zero, __if_else_12
    li $t0, 0
    li $t1, 1
    sub $t0, $t0, $t1
    sw $t0, 20($sp)
    lw $t0, 20($sp)
    sw $t0, 8($sp)
    j __if_end_13
__if_else_12:
    li $t0, 0
    sw $t0, 8($sp)
__if_end_13:
__if_end_11:
    lw $t0, 8($sp)
    move $v0, $t0
    j __return_fn_compare
__return_fn_compare:
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
    lw $t1, 4($sp)
    slt $t2, $t1, $t0
    sw $t2, 16($sp)
    lw $t0, 16($sp)
    sltu $t1, $zero, $t0
    beq $t1, $zero, __if_else_14
    lw $t0, 0($sp)
    sw $t0, 12($sp)
    j __if_end_15
__if_else_14:
    lw $t0, 4($sp)
    sw $t0, 12($sp)
__if_end_15:
    lw $t0, 12($sp)
    lw $t1, 8($sp)
    slt $t2, $t1, $t0
    sw $t2, 20($sp)
    lw $t0, 20($sp)
    sltu $t1, $zero, $t0
    beq $t1, $zero, __if_else_16
    lw $t0, 12($sp)
    move $v0, $t0
    j __return_fn_max3
    j __if_end_17
__if_else_16:
    lw $t0, 8($sp)
    move $v0, $t0
    j __return_fn_max3
__if_end_17:
__return_fn_max3:
    lw $ra, 396($sp)
    addi $sp, $sp, 400
    jr $ra

fn_min3:
    addi $sp, $sp, -400
    sw $ra, 396($sp)
    sw $a0, 0($sp)
    sw $a1, 4($sp)
    sw $a2, 8($sp)

    lw $t0, 0($sp)
    lw $t1, 4($sp)
    slt $t2, $t0, $t1
    sw $t2, 12($sp)
    lw $t0, 12($sp)
    sltu $t1, $zero, $t0
    beq $t1, $zero, __if_else_18
    lw $t0, 0($sp)
    lw $t1, 8($sp)
    slt $t2, $t0, $t1
    sw $t2, 16($sp)
    lw $t0, 16($sp)
    sltu $t1, $zero, $t0
    beq $t1, $zero, __if_else_20
    lw $t0, 0($sp)
    move $v0, $t0
    j __return_fn_min3
    j __if_end_21
__if_else_20:
    lw $t0, 8($sp)
    move $v0, $t0
    j __return_fn_min3
__if_end_21:
    j __if_end_19
__if_else_18:
    lw $t0, 4($sp)
    lw $t1, 8($sp)
    slt $t2, $t0, $t1
    sw $t2, 20($sp)
    lw $t0, 20($sp)
    sltu $t1, $zero, $t0
    beq $t1, $zero, __if_else_22
    lw $t0, 4($sp)
    move $v0, $t0
    j __return_fn_min3
    j __if_end_23
__if_else_22:
    lw $t0, 8($sp)
    move $v0, $t0
    j __return_fn_min3
__if_end_23:
__if_end_19:
__return_fn_min3:
    lw $ra, 396($sp)
    addi $sp, $sp, 400
    jr $ra

fn_inRange:
    addi $sp, $sp, -400
    sw $ra, 396($sp)
    sw $a0, 0($sp)
    sw $a1, 4($sp)
    sw $a2, 8($sp)

    lw $t0, 0($sp)
    lw $t1, 4($sp)
    slt $t2, $t0, $t1
    xori $t2, $t2, 1
    sw $t2, 12($sp)
    lw $t0, 12($sp)
    sltu $t1, $zero, $t0
    beq $t1, $zero, __if_else_24
    lw $t0, 0($sp)
    lw $t1, 8($sp)
    slt $t2, $t1, $t0
    xori $t2, $t2, 1
    sw $t2, 16($sp)
    lw $t0, 16($sp)
    sltu $t1, $zero, $t0
    beq $t1, $zero, __if_else_26
    li $t0, 1
    move $v0, $t0
    j __return_fn_inRange
    j __if_end_27
__if_else_26:
    li $t0, 0
    move $v0, $t0
    j __return_fn_inRange
__if_end_27:
    j __if_end_25
__if_else_24:
    li $t0, 0
    move $v0, $t0
    j __return_fn_inRange
__if_end_25:
__return_fn_inRange:
    lw $ra, 396($sp)
    addi $sp, $sp, 400
    jr $ra

fn_conditionalAdd:
    addi $sp, $sp, -400
    sw $ra, 396($sp)
    sw $a0, 0($sp)
    sw $a1, 4($sp)

    lw $t0, 0($sp)
    li $t1, 0
    slt $t2, $t1, $t0
    sw $t2, 8($sp)
    lw $t0, 8($sp)
    sltu $t1, $zero, $t0
    beq $t1, $zero, __if_else_28
    lw $t0, 4($sp)
    li $t1, 0
    slt $t2, $t1, $t0
    sw $t2, 12($sp)
    lw $t0, 12($sp)
    sltu $t1, $zero, $t0
    beq $t1, $zero, __if_else_30
    lw $t0, 0($sp)
    lw $t1, 4($sp)
    add $t0, $t0, $t1
    sw $t0, 16($sp)
    lw $t0, 16($sp)
    move $v0, $t0
    j __return_fn_conditionalAdd
    j __if_end_31
__if_else_30:
    lw $t0, 0($sp)
    move $v0, $t0
    j __return_fn_conditionalAdd
__if_end_31:
    j __if_end_29
__if_else_28:
    lw $t0, 4($sp)
    li $t1, 0
    slt $t2, $t1, $t0
    sw $t2, 20($sp)
    lw $t0, 20($sp)
    sltu $t1, $zero, $t0
    beq $t1, $zero, __if_else_32
    lw $t0, 4($sp)
    move $v0, $t0
    j __return_fn_conditionalAdd
    j __if_end_33
__if_else_32:
    li $t0, 0
    move $v0, $t0
    j __return_fn_conditionalAdd
__if_end_33:
__if_end_29:
__return_fn_conditionalAdd:
    lw $ra, 396($sp)
    addi $sp, $sp, 400
    jr $ra

fn_safeDivide:
    addi $sp, $sp, -400
    sw $ra, 396($sp)
    sw $a0, 0($sp)
    sw $a1, 4($sp)

    lw $t0, 4($sp)
    li $t1, 0
    xor $t3, $t0, $t1
    sltiu $t2, $t3, 1
    sw $t2, 8($sp)
    lw $t0, 8($sp)
    sltu $t1, $zero, $t0
    beq $t1, $zero, __if_else_34
    li $t0, 0
    move $v0, $t0
    j __return_fn_safeDivide
    j __if_end_35
__if_else_34:
    lw $t0, 0($sp)
    lw $t1, 4($sp)
    div $t0, $t1
    mflo $t0
    sw $t0, 12($sp)
    lw $t0, 12($sp)
    move $v0, $t0
    j __return_fn_safeDivide
__if_end_35:
__return_fn_safeDivide:
    lw $ra, 396($sp)
    addi $sp, $sp, 400
    jr $ra

fn_conditionalMultiply:
    addi $sp, $sp, -400
    sw $ra, 396($sp)
    sw $a0, 0($sp)
    sw $a1, 4($sp)

    lw $t0, 0($sp)
    li $t1, 0
    xor $t2, $t0, $t1
    sltu $t2, $zero, $t2
    sw $t2, 12($sp)
    lw $t0, 12($sp)
    sltu $t1, $zero, $t0
    beq $t1, $zero, __if_else_36
    lw $t0, 4($sp)
    li $t1, 0
    xor $t2, $t0, $t1
    sltu $t2, $zero, $t2
    sw $t2, 16($sp)
    lw $t0, 16($sp)
    sltu $t1, $zero, $t0
    beq $t1, $zero, __if_else_38
    lw $t0, 0($sp)
    lw $t1, 4($sp)
    mul $t0, $t0, $t1
    sw $t0, 20($sp)
    lw $t0, 20($sp)
    sw $t0, 8($sp)
    j __if_end_39
__if_else_38:
    li $t0, 0
    sw $t0, 8($sp)
__if_end_39:
    j __if_end_37
__if_else_36:
    li $t0, 0
    sw $t0, 8($sp)
__if_end_37:
    lw $t0, 8($sp)
    move $v0, $t0
    j __return_fn_conditionalMultiply
__return_fn_conditionalMultiply:
    lw $ra, 396($sp)
    addi $sp, $sp, 400
    jr $ra

fn_complexCondition:
    addi $sp, $sp, -400
    sw $ra, 396($sp)
    sw $a0, 0($sp)
    sw $a1, 4($sp)
    sw $a2, 8($sp)

    lw $t0, 0($sp)
    move $a0, $t0
    lw $t0, 4($sp)
    move $a1, $t0
    jal fn_max
    move $t0, $v0
    sw $t0, 16($sp)
    lw $t0, 16($sp)
    lw $t1, 8($sp)
    slt $t2, $t1, $t0
    sw $t2, 20($sp)
    lw $t0, 20($sp)
    sltu $t1, $zero, $t0
    beq $t1, $zero, __if_else_40
    lw $t0, 0($sp)
    move $a0, $t0
    lw $t0, 4($sp)
    move $a1, $t0
    jal fn_max
    move $t0, $v0
    sw $t0, 24($sp)
    lw $t0, 24($sp)
    lw $t1, 8($sp)
    add $t0, $t0, $t1
    sw $t0, 28($sp)
    lw $t0, 28($sp)
    sw $t0, 12($sp)
    j __if_end_41
__if_else_40:
    lw $t0, 0($sp)
    move $a0, $t0
    lw $t0, 4($sp)
    move $a1, $t0
    jal fn_min
    move $t0, $v0
    sw $t0, 32($sp)
    lw $t0, 32($sp)
    lw $t1, 8($sp)
    slt $t2, $t0, $t1
    sw $t2, 36($sp)
    lw $t0, 36($sp)
    sltu $t1, $zero, $t0
    beq $t1, $zero, __if_else_42
    lw $t0, 0($sp)
    move $a0, $t0
    lw $t0, 4($sp)
    move $a1, $t0
    jal fn_min
    move $t0, $v0
    sw $t0, 40($sp)
    lw $t0, 40($sp)
    lw $t1, 8($sp)
    sub $t0, $t0, $t1
    sw $t0, 44($sp)
    lw $t0, 44($sp)
    sw $t0, 12($sp)
    j __if_end_43
__if_else_42:
    lw $t0, 0($sp)
    lw $t1, 4($sp)
    add $t0, $t0, $t1
    sw $t0, 48($sp)
    lw $t0, 48($sp)
    lw $t1, 8($sp)
    add $t0, $t0, $t1
    sw $t0, 52($sp)
    lw $t0, 52($sp)
    sw $t0, 12($sp)
__if_end_43:
__if_end_41:
    lw $t0, 12($sp)
    move $v0, $t0
    j __return_fn_complexCondition
__return_fn_complexCondition:
    lw $ra, 396($sp)
    addi $sp, $sp, 400
    jr $ra

fn_nestedWithFunctions:
    addi $sp, $sp, -400
    sw $ra, 396($sp)
    sw $a0, 0($sp)
    sw $a1, 4($sp)
    sw $a2, 8($sp)

    lw $t0, 0($sp)
    move $a0, $t0
    jal fn_absolute
    move $t0, $v0
    sw $t0, 16($sp)
    lw $t0, 4($sp)
    move $a0, $t0
    jal fn_absolute
    move $t0, $v0
    sw $t0, 20($sp)
    lw $t0, 16($sp)
    lw $t1, 20($sp)
    slt $t2, $t1, $t0
    sw $t2, 24($sp)
    lw $t0, 24($sp)
    sltu $t1, $zero, $t0
    beq $t1, $zero, __if_else_44
    lw $t0, 0($sp)
    move $a0, $t0
    lw $t0, 8($sp)
    move $a1, $t0
    jal fn_max
    move $t0, $v0
    sw $t0, 28($sp)
    lw $t0, 28($sp)
    li $t1, 0
    slt $t2, $t1, $t0
    sw $t2, 32($sp)
    lw $t0, 32($sp)
    sltu $t1, $zero, $t0
    beq $t1, $zero, __if_else_46
    lw $t0, 0($sp)
    move $a0, $t0
    lw $t0, 8($sp)
    move $a1, $t0
    jal fn_max
    move $t0, $v0
    sw $t0, 36($sp)
    lw $t0, 4($sp)
    move $a0, $t0
    lw $t0, 8($sp)
    move $a1, $t0
    jal fn_min
    move $t0, $v0
    sw $t0, 40($sp)
    lw $t0, 36($sp)
    lw $t1, 40($sp)
    add $t0, $t0, $t1
    sw $t0, 44($sp)
    lw $t0, 44($sp)
    sw $t0, 12($sp)
    j __if_end_47
__if_else_46:
    lw $t0, 0($sp)
    lw $t1, 4($sp)
    sub $t0, $t0, $t1
    sw $t0, 48($sp)
    lw $t0, 48($sp)
    move $a0, $t0
    jal fn_absolute
    move $t0, $v0
    sw $t0, 52($sp)
    lw $t0, 52($sp)
    sw $t0, 12($sp)
__if_end_47:
    j __if_end_45
__if_else_44:
    lw $t0, 4($sp)
    move $a0, $t0
    lw $t0, 8($sp)
    move $a1, $t0
    jal fn_compare
    move $t0, $v0
    sw $t0, 56($sp)
    lw $t0, 56($sp)
    li $t1, 0
    slt $t2, $t1, $t0
    sw $t2, 60($sp)
    lw $t0, 60($sp)
    sltu $t1, $zero, $t0
    beq $t1, $zero, __if_else_48
    lw $t0, 4($sp)
    lw $t1, 8($sp)
    mul $t0, $t0, $t1
    sw $t0, 64($sp)
    lw $t0, 64($sp)
    sw $t0, 12($sp)
    j __if_end_49
__if_else_48:
    lw $t0, 4($sp)
    lw $t1, 8($sp)
    add $t0, $t0, $t1
    sw $t0, 68($sp)
    lw $t0, 68($sp)
    sw $t0, 12($sp)
__if_end_49:
__if_end_45:
    lw $t0, 12($sp)
    move $v0, $t0
    j __return_fn_nestedWithFunctions
__return_fn_nestedWithFunctions:
    lw $ra, 396($sp)
    addi $sp, $sp, 400
    jr $ra

fn_conditionalArraySum:
    addi $sp, $sp, -400
    sw $ra, 396($sp)
    sw $a0, 0($sp)
    sw $a1, 4($sp)
    sw $a2, 8($sp)

    li $t0, 0
    sw $t0, 12($sp)
    li $t0, 0
    lw $t1, 0($sp)
    sll $t0, $t0, 2
    add $t1, $t1, $t0
    lw $t1, 0($t1)
    sw $t1, 20($sp)
    lw $t0, 20($sp)
    sw $t0, 16($sp)
    lw $t0, 16($sp)
    lw $t1, 8($sp)
    slt $t2, $t1, $t0
    sw $t2, 24($sp)
    lw $t0, 24($sp)
    sltu $t1, $zero, $t0
    beq $t1, $zero, __if_end_50
    lw $t0, 12($sp)
    lw $t1, 16($sp)
    add $t0, $t0, $t1
    sw $t0, 28($sp)
    lw $t0, 28($sp)
    sw $t0, 12($sp)
__if_end_50:
    li $t0, 1
    lw $t1, 0($sp)
    sll $t0, $t0, 2
    add $t1, $t1, $t0
    lw $t1, 0($t1)
    sw $t1, 32($sp)
    lw $t0, 32($sp)
    sw $t0, 16($sp)
    lw $t0, 16($sp)
    lw $t1, 8($sp)
    slt $t2, $t1, $t0
    sw $t2, 36($sp)
    lw $t0, 36($sp)
    sltu $t1, $zero, $t0
    beq $t1, $zero, __if_end_51
    lw $t0, 12($sp)
    lw $t1, 16($sp)
    add $t0, $t0, $t1
    sw $t0, 40($sp)
    lw $t0, 40($sp)
    sw $t0, 12($sp)
__if_end_51:
    li $t0, 2
    lw $t1, 0($sp)
    sll $t0, $t0, 2
    add $t1, $t1, $t0
    lw $t1, 0($t1)
    sw $t1, 44($sp)
    lw $t0, 44($sp)
    sw $t0, 16($sp)
    lw $t0, 16($sp)
    lw $t1, 8($sp)
    slt $t2, $t1, $t0
    sw $t2, 48($sp)
    lw $t0, 48($sp)
    sltu $t1, $zero, $t0
    beq $t1, $zero, __if_end_52
    lw $t0, 12($sp)
    lw $t1, 16($sp)
    add $t0, $t0, $t1
    sw $t0, 52($sp)
    lw $t0, 52($sp)
    sw $t0, 12($sp)
__if_end_52:
    li $t0, 3
    lw $t1, 0($sp)
    sll $t0, $t0, 2
    add $t1, $t1, $t0
    lw $t1, 0($t1)
    sw $t1, 56($sp)
    lw $t0, 56($sp)
    sw $t0, 16($sp)
    lw $t0, 16($sp)
    lw $t1, 8($sp)
    slt $t2, $t1, $t0
    sw $t2, 60($sp)
    lw $t0, 60($sp)
    sltu $t1, $zero, $t0
    beq $t1, $zero, __if_end_53
    lw $t0, 12($sp)
    lw $t1, 16($sp)
    add $t0, $t0, $t1
    sw $t0, 64($sp)
    lw $t0, 64($sp)
    sw $t0, 12($sp)
__if_end_53:
    li $t0, 4
    lw $t1, 0($sp)
    sll $t0, $t0, 2
    add $t1, $t1, $t0
    lw $t1, 0($t1)
    sw $t1, 68($sp)
    lw $t0, 68($sp)
    sw $t0, 16($sp)
    lw $t0, 16($sp)
    lw $t1, 8($sp)
    slt $t2, $t1, $t0
    sw $t2, 72($sp)
    lw $t0, 72($sp)
    sltu $t1, $zero, $t0
    beq $t1, $zero, __if_end_54
    lw $t0, 12($sp)
    lw $t1, 16($sp)
    add $t0, $t0, $t1
    sw $t0, 76($sp)
    lw $t0, 76($sp)
    sw $t0, 12($sp)
__if_end_54:
    lw $t0, 12($sp)
    move $v0, $t0
    j __return_fn_conditionalArraySum
__return_fn_conditionalArraySum:
    lw $ra, 396($sp)
    addi $sp, $sp, 400
    jr $ra

fn_arrayMax:
    addi $sp, $sp, -400
    sw $ra, 396($sp)
    sw $a0, 0($sp)
    sw $a1, 4($sp)

    li $t0, 0
    lw $t1, 0($sp)
    sll $t0, $t0, 2
    add $t1, $t1, $t0
    lw $t1, 0($t1)
    sw $t1, 12($sp)
    lw $t0, 12($sp)
    sw $t0, 8($sp)
    li $t0, 1
    lw $t1, 0($sp)
    sll $t0, $t0, 2
    add $t1, $t1, $t0
    lw $t1, 0($t1)
    sw $t1, 16($sp)
    lw $t0, 16($sp)
    lw $t1, 8($sp)
    slt $t2, $t1, $t0
    sw $t2, 20($sp)
    lw $t0, 20($sp)
    sltu $t1, $zero, $t0
    beq $t1, $zero, __if_end_55
    li $t0, 1
    lw $t1, 0($sp)
    sll $t0, $t0, 2
    add $t1, $t1, $t0
    lw $t1, 0($t1)
    sw $t1, 24($sp)
    lw $t0, 24($sp)
    sw $t0, 8($sp)
__if_end_55:
    li $t0, 2
    lw $t1, 0($sp)
    sll $t0, $t0, 2
    add $t1, $t1, $t0
    lw $t1, 0($t1)
    sw $t1, 28($sp)
    lw $t0, 28($sp)
    lw $t1, 8($sp)
    slt $t2, $t1, $t0
    sw $t2, 32($sp)
    lw $t0, 32($sp)
    sltu $t1, $zero, $t0
    beq $t1, $zero, __if_end_56
    li $t0, 2
    lw $t1, 0($sp)
    sll $t0, $t0, 2
    add $t1, $t1, $t0
    lw $t1, 0($t1)
    sw $t1, 36($sp)
    lw $t0, 36($sp)
    sw $t0, 8($sp)
__if_end_56:
    li $t0, 3
    lw $t1, 0($sp)
    sll $t0, $t0, 2
    add $t1, $t1, $t0
    lw $t1, 0($t1)
    sw $t1, 40($sp)
    lw $t0, 40($sp)
    lw $t1, 8($sp)
    slt $t2, $t1, $t0
    sw $t2, 44($sp)
    lw $t0, 44($sp)
    sltu $t1, $zero, $t0
    beq $t1, $zero, __if_end_57
    li $t0, 3
    lw $t1, 0($sp)
    sll $t0, $t0, 2
    add $t1, $t1, $t0
    lw $t1, 0($t1)
    sw $t1, 48($sp)
    lw $t0, 48($sp)
    sw $t0, 8($sp)
__if_end_57:
    li $t0, 4
    lw $t1, 0($sp)
    sll $t0, $t0, 2
    add $t1, $t1, $t0
    lw $t1, 0($t1)
    sw $t1, 52($sp)
    lw $t0, 52($sp)
    lw $t1, 8($sp)
    slt $t2, $t1, $t0
    sw $t2, 56($sp)
    lw $t0, 56($sp)
    sltu $t1, $zero, $t0
    beq $t1, $zero, __if_end_58
    li $t0, 4
    lw $t1, 0($sp)
    sll $t0, $t0, 2
    add $t1, $t1, $t0
    lw $t1, 0($t1)
    sw $t1, 60($sp)
    lw $t0, 60($sp)
    sw $t0, 8($sp)
__if_end_58:
    lw $t0, 8($sp)
    move $v0, $t0
    j __return_fn_arrayMax
__return_fn_arrayMax:
    lw $ra, 396($sp)
    addi $sp, $sp, 400
    jr $ra

fn_countPositive:
    addi $sp, $sp, -400
    sw $ra, 396($sp)
    sw $a0, 0($sp)
    sw $a1, 4($sp)

    li $t0, 0
    sw $t0, 8($sp)
    li $t0, 0
    lw $t1, 0($sp)
    sll $t0, $t0, 2
    add $t1, $t1, $t0
    lw $t1, 0($t1)
    sw $t1, 12($sp)
    lw $t0, 12($sp)
    li $t1, 0
    slt $t2, $t1, $t0
    sw $t2, 16($sp)
    lw $t0, 16($sp)
    sltu $t1, $zero, $t0
    beq $t1, $zero, __if_end_59
    lw $t0, 8($sp)
    li $t1, 1
    add $t0, $t0, $t1
    sw $t0, 20($sp)
    lw $t0, 20($sp)
    sw $t0, 8($sp)
__if_end_59:
    li $t0, 1
    lw $t1, 0($sp)
    sll $t0, $t0, 2
    add $t1, $t1, $t0
    lw $t1, 0($t1)
    sw $t1, 24($sp)
    lw $t0, 24($sp)
    li $t1, 0
    slt $t2, $t1, $t0
    sw $t2, 28($sp)
    lw $t0, 28($sp)
    sltu $t1, $zero, $t0
    beq $t1, $zero, __if_end_60
    lw $t0, 8($sp)
    li $t1, 1
    add $t0, $t0, $t1
    sw $t0, 32($sp)
    lw $t0, 32($sp)
    sw $t0, 8($sp)
__if_end_60:
    li $t0, 2
    lw $t1, 0($sp)
    sll $t0, $t0, 2
    add $t1, $t1, $t0
    lw $t1, 0($t1)
    sw $t1, 36($sp)
    lw $t0, 36($sp)
    li $t1, 0
    slt $t2, $t1, $t0
    sw $t2, 40($sp)
    lw $t0, 40($sp)
    sltu $t1, $zero, $t0
    beq $t1, $zero, __if_end_61
    lw $t0, 8($sp)
    li $t1, 1
    add $t0, $t0, $t1
    sw $t0, 44($sp)
    lw $t0, 44($sp)
    sw $t0, 8($sp)
__if_end_61:
    li $t0, 3
    lw $t1, 0($sp)
    sll $t0, $t0, 2
    add $t1, $t1, $t0
    lw $t1, 0($t1)
    sw $t1, 48($sp)
    lw $t0, 48($sp)
    li $t1, 0
    slt $t2, $t1, $t0
    sw $t2, 52($sp)
    lw $t0, 52($sp)
    sltu $t1, $zero, $t0
    beq $t1, $zero, __if_end_62
    lw $t0, 8($sp)
    li $t1, 1
    add $t0, $t0, $t1
    sw $t0, 56($sp)
    lw $t0, 56($sp)
    sw $t0, 8($sp)
__if_end_62:
    li $t0, 4
    lw $t1, 0($sp)
    sll $t0, $t0, 2
    add $t1, $t1, $t0
    lw $t1, 0($t1)
    sw $t1, 60($sp)
    lw $t0, 60($sp)
    li $t1, 0
    slt $t2, $t1, $t0
    sw $t2, 64($sp)
    lw $t0, 64($sp)
    sltu $t1, $zero, $t0
    beq $t1, $zero, __if_end_63
    lw $t0, 8($sp)
    li $t1, 1
    add $t0, $t0, $t1
    sw $t0, 68($sp)
    lw $t0, 68($sp)
    sw $t0, 8($sp)
__if_end_63:
    lw $t0, 8($sp)
    move $v0, $t0
    j __return_fn_countPositive
__return_fn_countPositive:
    lw $ra, 396($sp)
    addi $sp, $sp, 400
    jr $ra

fn_deeplyNested:
    addi $sp, $sp, -400
    sw $ra, 396($sp)
    sw $a0, 0($sp)
    sw $a1, 4($sp)
    sw $a2, 8($sp)
    sw $a3, 12($sp)

    lw $t0, 0($sp)
    li $t1, 0
    slt $t2, $t1, $t0
    sw $t2, 20($sp)
    lw $t0, 20($sp)
    sltu $t1, $zero, $t0
    beq $t1, $zero, __if_else_64
    lw $t0, 4($sp)
    li $t1, 0
    slt $t2, $t1, $t0
    sw $t2, 24($sp)
    lw $t0, 24($sp)
    sltu $t1, $zero, $t0
    beq $t1, $zero, __if_else_66
    lw $t0, 8($sp)
    li $t1, 0
    slt $t2, $t1, $t0
    sw $t2, 28($sp)
    lw $t0, 28($sp)
    sltu $t1, $zero, $t0
    beq $t1, $zero, __if_else_68
    lw $t0, 12($sp)
    li $t1, 0
    slt $t2, $t1, $t0
    sw $t2, 32($sp)
    lw $t0, 32($sp)
    sltu $t1, $zero, $t0
    beq $t1, $zero, __if_else_70
    lw $t0, 0($sp)
    lw $t1, 4($sp)
    add $t0, $t0, $t1
    sw $t0, 36($sp)
    lw $t0, 36($sp)
    lw $t1, 8($sp)
    add $t0, $t0, $t1
    sw $t0, 40($sp)
    lw $t0, 40($sp)
    lw $t1, 12($sp)
    add $t0, $t0, $t1
    sw $t0, 44($sp)
    lw $t0, 44($sp)
    sw $t0, 16($sp)
    j __if_end_71
__if_else_70:
    lw $t0, 0($sp)
    lw $t1, 4($sp)
    add $t0, $t0, $t1
    sw $t0, 48($sp)
    lw $t0, 48($sp)
    lw $t1, 8($sp)
    add $t0, $t0, $t1
    sw $t0, 52($sp)
    lw $t0, 52($sp)
    sw $t0, 16($sp)
__if_end_71:
    j __if_end_69
__if_else_68:
    lw $t0, 12($sp)
    li $t1, 0
    slt $t2, $t1, $t0
    sw $t2, 56($sp)
    lw $t0, 56($sp)
    sltu $t1, $zero, $t0
    beq $t1, $zero, __if_else_72
    lw $t0, 0($sp)
    lw $t1, 4($sp)
    add $t0, $t0, $t1
    sw $t0, 60($sp)
    lw $t0, 60($sp)
    lw $t1, 12($sp)
    add $t0, $t0, $t1
    sw $t0, 64($sp)
    lw $t0, 64($sp)
    sw $t0, 16($sp)
    j __if_end_73
__if_else_72:
    lw $t0, 0($sp)
    lw $t1, 4($sp)
    add $t0, $t0, $t1
    sw $t0, 68($sp)
    lw $t0, 68($sp)
    sw $t0, 16($sp)
__if_end_73:
__if_end_69:
    j __if_end_67
__if_else_66:
    lw $t0, 8($sp)
    li $t1, 0
    slt $t2, $t1, $t0
    sw $t2, 72($sp)
    lw $t0, 72($sp)
    sltu $t1, $zero, $t0
    beq $t1, $zero, __if_else_74
    lw $t0, 12($sp)
    li $t1, 0
    slt $t2, $t1, $t0
    sw $t2, 76($sp)
    lw $t0, 76($sp)
    sltu $t1, $zero, $t0
    beq $t1, $zero, __if_else_76
    lw $t0, 0($sp)
    lw $t1, 8($sp)
    add $t0, $t0, $t1
    sw $t0, 80($sp)
    lw $t0, 80($sp)
    lw $t1, 12($sp)
    add $t0, $t0, $t1
    sw $t0, 84($sp)
    lw $t0, 84($sp)
    sw $t0, 16($sp)
    j __if_end_77
__if_else_76:
    lw $t0, 0($sp)
    lw $t1, 8($sp)
    add $t0, $t0, $t1
    sw $t0, 88($sp)
    lw $t0, 88($sp)
    sw $t0, 16($sp)
__if_end_77:
    j __if_end_75
__if_else_74:
    lw $t0, 0($sp)
    sw $t0, 16($sp)
__if_end_75:
__if_end_67:
    j __if_end_65
__if_else_64:
    lw $t0, 4($sp)
    li $t1, 0
    slt $t2, $t1, $t0
    sw $t2, 92($sp)
    lw $t0, 92($sp)
    sltu $t1, $zero, $t0
    beq $t1, $zero, __if_else_78
    lw $t0, 8($sp)
    li $t1, 0
    slt $t2, $t1, $t0
    sw $t2, 96($sp)
    lw $t0, 96($sp)
    sltu $t1, $zero, $t0
    beq $t1, $zero, __if_else_80
    lw $t0, 4($sp)
    lw $t1, 8($sp)
    add $t0, $t0, $t1
    sw $t0, 100($sp)
    lw $t0, 100($sp)
    sw $t0, 16($sp)
    j __if_end_81
__if_else_80:
    lw $t0, 4($sp)
    sw $t0, 16($sp)
__if_end_81:
    j __if_end_79
__if_else_78:
    li $t0, 0
    sw $t0, 16($sp)
__if_end_79:
__if_end_65:
    lw $t0, 16($sp)
    move $v0, $t0
    j __return_fn_deeplyNested
__return_fn_deeplyNested:
    lw $ra, 396($sp)
    addi $sp, $sp, 400
    jr $ra

fn_conditionalPrint:
    addi $sp, $sp, -400
    sw $ra, 396($sp)
    sw $a0, 0($sp)
    sw $a1, 4($sp)

    lw $t0, 0($sp)
    lw $t1, 4($sp)
    slt $t2, $t1, $t0
    sw $t2, 8($sp)
    lw $t0, 8($sp)
    sltu $t1, $zero, $t0
    beq $t1, $zero, __if_else_82
    lw $t0, 0($sp)
    move $a0, $t0
    jal fn_output
    move $t0, $v0
    sw $t0, 12($sp)
    j __if_end_83
__if_else_82:
    lw $t0, 4($sp)
    move $a0, $t0
    jal fn_output
    move $t0, $v0
    sw $t0, 16($sp)
__if_end_83:
__return_fn_conditionalPrint:
    lw $ra, 396($sp)
    addi $sp, $sp, 400
    jr $ra

fn_printMax:
    addi $sp, $sp, -400
    sw $ra, 396($sp)
    sw $a0, 0($sp)
    sw $a1, 4($sp)
    sw $a2, 8($sp)

    lw $t0, 0($sp)
    move $a0, $t0
    lw $t0, 4($sp)
    move $a1, $t0
    jal fn_max
    move $t0, $v0
    sw $t0, 16($sp)
    lw $t0, 16($sp)
    sw $t0, 12($sp)
    lw $t0, 12($sp)
    lw $t1, 8($sp)
    slt $t2, $t0, $t1
    sw $t2, 20($sp)
    lw $t0, 20($sp)
    sltu $t1, $zero, $t0
    beq $t1, $zero, __if_else_84
    lw $t0, 8($sp)
    move $a0, $t0
    jal fn_output
    move $t0, $v0
    sw $t0, 24($sp)
    j __if_end_85
__if_else_84:
    lw $t0, 12($sp)
    move $a0, $t0
    jal fn_output
    move $t0, $v0
    sw $t0, 28($sp)
__if_end_85:
__return_fn_printMax:
    lw $ra, 396($sp)
    addi $sp, $sp, 400
    jr $ra

fn_processArray:
    addi $sp, $sp, -400
    sw $ra, 396($sp)
    sw $a0, 0($sp)
    sw $a1, 4($sp)
    sw $a2, 8($sp)

    lw $t0, 0($sp)
    move $a0, $t0
    lw $t0, 4($sp)
    move $a1, $t0
    jal fn_arrayMax
    move $t0, $v0
    sw $t0, 12($sp)
    lw $t0, 12($sp)
    lw $t1, 8($sp)
    slt $t2, $t1, $t0
    sw $t2, 16($sp)
    lw $t0, 16($sp)
    sltu $t1, $zero, $t0
    beq $t1, $zero, __if_else_86
    lw $t0, 0($sp)
    move $a0, $t0
    lw $t0, 4($sp)
    move $a1, $t0
    jal fn_arrayMax
    move $t0, $v0
    sw $t0, 20($sp)
    lw $t0, 20($sp)
    move $a0, $t0
    jal fn_output
    move $t0, $v0
    sw $t0, 24($sp)
    j __if_end_87
__if_else_86:
    lw $t0, 0($sp)
    move $a0, $t0
    lw $t0, 4($sp)
    move $a1, $t0
    li $t0, 0
    move $a2, $t0
    jal fn_conditionalArraySum
    move $t0, $v0
    sw $t0, 28($sp)
    lw $t0, 28($sp)
    move $a0, $t0
    jal fn_output
    move $t0, $v0
    sw $t0, 32($sp)
__if_end_87:
__return_fn_processArray:
    lw $ra, 396($sp)
    addi $sp, $sp, 400
    jr $ra

main:
    addi $sp, $sp, -400
    # Declared array nums[5]
    jal fn_input
    move $t0, $v0
    sw $t0, 60($sp)
    lw $t0, 60($sp)
    sw $t0, 0($sp)
    jal fn_input
    move $t0, $v0
    sw $t0, 64($sp)
    lw $t0, 64($sp)
    sw $t0, 4($sp)
    jal fn_input
    move $t0, $v0
    sw $t0, 68($sp)
    lw $t0, 68($sp)
    sw $t0, 8($sp)
    lw $t0, 0($sp)
    move $a0, $t0
    lw $t0, 4($sp)
    move $a1, $t0
    jal fn_max
    move $t0, $v0
    sw $t0, 72($sp)
    lw $t0, 72($sp)
    sw $t0, 40($sp)
    lw $t0, 40($sp)
    move $a0, $t0
    jal fn_output
    move $t0, $v0
    sw $t0, 76($sp)
    lw $t0, 0($sp)
    move $a0, $t0
    lw $t0, 4($sp)
    move $a1, $t0
    jal fn_min
    move $t0, $v0
    sw $t0, 80($sp)
    lw $t0, 80($sp)
    sw $t0, 44($sp)
    lw $t0, 44($sp)
    move $a0, $t0
    jal fn_output
    move $t0, $v0
    sw $t0, 84($sp)
    lw $t0, 0($sp)
    move $a0, $t0
    jal fn_absolute
    move $t0, $v0
    sw $t0, 88($sp)
    lw $t0, 88($sp)
    sw $t0, 48($sp)
    lw $t0, 48($sp)
    move $a0, $t0
    jal fn_output
    move $t0, $v0
    sw $t0, 92($sp)
    lw $t0, 0($sp)
    move $a0, $t0
    jal fn_sign
    move $t0, $v0
    sw $t0, 96($sp)
    lw $t0, 96($sp)
    sw $t0, 52($sp)
    lw $t0, 52($sp)
    move $a0, $t0
    jal fn_output
    move $t0, $v0
    sw $t0, 100($sp)
    lw $t0, 0($sp)
    move $a0, $t0
    lw $t0, 4($sp)
    move $a1, $t0
    jal fn_compare
    move $t0, $v0
    sw $t0, 104($sp)
    lw $t0, 104($sp)
    sw $t0, 36($sp)
    lw $t0, 36($sp)
    move $a0, $t0
    jal fn_output
    move $t0, $v0
    sw $t0, 108($sp)
    lw $t0, 0($sp)
    move $a0, $t0
    lw $t0, 4($sp)
    move $a1, $t0
    lw $t0, 8($sp)
    move $a2, $t0
    jal fn_max3
    move $t0, $v0
    sw $t0, 112($sp)
    lw $t0, 112($sp)
    sw $t0, 12($sp)
    lw $t0, 12($sp)
    move $a0, $t0
    jal fn_output
    move $t0, $v0
    sw $t0, 116($sp)
    lw $t0, 0($sp)
    move $a0, $t0
    lw $t0, 4($sp)
    move $a1, $t0
    lw $t0, 8($sp)
    move $a2, $t0
    jal fn_min3
    move $t0, $v0
    sw $t0, 120($sp)
    lw $t0, 120($sp)
    sw $t0, 12($sp)
    lw $t0, 12($sp)
    move $a0, $t0
    jal fn_output
    move $t0, $v0
    sw $t0, 124($sp)
    lw $t0, 0($sp)
    move $a0, $t0
    li $t0, 0
    move $a1, $t0
    li $t0, 100
    move $a2, $t0
    jal fn_inRange
    move $t0, $v0
    sw $t0, 128($sp)
    lw $t0, 128($sp)
    li $t1, 1
    xor $t3, $t0, $t1
    sltiu $t2, $t3, 1
    sw $t2, 132($sp)
    lw $t0, 132($sp)
    sltu $t1, $zero, $t0
    beq $t1, $zero, __if_else_88
    lw $t0, 0($sp)
    move $a0, $t0
    jal fn_output
    move $t0, $v0
    sw $t0, 136($sp)
    j __if_end_89
__if_else_88:
    li $t0, 0
    move $a0, $t0
    jal fn_output
    move $t0, $v0
    sw $t0, 140($sp)
__if_end_89:
    lw $t0, 0($sp)
    move $a0, $t0
    lw $t0, 4($sp)
    move $a1, $t0
    jal fn_conditionalAdd
    move $t0, $v0
    sw $t0, 144($sp)
    lw $t0, 144($sp)
    sw $t0, 12($sp)
    lw $t0, 12($sp)
    move $a0, $t0
    jal fn_output
    move $t0, $v0
    sw $t0, 148($sp)
    lw $t0, 0($sp)
    move $a0, $t0
    lw $t0, 4($sp)
    move $a1, $t0
    jal fn_safeDivide
    move $t0, $v0
    sw $t0, 152($sp)
    lw $t0, 152($sp)
    sw $t0, 12($sp)
    lw $t0, 12($sp)
    move $a0, $t0
    jal fn_output
    move $t0, $v0
    sw $t0, 156($sp)
    lw $t0, 0($sp)
    move $a0, $t0
    lw $t0, 4($sp)
    move $a1, $t0
    jal fn_conditionalMultiply
    move $t0, $v0
    sw $t0, 160($sp)
    lw $t0, 160($sp)
    sw $t0, 12($sp)
    lw $t0, 12($sp)
    move $a0, $t0
    jal fn_output
    move $t0, $v0
    sw $t0, 164($sp)
    li $t0, 0
    # Bounds check for array nums
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
    addi $t2, $sp, 16
    sll $t0, $t0, 2
    add $t2, $t2, $t0
    lw $t3, 0($sp)
    sw $t3, 0($t2)
    li $t0, 1
    # Bounds check for array nums
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
    addi $t2, $sp, 16
    sll $t0, $t0, 2
    add $t2, $t2, $t0
    lw $t3, 4($sp)
    sw $t3, 0($t2)
    li $t0, 2
    # Bounds check for array nums
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
    addi $t2, $sp, 16
    sll $t0, $t0, 2
    add $t2, $t2, $t0
    lw $t3, 8($sp)
    sw $t3, 0($t2)
    li $t0, 0
    lw $t1, 0($sp)
    sub $t0, $t0, $t1
    sw $t0, 168($sp)
    li $t0, 3
    # Bounds check for array nums
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
    addi $t2, $sp, 16
    sll $t0, $t0, 2
    add $t2, $t2, $t0
    lw $t3, 168($sp)
    sw $t3, 0($t2)
    lw $t0, 4($sp)
    lw $t1, 8($sp)
    sub $t0, $t0, $t1
    sw $t0, 172($sp)
    li $t0, 4
    # Bounds check for array nums
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
    addi $t2, $sp, 16
    sll $t0, $t0, 2
    add $t2, $t2, $t0
    lw $t3, 172($sp)
    sw $t3, 0($t2)
    li $t0, 0
    sw $t0, 56($sp)
    addi $t0, $sp, 16
    move $a0, $t0
    li $t0, 5
    move $a1, $t0
    lw $t0, 56($sp)
    move $a2, $t0
    jal fn_conditionalArraySum
    move $t0, $v0
    sw $t0, 176($sp)
    lw $t0, 176($sp)
    sw $t0, 12($sp)
    lw $t0, 12($sp)
    move $a0, $t0
    jal fn_output
    move $t0, $v0
    sw $t0, 180($sp)
    addi $t0, $sp, 16
    move $a0, $t0
    li $t0, 5
    move $a1, $t0
    jal fn_arrayMax
    move $t0, $v0
    sw $t0, 184($sp)
    lw $t0, 184($sp)
    sw $t0, 40($sp)
    lw $t0, 40($sp)
    move $a0, $t0
    jal fn_output
    move $t0, $v0
    sw $t0, 188($sp)
    addi $t0, $sp, 16
    move $a0, $t0
    li $t0, 5
    move $a1, $t0
    jal fn_countPositive
    move $t0, $v0
    sw $t0, 192($sp)
    lw $t0, 192($sp)
    sw $t0, 12($sp)
    lw $t0, 12($sp)
    move $a0, $t0
    jal fn_output
    move $t0, $v0
    sw $t0, 196($sp)
    lw $t0, 0($sp)
    move $a0, $t0
    lw $t0, 4($sp)
    move $a1, $t0
    lw $t0, 8($sp)
    move $a2, $t0
    jal fn_complexCondition
    move $t0, $v0
    sw $t0, 200($sp)
    lw $t0, 200($sp)
    sw $t0, 12($sp)
    lw $t0, 12($sp)
    move $a0, $t0
    jal fn_output
    move $t0, $v0
    sw $t0, 204($sp)
    lw $t0, 0($sp)
    move $a0, $t0
    lw $t0, 4($sp)
    move $a1, $t0
    lw $t0, 8($sp)
    move $a2, $t0
    jal fn_nestedWithFunctions
    move $t0, $v0
    sw $t0, 208($sp)
    lw $t0, 208($sp)
    sw $t0, 12($sp)
    lw $t0, 12($sp)
    move $a0, $t0
    jal fn_output
    move $t0, $v0
    sw $t0, 212($sp)
    lw $t0, 0($sp)
    move $a0, $t0
    lw $t0, 4($sp)
    move $a1, $t0
    lw $t0, 8($sp)
    move $a2, $t0
    li $t0, 5
    move $a3, $t0
    jal fn_deeplyNested
    move $t0, $v0
    sw $t0, 216($sp)
    lw $t0, 216($sp)
    sw $t0, 12($sp)
    lw $t0, 12($sp)
    move $a0, $t0
    jal fn_output
    move $t0, $v0
    sw $t0, 220($sp)
    lw $t0, 0($sp)
    move $a0, $t0
    lw $t0, 4($sp)
    move $a1, $t0
    jal fn_max
    move $t0, $v0
    sw $t0, 224($sp)
    lw $t0, 4($sp)
    move $a0, $t0
    lw $t0, 8($sp)
    move $a1, $t0
    jal fn_min
    move $t0, $v0
    sw $t0, 228($sp)
    lw $t0, 224($sp)
    lw $t1, 228($sp)
    slt $t2, $t1, $t0
    sw $t2, 232($sp)
    lw $t0, 232($sp)
    sltu $t1, $zero, $t0
    beq $t1, $zero, __if_else_90
    lw $t0, 0($sp)
    move $a0, $t0
    jal fn_absolute
    move $t0, $v0
    sw $t0, 236($sp)
    lw $t0, 8($sp)
    move $a0, $t0
    jal fn_absolute
    move $t0, $v0
    sw $t0, 240($sp)
    lw $t0, 236($sp)
    lw $t1, 240($sp)
    slt $t2, $t0, $t1
    xori $t2, $t2, 1
    sw $t2, 244($sp)
    lw $t0, 244($sp)
    sltu $t1, $zero, $t0
    beq $t1, $zero, __if_else_92
    lw $t0, 0($sp)
    lw $t1, 8($sp)
    add $t0, $t0, $t1
    sw $t0, 248($sp)
    lw $t0, 248($sp)
    sw $t0, 12($sp)
    j __if_end_93
__if_else_92:
    lw $t0, 0($sp)
    lw $t1, 8($sp)
    sub $t0, $t0, $t1
    sw $t0, 252($sp)
    lw $t0, 252($sp)
    sw $t0, 12($sp)
__if_end_93:
    j __if_end_91
__if_else_90:
    lw $t0, 4($sp)
    move $a0, $t0
    lw $t0, 8($sp)
    move $a1, $t0
    jal fn_compare
    move $t0, $v0
    sw $t0, 256($sp)
    lw $t0, 256($sp)
    li $t1, 0
    xor $t3, $t0, $t1
    sltiu $t2, $t3, 1
    sw $t2, 260($sp)
    lw $t0, 260($sp)
    sltu $t1, $zero, $t0
    beq $t1, $zero, __if_else_94
    lw $t0, 4($sp)
    lw $t1, 8($sp)
    mul $t0, $t0, $t1
    sw $t0, 264($sp)
    lw $t0, 264($sp)
    sw $t0, 12($sp)
    j __if_end_95
__if_else_94:
    lw $t0, 8($sp)
    move $a0, $t0
    li $t0, 2
    move $a1, $t0
    jal fn_safeDivide
    move $t0, $v0
    sw $t0, 268($sp)
    lw $t0, 4($sp)
    lw $t1, 268($sp)
    div $t0, $t1
    mflo $t0
    sw $t0, 272($sp)
    lw $t0, 272($sp)
    sw $t0, 12($sp)
__if_end_95:
__if_end_91:
    lw $t0, 12($sp)
    move $a0, $t0
    jal fn_output
    move $t0, $v0
    sw $t0, 276($sp)
    lw $t0, 0($sp)
    move $a0, $t0
    lw $t0, 4($sp)
    move $a1, $t0
    jal fn_conditionalPrint
    move $t0, $v0
    sw $t0, 280($sp)
    lw $t0, 0($sp)
    move $a0, $t0
    lw $t0, 4($sp)
    move $a1, $t0
    lw $t0, 8($sp)
    move $a2, $t0
    jal fn_printMax
    move $t0, $v0
    sw $t0, 284($sp)
    addi $t0, $sp, 16
    move $a0, $t0
    li $t0, 5
    move $a1, $t0
    li $t0, 10
    move $a2, $t0
    jal fn_processArray
    move $t0, $v0
    sw $t0, 288($sp)
    lw $t0, 0($sp)
    li $t1, 0
    slt $t2, $t1, $t0
    sw $t2, 292($sp)
    lw $t0, 292($sp)
    sltu $t1, $zero, $t0
    beq $t1, $zero, __if_end_96
    li $t0, 1
    move $a0, $t0
    jal fn_output
    move $t0, $v0
    sw $t0, 296($sp)
__if_end_96:
    lw $t0, 4($sp)
    li $t1, 0
    slt $t2, $t0, $t1
    sw $t2, 300($sp)
    lw $t0, 300($sp)
    sltu $t1, $zero, $t0
    beq $t1, $zero, __if_end_97
    li $t0, 2
    move $a0, $t0
    jal fn_output
    move $t0, $v0
    sw $t0, 304($sp)
__if_end_97:
    lw $t0, 8($sp)
    li $t1, 0
    xor $t3, $t0, $t1
    sltiu $t2, $t3, 1
    sw $t2, 308($sp)
    lw $t0, 308($sp)
    sltu $t1, $zero, $t0
    beq $t1, $zero, __if_end_98
    li $t0, 3
    move $a0, $t0
    jal fn_output
    move $t0, $v0
    sw $t0, 312($sp)
__if_end_98:
    lw $t0, 0($sp)
    lw $t1, 4($sp)
    xor $t2, $t0, $t1
    sltu $t2, $zero, $t2
    sw $t2, 316($sp)
    lw $t0, 316($sp)
    sltu $t1, $zero, $t0
    beq $t1, $zero, __if_end_99
    li $t0, 4
    move $a0, $t0
    jal fn_output
    move $t0, $v0
    sw $t0, 320($sp)
__if_end_99:
    lw $t0, 0($sp)
    lw $t1, 4($sp)
    slt $t2, $t1, $t0
    xori $t2, $t2, 1
    sw $t2, 324($sp)
    lw $t0, 324($sp)
    sltu $t1, $zero, $t0
    beq $t1, $zero, __if_end_100
    li $t0, 5
    move $a0, $t0
    jal fn_output
    move $t0, $v0
    sw $t0, 328($sp)
__if_end_100:
    lw $t0, 4($sp)
    lw $t1, 8($sp)
    slt $t2, $t0, $t1
    xori $t2, $t2, 1
    sw $t2, 332($sp)
    lw $t0, 332($sp)
    sltu $t1, $zero, $t0
    beq $t1, $zero, __if_end_101
    li $t0, 6
    move $a0, $t0
    jal fn_output
    move $t0, $v0
    sw $t0, 336($sp)
__if_end_101:
    lw $t0, 0($sp)
    move $a0, $t0
    jal fn_absolute
    move $t0, $v0
    sw $t0, 340($sp)
    lw $t0, 340($sp)
    move $a0, $t0
    lw $t0, 4($sp)
    move $a1, $t0
    jal fn_absolute
    move $t0, $v0
    sw $t0, 344($sp)
    lw $t0, 344($sp)
    move $a0, $t0
    jal fn_max
    move $t0, $v0
    sw $t0, 348($sp)
    lw $t0, 8($sp)
    move $a0, $t0
    lw $t0, 0($sp)
    move $a1, $t0
    lw $t0, 4($sp)
    move $a2, $t0
    jal fn_min3
    move $t0, $v0
    sw $t0, 352($sp)
    lw $t0, 348($sp)
    lw $t1, 352($sp)
    slt $t2, $t1, $t0
    sw $t2, 356($sp)
    lw $t0, 356($sp)
    sltu $t1, $zero, $t0
    beq $t1, $zero, __if_else_102
    lw $t0, 0($sp)
    move $a0, $t0
    jal fn_absolute
    move $t0, $v0
    sw $t0, 360($sp)
    lw $t0, 360($sp)
    move $a0, $t0
    lw $t0, 4($sp)
    move $a1, $t0
    jal fn_absolute
    move $t0, $v0
    sw $t0, 364($sp)
    lw $t0, 364($sp)
    move $a0, $t0
    jal fn_max
    move $t0, $v0
    sw $t0, 368($sp)
    lw $t0, 368($sp)
    move $a0, $t0
    jal fn_output
    move $t0, $v0
    sw $t0, 372($sp)
    j __if_end_103
__if_else_102:
    lw $t0, 8($sp)
    move $a0, $t0
    lw $t0, 0($sp)
    move $a1, $t0
    lw $t0, 4($sp)
    move $a2, $t0
    jal fn_min3
    move $t0, $v0
    sw $t0, 376($sp)
    lw $t0, 376($sp)
    move $a0, $t0
    jal fn_output
    move $t0, $v0
    sw $t0, 380($sp)
__if_end_103:
    lw $t0, 0($sp)
    move $a0, $t0
    lw $t0, 4($sp)
    move $a1, $t0
    jal fn_max
    move $t0, $v0
    sw $t0, 384($sp)
    lw $t0, 384($sp)
    move $a0, $t0
    lw $t0, 4($sp)
    move $a1, $t0
    lw $t0, 8($sp)
    move $a2, $t0
    jal fn_min
    move $t0, $v0
    sw $t0, 388($sp)
    lw $t0, 388($sp)
    move $a0, $t0
    jal fn_compare
    move $t0, $v0
    sw $t0, 392($sp)
    lw $t0, 392($sp)
    li $t1, 0
    slt $t2, $t1, $t0
    sw $t2, 396($sp)
    lw $t0, 396($sp)
    sltu $t1, $zero, $t0
    beq $t1, $zero, __if_else_104
    lw $t0, 8($sp)
    move $a0, $t0
    lw $t0, 0($sp)
    move $a1, $t0
    lw $t0, 4($sp)
    move $a2, $t0
    jal fn_min
    move $t0, $v0
    sw $t0, 400($sp)
    lw $t0, 400($sp)
    move $a0, $t0
    lw $t0, 0($sp)
    move $a1, $t0
    lw $t0, 4($sp)
    move $a2, $t0
    jal fn_max
    move $t0, $v0
    sw $t0, 404($sp)
    lw $t0, 404($sp)
    move $a0, $t0
    jal fn_inRange
    move $t0, $v0
    sw $t0, 408($sp)
    lw $t0, 408($sp)
    li $t1, 1
    xor $t3, $t0, $t1
    sltiu $t2, $t3, 1
    sw $t2, 412($sp)
    lw $t0, 412($sp)
    sltu $t1, $zero, $t0
    beq $t1, $zero, __if_else_106
    lw $t0, 0($sp)
    move $a0, $t0
    lw $t0, 4($sp)
    move $a1, $t0
    jal fn_conditionalAdd
    move $t0, $v0
    sw $t0, 416($sp)
    lw $t0, 4($sp)
    move $a0, $t0
    lw $t0, 8($sp)
    move $a1, $t0
    jal fn_conditionalMultiply
    move $t0, $v0
    sw $t0, 420($sp)
    lw $t0, 416($sp)
    lw $t1, 420($sp)
    add $t0, $t0, $t1
    sw $t0, 424($sp)
    lw $t0, 424($sp)
    sw $t0, 12($sp)
    j __if_end_107
__if_else_106:
    lw $t0, 0($sp)
    move $a0, $t0
    lw $t0, 4($sp)
    move $a1, $t0
    lw $t0, 8($sp)
    move $a2, $t0
    jal fn_max3
    move $t0, $v0
    sw $t0, 428($sp)
    lw $t0, 428($sp)
    move $a0, $t0
    lw $t0, 0($sp)
    move $a1, $t0
    lw $t0, 4($sp)
    move $a2, $t0
    lw $t0, 8($sp)
    move $a3, $t0
    jal fn_min3
    move $t0, $v0
    sw $t0, 432($sp)
    lw $t0, 432($sp)
    move $a0, $t0
    jal fn_safeDivide
    move $t0, $v0
    sw $t0, 436($sp)
    lw $t0, 436($sp)
    sw $t0, 12($sp)
__if_end_107:
    j __if_end_105
__if_else_104:
    lw $t0, 0($sp)
    lw $t1, 4($sp)
    sub $t0, $t0, $t1
    sw $t0, 440($sp)
    lw $t0, 440($sp)
    move $a0, $t0
    jal fn_absolute
    move $t0, $v0
    sw $t0, 444($sp)
    lw $t0, 4($sp)
    lw $t1, 8($sp)
    sub $t0, $t0, $t1
    sw $t0, 448($sp)
    lw $t0, 448($sp)
    move $a0, $t0
    jal fn_absolute
    move $t0, $v0
    sw $t0, 452($sp)
    lw $t0, 444($sp)
    lw $t1, 452($sp)
    slt $t2, $t1, $t0
    sw $t2, 456($sp)
    lw $t0, 456($sp)
    sltu $t1, $zero, $t0
    beq $t1, $zero, __if_else_108
    lw $t0, 0($sp)
    lw $t1, 4($sp)
    sub $t0, $t0, $t1
    sw $t0, 460($sp)
    lw $t0, 460($sp)
    move $a0, $t0
    jal fn_absolute
    move $t0, $v0
    sw $t0, 464($sp)
    lw $t0, 464($sp)
    sw $t0, 12($sp)
    j __if_end_109
__if_else_108:
    lw $t0, 4($sp)
    lw $t1, 8($sp)
    sub $t0, $t0, $t1
    sw $t0, 468($sp)
    lw $t0, 468($sp)
    move $a0, $t0
    jal fn_absolute
    move $t0, $v0
    sw $t0, 472($sp)
    lw $t0, 472($sp)
    sw $t0, 12($sp)
__if_end_109:
__if_end_105:
    lw $t0, 12($sp)
    move $a0, $t0
    jal fn_output
    move $t0, $v0
    sw $t0, 476($sp)
__return_main:
    addi $sp, $sp, 400
    li $v0, 10
    syscall


fn_input:
    li $v0, 5
    syscall
    jr $ra

fn_output:
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    jr $ra
