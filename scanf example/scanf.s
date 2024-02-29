
# Numbers of kernel functions.
EXIT_NR  = 1
READ_NR  = 3
WRITE_NR = 4

STDOUT = 1
STDIN = 0
EXIT_CODE_SUCCESS = 0


.data
.comm int, 4
.comm char, 1
.comm pointer, 8


liczba: .asciz "%d"
mychar: .asciz "%c"
pointerchar: .asciz "%s"
print: .asciz "\n%d%c%s\n"

# d - int
# c - char
# s - pointer


.text

.global main

main:
prologue:
push %ebp
movl %esp, %ebp
subl $80, %esp
push %edi
push %esi
push %ebx


push $int
push $liczba
call scanf
add $8, %esp

push $char
push $mychar
call scanf
add $8, %esp

push $pointer
push $pointerchar
call scanf
add $8, %esp

push $pointer
push char
push int
push $print
call printf
add $16, %esp

epilogue:
pop %ebx
pop %esi
pop %edi
leave
ret

mov $EXIT_NR, %eax
mov $EXIT_CODE_SUCCESS, %ebx 
int $0x80

# notes
# jg - Jump short if greater 
# jl - Jump short if less
# jle - Jump short if less or equal  
# jmp - jumps
# ah - register 8 bit
# asciz 


mytext: .asciz "Szymon\n"

