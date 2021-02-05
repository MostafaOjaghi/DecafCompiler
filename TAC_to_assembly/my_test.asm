
.text
.globl main
main:
addiu   $sp $sp -100
sw $fp 4($sp)
move $fp $sp
li $v0 5 
syscall 
sw $v0 4($fp)
li $v0 1 
lw $t0 4($fp)
move $a0 $t0 
syscall 
li $v0 5 
syscall 
sw $v0 8($fp)
li $v0 1 
lw $t0 8($fp)
move $a0 $t0 
syscall 
lw $t0 4($fp)
lw $t1 8($fp)
div $t0 $t0 $t1
sw $t0 12($fp)
li $v0 1 
lw $t0 12($fp)
move $a0 $t0 
syscall 
move $sp $fp
sw $fp 96($sp)
addiu   $sp $sp -100
