.data
_newline_char: .asciiz "\n"
_bool_true: .asciiz "true"
_bool_false: .asciiz "false"
# Will get filled in when we add variables

.text
# Emit the main function code from program
.globl main
main:
# Put the frame pointer and return address on the stack
addi $sp, $sp, -8
sw $ra, 4($sp)
sw $fp, 8($sp)
move $fp, $sp
# Now, all the statements that are part of main...
# Beginning binary operator code
# Begin function call to func
# Save return address
addi $sp, $sp, -4
sw $ra, 0($sp)
# Load number
li $t0, 1
add $sp, $sp, -4
sw $t0, ($sp)
# Pop argument 0 into $a0
lw $a0, 0($sp)
addi $sp, $sp, 4
jal func
# Restore return address
lw $ra, 0($sp)
addi $sp, $sp, 4
# Push return value onto stack - function wasn't void
addi $sp, $sp, -4
sw $v0, 0($sp)
# End function call to func
# Begin function call to func
# Save return address
addi $sp, $sp, -4
sw $ra, 0($sp)
# Load number
li $t0, 3
add $sp, $sp, -4
sw $t0, ($sp)
# Pop argument 0 into $a0
lw $a0, 0($sp)
addi $sp, $sp, 4
jal func
# Restore return address
lw $ra, 0($sp)
addi $sp, $sp, 4
# Push return value onto stack - function wasn't void
addi $sp, $sp, -4
sw $v0, 0($sp)
# End function call to func
# Now perform the operation and store the result in the stack
# Pop right operand off
# Load top off stack into $t0 and decrement the stack
lw $t0, ($sp)
addi $sp, $sp, 4
# Pop left operand off
# Load top off stack into $t1 and decrement the stack
lw $t1, ($sp)
addi $sp, $sp, 4
# Perform comparison: if ($t1 equal to $t0), set equal to = 1, else 0
seq $t2, $t1, $t0
# Store value in $t2 on top of the stack
add $sp, $sp, -4
sw $t2, ($sp)
# Put result on the stack
# Store value in $t2 on top of the stack
add $sp, $sp, -4
sw $t2, ($sp)
# Load value from the stack and print it, with a newline
lw $a0, ($sp)
addi $sp, $sp, 4
li $v0, 1
syscall
la $a0, _newline_char
li $v0, 4
syscall
# Beginning binary operator code
# Load number
li $t0, 0
add $sp, $sp, -4
sw $t0, ($sp)
# Load number
li $t0, 0
add $sp, $sp, -4
sw $t0, ($sp)
# Now perform the operation and store the result in the stack
# Pop right operand off
# Load top off stack into $t0 and decrement the stack
lw $t0, ($sp)
addi $sp, $sp, 4
# Pop left operand off
# Load top off stack into $t1 and decrement the stack
lw $t1, ($sp)
addi $sp, $sp, 4
# Perform comparison: if ($t1 equal to $t0), set equal to = 1, else 0
seq $t2, $t1, $t0
# Store value in $t2 on top of the stack
add $sp, $sp, -4
sw $t2, ($sp)
# Put result on the stack
# Store value in $t2 on top of the stack
add $sp, $sp, -4
sw $t2, ($sp)
# Load value from the stack and print it, with a newline
lw $a0, ($sp)
addi $sp, $sp, 4
li $v0, 1
syscall
la $a0, _newline_char
li $v0, 4
syscall
# Exit
li $v0, 10
syscall
# Emit every other function code from program
# Begin function func
func:
# Store the old frame pointer and the return address onto the stack - then, set the new frame pointer 
# To access these, do 4($fp) and 8($fp)
addi $sp, $sp, -8
sw $ra, 8($sp)
sw $fp, 4($sp)
addi $fp, $sp, 0
# Storing parameter n into 0($fp)
sw $a0, 0($fp)
# Function body
# Return statement
# Expression wasn't null! Emitting expression to store for return
# Beginning binary operator code
# Load variable n into $t0, and put it on the stack at the end
lw $t0, 0($fp)
add $sp, $sp, -4
sw $t0, ($sp)

# Load number
li $t0, 7
add $sp, $sp, -4
sw $t0, ($sp)
# Now perform the operation and store the result in the stack
# Pop right operand off
# Load top off stack into $t0 and decrement the stack
lw $t0, ($sp)
addi $sp, $sp, 4
# Pop left operand off
# Load top off stack into $t1 and decrement the stack
lw $t1, ($sp)
addi $sp, $sp, 4
# Perform comparison: if ($t1 greater than $t0), set greater than = 1, else 0
sgt $t2, $t1, $t0
# Store value in $t2 on top of the stack
add $sp, $sp, -4
sw $t2, ($sp)
# Put result on the stack
# Store value in $t2 on top of the stack
add $sp, $sp, -4
sw $t2, ($sp)
lw $v0, ($sp)
addi $sp, $sp, 4
# Clean up everything - including stack pointer
move $sp, $fp
lw $ra, 8($fp)
lw $fp, 4($fp)
jr $ra
# Default return if no explicit return was emitted - doesn't return any value
lw $ra, 8($fp)
lw $fp, 4($fp)
jr $ra
# End of function func

# All the labels for functions, including main: globl makes a label accessible across the entire program
# Also, for simplicity's sake, I will put a _print_bool function here

# Bool is passed in $a0
_print_bool:
    # Only using registers $a0 and $v0, so I don't think we need to save registers
    beqz $a0, _print_false
    # Else, print true
    la $a0, _bool_true # Load string for false
    li $v0, 4 # Syscall for string printing
    syscall
    jr $ra # Jump back

_print_false:
    la $a0, _bool_false # Load string for true
    li $v0, 4 # Syscall for string printing
    syscall
    jr $ra # Jump back
