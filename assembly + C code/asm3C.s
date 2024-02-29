.data
.globl myvar # symbol marked after .globl has global 
.align 4

myvar: .int 7

#Directive .align Assembler is used to align data or code to a specific
#memory granulation. The granulation determines,
#at what position in memory the data should be located.
