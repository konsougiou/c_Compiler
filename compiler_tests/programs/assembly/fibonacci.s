.global fib
fib:
addiu $sp,$sp, -380
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
lw $t9,36 ($sp)
li $t8,0
addi $t8,1
slt $t9,$t9,$t8
beq $t9,$zero,label0
li $v0,0
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
addiu $sp,$sp,380
jr $ra
label0:
lw $t9,36 ($sp)
li $t8,1
beq $t9,$t8,label2
li $t9,0
j label3
label2:
li $t9,1
label3:
beq $t9,$zero,label1
li $v0,1
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
addiu $sp,$sp,380
jr $ra
label1:
lw $t9,36 ($sp)
li $t8,1
sub $a0,$t9,$t8
jal fib
move $t9,$v0
lw $t8,36 ($sp)
li $t7,2
sub $a0,$t8,$t7
sw $t9,56 ($sp)
jal fib
lw $t9,56 ($sp)
move $t8,$v0
add $v0,$t9,$t8
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
addiu $sp,$sp,380
jr $ra
