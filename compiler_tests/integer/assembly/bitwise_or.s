.global f
f:
addiu $sp,$sp, -64
sw $s0,4 ($sp)
sw $s1,8 ($sp)
sw $s2,12 ($sp)
sw $s3,16 ($sp)
sw $s4,20 ($sp)
sw $s5,24 ($sp)
sw $s6,28 ($sp)
sw $s7,32 ($sp)
sw $a0,36 ($sp)
sw $a1,40 ($sp)
sw $a2,44 ($sp)
sw $a3,48 ($sp)
sw $ra,52 ($sp)
li $t9,0
sw $t9,56($sp)
lw $t9,36 ($sp)
lw $t8,40 ($sp)
or $t9,$t9,$t8
sw $t9,56($sp)
lw $v0,56 ($sp)
lw $s0,4 ($sp)
lw $s1,8 ($sp)
lw $s2,12 ($sp)
lw $s3,16 ($sp)
lw $s4,20 ($sp)
lw $s5,24 ($sp)
lw $s6,28 ($sp)
lw $s7,32 ($sp)
lw $a0,36 ($sp)
lw $a1,40 ($sp)
lw $a2,44 ($sp)
lw $a3,48 ($sp)
lw $ra,52 ($sp)
addiu $sp,$sp,64
jr $ra
