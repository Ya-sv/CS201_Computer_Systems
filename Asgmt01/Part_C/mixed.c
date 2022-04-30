/* Assignment 1 part C
 * PUT YOUR NAME AND ANSWERS HERE
 * Explain the output of the following
 * values: 20, -20, 200, -200
 * Then fix the function to work correctly.
 * NOTE: ONLY change the function.
 * And don't change the types.
 * Name: Ya Zou
 * It will work fine for positives numbers(20,200) and 0, 
 because the variable b is unsigned integer data type and unsigned integerâ Who's range is from [0 to 4294967295], 
 variable a is integer data type which has a range from [-2,147,483,648 to 2,147,483,647 ], 
 because the data type is not matched that is why it only works for positive numbers and 0.
 I think there are two solutions for this program, we can change variable b to integer or signed integer data type,
 but the requirement is that we can't change the data type , so we can use type casting to achieve this. 
 For example, ( if (a <(int) b), if ((signed)a < (signed)b)
 */

#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
#include <stdlib.h>

void compare(int a)
{
	/* Change this function so it works correctly
	 * test it with both positive, negative and zero
	 * values. You don't need to worry about overflow.
	 */

	 // an unsigned is an unsigned int type
	unsigned b = 100;
	
	if (a >(int)b)
	{
		printf("a (%i) > b (%d)\n", a, b);
	}
	else
	{
		printf("a (%i) <= b (%d)\n", a, b);
	}
}



int main()
{
	int num = 0;
	printf("Enter an integer: ");
	scanf("%d", &num);
	compare(num);

	return 0;
}
