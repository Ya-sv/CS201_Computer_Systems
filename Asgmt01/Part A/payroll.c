#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define SIZE 100

typedef struct
{
	char last_name[SIZE];
	double pay_rate;
}Employee;

// Print name and pay rate
void printPayroll(Employee list[], int count)
{
	 printf("*** PAYROLL ***\n");
	 for (int i = 0; i < count; i++)
	 {
		printf("Last Name: %s\n", list[i].last_name);
		printf("Pay Rate: %g\n", list[i].pay_rate);
	 }
}



int createPayroll(Employee list[], int count)
{
	printf("how many employees?\n");
	scanf("%i", &count);

	for (int i = 0; i < count; i++)
	{
		char tname[SIZE];
		printf("For employee%i\n", i + 1);
		printf("last name? ");
		scanf("%s", &list[i].last_name);
		printf("pay rate?");
		scanf("%lf", &list[i].pay_rate);
	}
	return count;
}
	 


int main()
{
	Employee list[SIZE];
	int count = 0;
	count = createPayroll(list, count);
	printPayroll(list, count);
	return 0;
}
