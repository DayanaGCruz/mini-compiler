.data

__array_oob_msg: .asciiz "Runtime error: array index out of bounds\n"

.text
.globl main

fn_add:
    addi $sp, $sp, -400
    sw $ra, 396($sp)
    sw $a0, 0($sp)
    sw $a1, 4($sp)

    lw $t0, 0($sp)
    lw $t1, 4($sp)
    add $t0, $t0, $t1
    sw $t0, 12($sp)
    lw $t0, 12($sp)
    sw $t0, 8($sp)
    lw $t0, 8($sp)
    move $v0, $t0
    j __return_fn_add
__return_fn_add:
    lw $ra, 396($sp)
    addi $sp, $sp, 400
    jr $ra

fn_fortyTwo:
    addi $sp, $sp, -400
    sw $ra, 396($sp)
    li $t0, 42
    move $v0, $t0
    j __return_fn_fortyTwo
__return_fn_fortyTwo:
    lw $ra, 396($sp)
    addi $sp, $sp, 400
    jr $ra

fn_echoChar:
    addi $sp, $sp, -400
    sw $ra, 396($sp)
    sb $a0, 0($sp)

    lb $t0, 0($sp)
    li $v0, 11
    move $a0, $t0
    syscall
    li $v0, 11
    li $a0, 10
    syscall
__return_fn_echoChar:
    lw $ra, 396($sp)
    addi $sp, $sp, 400
    jr $ra

main:
    addi $sp, $sp, -400
    li $t0, 7
    move $a0, $t0
    li $t0, 5
    move $a1, $t0
    jal fn_add
    move $t0, $v0
    sw $t0, 8($sp)
    lw $t0, 8($sp)
    move $a0, $t0
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    li $t0, 1
    move $a0, $t0
    li $t0, 2
    move $a1, $t0
    jal fn_add
    move $t0, $v0
    sw $t0, 12($sp)
    lw $t0, 12($sp)
    move $a0, $t0
    jal fn_fortyTwo
    move $t0, $v0
    sw $t0, 16($sp)
    lw $t0, 16($sp)
    move $a0, $t0
    jal fn_add
    move $t0, $v0
    sw $t0, 20($sp)
    lw $t0, 20($sp)
    move $a0, $t0
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    li $t0, 122
    move $a0, $t0
    jal fn_echoChar
    move $t0, $v0
    sw $t0, 24($sp)
__return_main:
    addi $sp, $sp, 400
    li $v0, 10
    syscall

