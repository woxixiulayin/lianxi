#include <stdio.h>

int main()
{
	int a[4][5] = {0};
	int i,j;
	int sum, avr;
	sum = avr = 0;

	printf("请输入数据：\n");
	for(i=0;i<4;i++)
		{
			scanf("%d %d %d %d",&a[i][0],&a[i][1],&a[i][2],&a[i][3]);
			sum = a[i][0] +a[i][1]+a[i][2]+a[i][3];
			a[i][4]= sum / 4;
		}
	for(j = 0;j<5;j++)
	{
		a[3][j] = (a[0][j]+a[1][j]+a[2][j]) / 3;
	}
	
	for(i =0;i<4;i++)
	{
		for(j = 0;j<5;j++) 	printf("%-4d", a[i][j]);
		printf("\n");
	}

	return 0;

}
