.data

.text
.globl main
main:
    # Allocate stack space
    addi $sp, $sp, -400

    # Declared a at offset 0
    # Declared b at offset 4
    # Declared c at offset 8
    li $t0, 10
    sw $t0, 0($sp)
    li $t0, 3
    sw $t0, 4($sp)
    lw $t0, 0($sp)
    lw $t1, 4($sp)
    sub $t0, $t0, $t1
    sw $t0, 8($sp)
    lw $t0, 8($sp)
    # Print integer
    move $a0, $t0
    li $v0, 1
    syscall
    # Print newline
    li $v0, 11
    li $a0, 10
    syscall
    lw $t0, 0($sp)
    lw $t1, 4($sp)
    add $t0, $t0, $t1
    li $t1, 2
    sub $t0, $t0, $t1
    sw $t0, 8($sp)
    lw $t0, 8($sp)
    # Print integer
    move $a0, $t0
    li $v0, 1
    syscall
    # Print newline
    li $v0, 11
    li $a0, 10
    syscall
    lw $t0, 0($sp)
    lw $t1, 4($sp)
    sub $t0, $t0, $t1
    li $t1, 2
    sub $t0, $t0, $t1
    sw $t0, 8($sp)
    lw $t0, 8($sp)
    # Print integer
    move $a0, $t0
    li $v0, 1
    syscall
    # Print newline
    li $v0, 11
    li $a0, 10
    syscall
    li $t0, 5
    lw $t1, 0($sp)
    lw $t2, 4($sp)
    sub $t1, $t1, $t2
    sub $t0, $t0, $t1
    sw $t0, 8($sp)
    lw $t0, 8($sp)
    # Print integer
    move $a0, $t0
    li $v0, 1
    syscall
    # Print newline
    li $v0, 11
    li $a0, 10
    syscall

    # Exit program
    addi $sp, $sp, 400
    li $v0, 10
    syscall
