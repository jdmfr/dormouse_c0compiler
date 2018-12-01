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
subi $sp ,$sp , 40
move $fp,$sp
li $a3 ,3
sw $a3 ,0($fp)
li $a3 ,-1
sw $a3 ,4($fp)
li $a3 ,-2
sw $a3 ,8($fp)
li $a3 ,65
sw $a3 ,12($fp)
li  $a3 , 1
sw  $a3 , 36($gp)
li  $s1 , 66
li  $s2 , 67
li  $s0 , 53
li  $s5 , 42
li  $s4 , 2
li  $s3 , 68
la $a0,$string0
li $v0,4
syscall
move $a0, $s0
li $v0,11
syscall
lw $a0, 0($gp)
li $v0 , 1
syscall
lw $a0, 0($fp)
li $v0 , 1
syscall
move $a0, $s4
li $v0 , 1
syscall
lw $a0, 4($gp)
li $v0 , 1
syscall
lw $a0, 8($gp)
li $v0 , 1
syscall
lw $a0, 4($fp)
li $v0 , 1
syscall
lw $a0, 8($fp)
li $v0 , 1
syscall
lw $a0, 28($gp)
li $v0 , 1
syscall
lw $a0, 32($gp)
li $v0 , 1
syscall
la $a0,$string1
li $v0,4
syscall
lw $a0, 12($fp)
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
lw $a0, 12($gp)
li $v0,11
syscall
move $a0, $s5
li $v0,11
syscall
add $sp, $sp, 40
jr $ra
foo1:
subi $sp ,$sp , 0
move $fp,$sp
li $v0 ,1
addi $sp,$sp,0
jr $ra
add $sp, $sp, 0
jr $ra
foo2:
subi $sp ,$sp , 4
move $fp,$sp
lw $s0 , 0($fp)
move $v0 ,$s0
addi $sp,$sp,4
jr $ra
add $sp, $sp, 4
jr $ra
foo3:
subi $sp ,$sp , 0
move $fp,$sp
li $v0 ,98
addi $sp,$sp,0
jr $ra
add $sp, $sp, 0
jr $ra
op_test:
subi $sp ,$sp , 32
move $fp,$sp
lw $s4 , 0($fp)
lw $s5 , 4($fp)
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
sw $fp , -92($sp)
sw $ra , -96($sp)
subi  $sp,$sp ,96
 jal foo1
lw $ra , 0($sp)
lw $fp , 4($sp)
lw $k1 , 16($sp)
lw $k0 , 20($sp)
lw $t9 , 24($sp)
lw $t8 , 28($sp)
lw $s7 , 32($sp)
lw $s6 , 36($sp)
lw $s5 , 40($sp)
lw $s4 , 44($sp)
lw $s3 , 48($sp)
lw $s2 , 52($sp)
lw $s1 , 56($sp)
lw $s0 , 60($sp)
lw $t7 , 64($sp)
lw $t6 , 68($sp)
lw $t5 , 72($sp)
lw $t4 , 76($sp)
lw $t3 , 80($sp)
lw $t2 , 84($sp)
lw $t1 , 88($sp)
lw $t0 , 92($sp)
addi $sp,$sp , 96
add  $t0 , $v0 , 31
move $s1 , $t0
move $a3 , $s1
sw  $a3 , 4040($gp)
li  $a3 , 114
sw  $a3 , 4044($gp)
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
sw $fp , -92($sp)
sw $ra , -96($sp)
subi  $sp,$sp ,96
 jal foo1
lw $ra , 0($sp)
lw $fp , 4($sp)
lw $k1 , 16($sp)
lw $k0 , 20($sp)
lw $t9 , 24($sp)
lw $t8 , 28($sp)
lw $s7 , 32($sp)
lw $s6 , 36($sp)
lw $s5 , 40($sp)
lw $s4 , 44($sp)
lw $s3 , 48($sp)
lw $s2 , 52($sp)
lw $s1 , 56($sp)
lw $s0 , 60($sp)
lw $t7 , 64($sp)
lw $t6 , 68($sp)
lw $t5 , 72($sp)
lw $t4 , 76($sp)
lw $t3 , 80($sp)
lw $t2 , 84($sp)
lw $t1 , 88($sp)
lw $t0 , 92($sp)
addi $sp,$sp , 96
li   $a3 ,  34
div  $t1 , $a3 , $v0
li   $a3 ,  68
add  $t2 , $a3 , $t1
move $s0 , $t2
sub  $t3 , $s0 , 1
move $s3 , $t3
li   $a3 ,  68
sub  $t4 , $a3 , 67
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
sw $fp , -92($sp)
sw $ra , -96($sp)
subi  $sp,$sp ,96
 jal foo1
lw $ra , 0($sp)
lw $fp , 4($sp)
lw $k1 , 16($sp)
lw $k0 , 20($sp)
lw $t9 , 24($sp)
lw $t8 , 28($sp)
lw $s7 , 32($sp)
lw $s6 , 36($sp)
lw $s5 , 40($sp)
lw $s4 , 44($sp)
lw $s3 , 48($sp)
lw $s2 , 52($sp)
lw $s1 , 56($sp)
lw $s0 , 60($sp)
lw $t7 , 64($sp)
lw $t6 , 68($sp)
lw $t5 , 72($sp)
lw $t4 , 76($sp)
lw $t3 , 80($sp)
lw $t2 , 84($sp)
lw $t1 , 88($sp)
lw $t0 , 92($sp)
addi $sp,$sp , 96
sub  $t5 , $t4 , $v0
add  $t6 , $t5 , $s5
move $s2 , $t6
addi $a3 ,$fp ,12
addi $a3 , $a3 , 4
sw $s4 , 0($a3)
mul  $t7 , $s0 , 25
li   $a3 ,  3
mul  $t8 , $a3 , 4
div  $t9 , $t8 , 2
add  $t0 , $t7 , $t9
li   $a3 ,  5
mul  $t1 , $a3 , 3
sub  $t2 , $t0 , $t1
add  $t3 , $s3 , 1
sub  $t4 , $s0 , $t3
add  $t5 , $t2 , $t4
add  $t6 , $t5 , $s2
addi $a3 ,$fp ,12
sll $a2,$0,2
add $a3,$a3,$a2
sw $t6 , 0($a3)
addi $a3 , $fp , 12
lw $t7 , 0($a3)
lw $a2 , 4044($gp)
bne $t7 , $a2 , label.0
la $a0,$string3
li $v0,4
syscall
j label.1
label.0:
label.1:
addi $sp,$sp,32
jr $ra
add $sp, $sp, 32
jr $ra
while_switch:
subi $sp ,$sp , 8
move $fp,$sp
li  $s1 , 97
label.2:
bne $s1 , 97 ,label.4
la $a0,$string4
li $v0,4
syscall
li  $s1 , 98
j label.3
label.4:
bne $s1 , 98 ,label.5
la $a0,$string5
li $v0,4
syscall
li  $s1 , 99
j label.3
label.5:
bne $s1 , 99 ,label.6
la $a0,$string6
li $v0,4
syscall
li  $s1 , 100
j label.3
label.6:
label.3:
bne $s1 , 100 ,label.2
lw  $a3 , 4($gp)
sub  $t8 , $a3 , 1
move $s0 , $t8
label.7:
li   $a3 ,  32
div  $t9 , $a3 , 32
sub  $t0 , $s0 , $t9
add  $t1 , $t0 , 1
bne $t1 , 0 ,label.9
li  $s0 , 1
j label.8
label.9:
bne $t1 , 1 ,label.10
add  $t2 , $s0 , 1
move $s0 , $t2
j label.8
label.10:
bne $t1 , 2 ,label.11
li   $a3 ,  0
sub  $t3 , $a3 , 32
move $s0 , $t3
j label.8
label.11:
label.8:
bge $s0 , 0 ,label.7
li   $a3 ,  0
lw  $t4 , 4040($gp)
sub  $t5 , $a3 , $t4
beq $s0 , $t5 , label.12
la $a0,$string7
li $v0,4
syscall
j label.13
label.12:
la $a0,$string8
li $v0,4
syscall
li   $a3 ,  97
add  $t6 , $a3 , 0
move $s0 , $t6
label.13:
label.14:
bne $s0 , 97 ,label.16
la $a0,$string9
li $v0,4
syscall
label.17:
add  $t7 , $s0 , 1
move $s0 , $t7
li   $a3 ,  99
add  $t8 , $a3 , 0
blt $s0 , $t8 , label.17
j label.15
label.16:
bne $s0 , 99 ,label.18
label.19:
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
sw $fp , -92($sp)
sw $ra , -96($sp)
subi  $sp,$sp ,96
 jal foo1
lw $ra , 0($sp)
lw $fp , 4($sp)
lw $k1 , 16($sp)
lw $k0 , 20($sp)
lw $t9 , 24($sp)
lw $t8 , 28($sp)
lw $s7 , 32($sp)
lw $s6 , 36($sp)
lw $s5 , 40($sp)
lw $s4 , 44($sp)
lw $s3 , 48($sp)
lw $s2 , 52($sp)
lw $s1 , 56($sp)
lw $s0 , 60($sp)
lw $t7 , 64($sp)
lw $t6 , 68($sp)
lw $t5 , 72($sp)
lw $t4 , 76($sp)
lw $t3 , 80($sp)
lw $t2 , 84($sp)
lw $t1 , 88($sp)
lw $t0 , 92($sp)
addi $sp,$sp , 96
add  $t9 , $s0 , $v0
move $s0 , $t9
li   $a3 ,  100
add  $t0 , $a3 , 0
beq $s0 , $t0 , label.19
j label.15
label.18:
bne $s0 , -32 ,label.20
la $a0,$string10
li $v0,4
syscall
j label.15
label.20:
li   $a3 ,  105
add  $t1 , $a3 , 0
beq $s0 , $t1 , label.21
la $a0,$string11
li $v0,4
syscall
add  $t2 , $s0 , 1
move $s0 , $t2
j label.22
label.21:
la $a0,$string12
li $v0,4
syscall
li $v0 ,1
addi $sp,$sp,8
jr $ra
label.22:
label.15:
li $a3 , 1
bne $a3 , 0 ,label.14
li $v0 ,0
addi $sp,$sp,8
jr $ra
add $sp, $sp, 8
jr $ra
while_switch_test:
subi $sp ,$sp , 0
move $fp,$sp
la $a0,$string13
li $v0,4
syscall
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
sw $fp , -92($sp)
sw $ra , -96($sp)
subi  $sp,$sp ,96
 jal while_switch
lw $ra , 0($sp)
lw $fp , 4($sp)
lw $k1 , 16($sp)
lw $k0 , 20($sp)
lw $t9 , 24($sp)
lw $t8 , 28($sp)
lw $s7 , 32($sp)
lw $s6 , 36($sp)
lw $s5 , 40($sp)
lw $s4 , 44($sp)
lw $s3 , 48($sp)
lw $s2 , 52($sp)
lw $s1 , 56($sp)
lw $s0 , 60($sp)
lw $t7 , 64($sp)
lw $t6 , 68($sp)
lw $t5 , 72($sp)
lw $t4 , 76($sp)
lw $t3 , 80($sp)
lw $t2 , 84($sp)
lw $t1 , 88($sp)
lw $t0 , 92($sp)
addi $sp,$sp , 96
beq $v0 , 0 ,label.23
la $a0,$string14
li $v0,4
syscall
j label.24
label.23:
label.24:
add $sp, $sp, 0
jr $ra
if_and_glo_loc_test:
subi $sp ,$sp , 32
move $fp,$sp
li $a3 ,1
sw $a3 ,0($fp)
li $a3 ,97
sw $a3 ,4($fp)
li  $s5 , 0
lw $s0 , 0($fp)
bne $s0 , 4 ,label.25
la $a0,$string15
li $v0,4
syscall
j label.26
label.25:
bne $s0 , 1 ,label.27
j label.28
label.27:
la $a0,$string16
li $v0,4
syscall
label.28:
label.26:
li  $s0 , 2
add  $t3 , $s0 , $s5
add  $t4 , $t3 , 1
move $s4 , $t4
li  $s3 , 98
li  $s2 , 43
lw  $a3 , 20($gp)
add  $t5 , $a3 , 10
move $s1 , $t5
bne $s0 , 2 ,label.29
lw $a3, 4($fp)
bne $a3 , 97 ,label.30
ble $s3 , 50 ,label.31
bge $s4 , 4 ,label.32
blt $s2 , 43 ,label.33
bgt $s2 , 43 ,label.34
add  $t6 , $s1 , 6
move $s1 , $t6
j label.35
label.34:
label.35:
j label.36
label.33:
la $a0,$string17
li $v0,4
syscall
label.36:
j label.37
label.32:
label.37:
j label.38
label.31:
label.38:
j label.39
label.30:
label.39:
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
addi $sp,$sp,32
jr $ra
add $sp, $sp, 32
jr $ra
array_test:
subi $sp ,$sp , 12
move $fp,$sp
li  $s0 , 0
li  $s2 , 0
label.43:
add  $t7 , $s0 , 1
la $a3 ,   g_arr_a
sll $a2, $s0 , 2
add $a3,$a3,$a2
sw $t7 , 0($a3)
add  $t8 , $s0 , 1
move $s0 , $t8
ble $s0 , 999 ,label.43
li  $s1 , 0
li  $s0 , 0
label.44:
la $a3 ,  g_arr_a
sll $a2 , $s0,2
add $a3,$a2,$a3
lw $t9 , 0($a3)
add  $t0 , $s1 , $t9
move $s1 , $t0
lw  $t1 , 4($gp)
add  $t2 , $s0 , $t1
move $s0 , $t2
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
add  $t3 , $s2 , 3
move $s2 , $t3
label.46:
la $a3 ,   _g_str_r
addi $a3 , $a3 , 388
li $a2,97
sw $a2,0($a3)
la $a3 ,  _g_str_r
lw $t4 , 388($a3)
bne $t4 , 97 ,label.47
add  $t5 , $s2 , 3
move $s2 , $t5
j label.48
label.47:
add  $t6 , $s2 , 1024
move $s2 , $t6
label.48:
la $a0,$string22
li $v0,4
syscall
move $a0, $s2
li $v0 , 1
syscall
addi $sp,$sp,12
jr $ra
add $sp, $sp, 12
jr $ra
quick_sort:
subi $sp ,$sp , 24
move $fp,$sp
lw $s5 , 0($fp)
lw $s4 , 4($fp)
bge $s5 , $s4 , label.49
move $s0 , $s5
move $s2 , $s4
la $a3 ,  g_qsa
sll $a2 , $s0,2
add $a3,$a2,$a3
lw $t7 , 0($a3)
move $s3 , $t7
li  $s1 , 0
label.50:
label.51:
bge $s0 , $s2 , label.52
la $a3 ,  g_qsa
sll $a2 , $s2,2
add $a3,$a2,$a3
lw $t8 , 0($a3)
ble $t8 , $s3 , label.53
sub  $t9 , $s2 , 1
move $s2 , $t9
j label.54
label.53:
li  $s1 , 1
label.54:
j label.55
label.52:
li  $s1 , 1
label.55:
beq $s1 , 0 ,label.51
bge $s0 , $s2 , label.56
la $a3 ,  g_qsa
sll $a2 , $s2,2
add $a3,$a2,$a3
lw $t0 , 0($a3)
la $a3 ,   g_qsa
sll $a2, $s0 , 2
add $a3,$a3,$a2
sw $t0 , 0($a3)
add  $t1 , $s0 , 1
move $s0 , $t1
li  $s1 , 0
j label.57
label.56:
label.57:
label.58:
bge $s0 , $s2 , label.59
la $a3 ,  g_qsa
sll $a2 , $s0,2
add $a3,$a2,$a3
lw $t2 , 0($a3)
bge $t2 , $s3 , label.60
add  $t3 , $s0 , 1
move $s0 , $t3
j label.61
label.60:
li  $s1 , 1
label.61:
j label.62
label.59:
li  $s1 , 1
label.62:
beq $s1 , 0 ,label.58
bge $s0 , $s2 , label.63
la $a3 ,  g_qsa
sll $a2 , $s0,2
add $a3,$a2,$a3
lw $t4 , 0($a3)
la $a3 ,   g_qsa
sll $a2, $s2 , 2
add $a3,$a3,$a2
sw $t4 , 0($a3)
sub  $t5 , $s2 , 1
move $s2 , $t5
li  $s1 , 0
j label.64
label.63:
label.64:
blt $s0 , $s2 , label.50
la $a3 ,   g_qsa
sll $a2, $s0 , 2
add $a3,$a3,$a2
sw $s3 , 0($a3)
sw $s5 , -4($sp)
sub  $t6 , $s0 , 1
sw $t6 , -8($sp)
lw  $a3 , -8($sp)
sw  $a3 , -116($sp)
lw  $a3 , -4($sp)
sw  $a3 , -120($sp)
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
sw $fp , -92($sp)
sw $ra , -96($sp)
subi  $sp,$sp ,96
 jal quick_sort
lw $ra , 0($sp)
lw $fp , 4($sp)
lw $k1 , 16($sp)
lw $k0 , 20($sp)
lw $t9 , 24($sp)
lw $t8 , 28($sp)
lw $s7 , 32($sp)
lw $s6 , 36($sp)
lw $s5 , 40($sp)
lw $s4 , 44($sp)
lw $s3 , 48($sp)
lw $s2 , 52($sp)
lw $s1 , 56($sp)
lw $s0 , 60($sp)
lw $t7 , 64($sp)
lw $t6 , 68($sp)
lw $t5 , 72($sp)
lw $t4 , 76($sp)
lw $t3 , 80($sp)
lw $t2 , 84($sp)
lw $t1 , 88($sp)
lw $t0 , 92($sp)
addi $sp,$sp , 96
add  $t7 , $s0 , 1
sw $t7 , -4($sp)
sw $s4 , -8($sp)
lw  $a3 , -8($sp)
sw  $a3 , -116($sp)
lw  $a3 , -4($sp)
sw  $a3 , -120($sp)
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
sw $fp , -92($sp)
sw $ra , -96($sp)
subi  $sp,$sp ,96
 jal quick_sort
lw $ra , 0($sp)
lw $fp , 4($sp)
lw $k1 , 16($sp)
lw $k0 , 20($sp)
lw $t9 , 24($sp)
lw $t8 , 28($sp)
lw $s7 , 32($sp)
lw $s6 , 36($sp)
lw $s5 , 40($sp)
lw $s4 , 44($sp)
lw $s3 , 48($sp)
lw $s2 , 52($sp)
lw $s1 , 56($sp)
lw $s0 , 60($sp)
lw $t7 , 64($sp)
lw $t6 , 68($sp)
lw $t5 , 72($sp)
lw $t4 , 76($sp)
lw $t3 , 80($sp)
lw $t2 , 84($sp)
lw $t1 , 88($sp)
lw $t0 , 92($sp)
addi $sp,$sp , 96
j label.65
label.49:
label.65:
li $v0 ,0
addi $sp,$sp,24
jr $ra
add $sp, $sp, 24
jr $ra
quick_sort_test:
subi $sp ,$sp , 12
move $fp,$sp
li  $s0 , 0
la $a0,$string23
li $v0,4
syscall
la $a0,$string24
li $v0,4
syscall
li $v0, 5
syscall
move $s1, $v0
label.66:
bgt $s1 , 0 ,label.67
ble $s1 , 20 ,label.68
la $a0,$string25
li $v0,4
syscall
li $v0, 5
syscall
move $s1, $v0
j label.69
label.68:
label.69:
j label.70
label.67:
label.70:
ble $s1 , 0 ,label.66
label.71:
li $v0, 5
syscall
move $s2, $v0
la $a3 ,   g_qsa
sll $a2, $s0 , 2
add $a3,$a3,$a2
sw $s2 , 0($a3)
add  $t8 , $s0 , 1
move $s0 , $t8
blt $s0 , $s1 , label.71
li $a3 , 0
sw $a3 , -4($sp)
sub  $t9 , $s1 , 1
sw $t9 , -8($sp)
lw  $a3 , -8($sp)
sw  $a3 , -116($sp)
lw  $a3 , -4($sp)
sw  $a3 , -120($sp)
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
sw $fp , -92($sp)
sw $ra , -96($sp)
subi  $sp,$sp ,96
 jal quick_sort
lw $ra , 0($sp)
lw $fp , 4($sp)
lw $k1 , 16($sp)
lw $k0 , 20($sp)
lw $t9 , 24($sp)
lw $t8 , 28($sp)
lw $s7 , 32($sp)
lw $s6 , 36($sp)
lw $s5 , 40($sp)
lw $s4 , 44($sp)
lw $s3 , 48($sp)
lw $s2 , 52($sp)
lw $s1 , 56($sp)
lw $s0 , 60($sp)
lw $t7 , 64($sp)
lw $t6 , 68($sp)
lw $t5 , 72($sp)
lw $t4 , 76($sp)
lw $t3 , 80($sp)
lw $t2 , 84($sp)
lw $t1 , 88($sp)
lw $t0 , 92($sp)
addi $sp,$sp , 96
li  $s0 , 0
label.72:
la $a3 ,  g_qsa
sll $a2 , $s0,2
add $a3,$a2,$a3
lw $t0 , 0($a3)
move $a0, $t0
li $v0 , 1
syscall
add  $t1 , $s0 , 1
move $s0 , $t1
blt $s0 , $s1 , label.72
addi $sp,$sp,12
jr $ra
add $sp, $sp, 12
jr $ra
gcd:
subi $sp ,$sp , 12
move $fp,$sp
lw $s1 , 0($fp)
lw $s0 , 4($fp)
ble $s0 , 0 ,label.73
div  $t2 , $s1 , $s0
mul  $t3 , $t2 , $s0
sub  $t4 , $s1 , $t3
move $s2 , $t4
sw $s0 , -4($sp)
sw $s2 , -8($sp)
lw  $a3 , -8($sp)
sw  $a3 , -104($sp)
lw  $a3 , -4($sp)
sw  $a3 , -108($sp)
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
sw $fp , -92($sp)
sw $ra , -96($sp)
subi  $sp,$sp ,96
 jal gcd
lw $ra , 0($sp)
lw $fp , 4($sp)
lw $k1 , 16($sp)
lw $k0 , 20($sp)
lw $t9 , 24($sp)
lw $t8 , 28($sp)
lw $s7 , 32($sp)
lw $s6 , 36($sp)
lw $s5 , 40($sp)
lw $s4 , 44($sp)
lw $s3 , 48($sp)
lw $s2 , 52($sp)
lw $s1 , 56($sp)
lw $s0 , 60($sp)
lw $t7 , 64($sp)
lw $t6 , 68($sp)
lw $t5 , 72($sp)
lw $t4 , 76($sp)
lw $t3 , 80($sp)
lw $t2 , 84($sp)
lw $t1 , 88($sp)
lw $t0 , 92($sp)
addi $sp,$sp , 96
addi $sp,$sp,12
jr $ra
j label.74
label.73:
move $v0 ,$s1
addi $sp,$sp,12
jr $ra
label.74:
add $sp, $sp, 12
jr $ra
gcd_test:
subi $sp ,$sp , 12
move $fp,$sp
la $a0,$string26
li $v0,4
syscall
la $a0,$string27
li $v0,4
syscall
li $v0, 5
syscall
move $s0, $v0
label.75:
bge $s0 , 0 ,label.76
la $a0,$string28
li $v0,4
syscall
li $v0, 5
syscall
move $s0, $v0
j label.77
label.76:
label.77:
blt $s0 , 0 ,label.75
li $v0, 5
syscall
move $s1, $v0
label.78:
bge $s1 , 0 ,label.79
la $a0,$string28
li $v0,4
syscall
li $v0, 5
syscall
move $s1, $v0
j label.80
label.79:
label.80:
blt $s1 , 0 ,label.78
sw $s0 , -4($sp)
sw $s1 , -8($sp)
lw  $a3 , -8($sp)
sw  $a3 , -104($sp)
lw  $a3 , -4($sp)
sw  $a3 , -108($sp)
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
sw $fp , -92($sp)
sw $ra , -96($sp)
subi  $sp,$sp ,96
 jal gcd
lw $ra , 0($sp)
lw $fp , 4($sp)
lw $k1 , 16($sp)
lw $k0 , 20($sp)
lw $t9 , 24($sp)
lw $t8 , 28($sp)
lw $s7 , 32($sp)
lw $s6 , 36($sp)
lw $s5 , 40($sp)
lw $s4 , 44($sp)
lw $s3 , 48($sp)
lw $s2 , 52($sp)
lw $s1 , 56($sp)
lw $s0 , 60($sp)
lw $t7 , 64($sp)
lw $t6 , 68($sp)
lw $t5 , 72($sp)
lw $t4 , 76($sp)
lw $t3 , 80($sp)
lw $t2 , 84($sp)
lw $t1 , 88($sp)
lw $t0 , 92($sp)
addi $sp,$sp , 96
move  $s2 , $v0
la $a0,$string29
li $v0,4
syscall
move $a0, $s2
li $v0 , 1
syscall
add $sp, $sp, 12
jr $ra
main:
subi $sp ,$sp , 4
move $fp,$sp
la $a0,$string30
li $v0,4
syscall
la $a0,$string31
li $v0,4
syscall
li $v0, 5
syscall
move $s0, $v0
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
sw $fp , -92($sp)
sw $ra , -96($sp)
subi  $sp,$sp ,96
 jal pr_glo_and_local_test
lw $ra , 0($sp)
lw $fp , 4($sp)
lw $k1 , 16($sp)
lw $k0 , 20($sp)
lw $t9 , 24($sp)
lw $t8 , 28($sp)
lw $s7 , 32($sp)
lw $s6 , 36($sp)
lw $s5 , 40($sp)
lw $s4 , 44($sp)
lw $s3 , 48($sp)
lw $s2 , 52($sp)
lw $s1 , 56($sp)
lw $s0 , 60($sp)
lw $t7 , 64($sp)
lw $t6 , 68($sp)
lw $t5 , 72($sp)
lw $t4 , 76($sp)
lw $t3 , 80($sp)
lw $t2 , 84($sp)
lw $t1 , 88($sp)
lw $t0 , 92($sp)
addi $sp,$sp , 96
bne $s0 , 0 ,label.81
li $a3 , 1
sw $a3 , -4($sp)
li $a3 , 98
sw $a3 , -8($sp)
lw  $a3 , -4($sp)
sw  $a3 , -100($sp)
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
sw $fp , -92($sp)
sw $ra , -96($sp)
subi  $sp,$sp ,96
 jal foo2
lw $ra , 0($sp)
lw $fp , 4($sp)
lw $k1 , 16($sp)
lw $k0 , 20($sp)
lw $t9 , 24($sp)
lw $t8 , 28($sp)
lw $s7 , 32($sp)
lw $s6 , 36($sp)
lw $s5 , 40($sp)
lw $s4 , 44($sp)
lw $s3 , 48($sp)
lw $s2 , 52($sp)
lw $s1 , 56($sp)
lw $s0 , 60($sp)
lw $t7 , 64($sp)
lw $t6 , 68($sp)
lw $t5 , 72($sp)
lw $t4 , 76($sp)
lw $t3 , 80($sp)
lw $t2 , 84($sp)
lw $t1 , 88($sp)
lw $t0 , 92($sp)
addi $sp,$sp , 96
sw $v0 , -4($sp)
lw  $a3 , -8($sp)
sw  $a3 , -124($sp)
lw  $a3 , -4($sp)
sw  $a3 , -128($sp)
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
sw $fp , -92($sp)
sw $ra , -96($sp)
subi  $sp,$sp ,96
 jal op_test
lw $ra , 0($sp)
lw $fp , 4($sp)
lw $k1 , 16($sp)
lw $k0 , 20($sp)
lw $t9 , 24($sp)
lw $t8 , 28($sp)
lw $s7 , 32($sp)
lw $s6 , 36($sp)
lw $s5 , 40($sp)
lw $s4 , 44($sp)
lw $s3 , 48($sp)
lw $s2 , 52($sp)
lw $s1 , 56($sp)
lw $s0 , 60($sp)
lw $t7 , 64($sp)
lw $t6 , 68($sp)
lw $t5 , 72($sp)
lw $t4 , 76($sp)
lw $t3 , 80($sp)
lw $t2 , 84($sp)
lw $t1 , 88($sp)
lw $t0 , 92($sp)
addi $sp,$sp , 96
j label.82
label.81:
li $a3 , 1
sw $a3 , -4($sp)
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
sw $fp , -92($sp)
sw $ra , -96($sp)
subi  $sp,$sp ,96
 jal foo3
lw $ra , 0($sp)
lw $fp , 4($sp)
lw $k1 , 16($sp)
lw $k0 , 20($sp)
lw $t9 , 24($sp)
lw $t8 , 28($sp)
lw $s7 , 32($sp)
lw $s6 , 36($sp)
lw $s5 , 40($sp)
lw $s4 , 44($sp)
lw $s3 , 48($sp)
lw $s2 , 52($sp)
lw $s1 , 56($sp)
lw $s0 , 60($sp)
lw $t7 , 64($sp)
lw $t6 , 68($sp)
lw $t5 , 72($sp)
lw $t4 , 76($sp)
lw $t3 , 80($sp)
lw $t2 , 84($sp)
lw $t1 , 88($sp)
lw $t0 , 92($sp)
addi $sp,$sp , 96
sw $v0 , -4($sp)
lw  $a3 , -8($sp)
sw  $a3 , -124($sp)
lw  $a3 , -4($sp)
sw  $a3 , -128($sp)
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
sw $fp , -92($sp)
sw $ra , -96($sp)
subi  $sp,$sp ,96
 jal op_test
lw $ra , 0($sp)
lw $fp , 4($sp)
lw $k1 , 16($sp)
lw $k0 , 20($sp)
lw $t9 , 24($sp)
lw $t8 , 28($sp)
lw $s7 , 32($sp)
lw $s6 , 36($sp)
lw $s5 , 40($sp)
lw $s4 , 44($sp)
lw $s3 , 48($sp)
lw $s2 , 52($sp)
lw $s1 , 56($sp)
lw $s0 , 60($sp)
lw $t7 , 64($sp)
lw $t6 , 68($sp)
lw $t5 , 72($sp)
lw $t4 , 76($sp)
lw $t3 , 80($sp)
lw $t2 , 84($sp)
lw $t1 , 88($sp)
lw $t0 , 92($sp)
addi $sp,$sp , 96
label.82:
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
sw $fp , -92($sp)
sw $ra , -96($sp)
subi  $sp,$sp ,96
 jal while_switch_test
lw $ra , 0($sp)
lw $fp , 4($sp)
lw $k1 , 16($sp)
lw $k0 , 20($sp)
lw $t9 , 24($sp)
lw $t8 , 28($sp)
lw $s7 , 32($sp)
lw $s6 , 36($sp)
lw $s5 , 40($sp)
lw $s4 , 44($sp)
lw $s3 , 48($sp)
lw $s2 , 52($sp)
lw $s1 , 56($sp)
lw $s0 , 60($sp)
lw $t7 , 64($sp)
lw $t6 , 68($sp)
lw $t5 , 72($sp)
lw $t4 , 76($sp)
lw $t3 , 80($sp)
lw $t2 , 84($sp)
lw $t1 , 88($sp)
lw $t0 , 92($sp)
addi $sp,$sp , 96
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
sw $fp , -92($sp)
sw $ra , -96($sp)
subi  $sp,$sp ,96
 jal if_and_glo_loc_test
lw $ra , 0($sp)
lw $fp , 4($sp)
lw $k1 , 16($sp)
lw $k0 , 20($sp)
lw $t9 , 24($sp)
lw $t8 , 28($sp)
lw $s7 , 32($sp)
lw $s6 , 36($sp)
lw $s5 , 40($sp)
lw $s4 , 44($sp)
lw $s3 , 48($sp)
lw $s2 , 52($sp)
lw $s1 , 56($sp)
lw $s0 , 60($sp)
lw $t7 , 64($sp)
lw $t6 , 68($sp)
lw $t5 , 72($sp)
lw $t4 , 76($sp)
lw $t3 , 80($sp)
lw $t2 , 84($sp)
lw $t1 , 88($sp)
lw $t0 , 92($sp)
addi $sp,$sp , 96
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
sw $fp , -92($sp)
sw $ra , -96($sp)
subi  $sp,$sp ,96
 jal array_test
lw $ra , 0($sp)
lw $fp , 4($sp)
lw $k1 , 16($sp)
lw $k0 , 20($sp)
lw $t9 , 24($sp)
lw $t8 , 28($sp)
lw $s7 , 32($sp)
lw $s6 , 36($sp)
lw $s5 , 40($sp)
lw $s4 , 44($sp)
lw $s3 , 48($sp)
lw $s2 , 52($sp)
lw $s1 , 56($sp)
lw $s0 , 60($sp)
lw $t7 , 64($sp)
lw $t6 , 68($sp)
lw $t5 , 72($sp)
lw $t4 , 76($sp)
lw $t3 , 80($sp)
lw $t2 , 84($sp)
lw $t1 , 88($sp)
lw $t0 , 92($sp)
addi $sp,$sp , 96
beq $s0 , 0 ,label.83
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
sw $fp , -92($sp)
sw $ra , -96($sp)
subi  $sp,$sp ,96
 jal quick_sort_test
lw $ra , 0($sp)
lw $fp , 4($sp)
lw $k1 , 16($sp)
lw $k0 , 20($sp)
lw $t9 , 24($sp)
lw $t8 , 28($sp)
lw $s7 , 32($sp)
lw $s6 , 36($sp)
lw $s5 , 40($sp)
lw $s4 , 44($sp)
lw $s3 , 48($sp)
lw $s2 , 52($sp)
lw $s1 , 56($sp)
lw $s0 , 60($sp)
lw $t7 , 64($sp)
lw $t6 , 68($sp)
lw $t5 , 72($sp)
lw $t4 , 76($sp)
lw $t3 , 80($sp)
lw $t2 , 84($sp)
lw $t1 , 88($sp)
lw $t0 , 92($sp)
addi $sp,$sp , 96
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
sw $fp , -92($sp)
sw $ra , -96($sp)
subi  $sp,$sp ,96
 jal gcd_test
lw $ra , 0($sp)
lw $fp , 4($sp)
lw $k1 , 16($sp)
lw $k0 , 20($sp)
lw $t9 , 24($sp)
lw $t8 , 28($sp)
lw $s7 , 32($sp)
lw $s6 , 36($sp)
lw $s5 , 40($sp)
lw $s4 , 44($sp)
lw $s3 , 48($sp)
lw $s2 , 52($sp)
lw $s1 , 56($sp)
lw $s0 , 60($sp)
lw $t7 , 64($sp)
lw $t6 , 68($sp)
lw $t5 , 72($sp)
lw $t4 , 76($sp)
lw $t3 , 80($sp)
lw $t2 , 84($sp)
lw $t1 , 88($sp)
lw $t0 , 92($sp)
addi $sp,$sp , 96
j label.84
label.83:
label.84:
li $v0 ,10
syscall
add $sp, $sp, 4
li $v0 ,10
syscall
