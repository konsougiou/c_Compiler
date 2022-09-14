.global bsqrt
bsqrt:
addiu $sp,$sp, -60
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
label0:
lw $t9,36 ($sp)
li $t8,1
add $t9,$t9,$t8
lw $t8,40 ($sp)
slt $t9,$t9,$t8
beq $t9,$zero,label1
lw $t9,36 ($sp)
lw $t8,40 ($sp)
add $t9,$t9,$t8
li $t8,1
srl $t9,$t9,$t8
sw $t9,56 ($sp)
lw $t9,56 ($sp)
lw $t8,56 ($sp)
mul $t9,$t9,$t8
sw $t9,60 ($sp)
lw $t9,60 ($sp)
lw $t8,44 ($sp)
addi $t8,1
slt $t9,$t9,$t8
beq $t9,$zero,label2
lw $t9,56 ($sp)
sw $t9,36($sp)
j label3
label2:
lw $t9,56 ($sp)
sw $t9,40($sp)
label3:
j label0
label1:
lw $t9,36 ($sp)
lw $t8,36 ($sp)
mul $t9,$t9,$t8
lw $t8,44 ($sp)
slt $t9,$t9,$t8
beq $t9,$zero,label4
lw $v0,40 ($sp)
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
addiu $sp,$sp,60
jr $ra
j label5
label4:
lw $v0,36 ($sp)
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
addiu $sp,$sp,60
jr $ra
label5:
