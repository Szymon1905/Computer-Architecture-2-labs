.data
control_word: .short 0 # 2 bytes enough for Control word which is 16 bit



.text
.global loadmydata, setmydata
.type loadmydata, @function
.type setmydata, @function

loadmydata:
	push %ebp
	mov %esp, %ebp
	push %esi

	mov $control_word, %esi  # new adress loaded control worda to esi register

	fstcw (%esi) #  save control word to address in memory

	mov (%esi), %ax      #copies control word to ax to print later (2 bytes, enough for short)

	pop %esi
	mov %ebp, %esp
	pop %ebp

	ret

setmydata:

	push %ebp
	mov %esp, %ebp
	push %ebx
	push %esi

	movl 8(%ebp), %ebx  # w ebx is adress of control word for FPU, 

	mov %bx, control_word   # parameter for fldcw

	mov $control_word, %esi  #adress of control word to esi

	fclex # clears flags of FPU

	fldcw (%esi)  # loads control word to FPU from address in esi

	pop %esi
	pop %ebx
	mov %ebp, %esp
	pop %ebp

	ret

