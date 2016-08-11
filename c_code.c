#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_VARIABLE_COUNT 5
#define MAX_TERM_COUNT 32 //no of terms = pow(no_of_variables, 2)

int expression[MAX_TERM_COUNT];
int variable_count;
int term_count;

int main()
{
	printf("Enter no of variables  \n");
	scanf("%d", &variable_count);
	if(variable_count > MAX_VARIABLE_COUNT)
		exit(1);
	term_count = pow(variable_count, 2);
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
	int changes;
	int stage1[100][2];
	int counter1 =0;
	for(int i=0; i<term_count-1; i++)
		for(int j=i+1; j<term_count; j++)
		{
			if((expression[i] > 0) && (expression[j] > 0))
			{
				changes = i ^ j;
				if((changes==1)||(changes==2)||(changes==4)||(changes==8)||(changes==16))
				{
					stage1[counter1][0] = i;
					stage1[counter1][1] = j;
					counter1++;
					printf("( %d , %d )\n", i, j);
				}
			}
		}
	int stage2[100][4];
	int counter2 =0;
	for(int i=0; i<counter1; i++)
		for(int j=i+1; j<=counter1; j++)
			if((stage1[i][0] ^ stage1[i][1]) == (stage1[j][0] ^ stage1[j][1]))
			{
				changes = (stage1[i][0] ^ stage1[i][1]);
				int changes2= stage1[i][0] ^ stage1[j][0];
				if((changes2==1|changes)||(changes2==2|changes)||(changes2==4|changes)||(changes2==8|changes)||(changes2==16|changes))
				{
					stage2[counter2][0] = stage1[i][0];
					stage2[counter2][1] = stage1[i][1];
					stage2[counter2][2] = stage1[j][0];
					stage2[counter2][3] = stage1[j][1];
					printf("( %d, %d, %d, %d )\n", stage2[counter2][0], stage2[counter2][1], stage2[counter2][2], stage2[counter2][3]);
				}
			}

}