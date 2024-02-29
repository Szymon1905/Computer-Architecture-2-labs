# Numbers of kernel functions.
EXIT_NR  = 1
EXIT_CODE_SUCCESS = 0

.data
myvalue: .float 0e1
zero: .float 0e0
three: .float 0e3
.text

.global main
main:
fld myvalue
fstsw %ax
fdiv zero
fstsw %ax

finit

fld myvalue
fstsw %ax
fdiv three
fstsw %ax


mov $EXIT_NR, %eax
mov $EXIT_CODE_SUCCESS, %ebx 
int $0x80

