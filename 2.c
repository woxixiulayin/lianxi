#include <stdio.h>

int rat(int n)
{
	if(n < 3) return 1;
	else return rat(n -1) + rat(n - 2);

}
int main()
{
	int n = 0;
	printf("输入月数:");
	scanf("%d", &n);
	printf("兔子数目是%d\n", rat(n));
}
