.data

.text
.globl main

main:
    addi $sp, $sp, -400
    # Struct Point defined
    # Declared struct Point p at offset 0
    # Declared total at offset 12
    li $t0, 5
    # Struct assignment: p.x = ...
    sw $t0, 0($sp)
    li $t0, 7
    # Struct assignment: p.y = ...
    sw $t0, 4($sp)
    li $t0, 65
    # Struct assignment: p.tag = ...
    sb $t0, 8($sp)
    # Struct access: p.x
    lw $t0, 0($sp)
    # Struct access: p.y
    lw $t1, 4($sp)
    add $t0, $t0, $t1
    sw $t0, 12($sp)
    lw $t0, 12($sp)
    # Print integer
    move $a0, $t0
    li $v0, 1
    syscall
    # Print newline
    li $v0, 11
    li $a0, 10
    syscall
    # Struct access: p.tag
    lb $t0, 8($sp)
    # Print character
    li $v0, 11
    move $a0, $t0
    syscall
    # Print newline
    li $v0, 11
    li $a0, 10
    syscall
__return_main:
    addi $sp, $sp, 400
    li $v0, 10
    syscall

