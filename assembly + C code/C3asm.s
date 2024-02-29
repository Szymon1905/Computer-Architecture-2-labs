SYSEXIT		= 1
EXIT_SUCCESS	= 0
.text

# format for printf
format: .string "%d\n"

.global main
main:

# ekwiwalent -> printf(" %d\n", var_c);
push myvar
push $format
call printf
add $8, %esp  # moves stack for beginning after printf  , 4 bytes per var 4+4=8

decl myvar # l-sufix for 32 bit values

# equivalet-> printf("%d\n", var_c);
push myvar
push $format
call printf
add $8, %esp


