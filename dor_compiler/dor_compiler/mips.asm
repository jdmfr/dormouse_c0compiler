.data
scale:  .word   100
test:  .word   20
char_test:  .word   121
mark:  .space  400
data:  .space  400
a:  .space  4
b:  .space  4
c:  .space  4
d:  .space  4
e:  .space  4
n:  .space  4
$string0  :  .asciiz  "Full permutation, please input a number(<100)"
$string1  :  .asciiz  "Finished!"
$string2  :  .asciiz  "Three integers"
$string3  :  .asciiz  "Please input e/r/n/v instead of "
.text
li $gp ,0x10010000
j main


sqrt:
add $fp,$sp,$0 
addi $sp ,$sp , -4
lw $s0 , -4($fp)
mul  $t0 , $s0 , $s0
move $v0, $t0
addi $sp , $fp ,88
jr $ra
addi $sp , $fp ,88
jr $ra
arrange:
add $fp,$sp,$0 
addi $sp ,$sp , -24
lw $s2 , -4($fp)
lw $s3 , -8($fp)
lw $s4 , -12($fp)
lw $s5 , -16($fp)
lw $s1 , -20($fp)
li  $s0 , 0
lw $a2 , 832($gp)
bne $s1 , $a2 , label.0
addi $sp , $fp ,88
jr $ra
j label.1
label.0:
label.1:
label.2:
la $a3 ,  mark
sll $a2 , $s0,2
add $a3,$a2,$a3
lw $t1 , 0($a3)
bne $t1 , 0 ,label.3
la $a3 ,   mark
sll $a2, $s0 , 2
add $a3,$a3,$a2
li $a2,1
sw $a2,0($a3)
la $a3 ,   data
sll $a2, $s1 , 2
add $a3,$a3,$a2
sw $s0 , 0($a3)
add  $t2 , $s1 , 1
li $a3 , 0
sw $a3 , -92($sp)
li $a3 , 0
sw $a3 , -96($sp)
li $a3 , 0
sw $a3 , -100($sp)
li $a3 , 0
sw $a3 , -104($sp)
sw $t2 , -108($sp)
sw $t0 , -4($sp)
sw $t1 , -8($sp)
sw $t2 , -12($sp)
sw $t3 , -16($sp)
sw $t4 , -20($sp)
sw $t5 , -24($sp)
sw $t6 , -28($sp)
sw $t7 , -32($sp)
sw $s0 , -36($sp)
sw $s1 , -40($sp)
sw $s2 , -44($sp)
sw $s3 , -48($sp)
sw $s4 , -52($sp)
sw $s5 , -56($sp)
sw $s6 , -60($sp)
sw $s7 , -64($sp)
sw $t8 , -68($sp)
sw $t9 , -72($sp)
sw $k0 , -76($sp)
sw $k1 , -80($sp)
sw $ra , -84($sp)
sw  $fp, -88($sp)
addi  $sp,$sp ,-88
 jal arrange
lw $ra , 4($fp)
lw $k1 , 8($fp)
lw $k0 , 12($fp)
lw $t9 , 16($fp)
lw $t8 , 20($fp)
lw $s7 , 24($fp)
lw $s6 , 28($fp)
lw $s5 , 32($fp)
lw $s4 , 36($fp)
lw $s3 , 40($fp)
lw $s2 , 44($fp)
lw $s1 , 48($fp)
lw $s0 , 52($fp)
lw $t7 , 56($fp)
lw $t6 , 60($fp)
lw $t5 , 64($fp)
lw $t4 , 68($fp)
lw $t3 , 72($fp)
lw $t2 , 76($fp)
lw $t1 , 80($fp)
lw $t0 , 84($fp)
lw  $fp, 0($fp)
la $a3 ,   mark
sll $a2, $s0 , 2
add $a3,$a3,$a2
li $a2,0
sw $a2,0($a3)
j label.4
label.3:
label.4:
add  $t3 , $s0 , 1
move $s0 , $t3
lw $a2 , 832($gp)
blt $s0 , $a2 , label.2
addi $sp , $fp ,88
jr $ra
foo_recursion:
add $fp,$sp,$0 
addi $sp ,$sp , -4
li  $s0 , 0
la $a0,$string0
li $v0,4
syscall
li $v0, 5
syscall
sw $v0, 832($gp)
label.5:
la $a3 ,   mark
sll $a2, $s0 , 2
add $a3,$a3,$a2
li $a2,0
sw $a2,0($a3)
add  $t4 , $s0 , 1
move $s0 , $t4
lw $a2 , 832($gp)
blt $s0 , $a2 , label.5
li $a3 , 1
sw $a3 , -92($sp)
li $a3 , 2
sw $a3 , -96($sp)
li $a3 , 3
sw $a3 , -100($sp)
li $a3 , 4
sw $a3 , -104($sp)
li $a3 , 0
sw $a3 , -108($sp)
sw $t0 , -4($sp)
sw $t1 , -8($sp)
sw $t2 , -12($sp)
sw $t3 , -16($sp)
sw $t4 , -20($sp)
sw $t5 , -24($sp)
sw $t6 , -28($sp)
sw $t7 , -32($sp)
sw $s0 , -36($sp)
sw $s1 , -40($sp)
sw $s2 , -44($sp)
sw $s3 , -48($sp)
sw $s4 , -52($sp)
sw $s5 , -56($sp)
sw $s6 , -60($sp)
sw $s7 , -64($sp)
sw $t8 , -68($sp)
sw $t9 , -72($sp)
sw $k0 , -76($sp)
sw $k1 , -80($sp)
sw $ra , -84($sp)
sw  $fp, -88($sp)
addi  $sp,$sp ,-88
 jal arrange
lw $ra , 4($fp)
lw $k1 , 8($fp)
lw $k0 , 12($fp)
lw $t9 , 16($fp)
lw $t8 , 20($fp)
lw $s7 , 24($fp)
lw $s6 , 28($fp)
lw $s5 , 32($fp)
lw $s4 , 36($fp)
lw $s3 , 40($fp)
lw $s2 , 44($fp)
lw $s1 , 48($fp)
lw $s0 , 52($fp)
lw $t7 , 56($fp)
lw $t6 , 60($fp)
lw $t5 , 64($fp)
lw $t4 , 68($fp)
lw $t3 , 72($fp)
lw $t2 , 76($fp)
lw $t1 , 80($fp)
lw $t0 , 84($fp)
lw  $fp, 0($fp)
la $a0,$string1
li $v0,4
syscall
addi $sp , $fp ,88
jr $ra
foo_expr:
add $fp,$sp,$0 
addi $sp ,$sp , -16
li  $s0 , 0
la $a0,$string2
li $v0,4
syscall
li $v0, 5
syscall
move $s1, $v0
li $v0, 5
syscall
move $s2, $v0
li $v0, 5
syscall
move $s3, $v0
label.6:
la $a3 ,   data
sll $a2, $s0 , 2
add $a3,$a3,$a2
sw $s0 , 0($a3)
add  $t5 , $s0 , 1
move $s0 , $t5
lw $a2 , 0($gp)
blt $s0 , $a2 , label.6
la $a3 ,  data
sll $a2 , $s2,2
add $a3,$a2,$a3
lw $t6 , 0($a3)
mul  $t7 , $s1 , $t6
li   $a3 ,  0
sub  $t8 , $a3 , $t7
li   $a3 ,  -2
mul  $t9 , $a3 , 99
add  $t0 , $t8 , $t9
sw $s3 , -92($sp)
sw $t0 , -4($sp)
sw $t1 , -8($sp)
sw $t2 , -12($sp)
sw $t3 , -16($sp)
sw $t4 , -20($sp)
sw $t5 , -24($sp)
sw $t6 , -28($sp)
sw $t7 , -32($sp)
sw $s0 , -36($sp)
sw $s1 , -40($sp)
sw $s2 , -44($sp)
sw $s3 , -48($sp)
sw $s4 , -52($sp)
sw $s5 , -56($sp)
sw $s6 , -60($sp)
sw $s7 , -64($sp)
sw $t8 , -68($sp)
sw $t9 , -72($sp)
sw $k0 , -76($sp)
sw $k1 , -80($sp)
sw $ra , -84($sp)
sw  $fp, -88($sp)
addi  $sp,$sp ,-88
 jal sqrt
lw $ra , 4($fp)
lw $k1 , 8($fp)
lw $k0 , 12($fp)
lw $t9 , 16($fp)
lw $t8 , 20($fp)
lw $s7 , 24($fp)
lw $s6 , 28($fp)
lw $s5 , 32($fp)
lw $s4 , 36($fp)
lw $s3 , 40($fp)
lw $s2 , 44($fp)
lw $s1 , 48($fp)
lw $s0 , 52($fp)
lw $t7 , 56($fp)
lw $t6 , 60($fp)
lw $t5 , 64($fp)
lw $t4 , 68($fp)
lw $t3 , 72($fp)
lw $t2 , 76($fp)
lw $t1 , 80($fp)
lw $t0 , 84($fp)
lw  $fp, 0($fp)
move  $t1 , $v0
add  $t2 , $t0 , $t1
li   $a3 ,  5
div  $t3 , $a3 , 2
mul  $t4 , $t3 , 1
addi $sp,$sp, -4
sw $t5, 0($sp) 
sub  $t5 , $t2 , $t4
move $v0, $t5
addi $sp , $fp ,88
jr $ra
addi $sp , $fp ,88
jr $ra
do_nothing:
add $fp,$sp,$0 
addi $sp ,$sp , -0
addi $sp , $fp ,88
jr $ra
value:
add $fp,$sp,$0 
addi $sp ,$sp , -8
li $a3 ,110
sw $a3 ,-4($fp)
li $v0, 5
syscall
move $s0, $v0
bne $s0 , 1 ,label.8
lw $a0, -4($fp)
li $v0 , 1
syscall
j label.7
label.8:
bne $s0 , 2 ,label.9
li $a0, 98
li $v0,11
syscall
j label.7
label.9:
li $a0, 98
li $v0,11
syscall
label.7:
addi $sp , $fp ,88
jr $ra
main:
add $fp,$sp,$0 
addi $sp ,$sp , -4
li $v0 ,12
syscall
move $s0 , $v0 
label.10:
li   $a3 ,  0
sub  $t6 , $a3 , 1
beq $t6 , 0 ,label.11
bne $s0 , 101 ,label.13
sw $t0 , -4($sp)
sw $t1 , -8($sp)
sw $t2 , -12($sp)
sw $t3 , -16($sp)
sw $t4 , -20($sp)
sw $t5 , -24($sp)
sw $t6 , -28($sp)
sw $t7 , -32($sp)
sw $s0 , -36($sp)
sw $s1 , -40($sp)
sw $s2 , -44($sp)
sw $s3 , -48($sp)
sw $s4 , -52($sp)
sw $s5 , -56($sp)
sw $s6 , -60($sp)
sw $s7 , -64($sp)
sw $t8 , -68($sp)
sw $t9 , -72($sp)
sw $k0 , -76($sp)
sw $k1 , -80($sp)
sw $ra , -84($sp)
sw  $fp, -88($sp)
addi  $sp,$sp ,-88
 jal foo_expr
lw $ra , 4($fp)
lw $k1 , 8($fp)
lw $k0 , 12($fp)
lw $t9 , 16($fp)
lw $t8 , 20($fp)
lw $s7 , 24($fp)
lw $s6 , 28($fp)
lw $s5 , 32($fp)
lw $s4 , 36($fp)
lw $s3 , 40($fp)
lw $s2 , 44($fp)
lw $s1 , 48($fp)
lw $s0 , 52($fp)
lw $t7 , 56($fp)
lw $t6 , 60($fp)
lw $t5 , 64($fp)
lw $t4 , 68($fp)
lw $t3 , 72($fp)
lw $t2 , 76($fp)
lw $t1 , 80($fp)
lw $t0 , 84($fp)
lw  $fp, 0($fp)
move  $t7 , $v0
move $a0, $t7
li $v0 , 1
syscall
j label.12
label.13:
bne $s0 , 114 ,label.14
sw $t0 , -4($sp)
sw $t1 , -8($sp)
sw $t2 , -12($sp)
sw $t3 , -16($sp)
sw $t4 , -20($sp)
sw $t5 , -24($sp)
sw $t6 , -28($sp)
sw $t7 , -32($sp)
sw $s0 , -36($sp)
sw $s1 , -40($sp)
sw $s2 , -44($sp)
sw $s3 , -48($sp)
sw $s4 , -52($sp)
sw $s5 , -56($sp)
sw $s6 , -60($sp)
sw $s7 , -64($sp)
sw $t8 , -68($sp)
sw $t9 , -72($sp)
sw $k0 , -76($sp)
sw $k1 , -80($sp)
sw $ra , -84($sp)
sw  $fp, -88($sp)
addi  $sp,$sp ,-88
 jal foo_recursion
lw $ra , 4($fp)
lw $k1 , 8($fp)
lw $k0 , 12($fp)
lw $t9 , 16($fp)
lw $t8 , 20($fp)
lw $s7 , 24($fp)
lw $s6 , 28($fp)
lw $s5 , 32($fp)
lw $s4 , 36($fp)
lw $s3 , 40($fp)
lw $s2 , 44($fp)
lw $s1 , 48($fp)
lw $s0 , 52($fp)
lw $t7 , 56($fp)
lw $t6 , 60($fp)
lw $t5 , 64($fp)
lw $t4 , 68($fp)
lw $t3 , 72($fp)
lw $t2 , 76($fp)
lw $t1 , 80($fp)
lw $t0 , 84($fp)
lw  $fp, 0($fp)
j label.12
label.14:
bne $s0 , 110 ,label.15
sw $t0 , -4($sp)
sw $t1 , -8($sp)
sw $t2 , -12($sp)
sw $t3 , -16($sp)
sw $t4 , -20($sp)
sw $t5 , -24($sp)
sw $t6 , -28($sp)
sw $t7 , -32($sp)
sw $s0 , -36($sp)
sw $s1 , -40($sp)
sw $s2 , -44($sp)
sw $s3 , -48($sp)
sw $s4 , -52($sp)
sw $s5 , -56($sp)
sw $s6 , -60($sp)
sw $s7 , -64($sp)
sw $t8 , -68($sp)
sw $t9 , -72($sp)
sw $k0 , -76($sp)
sw $k1 , -80($sp)
sw $ra , -84($sp)
sw  $fp, -88($sp)
addi  $sp,$sp ,-88
 jal do_nothing
lw $ra , 4($fp)
lw $k1 , 8($fp)
lw $k0 , 12($fp)
lw $t9 , 16($fp)
lw $t8 , 20($fp)
lw $s7 , 24($fp)
lw $s6 , 28($fp)
lw $s5 , 32($fp)
lw $s4 , 36($fp)
lw $s3 , 40($fp)
lw $s2 , 44($fp)
lw $s1 , 48($fp)
lw $s0 , 52($fp)
lw $t7 , 56($fp)
lw $t6 , 60($fp)
lw $t5 , 64($fp)
lw $t4 , 68($fp)
lw $t3 , 72($fp)
lw $t2 , 76($fp)
lw $t1 , 80($fp)
lw $t0 , 84($fp)
lw  $fp, 0($fp)
j label.12
label.15:
bne $s0 , 118 ,label.16
sw $t0 , -4($sp)
sw $t1 , -8($sp)
sw $t2 , -12($sp)
sw $t3 , -16($sp)
sw $t4 , -20($sp)
sw $t5 , -24($sp)
sw $t6 , -28($sp)
sw $t7 , -32($sp)
sw $s0 , -36($sp)
sw $s1 , -40($sp)
sw $s2 , -44($sp)
sw $s3 , -48($sp)
sw $s4 , -52($sp)
sw $s5 , -56($sp)
sw $s6 , -60($sp)
sw $s7 , -64($sp)
sw $t8 , -68($sp)
sw $t9 , -72($sp)
sw $k0 , -76($sp)
sw $k1 , -80($sp)
sw $ra , -84($sp)
sw  $fp, -88($sp)
addi  $sp,$sp ,-88
 jal value
lw $ra , 4($fp)
lw $k1 , 8($fp)
lw $k0 , 12($fp)
lw $t9 , 16($fp)
lw $t8 , 20($fp)
lw $s7 , 24($fp)
lw $s6 , 28($fp)
lw $s5 , 32($fp)
lw $s4 , 36($fp)
lw $s3 , 40($fp)
lw $s2 , 44($fp)
lw $s1 , 48($fp)
lw $s0 , 52($fp)
lw $t7 , 56($fp)
lw $t6 , 60($fp)
lw $t5 , 64($fp)
lw $t4 , 68($fp)
lw $t3 , 72($fp)
lw $t2 , 76($fp)
lw $t1 , 80($fp)
lw $t0 , 84($fp)
lw  $fp, 0($fp)
j label.12
label.16:
la $a0,$string3
li $v0,4
syscall
move $a0, $s0
li $v0,11
syscall
label.12:
j label.17
label.11:
label.17:
li $a3 , 0
bne $a3 , 0 ,label.10
li $v0 ,10
syscall
addi $sp , $fp ,88
li $v0 ,10
syscall
