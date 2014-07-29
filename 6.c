#include <stdio.h>
#include <math.h>

int main()
{
	int a[4][4] = {0};

	int i,j;
	
	for(i = 0;i < 4;i++)
	{
		for(j =0;j<4;j++)
		{
			a[i][j] = rand()%100;
			printf("%-4d",a[i][j]);
		}
		printf("\n");
	}
	
printf("\n");
	for(j = 3;j>=0 ;j--)
	{
		for(i = 0;i<4;i++)	
		{
			printf("%-4d",a[i][j]);
		}
		printf("\n");
	}
	return 0;
}
