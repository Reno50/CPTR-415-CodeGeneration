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
# Allocating space for y, which requires 4 bytes, and setting it to 0
add $sp, $sp, -4
li $t0, 0
sw $t0, ($sp)
# Allocating space for x, which requires 4 bytes, and setting it to 0
add $sp, $sp, -4
li $t0, 0
sw $t0, ($sp)
# Load number
li $t0, 3
add $sp, $sp, -4
sw $t0, ($sp)
# Unary minus - set number at top of stack to a negative number
lw $t0, ($sp)
sub $t0, $zero, $t0
sw $t0, ($sp)
# Load top off stack into $t1 and decrement the stack
lw $t1, ($sp)
addi $sp, $sp, 4
# Store word into variable with a frame pointer offset of -4
sw $t1, -4($fp)
# Load number
li $t0, 4
add $sp, $sp, -4
sw $t0, ($sp)
# Unary minus - set number at top of stack to a negative number
lw $t0, ($sp)
sub $t0, $zero, $t0
sw $t0, ($sp)
# Load top off stack into $t1 and decrement the stack
lw $t1, ($sp)
addi $sp, $sp, 4
# Store word into variable with a frame pointer offset of -8
sw $t1, -8($fp)
# Begin function call to func
# Save return address
addi $sp, $sp, -4
sw $ra, 0($sp)
# Load variable x into $t0, and put it on the stack at the end
lw $t0, -8($fp)
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
# Expression wasn't null!
# Load variable n into $t0, and put it on the stack at the end
lw $t0, 0($fp)
add $sp, $sp, -4
sw $t0, ($sp)

lw $v0, ($sp)
addi $sp, $sp, 4
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
