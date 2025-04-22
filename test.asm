.data
_newline_char: .asciiz "
"
_bool_true: .asciiz "true"
_bool_false: .asciiz "false"
# Will get filled in when we add variables

.text
# All the labels for functions, including main: globl makes a label accessible across the entire program
globl _main
_main:
# Now, all the statements that are part of main...
li $t0 1173
add $sp, $sp, -4
sw $t0, ($sp)
# Load value from the stack and print it, with a newline
lw $a0, ($sp)
addiu $sp, $sp, -4
li $v0, 4
syscall
li $a0, _newline_char
li $v0, 4
syscall
