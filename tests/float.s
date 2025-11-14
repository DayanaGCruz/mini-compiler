.data

.text
.globl main

main:
    addi $sp, $sp, -400
    # Declared a at offset 0 (float)
    # Declared b at offset 4 (float)
    # Declared prod at offset 8 (float)
    # Declared ratio at offset 12 (float)
    # Declared mix at offset 16 (float)
    li.s $f0, 3.500000
    swc1 $f0, 0($sp)
    li.s $f0, 2.000000
    swc1 $f0, 4($sp)
    lwc1 $f0, 0($sp)
    lwc1 $f1, 4($sp)
    mul.s $f0, $f0, $f1
    swc1 $f0, 8($sp)
    lwc1 $f0, 0($sp)
    lwc1 $f1, 4($sp)
    div.s $f0, $f0, $f1
    swc1 $f0, 12($sp)
    lwc1 $f0, 8($sp)
    lwc1 $f1, 12($sp)
    add.s $f0, $f0, $f1
    li.s $f1, 1.500000
    sub.s $f0, $f0, $f1
    swc1 $f0, 16($sp)
    lwc1 $f0, 8($sp)
    # Print float
    mov.s $f12, $f0
    li $v0, 2
    syscall
    # Print newline
    li $v0, 11
    li $a0, 10
    syscall
    lwc1 $f0, 12($sp)
    # Print float
    mov.s $f12, $f0
    li $v0, 2
    syscall
    # Print newline
    li $v0, 11
    li $a0, 10
    syscall
    lwc1 $f0, 16($sp)
    # Print float
    mov.s $f12, $f0
    li $v0, 2
    syscall
    # Print newline
    li $v0, 11
    li $a0, 10
    syscall
__return_main:
    addi $sp, $sp, 400
    li $v0, 10
    syscall

