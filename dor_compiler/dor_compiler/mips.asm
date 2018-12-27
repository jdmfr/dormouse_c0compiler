.data
g_const_ia:  .word   4
g_const_ib:  .word   1
g_const_ic:  .word   0
g_const_plus:  .word   43
g_const_minus:  .word   45
int_const_c:  .word   0
int_const_d:  .word   0
int_const_e:  .word   -3
int_const_f:  .word   -4
g_int_a:  .space  4
g_arr_a:  .space  4000
g_int_32:  .space  4
_g_ch_r:  .space  4
_g_str_r:  .space  4000
g_qsa:  .space  80
$string0  :  .asciiz  "  __Welcome__to__ ::  pr_glo_and_local"
$string1  :  .asciiz  "print_string_and_ident_test::"
$string2  :  .asciiz  "print_operators_test::"
$string3  :  .asciiz  "Hi_DorMouse:: op_test_passed!"
$string4  :  .asciiz  "This is a !"
$string5  :  .asciiz  "This is b !"
$string6  :  .asciiz  "This is c !"
$string7  :  .asciiz  "while_switch_part1_ERROR!!!"
$string8  :  .asciiz  "while_switch_part1_over..."
$string9  :  .asciiz  "while_switch_part2_start...."
$string10  :  .asciiz  "while_switch_part1_still_ERROR!!!"
$string11  :  .asciiz  "while_switch_part2_should_cycle_4!!!..."
$string12  :  .asciiz  "while_switch_part2_over...."
$string13  :  .asciiz  "__Welcome__to__:: while_switch_test"
$string14  :  .asciiz  "Hi_DorMouse:: while_switch_test_passed!"
$string15  :  .asciiz  "wrong glo-loc 1 ..."
$string16  :  .asciiz  "still wrong glo-loc 1 ..."
$string17  :  .asciiz  "5 or 4 in if_test_wrong!!!.."
$string18  :  .asciiz  "1 .. 2 or 3 in if_test_wrong!!!..."
$string19  :  .asciiz  "Hi_DorMouse::if_and_glo-loc_test_passed!"
$string20  :  .asciiz  "Crystal::Sorry"
$string21  :  .asciiz  "array_test_part_1_ans::"
$string22  :  .asciiz  "array_test_part_2_ans::"
$string23  :  .asciiz  "__Welcome__to__::quick_sort_test..."
$string24  :  .asciiz  "DorMouse,please Input the length(1..20)"
$string25  :  .asciiz  "Invalid length,sorry,agian please::"
$string26  :  .asciiz  "__Welcome__to__::gcd_test..."
$string27  :  .asciiz  "Ringo,please Input a number"
$string28  :  .asciiz  "Invalid integer ,sorry,agian please::"
$string29  :  .asciiz  "answer is:: "
$string30  :  .asciiz  "__Welcome__to__DorMouse_C"
$string31  :  .asciiz  "Input 0, and skip quick_sort_test & gcd_test "
.text
li $gp ,0x10010000
j main


pr_glo_and_local_test:
add $fp,$sp,$0 
addi $sp ,$sp , -40
li $a2 , 1
sw $a2,36($gp)
li $s1 , 66
li $s2 , 67
li $s0 , 53
li $s5 , 42
li $s4 , 2
li $s3 , 68
la $a0,$string0
li $v0,4
syscall
move $a0, $s0
li $v0,11
syscall
li $a0, 4
li $v0 , 1
syscall
li $a0, 3
li $v0 , 1
syscall
move $a0, $s4
li $v0 , 1
syscall
li $a0, 1
li $v0 , 1
syscall
li $a0, 0
li $v0 , 1
syscall
li $a0, -1
li $v0 , 1
syscall
li $a0, -2
li $v0 , 1
syscall
li $a0, -3
li $v0 , 1
syscall
li $a0, -4
li $v0 , 1
syscall
la $a0,$string1
li $v0,4
syscall
li $a0, 65
li $v0,11
syscall
move $a0, $s1
li $v0,11
syscall
move $a0, $s2
li $v0,11
syscall
move $a0, $s3
li $v0,11
syscall
la $a0,$string2
li $v0,4
syscall
li $a0, 43
li $v0,11
syscall
move $a0, $s5
li $v0,11
syscall
addi $sp , $fp ,40
jr $ra
foo1:
add $fp,$sp,$0 
li $v1 ,1
addi $sp , $fp ,40
jr $ra
addi $sp , $fp ,40
jr $ra
foo2:
add $fp,$sp,$0 
addi $sp ,$sp , -4
lw $s0 , -4($fp)
move $v1 ,$s0
addi $sp , $fp ,40
jr $ra
addi $sp , $fp ,40
jr $ra
foo3:
add $fp,$sp,$0 
li $v1 ,98
addi $sp , $fp ,40
jr $ra
addi $sp , $fp ,40
jr $ra
op_test:
add $fp,$sp,$0 
addi $sp ,$sp , -120
lw $s4 , -4($fp)
lw $s5 , -8($fp)
sw  $s0,  -4($sp)
sw  $s1,  -8($sp)
sw  $s2,  -12($sp)
sw  $s3,  -16($sp)
sw  $s4,  -20($sp)
sw  $s5,  -24($sp)
sw  $s6,  -28($sp)
sw  $s7,  -32($sp)
sw  $ra,  -36($sp)
sw  $fp,  -40($sp)
addi  $sp,$sp ,-40
 jal foo1
lw  $s0,  36($fp)
lw  $s1,  32($fp)
lw  $s2,  28($fp)
lw  $s3,  24($fp)
lw  $s4,  20($fp)
lw  $s5,  16($fp)
lw  $s6,  12($fp)
lw  $s7,  8($fp)
lw  $ra,  4($fp)
lw  $fp,  0($fp)
move $t0 , $v1
add  $t1 , $t0 , 31
move $s1 , $t1
move $a2 , $s1
sw $a2,4040($gp)
li $a2 , 114
sw $a2,4044($gp)
sw $t0 , -36($fp)
sw $t1 , -40($fp)
sw  $s0,  -4($sp)
sw  $s1,  -8($sp)
sw  $s2,  -12($sp)
sw  $s3,  -16($sp)
sw  $s4,  -20($sp)
sw  $s5,  -24($sp)
sw  $s6,  -28($sp)
sw  $s7,  -32($sp)
sw  $ra,  -36($sp)
sw  $fp,  -40($sp)
addi  $sp,$sp ,-40
 jal foo1
lw  $s0,  36($fp)
lw  $s1,  32($fp)
lw  $s2,  28($fp)
lw  $s3,  24($fp)
lw  $s4,  20($fp)
lw  $s5,  16($fp)
lw  $s6,  12($fp)
lw  $s7,  8($fp)
lw  $ra,  4($fp)
lw  $fp,  0($fp)
move $t0 , $v1
li   $a3 ,  34
div  $t1 , $a3 , $t0
li   $a3 ,  68
add  $t2 , $a3 , $t1
move $s0 , $t2
sub  $t3 , $s0 , 1
move $s3 , $t3
li   $a3 ,  68
sub  $t4 , $a3 , 67
sw $t0 , -44($fp)
sw $t1 , -48($fp)
sw $t2 , -52($fp)
sw $t3 , -56($fp)
sw $t4 , -60($fp)
sw  $s0,  -4($sp)
sw  $s1,  -8($sp)
sw  $s2,  -12($sp)
sw  $s3,  -16($sp)
sw  $s4,  -20($sp)
sw  $s5,  -24($sp)
sw  $s6,  -28($sp)
sw  $s7,  -32($sp)
sw  $ra,  -36($sp)
sw  $fp,  -40($sp)
addi  $sp,$sp ,-40
 jal foo1
lw  $s0,  36($fp)
lw  $s1,  32($fp)
lw  $s2,  28($fp)
lw  $s3,  24($fp)
lw  $s4,  20($fp)
lw  $s5,  16($fp)
lw  $s6,  12($fp)
lw  $s7,  8($fp)
lw  $ra,  4($fp)
lw  $fp,  0($fp)
move $t0 , $v1
lw $t1, -60($fp)
sub  $t2 , $t1 , $t0
add  $t3 , $t2 , $s5
move $s2 , $t3
addi $a3 ,$fp ,-20
addi $a3 , $a3 , 4
sw $s4 , 0($a3)
mul  $t4 , $s0 , 25
li   $a3 ,  3
mul  $t5 , $a3 , 4
div  $t6 , $t5 , 2
add  $t7 , $t4 , $t6
li   $a3 ,  5
mul  $t8 , $a3 , 3
sub  $t9 , $t7 , $t8
sw $t0, -64($fp)
add  $t0 , $s3 , 1
sub  $t1 , $s0 , $t0
sw $t2, -68($fp)
add  $t2 , $t9 , $t1
sw $t3, -72($fp)
add  $t3 , $t2 , $s2
addi $a3 ,$fp ,-20
sll $a2,$0,2
add $a3,$a3,$a2
sw $t3 , 0($a3)
sw $t4, -76($fp)
addi $a3 , $fp , -20
lw $t4 , 0($a3)
sw $t5, -80($fp)
lw  $t5 , 4044($gp)
sw $t6, -84($fp)
add  $t6 , $t5 , 0
bne $t4 , $t6 , label.0
la $a0,$string3
li $v0,4
syscall
label.0:
addi $sp , $fp ,40
jr $ra
addi $sp , $fp ,40
jr $ra
while_switch:
add $fp,$sp,$0 
addi $sp ,$sp , -64
li $s1 , 97
label.2:
bne $s1 , 97 ,label.4
la $a0,$string4
li $v0,4
syscall
li $s1 , 98
j label.6
label.4:
bne $s1 , 98 ,label.5
la $a0,$string5
li $v0,4
syscall
li $s1 , 99
j label.6
label.5:
bne $s1 , 99 ,label.6
la $a0,$string6
li $v0,4
syscall
li $s1 , 100
label.6:
bne $s1 , 100 ,label.2
li   $a3 ,  1
sub  $t0 , $a3 , 1
move $s0 , $t0
label.7:
li   $a3 ,  32
div  $t1 , $a3 , 32
sub  $t2 , $s0 , $t1
add  $t3 , $t2 , 1
bne $t3 , 0 ,label.9
li $s0 , 1
j label.11
label.9:
bne $t3 , 1 ,label.10
add  $t4 , $s0 , 1
move $s0 , $t4
j label.11
label.10:
bne $t3 , 2 ,label.11
li $s0 , -32
label.11:
bge $s0 , 0 ,label.7
li   $a3 ,  0
lw  $t5 , 4040($gp)
sub  $t6 , $a3 , $t5
beq $s0 , $t6 , label.12
la $a0,$string7
li $v0,4
syscall
j label.13
label.12:
la $a0,$string8
li $v0,4
syscall
li   $a3 ,  97
add  $t7 , $a3 , 0
move $s0 , $t7
label.13:
label.14:
bne $s0 , 97 ,label.16
la $a0,$string9
li $v0,4
syscall
label.17:
add  $t8 , $s0 , 1
move $s0 , $t8
li   $a3 ,  99
add  $t9 , $a3 , 0
blt $s0 , $t9 , label.17
j label.22
label.16:
bne $s0 , 99 ,label.18
label.19:
sw $t0 , -12($fp)
sw $t1 , -16($fp)
sw $t2 , -20($fp)
sw $t3 , -24($fp)
sw $t4 , -28($fp)
sw $t6 , -32($fp)
sw $t7 , -36($fp)
sw $t8 , -40($fp)
sw $t9 , -44($fp)
sw  $s0,  -4($sp)
sw  $s1,  -8($sp)
sw  $s2,  -12($sp)
sw  $s3,  -16($sp)
sw  $s4,  -20($sp)
sw  $s5,  -24($sp)
sw  $s6,  -28($sp)
sw  $s7,  -32($sp)
sw  $ra,  -36($sp)
sw  $fp,  -40($sp)
addi  $sp,$sp ,-40
 jal foo1
lw  $s0,  36($fp)
lw  $s1,  32($fp)
lw  $s2,  28($fp)
lw  $s3,  24($fp)
lw  $s4,  20($fp)
lw  $s5,  16($fp)
lw  $s6,  12($fp)
lw  $s7,  8($fp)
lw  $ra,  4($fp)
lw  $fp,  0($fp)
move $t0 , $v1
add  $t1 , $s0 , $t0
move $s0 , $t1
li   $a3 ,  100
add  $t2 , $a3 , 0
beq $s0 , $t2 , label.19
j label.22
label.18:
bne $s0 , -32 ,label.20
la $a0,$string10
li $v0,4
syscall
j label.22
label.20:
li   $a3 ,  105
add  $t3 , $a3 , 0
beq $s0 , $t3 , label.21
la $a0,$string11
li $v0,4
syscall
add  $t4 , $s0 , 1
move $s0 , $t4
j label.22
label.21:
la $a0,$string12
li $v0,4
syscall
li $v1 ,1
addi $sp , $fp ,40
jr $ra
label.22:
li $a3 , 1
bne $a3 , 0 ,label.14
li $v1 ,0
addi $sp , $fp ,40
jr $ra
addi $sp , $fp ,40
jr $ra
while_switch_test:
add $fp,$sp,$0 
addi $sp ,$sp , -4
la $a0,$string13
li $v0,4
syscall
sw  $s0,  -4($sp)
sw  $s1,  -8($sp)
sw  $s2,  -12($sp)
sw  $s3,  -16($sp)
sw  $s4,  -20($sp)
sw  $s5,  -24($sp)
sw  $s6,  -28($sp)
sw  $s7,  -32($sp)
sw  $ra,  -36($sp)
sw  $fp,  -40($sp)
addi  $sp,$sp ,-40
 jal while_switch
lw  $s0,  36($fp)
lw  $s1,  32($fp)
lw  $s2,  28($fp)
lw  $s3,  24($fp)
lw  $s4,  20($fp)
lw  $s5,  16($fp)
lw  $s6,  12($fp)
lw  $s7,  8($fp)
lw  $ra,  4($fp)
lw  $fp,  0($fp)
move $t0 , $v1
beq $t0 , 0 ,label.23
la $a0,$string14
li $v0,4
syscall
label.23:
addi $sp , $fp ,40
jr $ra
if_and_glo_loc_test:
add $fp,$sp,$0 
addi $sp ,$sp , -56
li $s5 , 0
li $s0 , 1
bne $s0 , 4 ,label.25
la $a0,$string15
li $v0,4
syscall
j label.28
label.25:
bne $s0 , 1 ,label.27
j label.28
label.27:
la $a0,$string16
li $v0,4
syscall
label.28:
li $s0 , 2
add  $t0 , $s0 , $s5
add  $t1 , $t0 , 1
move $s4 , $t1
li $s3 , 98
li $s2 , 43
li   $a3 ,  0
add  $t2 , $a3 , 10
move $s1 , $t2
bne $s0 , 2 ,label.29
li $a3 , 97
bne $a3 , 97 ,label.30
ble $s3 , 50 ,label.31
bge $s4 , 4 ,label.32
add  $t3 , $s2 , 0
blt $t3 , 43 ,label.33
add  $t4 , $s2 , 0
bgt $t4 , 43 ,label.34
add  $t5 , $s1 , 6
move $s1 , $t5
label.34:
j label.36
label.33:
la $a0,$string17
li $v0,4
syscall
label.36:
label.32:
label.31:
label.30:
j label.40
label.29:
la $a0,$string18
li $v0,4
syscall
label.40:
beq $s1 , 16 ,label.41
la $a0,$string19
li $v0,4
syscall
j label.42
label.41:
la $a0,$string20
li $v0,4
syscall
label.42:
addi $sp , $fp ,40
jr $ra
addi $sp , $fp ,40
jr $ra
array_test:
add $fp,$sp,$0 
addi $sp ,$sp , -48
li $s0 , 0
li $s2 , 0
label.43:
add  $t0 , $s0 , 1
la $a3 ,   g_arr_a
sll $a2, $s0 , 2
add $a3,$a3,$a2
sw $t0 , 0($a3)
add  $t1 , $s0 , 1
move $s0 , $t1
ble $s0 , 999 ,label.43
li $s1 , 0
li $s0 , 0
label.44:
la $a3 ,  g_arr_a
sll $a2, $s0,2
add $a3,$a2,$a3
lw $t2 , 0($a3)
add  $t3 , $s1 , $t2
move $s1 , $t3
add  $t4 , $s0 , 1
move $s0 , $t4
blt $s0 , 1000 ,label.44
la $a0,$string21
li $v0,4
syscall
move $a0, $s1
li $v0 , 1
syscall
bne $s1 , 5050 ,label.45
j label.46
label.45:
add  $t5 , $s2 , 3
move $s2 , $t5
label.46:
la $a3 ,   _g_str_r
addi $a3 , $a3 , 388
li $a2,97
sw $a2,0($a3)
la $a3 ,  _g_str_r
lw $t6 , 388($a3)
bne $t6 , 97 ,label.47
add  $t7 , $s2 , 3
move $s2 , $t7
j label.48
label.47:
add  $t8 , $s2 , 1024
move $s2 , $t8
label.48:
la $a0,$string22
li $v0,4
syscall
move $a0, $s2
li $v0 , 1
syscall
addi $sp , $fp ,40
jr $ra
addi $sp , $fp ,40
jr $ra
quick_sort:
add $fp,$sp,$0 
addi $sp ,$sp , -68
lw $s5 , -4($fp)
lw $s4 , -8($fp)
bge $s5 , $s4 , label.49
move $s0 , $s5
move $s2 , $s4
la $a3 ,  g_qsa
sll $a2, $s0,2
add $a3,$a2,$a3
lw $t0 , 0($a3)
move $s3 , $t0
li $s1 , 0
label.50:
label.51:
bge $s0 , $s2 , label.52
la $a3 ,  g_qsa
sll $a2, $s2,2
add $a3,$a2,$a3
lw $t1 , 0($a3)
ble $t1 , $s3 , label.53
sub  $t2 , $s2 , 1
move $s2 , $t2
j label.54
label.53:
li $s1 , 1
label.54:
j label.55
label.52:
li $s1 , 1
label.55:
beq $s1 , 0 ,label.51
bge $s0 , $s2 , label.56
la $a3 ,  g_qsa
sll $a2, $s2,2
add $a3,$a2,$a3
lw $t3 , 0($a3)
la $a3 ,   g_qsa
sll $a2, $s0 , 2
add $a3,$a3,$a2
sw $t3 , 0($a3)
add  $t4 , $s0 , 1
move $s0 , $t4
li $s1 , 0
label.56:
label.58:
bge $s0 , $s2 , label.59
la $a3 ,  g_qsa
sll $a2, $s0,2
add $a3,$a2,$a3
lw $t5 , 0($a3)
bge $t5 , $s3 , label.60
add  $t6 , $s0 , 1
move $s0 , $t6
j label.61
label.60:
li $s1 , 1
label.61:
j label.62
label.59:
li $s1 , 1
label.62:
beq $s1 , 0 ,label.58
bge $s0 , $s2 , label.63
la $a3 ,  g_qsa
sll $a2, $s0,2
add $a3,$a2,$a3
lw $t7 , 0($a3)
la $a3 ,   g_qsa
sll $a2, $s2 , 2
add $a3,$a3,$a2
sw $t7 , 0($a3)
sub  $t8 , $s2 , 1
move $s2 , $t8
li $s1 , 0
label.63:
blt $s0 , $s2 , label.50
la $a3 ,   g_qsa
sll $a2, $s0 , 2
add $a3,$a3,$a2
sw $s3 , 0($a3)
sub  $t9 , $s0 , 1
sw $s5 , -44($sp)
sw $t9 , -48($sp)
sw $t0 , -28($fp)
sw $t1 , -32($fp)
sw $t2 , -36($fp)
sw $t3 , -40($fp)
sw $t4 , -44($fp)
sw $t5 , -48($fp)
sw $t6 , -52($fp)
sw $t7 , -56($fp)
sw $t8 , -60($fp)
sw $t9 , -64($fp)
sw  $s0,  -4($sp)
sw  $s1,  -8($sp)
sw  $s2,  -12($sp)
sw  $s3,  -16($sp)
sw  $s4,  -20($sp)
sw  $s5,  -24($sp)
sw  $s6,  -28($sp)
sw  $s7,  -32($sp)
sw  $ra,  -36($sp)
sw  $fp,  -40($sp)
addi  $sp,$sp ,-40
 jal quick_sort
lw  $s0,  36($fp)
lw  $s1,  32($fp)
lw  $s2,  28($fp)
lw  $s3,  24($fp)
lw  $s4,  20($fp)
lw  $s5,  16($fp)
lw  $s6,  12($fp)
lw  $s7,  8($fp)
lw  $ra,  4($fp)
lw  $fp,  0($fp)
add  $t0 , $s0 , 1
sw $t0 , -44($sp)
sw $s4 , -48($sp)
sw $t0 , -68($fp)
sw  $s0,  -4($sp)
sw  $s1,  -8($sp)
sw  $s2,  -12($sp)
sw  $s3,  -16($sp)
sw  $s4,  -20($sp)
sw  $s5,  -24($sp)
sw  $s6,  -28($sp)
sw  $s7,  -32($sp)
sw  $ra,  -36($sp)
sw  $fp,  -40($sp)
addi  $sp,$sp ,-40
 jal quick_sort
lw  $s0,  36($fp)
lw  $s1,  32($fp)
lw  $s2,  28($fp)
lw  $s3,  24($fp)
lw  $s4,  20($fp)
lw  $s5,  16($fp)
lw  $s6,  12($fp)
lw  $s7,  8($fp)
lw  $ra,  4($fp)
lw  $fp,  0($fp)
label.49:
li $v1 ,0
addi $sp , $fp ,40
jr $ra
addi $sp , $fp ,40
jr $ra
quick_sort_test:
add $fp,$sp,$0 
addi $sp ,$sp , -28
li $s0 , 0
la $a0,$string23
li $v0,4
syscall
la $a0,$string24
li $v0,4
syscall
li $v0, 5
syscall
move $v1, $v0
move $s1, $v1
label.66:
bgt $s1 , 0 ,label.67
ble $s1 , 20 ,label.68
la $a0,$string25
li $v0,4
syscall
li $v0, 5
syscall
move $v1, $v0
move $s1, $v1
label.68:
label.67:
ble $s1 , 0 ,label.66
label.71:
li $v0, 5
syscall
move $v1, $v0
move $s2, $v1
la $a3 ,   g_qsa
sll $a2, $s0 , 2
add $a3,$a3,$a2
sw $s2 , 0($a3)
add  $t0 , $s0 , 1
move $s0 , $t0
blt $s0 , $s1 , label.71
sub  $t1 , $s1 , 1
li $a3 , 0
sw $a3 , -44($sp)
sw $t1 , -48($sp)
sw $t0 , -16($fp)
sw $t1 , -20($fp)
sw  $s0,  -4($sp)
sw  $s1,  -8($sp)
sw  $s2,  -12($sp)
sw  $s3,  -16($sp)
sw  $s4,  -20($sp)
sw  $s5,  -24($sp)
sw  $s6,  -28($sp)
sw  $s7,  -32($sp)
sw  $ra,  -36($sp)
sw  $fp,  -40($sp)
addi  $sp,$sp ,-40
 jal quick_sort
lw  $s0,  36($fp)
lw  $s1,  32($fp)
lw  $s2,  28($fp)
lw  $s3,  24($fp)
lw  $s4,  20($fp)
lw  $s5,  16($fp)
lw  $s6,  12($fp)
lw  $s7,  8($fp)
lw  $ra,  4($fp)
lw  $fp,  0($fp)
li $s0 , 0
label.72:
la $a3 ,  g_qsa
sll $a2, $s0,2
add $a3,$a2,$a3
lw $t0 , 0($a3)
move $a0, $t0
li $v0 , 1
syscall
add  $t1 , $s0 , 1
move $s0 , $t1
blt $s0 , $s1 , label.72
addi $sp , $fp ,40
jr $ra
addi $sp , $fp ,40
jr $ra
gcd:
add $fp,$sp,$0 
addi $sp ,$sp , -28
lw $s1 , -4($fp)
lw $s0 , -8($fp)
ble $s0 , 0 ,label.73
div  $t0 , $s1 , $s0
mul  $t1 , $t0 , $s0
sub  $t2 , $s1 , $t1
move $s2 , $t2
sw $s0 , -44($sp)
sw $s2 , -48($sp)
sw $t0 , -16($fp)
sw $t1 , -20($fp)
sw $t2 , -24($fp)
sw  $s0,  -4($sp)
sw  $s1,  -8($sp)
sw  $s2,  -12($sp)
sw  $s3,  -16($sp)
sw  $s4,  -20($sp)
sw  $s5,  -24($sp)
sw  $s6,  -28($sp)
sw  $s7,  -32($sp)
sw  $ra,  -36($sp)
sw  $fp,  -40($sp)
addi  $sp,$sp ,-40
 jal gcd
lw  $s0,  36($fp)
lw  $s1,  32($fp)
lw  $s2,  28($fp)
lw  $s3,  24($fp)
lw  $s4,  20($fp)
lw  $s5,  16($fp)
lw  $s6,  12($fp)
lw  $s7,  8($fp)
lw  $ra,  4($fp)
lw  $fp,  0($fp)
move $t0 , $v1
move $v1, $t0
addi $sp , $fp ,40
jr $ra
j label.74
label.73:
move $v1 ,$s1
addi $sp , $fp ,40
jr $ra
label.74:
addi $sp , $fp ,40
jr $ra
gcd_test:
add $fp,$sp,$0 
addi $sp ,$sp , -16
la $a0,$string26
li $v0,4
syscall
la $a0,$string27
li $v0,4
syscall
li $v0, 5
syscall
move $v1, $v0
move $s0, $v1
label.75:
bge $s0 , 0 ,label.76
la $a0,$string28
li $v0,4
syscall
li $v0, 5
syscall
move $v1, $v0
move $s0, $v1
label.76:
blt $s0 , 0 ,label.75
li $v0, 5
syscall
move $v1, $v0
move $s1, $v1
label.78:
bge $s1 , 0 ,label.79
la $a0,$string28
li $v0,4
syscall
li $v0, 5
syscall
move $v1, $v0
move $s1, $v1
label.79:
blt $s1 , 0 ,label.78
sw $s0 , -44($sp)
sw $s1 , -48($sp)
sw  $s0,  -4($sp)
sw  $s1,  -8($sp)
sw  $s2,  -12($sp)
sw  $s3,  -16($sp)
sw  $s4,  -20($sp)
sw  $s5,  -24($sp)
sw  $s6,  -28($sp)
sw  $s7,  -32($sp)
sw  $ra,  -36($sp)
sw  $fp,  -40($sp)
addi  $sp,$sp ,-40
 jal gcd
lw  $s0,  36($fp)
lw  $s1,  32($fp)
lw  $s2,  28($fp)
lw  $s3,  24($fp)
lw  $s4,  20($fp)
lw  $s5,  16($fp)
lw  $s6,  12($fp)
lw  $s7,  8($fp)
lw  $ra,  4($fp)
lw  $fp,  0($fp)
move $t0 , $v1
move $s2 , $t0
la $a0,$string29
li $v0,4
syscall
move $a0, $s2
li $v0 , 1
syscall
addi $sp , $fp ,40
jr $ra
main:
add $fp,$sp,$0 
addi $sp ,$sp , -12
la $a0,$string30
li $v0,4
syscall
la $a0,$string31
li $v0,4
syscall
li $v0, 5
syscall
move $v1, $v0
move $s0, $v1
sw  $s0,  -4($sp)
sw  $s1,  -8($sp)
sw  $s2,  -12($sp)
sw  $s3,  -16($sp)
sw  $s4,  -20($sp)
sw  $s5,  -24($sp)
sw  $s6,  -28($sp)
sw  $s7,  -32($sp)
sw  $ra,  -36($sp)
sw  $fp,  -40($sp)
addi  $sp,$sp ,-40
 jal pr_glo_and_local_test
lw  $s0,  36($fp)
lw  $s1,  32($fp)
lw  $s2,  28($fp)
lw  $s3,  24($fp)
lw  $s4,  20($fp)
lw  $s5,  16($fp)
lw  $s6,  12($fp)
lw  $s7,  8($fp)
lw  $ra,  4($fp)
lw  $fp,  0($fp)
bne $s0 , 0 ,label.81
li $a3 , 98
sw $a3 , -44($sp)
sw  $s0,  -4($sp)
sw  $s1,  -8($sp)
sw  $s2,  -12($sp)
sw  $s3,  -16($sp)
sw  $s4,  -20($sp)
sw  $s5,  -24($sp)
sw  $s6,  -28($sp)
sw  $s7,  -32($sp)
sw  $ra,  -36($sp)
sw  $fp,  -40($sp)
addi  $sp,$sp ,-40
 jal foo2
lw  $s0,  36($fp)
lw  $s1,  32($fp)
lw  $s2,  28($fp)
lw  $s3,  24($fp)
lw  $s4,  20($fp)
lw  $s5,  16($fp)
lw  $s6,  12($fp)
lw  $s7,  8($fp)
lw  $ra,  4($fp)
lw  $fp,  0($fp)
move $t0 , $v1
li $a3 , 1
sw $a3 , -44($sp)
sw $t0 , -48($sp)
sw $t0 , -8($fp)
sw  $s0,  -4($sp)
sw  $s1,  -8($sp)
sw  $s2,  -12($sp)
sw  $s3,  -16($sp)
sw  $s4,  -20($sp)
sw  $s5,  -24($sp)
sw  $s6,  -28($sp)
sw  $s7,  -32($sp)
sw  $ra,  -36($sp)
sw  $fp,  -40($sp)
addi  $sp,$sp ,-40
 jal op_test
lw  $s0,  36($fp)
lw  $s1,  32($fp)
lw  $s2,  28($fp)
lw  $s3,  24($fp)
lw  $s4,  20($fp)
lw  $s5,  16($fp)
lw  $s6,  12($fp)
lw  $s7,  8($fp)
lw  $ra,  4($fp)
lw  $fp,  0($fp)
j label.82
label.81:
sw  $s0,  -4($sp)
sw  $s1,  -8($sp)
sw  $s2,  -12($sp)
sw  $s3,  -16($sp)
sw  $s4,  -20($sp)
sw  $s5,  -24($sp)
sw  $s6,  -28($sp)
sw  $s7,  -32($sp)
sw  $ra,  -36($sp)
sw  $fp,  -40($sp)
addi  $sp,$sp ,-40
 jal foo3
lw  $s0,  36($fp)
lw  $s1,  32($fp)
lw  $s2,  28($fp)
lw  $s3,  24($fp)
lw  $s4,  20($fp)
lw  $s5,  16($fp)
lw  $s6,  12($fp)
lw  $s7,  8($fp)
lw  $ra,  4($fp)
lw  $fp,  0($fp)
move $t0 , $v1
li $a3 , 1
sw $a3 , -44($sp)
sw $t0 , -48($sp)
sw $t0 , -12($fp)
sw  $s0,  -4($sp)
sw  $s1,  -8($sp)
sw  $s2,  -12($sp)
sw  $s3,  -16($sp)
sw  $s4,  -20($sp)
sw  $s5,  -24($sp)
sw  $s6,  -28($sp)
sw  $s7,  -32($sp)
sw  $ra,  -36($sp)
sw  $fp,  -40($sp)
addi  $sp,$sp ,-40
 jal op_test
lw  $s0,  36($fp)
lw  $s1,  32($fp)
lw  $s2,  28($fp)
lw  $s3,  24($fp)
lw  $s4,  20($fp)
lw  $s5,  16($fp)
lw  $s6,  12($fp)
lw  $s7,  8($fp)
lw  $ra,  4($fp)
lw  $fp,  0($fp)
label.82:
sw  $s0,  -4($sp)
sw  $s1,  -8($sp)
sw  $s2,  -12($sp)
sw  $s3,  -16($sp)
sw  $s4,  -20($sp)
sw  $s5,  -24($sp)
sw  $s6,  -28($sp)
sw  $s7,  -32($sp)
sw  $ra,  -36($sp)
sw  $fp,  -40($sp)
addi  $sp,$sp ,-40
 jal while_switch_test
lw  $s0,  36($fp)
lw  $s1,  32($fp)
lw  $s2,  28($fp)
lw  $s3,  24($fp)
lw  $s4,  20($fp)
lw  $s5,  16($fp)
lw  $s6,  12($fp)
lw  $s7,  8($fp)
lw  $ra,  4($fp)
lw  $fp,  0($fp)
sw  $s0,  -4($sp)
sw  $s1,  -8($sp)
sw  $s2,  -12($sp)
sw  $s3,  -16($sp)
sw  $s4,  -20($sp)
sw  $s5,  -24($sp)
sw  $s6,  -28($sp)
sw  $s7,  -32($sp)
sw  $ra,  -36($sp)
sw  $fp,  -40($sp)
addi  $sp,$sp ,-40
 jal if_and_glo_loc_test
lw  $s0,  36($fp)
lw  $s1,  32($fp)
lw  $s2,  28($fp)
lw  $s3,  24($fp)
lw  $s4,  20($fp)
lw  $s5,  16($fp)
lw  $s6,  12($fp)
lw  $s7,  8($fp)
lw  $ra,  4($fp)
lw  $fp,  0($fp)
sw  $s0,  -4($sp)
sw  $s1,  -8($sp)
sw  $s2,  -12($sp)
sw  $s3,  -16($sp)
sw  $s4,  -20($sp)
sw  $s5,  -24($sp)
sw  $s6,  -28($sp)
sw  $s7,  -32($sp)
sw  $ra,  -36($sp)
sw  $fp,  -40($sp)
addi  $sp,$sp ,-40
 jal array_test
lw  $s0,  36($fp)
lw  $s1,  32($fp)
lw  $s2,  28($fp)
lw  $s3,  24($fp)
lw  $s4,  20($fp)
lw  $s5,  16($fp)
lw  $s6,  12($fp)
lw  $s7,  8($fp)
lw  $ra,  4($fp)
lw  $fp,  0($fp)
beq $s0 , 0 ,label.83
sw  $s0,  -4($sp)
sw  $s1,  -8($sp)
sw  $s2,  -12($sp)
sw  $s3,  -16($sp)
sw  $s4,  -20($sp)
sw  $s5,  -24($sp)
sw  $s6,  -28($sp)
sw  $s7,  -32($sp)
sw  $ra,  -36($sp)
sw  $fp,  -40($sp)
addi  $sp,$sp ,-40
 jal quick_sort_test
lw  $s0,  36($fp)
lw  $s1,  32($fp)
lw  $s2,  28($fp)
lw  $s3,  24($fp)
lw  $s4,  20($fp)
lw  $s5,  16($fp)
lw  $s6,  12($fp)
lw  $s7,  8($fp)
lw  $ra,  4($fp)
lw  $fp,  0($fp)
sw  $s0,  -4($sp)
sw  $s1,  -8($sp)
sw  $s2,  -12($sp)
sw  $s3,  -16($sp)
sw  $s4,  -20($sp)
sw  $s5,  -24($sp)
sw  $s6,  -28($sp)
sw  $s7,  -32($sp)
sw  $ra,  -36($sp)
sw  $fp,  -40($sp)
addi  $sp,$sp ,-40
 jal gcd_test
lw  $s0,  36($fp)
lw  $s1,  32($fp)
lw  $s2,  28($fp)
lw  $s3,  24($fp)
lw  $s4,  20($fp)
lw  $s5,  16($fp)
lw  $s6,  12($fp)
lw  $s7,  8($fp)
lw  $ra,  4($fp)
lw  $fp,  0($fp)
label.83:
li $v0 ,10
syscall
addi $sp , $fp ,40
li $v0 ,10
syscall
