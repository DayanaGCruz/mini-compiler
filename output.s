.data

.text
.globl main

fn_scaleAndShift:
    addi $sp, $sp, -400
    sw $ra, 396($sp)
    sw $a0, 0($sp)
    sw $a1, 4($sp)

    lw $t0, 0($sp)
    mtc1 $t0, $f0
    cvt.s.w $f0, $f0
    lwc1 $f1, 4($sp)
    mul.s $f0, $f0, $f1
    swc1 $f0, 12($sp)
    lwc1 $f0, 12($sp)
    swc1 $f0, 8($sp)
    lwc1 $f0, 8($sp)
    mov.s $f0, $f0
    mfc1 $v0, $f0
    j __return_fn_scaleAndShift
__return_fn_scaleAndShift:
    lw $ra, 396($sp)
    addi $sp, $sp, 400
    jr $ra

main:
    addi $sp, $sp, -400
    # Declared array numbers[2]
    # Struct Pair defined
    # Declared struct Pair p
    li $t0, 0
    sll $t0, $t0, 2
    addi $t1, $sp, 0
    add $t1, $t1, $t0
    li $t2, 3
    sw $t2, 0($t1)
    li $t0, 1
    sll $t0, $t0, 2
    addi $t1, $sp, 0
    add $t1, $t1, $t0
    li $t2, 4
    sw $t2, 0($t1)
    li $t0, 0
    sll $t0, $t0, 2
    addi $t1, $sp, 0
    add $t1, $t1, $t0
    lw $t1, 0($t1)
    sw $t1, 20($sp)
    li $t0, 1
    sll $t0, $t0, 2
    addi $t1, $sp, 0
    add $t1, $t1, $t0
    lw $t1, 0($t1)
    sw $t1, 24($sp)
    lw $t0, 20($sp)
    lw $t1, 24($sp)
    add $t0, $t0, $t1
    sw $t0, 28($sp)
    lw $t0, 28($sp)
    move $a0, $t0
    li.s $f0, 1.500000
    mfc1 $t0, $f0
    move $a1, $t0
    jal fn_scaleAndShift
    swc1 $f0, 32($sp)
    lwc1 $f0, 32($sp)
    swc1 $f0, 8($sp)
    lwc1 $f0, 32($sp)
    mov.s $f12, $f0
    li $v0, 2
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    li $t0, 0
    sll $t0, $t0, 2
    addi $t1, $sp, 0
    add $t1, $t1, $t0
    lw $t1, 0($t1)
    sw $t1, 36($sp)
    li $t0, 1
    sll $t0, $t0, 2
    addi $t1, $sp, 0
    add $t1, $t1, $t0
    lw $t1, 0($t1)
    sw $t1, 40($sp)
    lw $t0, 36($sp)
    lw $t1, 40($sp)
    mul $t0, $t0, $t1
    sw $t0, 44($sp)
    lw $t0, 44($sp)
    sw $t0, 12($sp)
    li $t0, 66
    sb $t0, 16($sp)
    lw $t0, 44($sp)
    sw $t0, 48($sp)
    lw $t0, 44($sp)
    move $a0, $t0
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    li $t0, 66
    sb $t0, 52($sp)
    li $t0, 66
    li $v0, 11
    move $a0, $t0
    syscall
    li $v0, 11
    li $a0, 10
    syscall
__return_main:
    addi $sp, $sp, 400
    li $v0, 10
    syscall

