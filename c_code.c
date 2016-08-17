#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_VARIABLE_COUNT 5
#define MAX_TERM_COUNT 32 //no of terms = pow(no_of_variables, 2)

int expression[MAX_TERM_COUNT];
int variable_count;
int term_count;

int sort_n_eliminate(int* array, int size);

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
					sort_n_eliminate(stage2[counter2], 4);
					if(stage2[counter2][1] != -1)
						printf("( %d, %d, %d, %d )\n", stage2[counter2][0], stage2[counter2][1], stage2[counter2][2], stage2[counter2][3]);
					counter2++;
				}
			}
	int stage3[100][8];
	int counter3 =0;
	for(int i=0; i<counter2; i++)
		for(int j=i+1; j<=counter2; j++)
			if((stage2[i][0] ^ stage2[i][3]) == (stage2[j][0] ^ stage2[j][3]))
			{
				changes = (stage2[i][0] ^ stage2[i][3]);
				int changes2= stage2[i][0] ^ stage2[j][0];
				if((changes2==1|changes)||(changes2==2|changes)||(changes2==4|changes)||(changes2==8|changes)||(changes2==16|changes))
				{
					stage3[counter3][0] = stage2[i][0];
					stage3[counter3][1] = stage2[i][1];
					stage3[counter3][2] = stage2[i][2];
					stage3[counter3][3] = stage2[i][3];
					stage3[counter3][4] = stage2[j][0];
					stage3[counter3][5] = stage2[j][1];
					stage3[counter3][6] = stage2[j][2];
					stage3[counter3][7] = stage2[j][3];
					sort_n_eliminate(stage3[counter3], 8);
					if(stage3[counter3][1] != -1)
					{
						printf("(");
					    for(int x=0; x<7; x++)
							printf(" %d,", stage3[counter3][x]);
						printf(" %d )\n", stage3[counter3][7]);
					}
					counter3++;
				}
			}

	int stage4[100][16];
	int counter4 =0;
	for(int i=0; i<counter3; i++)
		for(int j=i+1; j<=counter3; j++)
			if((stage3[i][0] ^ stage3[i][3]) == (stage3[j][0] ^ stage3[j][3]))
			{
				changes = (stage3[i][0] ^ stage3[i][3]);
				int changes2= stage3[i][0] ^ stage3[j][0];
				if((changes2==1|changes)||(changes2==2|changes)||(changes2==4|changes)||(changes2==8|changes)||(changes2==16|changes))
				{
					for(int x=0; x<8; x++)
						stage4[counter4][x] = stage3[i][x];
					for(int x=8; x<16; x++)
						stage4[counter4][x+8] = stage3[i][x];
					sort_n_eliminate(stage4[counter4], 16);
					if(stage4[counter4][1] != -1)
					{
						printf("(");
					    for(int x=0; x<15; x++)
							printf(" %d,", stage3[counter3][x]);
						printf(" %d )\n", stage3[counter3][15]);
					}
					counter4++;
				}
			}

}


int sort_n_eliminate(int* array, int size)
{
	int temp;
	int eliminate = 0;
	for(int i=0; i<size-1; i++)
		for(int j=i+1; j<size; j++)
		{
			if(array[i]>array[j])
			{
				temp = array[i];
				array[i] = array[j];
				array[j] = temp;
			}
			else if(array[i]==array[j])
				eliminate=1;
		}
	if(eliminate==1)
		for(int i=0; i<size; i++)
			array[i] = -1;
}