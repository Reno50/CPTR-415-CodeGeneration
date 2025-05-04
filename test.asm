.data
_newline_char: .asciiz "\n"
_bool_true: .asciiz "true"
_bool_false: .asciiz "false"
# Will get filled in when we add variables

.text
# Emit the main function code from program
.globl main
main:
# Now, all the statements that are part of main...
# Store the old frame pointer and the return address onto the stack - then, set the new frame pointer 
# To access these, do 4($fp) and 8($fp)
sw $ra, -4($sp)
sw $fp, -8($sp)
addi $fp, $sp, -8
addi $sp, $sp, -8
# Allocating space for y, which requires 4 bytes, and setting it to 0
add $sp, $sp, -4
li $t0, 0
sw $t0, ($sp)
# Allocating space for x, which requires 4 bytes, and setting it to 0
add $sp, $sp, -4
li $t0, 0
sw $t0, ($sp)
# Load number
li $t0, 1
add $sp, $sp, -4
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
# Load top off stack into $t1 and decrement the stack
lw $t1, ($sp)
addi $sp, $sp, 4
# Store word into variable with a frame pointer offset of -8
sw $t1, -8($fp)
# Beginning binary operator code
# Load variable y into $t0, and put it on the stack at the end
lw $t0, -4($fp)
add $sp, $sp, -4
sw $t0, ($sp)

# Load variable x into $t0, and put it on the stack at the end
lw $t0, -8($fp)
add $sp, $sp, -4
sw $t0, ($sp)

# Now perform the operation and store the result in the stack
# Pop left operand off
# Load top off stack into $t0 and decrement the stack
lw $t0, ($sp)
addi $sp, $sp, 4
# Pop right operand off
# Load top off stack into $t1 and decrement the stack
lw $t1, ($sp)
addi $sp, $sp, 4
# Perform addition into t2
add $t2, $t0, $t1
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
