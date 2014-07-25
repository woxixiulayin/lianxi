#include <stdio.h>

int main()
{
	int i,j,n, q1,q2,all;
	for(n=1; n<=100000;n++)
	{	
		q1 = q2 = all = 1;
		for(i = 2; i < n;i++)
		{
			if(n%i !=0) continue;
			q1 = i;
			q2 = n / q1;
			if(q1 > q2) break;
			else if(q1 == q2) all += q1;
			else  all += q1 + q2;
		}
 	 if(all == n) printf("%-3d\n", n);
	}
return 0;	
}
