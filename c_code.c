#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_VARIABLE_COUNT 5
#define MAX_TERM_COUNT 32 //no of terms = pow(no_of_variables, 2)
int main()
{
	int variable_count;
	int term_count;
	printf("Enter no of variables  \n");
	scanf("%d", &variable_count);
	if(variable_count > MAX_VARIABLE_COUNT)
		exit(1);
	term_count = pow(variable_count, 2);
	int expression[MAX_TERM_COUNT];
	for(int count = 0; count<MAX_TERM_COUNT; count++)
		expression[count] = 0;
	int check =1;
	printf("Enter decimal equivalant of minterms and enter -1 to stop \n");
	while(check == 1)
	{
		int input_value;
		scanf("%d", &input_value);
		if(input_value <0)
			check = 0;
		else if(input_value < term_count)
			expression[input_value] = 1; //for every minterm set the array term to 1
	}
	check =1;
	printf("Enter decimal equivalant of dont care terms and enter -1 to stop \n");
	while(check == 1)
	{
		int input_value;
		scanf("%d", &input_value);
		if(input_value <0)
			check = 0;
		else if(input_value < term_count)
			expression[input_value] = 2; //for every dont care term set the array term to 2
	}

	

}