.data

__array_oob_msg: .asciiz "Runtime error: array index out of bounds\n"

.text
.globl main

main:
    addi $sp, $sp, -400
    li.s $f0, 7.000000
    mov.s $f12, $f0
    li $v0, 2
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    li.s $f0, 1.750000
    mov.s $f12, $f0
    li $v0, 2
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    li.s $f0, 7.250000
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

