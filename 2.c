#include <stdio.h>

int rat(int n)
{
	if(n < 3) return 1;
	else return rat(n -1) + rat(n - 2);

}
int main()
{
	int n = 0;
	int a1=1;
	int i =0;
	int a2 = 1;
	int tmp;
	for(i = 0;i<20;i++)
	{
if(i>2)	
{
tmp = a1;
a1 = a1+a2;
a2 = tmp;
printf("%d\n",a1);
}
else printf("1\n");
	

	}

	printf("输入月数:");
	scanf("%d", &n);
	printf("兔子数目是%d\n", rat(n));
}
