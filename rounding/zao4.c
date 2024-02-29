#include <stdio.h>


extern short loadmydata();
extern void setdata(short controlword);

extern double rounding();
short controlword;
double myvar;


int main (){


printf("wynik faktyczny = 3.5\n");

controlword = loadmydata();
printf("CW: %x\n", controlword);
myvar = rounding();
printf("rounding to nearest, if equal, round to the nearest even integer : %0.2f\n", myvar);

	
controlword = controlword | 3072; // OR with 0000 1100 0000 0000 
// OR changes bits nr 10 and 11 to 11

setdata(controlword);


controlword = loadmydata();
printf("CW: %x\n", controlword);	
myvar = rounding();
printf("after change (Round by truncation) : %0.2f\n", myvar);

controlword = controlword & 62463;  
// AND changes bits nr 10 i 11 to 00

controlword = controlword | 1024;
// OR changes bits nr 10 i 11 to 01

setdata(controlword);


controlword = loadmydata();
printf("ControlWord: %x\n", controlword);
myvar = rounding();
printf("After change  (rounding to minus infinity) : %0.2f\n", myvar);

controlword = controlword & 62463;  
// AND zmieni bits nr 10 i 11 to 00

controlword = controlword | 2048;
// OR changes bits nr 10 i 11 to 10

setdata(controlword);


controlword = loadmydata();
printf("CW: %x\n", controlword);	
myvar = rounding();
printf("After change  (rounding to plus infinity) : %0.2f\n", myvar);




return 0;
}
