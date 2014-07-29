#include <stdio.h>

int main()
{
	int a[10][10] = {0};
	int i,j;
	
	for(i =0; i<10 ;i++)
		{
		for(j = 0;j<i;j++) 
		{
		a[i][j] = a[i-1][j-1] +a[i-1][j];
		printf("%-4d",a[i][j]);
		}
		a[i][j] = 1;

		printf("%-4d\n",a[i][j]);
		}
		
}

