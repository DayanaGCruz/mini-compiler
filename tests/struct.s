.data

__array_oob_msg: .asciiz "Runtime error: array index out of bounds\n"

.text
.globl main

main:
    addi $sp, $sp, -400
    # Struct Point defined
    # Declared struct Point p
    li $t0, 5
    sw $t0, 0($sp)
    li $t0, 7
    sw $t0, 4($sp)
    li $t0, 65
    sb $t0, 8($sp)
    li $t0, 12
    move $a0, $t0
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    li $t0, 65
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

