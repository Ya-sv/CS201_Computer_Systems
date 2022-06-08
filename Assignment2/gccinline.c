/*  assignment 2
 *  PUT YOUR NAME HERE
 *  Name: Ya Zou
 * 
 */ 

#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
#include <math.h>

/* Part B: 10 points
 * See instructions on how to do this part.
 * See the web site:
 *  http://www.ibiblio.org/gferg/ldp/GCC-Inline-Assembly-HOWTO.html#s4
 * for information on how to write gcc inline 
 * assembly.
 */
int regular_pay_asm(int payrate, int hours)
{
	// remember to put any register names
	// you are directly using in the
	// clobber list.
	// gpay - %0  hours - %1  payrate - %2
	int gpay=0;
    asm("	cmp $0, %1\n" 	// Compare hours with 0, hours can't be negative
	"	jl Error\n"	// If hours less than 40 jump to Error
	"	cmp $40,%1\n"
	"	jge doThis\n"
	"	imul %2,%1\n"
	"	mov %1,%0\n"
	"	jmp Done \n"
	"Error:\n"
        "	mov $-1,%0\n"
	"	jmp Done \n"
	"doThis:\n"
	"	mov $40,%1\n"
	"	imul %2,%1\n"
	"	mov %1,%0\n"
	"Done:\n"
    : "=r"(gpay) /* output */
    : "r"(hours), "r"(payrate)/* input */
    :             /* clobbered register */
    );
	
	return gpay;
}


int regular_pay_c(int pay_rate, int hours)
{
   int pay = 0;	
   if (hours>= 0 && hours<= 40)
   { 
	pay = hours * pay_rate;
   } 
   else if (hours > 40 )
   {
    	int hours = 40;
	pay = hours * pay_rate;
   }
   else
   {
	printf("opps,something went wrong!Please check your input information");
	return -1;
   }	
	return pay;

}

int main()
{
   int pay_rate = 15;
   int hours = 30;
   
   printf("enter pay rate: ");
   scanf("%d",&pay_rate);
   printf("enter hours: ");
   scanf("%d",&hours);
   
   int rpay_c = regular_pay_c(pay_rate, hours);
   int rpay_asm = regular_pay_asm(pay_rate, hours);
   printf("regular pay (C) is: %d \n",rpay_c);
   printf("regular pay (asm) is: %d \n", rpay_asm);
   
   return 0;
}
