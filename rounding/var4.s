.data
myvar: .double 3.5

.text
.global roundfunc
.type roundfunc, @function

roundfunc:
push %ebp
mov %esp, %ebp

fldl myvar # puts fpu on stack

frndint  #round to int

mov %ebp, %esp
pop %ebp

ret
